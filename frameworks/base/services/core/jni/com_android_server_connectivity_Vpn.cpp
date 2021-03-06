/*
 * Copyright (C) 2011 The Android Open Source Project
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

#define LOG_NDEBUG 0

#define LOG_TAG "VpnJni"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <linux/route.h>
#include <linux/ipv6_route.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <log/log.h>
#include <android/log.h>

#include "netutils/ifc.h"

#include "jni.h"
#include <nativehelper/JNIHelp.h>

namespace android
{

static int inet4 = -1;
static int inet6 = -1;

static inline in_addr_t *as_in_addr(sockaddr *sa) {
    return &((sockaddr_in *)sa)->sin_addr.s_addr;
}

//------------------------------------------------------------------------------

#define SYSTEM_ERROR (-1)
#define BAD_ARGUMENT (-2)

static int create_interface(int mtu)
{
    int tun = open("/dev/tun", O_RDWR | O_NONBLOCK | O_CLOEXEC);

    ifreq ifr4;
    memset(&ifr4, 0, sizeof(ifr4));

    // Allocate interface.
    ifr4.ifr_flags = IFF_TUN | IFF_NO_PI;
    if (ioctl(tun, TUNSETIFF, &ifr4)) {
        ALOGE("Cannot allocate TUN: %s", strerror(errno));
        goto error;
    }

    // Activate interface.
    ifr4.ifr_flags = IFF_UP;
    if (ioctl(inet4, SIOCSIFFLAGS, &ifr4)) {
        ALOGE("Cannot activate %s: %s", ifr4.ifr_name, strerror(errno));
        goto error;
    }

    // Set MTU if it is specified.
    ifr4.ifr_mtu = mtu;
    if (mtu > 0 && ioctl(inet4, SIOCSIFMTU, &ifr4)) {
        ALOGE("Cannot set MTU on %s: %s", ifr4.ifr_name, strerror(errno));
        goto error;
    }

    return tun;

error:
    close(tun);
    return SYSTEM_ERROR;
}

static int get_interface_name(char *name, int tun)
{
    ifreq ifr4;
    if (ioctl(tun, TUNGETIFF, &ifr4)) {
        ALOGE("Cannot get interface name: %s", strerror(errno));
        return SYSTEM_ERROR;
    }
    strncpy(name, ifr4.ifr_name, IFNAMSIZ);
    return 0;
}

static int get_interface_index(const char *name)
{
    ifreq ifr4;
    strncpy(ifr4.ifr_name, name, IFNAMSIZ);
    if (ioctl(inet4, SIOGIFINDEX, &ifr4)) {
        ALOGE("Cannot get index of %s: %s", name, strerror(errno));
        return SYSTEM_ERROR;
    }
    return ifr4.ifr_ifindex;
}

static int set_addresses(const char *name, const char *addresses)
{
    int index = get_interface_index(name);
    if (index < 0) {
        return index;
    }

    ifreq ifr4;
    memset(&ifr4, 0, sizeof(ifr4));
    strncpy(ifr4.ifr_name, name, IFNAMSIZ);
    ifr4.ifr_addr.sa_family = AF_INET;
    ifr4.ifr_netmask.sa_family = AF_INET;

    in6_ifreq ifr6;
    memset(&ifr6, 0, sizeof(ifr6));
    ifr6.ifr6_ifindex = index;

    char address[65];
    int prefix;
    int chars;
    int count = 0;

    while (sscanf(addresses, " %64[^/]/%d %n", address, &prefix, &chars) == 2) {
        addresses += chars;

        if (strchr(address, ':')) {
            // Add an IPv6 address.
            if (inet_pton(AF_INET6, address, &ifr6.ifr6_addr) != 1 ||
                    prefix < 0 || prefix > 128) {
                count = BAD_ARGUMENT;
                break;
            }

            ifr6.ifr6_prefixlen = prefix;
            if (ioctl(inet6, SIOCSIFADDR, &ifr6)) {
                count = (errno == EINVAL) ? BAD_ARGUMENT : SYSTEM_ERROR;
                break;
            }
        } else {
            // Add an IPv4 address.
            if (inet_pton(AF_INET, address, as_in_addr(&ifr4.ifr_addr)) != 1 ||
                    prefix < 0 || prefix > 32) {
                count = BAD_ARGUMENT;
                break;
            }

            if (count) {
                snprintf(ifr4.ifr_name, sizeof(ifr4.ifr_name), "%s:%d", name, count);
            }
            if (ioctl(inet4, SIOCSIFADDR, &ifr4)) {
                count = (errno == EINVAL) ? BAD_ARGUMENT : SYSTEM_ERROR;
                break;
            }

            in_addr_t mask = prefix ? (~0 << (32 - prefix)) : 0;
            *as_in_addr(&ifr4.ifr_netmask) = htonl(mask);
            if (ioctl(inet4, SIOCSIFNETMASK, &ifr4)) {
                count = (errno == EINVAL) ? BAD_ARGUMENT : SYSTEM_ERROR;
                break;
            }
        }
        ALOGD("Address added on %s: %s/%d", name, address, prefix);
        ++count;
    }

    if (count == BAD_ARGUMENT) {
        ALOGE("Invalid address: %s/%d", address, prefix);
    } else if (count == SYSTEM_ERROR) {
        ALOGE("Cannot add address: %s/%d: %s", address, prefix, strerror(errno));
    } else if (*addresses) {
        ALOGE("Invalid address: %s", addresses);
        count = BAD_ARGUMENT;
    }

    return count;
}

static int reset_interface(const char *name)
{
    ifreq ifr4;
    strncpy(ifr4.ifr_name, name, IFNAMSIZ);
    ifr4.ifr_flags = 0;

    if (ioctl(inet4, SIOCSIFFLAGS, &ifr4) && errno != ENODEV) {
        ALOGE("Cannot reset %s: %s", name, strerror(errno));
        return SYSTEM_ERROR;
    }
    return 0;
}

static int check_interface(const char *name)
{
    ifreq ifr4;
    strncpy(ifr4.ifr_name, name, IFNAMSIZ);
    ifr4.ifr_flags = 0;

    if (ioctl(inet4, SIOCGIFFLAGS, &ifr4) && errno != ENODEV) {
        ALOGE("Cannot check %s: %s", name, strerror(errno));
    }
    return ifr4.ifr_flags;
}

static bool modifyAddress(JNIEnv *env, jobject thiz, jstring jName, jstring jAddress,
                          jint jPrefixLength, bool add)
{
    int error = SYSTEM_ERROR;
    const char *name = jName ? env->GetStringUTFChars(jName, NULL) : NULL;
    const char *address = jAddress ? env->GetStringUTFChars(jAddress, NULL) : NULL;

    if (!name) {
        jniThrowNullPointerException(env, "name");
    } else if (!address) {
        jniThrowNullPointerException(env, "address");
    } else {
        if (add) {
            if ((error = ifc_add_address(name, address, jPrefixLength)) != 0) {
                ALOGE("Cannot add address %s/%d on interface %s (%s)", address, jPrefixLength, name,
                      strerror(-error));
            }
        } else {
            if ((error = ifc_del_address(name, address, jPrefixLength)) != 0) {
                ALOGE("Cannot del address %s/%d on interface %s (%s)", address, jPrefixLength, name,
                      strerror(-error));
            }
        }
    }

    if (name) {
        env->ReleaseStringUTFChars(jName, name);
    }
    if (address) {
        env->ReleaseStringUTFChars(jAddress, address);
    }
    return !error;
}

//------------------------------------------------------------------------------

static void throwException(JNIEnv *env, int error, const char *message)
{
    if (error == SYSTEM_ERROR) {
        jniThrowException(env, "java/lang/IllegalStateException", message);
    } else {
        jniThrowException(env, "java/lang/IllegalArgumentException", message);
    }
}

static jint create(JNIEnv *env, jobject /* thiz */, jint mtu)
{
    int tun = create_interface(mtu);
    if (tun < 0) {
        throwException(env, tun, "Cannot create interface");
        return -1;
    }
    return tun;
}

