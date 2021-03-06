/*
 * Copyright (C) 2015 The Android Open Source Project
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

#pragma once

#include "AudioPolicyConfig.h"

namespace android {

status_t deserializeAudioPolicyFile(const char *fileName, AudioPolicyConfig *config);
// In VTS mode all vendor extensions are ignored. This is done because
// VTS tests are built using AOSP code and thus can not use vendor overlays
// of system libraries.
status_t deserializeAudioPolicyFileForVts(const char *fileName, AudioPolicyConfig *config);

} // namespace android
