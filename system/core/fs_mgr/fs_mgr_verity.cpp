/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/strings.h>
#include <android-base/unique_fd.h>
#include <crypto_utils/android_pubkey.h>
#include <cutils/properties.h>
#include <fs_mgr/file_wait.h>
#include <libdm/dm.h>
#include <logwrap/logwrap.h>
#include <openssl/obj_mac.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>

#include "fec/io.h"

#include "fs_mgr.h"
#include "fs_mgr_dm_linear.h"
#include "fs_mgr_priv.h"

// Realistically, this file should be part of the android::fs_mgr namespace;
using namespace android::fs_mgr;

#define VERITY_TABLE_RSA_KEY "/verity_key"
#define VERITY_TABLE_HASH_IDX 8
#define VERITY_TABLE_SALT_IDX 9

#define VERITY_TABLE_OPT_RESTART "restart_on_corruption"
#define VERITY_TABLE_OPT_LOGGING "ignore_corruption"
#define VERITY_TABLE_OPT_IGNZERO "ignore_zero_blocks"

#define VERITY_TABLE_OPT_FEC_FORMAT \
    "use_fec_from_device %s fec_start %" PRIu64 " fec_blocks %" PRIu64 \
    " fec_roots %u " VERITY_TABLE_OPT_IGNZERO
#define VERITY_TABLE_OPT_FEC_ARGS 9

#define METADATA_MAGIC 0x01564c54
#define METADATA_TAG_MAX_LENGTH 63
#define METADATA_EOD "eod"

#define VERITY_LASTSIG_TAG "verity_lastsig"

#define VERITY_STATE_TAG "verity_state"
#define VERITY_STATE_HEADER 0x83c0ae9d
#define VERITY_STATE_VERSION 1

#define VERITY_KMSG_RESTART "dm-verity device corrupted"
#define VERITY_KMSG_BUFSIZE 1024

#define READ_BUF_SIZE 4096

#define __STRINGIFY(x) #x
#define STRINGIFY(x) __STRINGIFY(x)

struct verity_state {
    uint32_t header;
    uint32_t version;
    int32_t mode;
};

extern struct fs_info info;

static RSA *load_key(const char *path)
{
    uint8_t key_data[ANDROID_PUBKEY_ENCODED_SIZE];

    auto f = std::unique_ptr<FILE, decltype(&fclose)>{fopen(path, "re"), fclose};
    if (!f) {
        LERROR << "Can't open " << path;
        return nullptr;
    }

    if (!fread(key_data, sizeof(key_data), 1, f.get())) {
        LERROR << "Could not read key!";
        return nullptr;
    }

    RSA* key = nullptr;
    if (!android_pubkey_decode(key_data, sizeof(key_data), &key)) {
        LERROR << "Could not parse key!";
        return nullptr;
    }

    return key;
}

static int verify_table(const uint8_t *signature, size_t signature_size,
        const char *table, uint32_t table_length)
{
    RSA *key;
    uint8_t hash_buf[SHA256_DIGEST_LENGTH];
    int retval = -1;

    // Hash the table
    SHA256((uint8_t*)table, table_length, hash_buf);

    // Now get the public key from the keyfile
    key = load_key(VERITY_TABLE_RSA_KEY);
    if (!key) {
        LERROR << "Couldn't load verity keys";
        goto out;
    }

    // verify the result
    if (!RSA_verify(NID_sha256, hash_buf, sizeof(hash_buf), signature,
                    signature_size, key)) {
        LERROR << "Couldn't verify table";
        goto out;
    }

    retval = 0;

out:
    RSA_free(key);
    return retval;
}

static int verify_verity_signature(const struct fec_verity_metadata& verity)
{
    if (verify_table(verity.signature, sizeof(verity.signature),
            verity.table, verity.table_length) == 0 ||
        verify_table(verity.ecc_signature, sizeof(verity.ecc_signature),
            verity.table, verity.table_length) == 0) {
        return 0;
    }

    return -1;
}

static int invalidate_table(char *table, size_t table_length)
{
    size_t n = 0;
    size_t idx = 0;
    size_t cleared = 0;

    while (n < table_length) {
        if (table[n++] == ' ') {
            ++idx;
        }

        if (idx != VERITY_TABLE_HASH_IDX && idx != VERITY_TABLE_SALT_IDX) {
            continue;
        }

        while (n < table_length && table[n] != ' ') {
            table[n++] = '0';
        }

        if (++cleared == 2) {
            return 0;
        }
    }

    return -1;
}

