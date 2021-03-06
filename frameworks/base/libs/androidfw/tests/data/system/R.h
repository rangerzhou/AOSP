/*
 * Copyright (C) 2014 The Android Open Source Project
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

#ifndef TEST_DATA_SYSTEM_R_H_
#define TEST_DATA_SYSTEM_R_H_

#include <cstdint>

namespace android {

struct R {
  struct attr {
    enum : uint32_t {
      background = 0x01010000,  // default
      foreground = 0x01010001,  // default
    };
  };

  struct style {
    enum : uint32_t {
      Theme_One = 0x01020000,  // default
    };
  };

  struct integer {
    enum : uint32_t {
      number = 0x01030000,  // sv
    };
  };

  struct string {
    enum : uint32_t {
      no = 0x01040009,
      yes = 0x01040013,
    };
  };
};

}  // namespace android

#endif  // TEST_DATA_SYSTEM_R_H_