static jstring getName(JNIEnv *env, jobject /* thiz */, jint tun)
{
    char name[IFNAMSIZ];
    if (get_interface_name(name, tun) < 0) {
        throwException(env, SYSTEM_ERROR, "Cannot get interface name");
        return NULL;
    }
    return env->NewStringUTF(name);
}

static jint setAddresses(JNIEnv *env, jobject /* thiz */, jstring jName,
        jstring jAddresses)
{
    const char *name = NULL;
    const char *addresses = NULL;
    int count = -1;

    name = jName ? env->GetStringUTFChars(jName, NULL) : NULL;
    if (!name) {
        jniThrowNullPointerException(env, "name");
        goto error;
    }
    addresses = jAddresses ? env->GetStringUTFChars(jAddresses, NULL) : NULL;
    if (!addresses) {
        jniThrowNullPointerException(env, "addresses");
        goto error;
    }
    count = set_addresses(name, addresses);
    if (count < 0) {
        throwException(env, count, "Cannot set address");
        count = -1;
    }

error:
    if (name) {
        env->ReleaseStringUTFChars(jName, name);
    }
    if (addresses) {
        env->ReleaseStringUTFChars(jAddresses, addresses);
    }
    return count;
}

static void reset(JNIEnv *env, jobject /* thiz */, jstring jName)
{
    const char *name = jName ? env->GetStringUTFChars(jName, NULL) : NULL;
    if (!name) {
        jniThrowNullPointerException(env, "name");
        return;
    }
    if (reset_interface(name) < 0) {
        throwException(env, SYSTEM_ERROR, "Cannot reset interface");
    }
    env->ReleaseStringUTFChars(jName, name);
}