struct verity_table_params {
    char *table;
    int mode;
    struct fec_ecc_metadata ecc;
    const char *ecc_dev;
};

typedef bool (*format_verity_table_func)(char *buf, const size_t bufsize,
        const struct verity_table_params *params);

static bool format_verity_table(char *buf, const size_t bufsize,
        const struct verity_table_params *params)
{
    const char *mode_flag = NULL;
    int res = -1;

    if (params->mode == VERITY_MODE_RESTART) {
        mode_flag = VERITY_TABLE_OPT_RESTART;
    } else if (params->mode == VERITY_MODE_LOGGING) {
        mode_flag = VERITY_TABLE_OPT_LOGGING;
    }

    if (params->ecc.valid) {
        if (mode_flag) {
            res = snprintf(buf, bufsize,
                    "%s %u %s " VERITY_TABLE_OPT_FEC_FORMAT,
                    params->table, 1 + VERITY_TABLE_OPT_FEC_ARGS, mode_flag, params->ecc_dev,
                    params->ecc.start / FEC_BLOCKSIZE, params->ecc.blocks, params->ecc.roots);
        } else {
            res = snprintf(buf, bufsize,
                    "%s %u " VERITY_TABLE_OPT_FEC_FORMAT,
                    params->table, VERITY_TABLE_OPT_FEC_ARGS, params->ecc_dev,
                    params->ecc.start / FEC_BLOCKSIZE, params->ecc.blocks, params->ecc.roots);
        }
    } else if (mode_flag) {
        res = snprintf(buf, bufsize, "%s 2 " VERITY_TABLE_OPT_IGNZERO " %s", params->table,
                    mode_flag);
    } else {
        res = snprintf(buf, bufsize, "%s 1 " VERITY_TABLE_OPT_IGNZERO, params->table);
    }

    if (res < 0 || (size_t)res >= bufsize) {
        LERROR << "Error building verity table; insufficient buffer size?";
        return false;
    }

    return true;
}

static bool format_legacy_verity_table(char *buf, const size_t bufsize,
        const struct verity_table_params *params)
{
    int res;

    if (params->mode == VERITY_MODE_EIO) {
        res = strlcpy(buf, params->table, bufsize);
    } else {
        res = snprintf(buf, bufsize, "%s %d", params->table, params->mode);
    }

    if (res < 0 || (size_t)res >= bufsize) {
        LERROR << "Error building verity table; insufficient buffer size?";
        return false;
    }

    return true;
}

static int load_verity_table(android::dm::DeviceMapper& dm, const std::string& name,
                             uint64_t device_size, const struct verity_table_params* params,
                             format_verity_table_func format) {
    android::dm::DmTable table;
    table.set_readonly(true);

    char buffer[DM_BUF_SIZE];
    if (!format(buffer, sizeof(buffer), params)) {
        LERROR << "Failed to format verity parameters";
        return -1;
    }

    android::dm::DmTargetVerityString target(0, device_size / 512, buffer);
    if (!table.AddTarget(std::make_unique<decltype(target)>(target))) {
        LERROR << "Failed to add verity target";
        return -1;
    }
    if (!dm.CreateDevice(name, table)) {
        LERROR << "Failed to create verity device \"" << name << "\"";
        return -1;
    }
    return 0;
}

static int read_partition(const char *path, uint64_t size)
{
    char buf[READ_BUF_SIZE];
    ssize_t size_read;
    android::base::unique_fd fd(TEMP_FAILURE_RETRY(open(path, O_RDONLY | O_CLOEXEC)));

    if (fd == -1) {
        PERROR << "Failed to open " << path;
        return -errno;
    }

    while (size) {
        size_read = TEMP_FAILURE_RETRY(read(fd, buf, READ_BUF_SIZE));
        if (size_read == -1) {
            PERROR << "Error in reading partition " << path;
            return -errno;
        }
        size -= size_read;
    }

    return 0;
}

