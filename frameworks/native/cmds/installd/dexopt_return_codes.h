/*
 * Copyright (C) 2018 The Android Open Source Project
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

namespace android {
namespace installd {

// Constants for exit codes that installd code emits. These are failure situations before calling
// any tools, e.g., in validation, and must not overlap with the exit codes of tools, so they
// can be distinguished.
enum DexoptReturnCodes : int {
    kSetGid = 64,
    kSetUid = 65,
    kCapSet = 66,
    kFlock = 67,
    kProfmanExec = 68,
    kSetSchedPolicy = 70,
    kSetPriority = 71,
    kDex2oatExec = 72,
    kInstructionSetLength = 73,
    kHashValidatePath = 74,
    kHashOpenPath = 75,
    kHashReadDex = 76,
    kHashWrite = 77,
};

inline const char* get_installd_return_code_name(DexoptReturnCodes code) {
    switch (code) {
        case kSetGid:
            return "setgid";
        case kSetUid:
            return "setuid";
        case kCapSet:
            return "capset";
        case kFlock:
            return "flock";
        case kProfmanExec:
            return "exec(profman)";
        case kSetSchedPolicy:
            return "setschedpolicy";
        case kSetPriority:
            return "setpriority";
        case kDex2oatExec:
            return "exec(dex2oat)";
        case kInstructionSetLength:
            return "instruction-set-length";
        case kHashValidatePath:
            return "hash(validate-path)";
        case kHashOpenPath:
            return "hash(open-path)";
        case kHashReadDex:
            return "hash(read-dex)";
        case kHashWrite:
            return "hash(write)";
    }
    return nullptr;
}

inline const char* get_dex2oat_return_code_name(int code) {
    if (code == 0) {
        return "dex2oat success";
    } else {
        return "dex2oat error";
    }
}

// Get some slightly descriptive string for the return code.
inline const char* get_return_code_name(int code) {
    const char* value = get_installd_return_code_name(static_cast<DexoptReturnCodes>(code));
    if (value != nullptr) {
        return value;
    }
    value = get_dex2oat_return_code_name(code);
    return value;
}

}  // namespace installd
}  // namespace android