static jint check(JNIEnv *env, jobject /* thiz */, jstring jName)
{
    const char *name = jName ? env->GetStringUTFChars(jName, NULL) : NULL;
    if (!name) {
        jniThrowNullPointerException(env, "name");
        return 0;
    }
    int flags = check_interface(name);
    env->ReleaseStringUTFChars(jName, name);
    return flags;
}

static bool addAddress(JNIEnv *env, jobject thiz, jstring jName, jstring jAddress,
                       jint jPrefixLength)
{
    return modifyAddress(env, thiz, jName, jAddress, jPrefixLength, true);
}

static bool delAddress(JNIEnv *env, jobject thiz, jstring jName, jstring jAddress,
                       jint jPrefixLength)
{
    return modifyAddress(env, thiz, jName, jAddress, jPrefixLength, false);
}

//------------------------------------------------------------------------------

static const JNINativeMethod gMethods[] = {
    {"jniCreate", "(I)I", (void *)create},
    {"jniGetName", "(I)Ljava/lang/String;", (void *)getName},
    {"jniSetAddresses", "(Ljava/lang/String;Ljava/lang/String;)I", (void *)setAddresses},
    {"jniReset", "(Ljava/lang/String;)V", (void *)reset},
    {"jniCheck", "(Ljava/lang/String;)I", (void *)check},
    {"jniAddAddress", "(Ljava/lang/String;Ljava/lang/String;I)Z", (void *)addAddress},
    {"jniDelAddress", "(Ljava/lang/String;Ljava/lang/String;I)Z", (void *)delAddress},
};

int register_android_server_connectivity_Vpn(JNIEnv *env)
{
    if (inet4 == -1) {
        inet4 = socket(AF_INET, SOCK_DGRAM, 0);
    }
    if (inet6 == -1) {
        inet6 = socket(AF_INET6, SOCK_DGRAM, 0);
    }
    return jniRegisterNativeMethods(env, "com/android/server/connectivity/Vpn",
            gMethods, NELEM(gMethods));
}

};