bool fs_mgr_load_verity_state(int* mode) {
    // unless otherwise specified, use EIO mode.
    *mode = VERITY_MODE_EIO;

    // The bootloader communicates verity mode via the kernel commandline
    std::string verity_mode;
    if (!fs_mgr_get_boot_config("veritymode", &verity_mode)) {
        return false;
    }

    if (verity_mode == "enforcing") {
        *mode = VERITY_MODE_DEFAULT;
    } else if (verity_mode == "logging") {
        *mode = VERITY_MODE_LOGGING;
    }

    return true;
}

// Update the verity table using the actual block device path.
// Two cases:
// Case-1: verity table is shared for devices with different by-name prefix.
// Example:
//   verity table token:       /dev/block/bootdevice/by-name/vendor
//   blk_device-1 (non-A/B):   /dev/block/platform/soc.0/7824900.sdhci/by-name/vendor
//   blk_device-2 (A/B):       /dev/block/platform/soc.0/f9824900.sdhci/by-name/vendor_a
//
// Case-2: append A/B suffix in the verity table.
// Example:
//   verity table token: /dev/block/platform/soc.0/7824900.sdhci/by-name/vendor
//   blk_device:         /dev/block/platform/soc.0/7824900.sdhci/by-name/vendor_a
static void update_verity_table_blk_device(const std::string& blk_device, char** table,
                                           bool slot_select) {
    bool updated = false;
    std::string result, ab_suffix;
    auto tokens = android::base::Split(*table, " ");

    // If slot_select is set, it means blk_device is already updated with ab_suffix.
    if (slot_select) ab_suffix = fs_mgr_get_slot_suffix();

    for (const auto& token : tokens) {
        std::string new_token;
        if (android::base::StartsWith(token, "/dev/block/")) {
            if (token == blk_device) return;  // no need to update if they're already the same.
            std::size_t found1 = blk_device.find("by-name");
            std::size_t found2 = token.find("by-name");
            if (found1 != std::string::npos && found2 != std::string::npos &&
                blk_device.substr(found1) == token.substr(found2) + ab_suffix) {
                new_token = blk_device;
            }
        }

        if (!new_token.empty()) {
            updated = true;
            LINFO << "Verity table: updated block device from '" << token << "' to '" << new_token
                  << "'";
        } else {
            new_token = token;
        }

        if (result.empty()) {
            result = new_token;
        } else {
            result += " " + new_token;
        }
    }

    if (!updated) {
        return;
    }

    free(*table);
    *table = strdup(result.c_str());
}

