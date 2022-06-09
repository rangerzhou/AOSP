/*
 * Copyright 2020 The Android Open Source Project
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

#ifndef BT_STACK_FUZZ_A2DP_CODECCONFIG_HELPERS_H_
#define BT_STACK_FUZZ_A2DP_CODECCONFIG_HELPERS_H_

// NOTE: This file should not be included directly.
//       It is included by the corresponding "...Functions.h" file.

#include <fuzzer/FuzzedDataProvider.h>
#include <vector>
#include "a2dp_codec_api.h"
#include "fuzzers/a2dp/codec/a2dpCodecInfoFuzzHelpers.h"

// Keep a vector of our initialized codec_config objects
// It will be up to the caller to free this array at the end of a fuzz loop
std::vector<std::shared_ptr<A2dpCodecConfig>> a2dp_codec_config_vect;

// Function to clean up and clear our allocated objects
void cleanupA2dpCodecConfigFuzz() {
  a2dp_codec_config_vect.clear();

  // Cleanup dependencies
  cleanupA2dpCodecInfoFuzz();
}

#endif  // BT_STACK_FUZZ_A2DP_CODECCONFIG_HELPERS_H_