// prepares the verity enabled (MF_VERIFY / MF_VERIFYATBOOT) fstab record for
// mount. The 'wait_for_verity_dev' parameter makes this function wait for the
// verity device to get created before return
int fs_mgr_setup_verity(FstabEntry* entry, bool wait_for_verity_dev) {
    int retval = FS_MGR_SETUP_VERITY_FAIL;
    int fd = -1;
    std::string verity_blk_name;
    struct fec_handle *f = NULL;
    struct fec_verity_metadata verity;
    struct verity_table_params params = { .table = NULL };

    const std::string mount_point(basename(entry->mount_point.c_str()));
    bool verified_at_boot = false;

    android::dm::DeviceMapper& dm = android::dm::DeviceMapper::Instance();

    if (fec_open(&f, entry->blk_device.c_str(), O_RDONLY, FEC_VERITY_DISABLE, FEC_DEFAULT_ROOTS) <
        0) {
        PERROR << "Failed to open '" << entry->blk_device << "'";
        return retval;
    }

    // read verity metadata
    if (fec_verity_get_metadata(f, &verity) < 0) {
        PERROR << "Failed to get verity metadata '" << entry->blk_device << "'";
        // Allow verity disabled when the device is unlocked without metadata
        if (fs_mgr_is_device_unlocked()) {
            retval = FS_MGR_SETUP_VERITY_SKIPPED;
            LWARNING << "Allow invalid metadata when the device is unlocked";
        }
        goto out;
    }

#ifdef ALLOW_ADBD_DISABLE_VERITY
    if (verity.disabled) {
        retval = FS_MGR_SETUP_VERITY_DISABLED;
        LINFO << "Attempt to cleanly disable verity - only works in USERDEBUG/ENG";
        goto out;
    }
#endif

    // read ecc metadata
    if (fec_ecc_get_metadata(f, &params.ecc) < 0) {
        params.ecc.valid = false;
    }

    params.ecc_dev = entry->blk_device.c_str();

    if (!fs_mgr_load_verity_state(&params.mode)) {
        /* if accessing or updating the state failed, switch to the default
         * safe mode. This makes sure the device won't end up in an endless
         * restart loop, and no corrupted data will be exposed to userspace
         * without a warning. */
        params.mode = VERITY_MODE_EIO;
    }

    if (!verity.table) {
        goto out;
    }

    params.table = strdup(verity.table);
    if (!params.table) {
        goto out;
    }

    // verify the signature on the table
    if (verify_verity_signature(verity) < 0) {
        // Allow signature verification error when the device is unlocked
        if (fs_mgr_is_device_unlocked()) {
            retval = FS_MGR_SETUP_VERITY_SKIPPED;
            LWARNING << "Allow signature verification error when the device is unlocked";
            goto out;
        }
        if (params.mode == VERITY_MODE_LOGGING) {
            // the user has been warned, allow mounting without dm-verity
            retval = FS_MGR_SETUP_VERITY_SKIPPED;
            goto out;
        }

        // invalidate root hash and salt to trigger device-specific recovery
        if (invalidate_table(params.table, verity.table_length) < 0) {
            goto out;
        }
    }

    LINFO << "Enabling dm-verity for " << mount_point.c_str()
          << " (mode " << params.mode << ")";

    // Update the verity params using the actual block device path
    update_verity_table_blk_device(entry->blk_device, &params.table,
                                   entry->fs_mgr_flags.slot_select);

    // load the verity mapping table
    if (load_verity_table(dm, mount_point, verity.data_size, &params, format_verity_table) == 0) {
        goto loaded;
    }

    if (params.ecc.valid) {
        // kernel may not support error correction, try without
        LINFO << "Disabling error correction for " << mount_point.c_str();
        params.ecc.valid = false;

        if (load_verity_table(dm, mount_point, verity.data_size, &params, format_verity_table) == 0) {
            goto loaded;
        }
    }

    // try the legacy format for backwards compatibility
    if (load_verity_table(dm, mount_point, verity.data_size, &params, format_legacy_verity_table) ==
        0) {
        goto loaded;
    }

    if (params.mode != VERITY_MODE_EIO) {
        // as a last resort, EIO mode should always be supported
        LINFO << "Falling back to EIO mode for " << mount_point.c_str();
        params.mode = VERITY_MODE_EIO;

        if (load_verity_table(dm, mount_point, verity.data_size, &params,
                              format_legacy_verity_table) == 0) {
            goto loaded;
        }
    }

    LERROR << "Failed to load verity table for " << mount_point.c_str();
    goto out;

loaded:
    if (!dm.GetDmDevicePathByName(mount_point, &verity_blk_name)) {
        LERROR << "Couldn't get verity device number!";
        goto out;
    }

    // mark the underlying block device as read-only
    fs_mgr_set_blk_ro(entry->blk_device);

    // Verify the entire partition in one go
    // If there is an error, allow it to mount as a normal verity partition.
    if (entry->fs_mgr_flags.verify_at_boot) {
        LINFO << "Verifying partition " << entry->blk_device << " at boot";
        int err = read_partition(verity_blk_name.c_str(), verity.data_size);
        if (!err) {
            LINFO << "Verified verity partition " << entry->blk_device << " at boot";
            verified_at_boot = true;
        }
    }

    // assign the new verity block device as the block device
    if (!verified_at_boot) {
        entry->blk_device = verity_blk_name;
    } else if (!dm.DeleteDevice(mount_point)) {
        LERROR << "Failed to remove verity device " << mount_point.c_str();
        goto out;
    }

    // make sure we've set everything up properly
    if (wait_for_verity_dev && !WaitForFile(entry->blk_device, 1s)) {
        goto out;
    }

    retval = FS_MGR_SETUP_VERITY_SUCCESS;

out:
    if (fd != -1) {
        close(fd);
    }

    fec_close(f);
    free(params.table);

    return retval;
}

bool fs_mgr_teardown_verity(FstabEntry* entry) {
    const std::string mount_point(basename(entry->mount_point.c_str()));
    if (!android::fs_mgr::UnmapDevice(mount_point)) {
        return false;
    }
    LINFO << "Unmapped verity device " << mount_point;
    return true;
}
