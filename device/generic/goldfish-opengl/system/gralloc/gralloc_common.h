/*
* Copyright 2019 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __GRALLOC_COMMON_H__
#define __GRALLOC_COMMON_H__

// Tell the emulator which gralloc formats
// need special handling.
enum EmulatorFrameworkFormat {
    FRAMEWORK_FORMAT_GL_COMPATIBLE = 0,
    FRAMEWORK_FORMAT_YV12 = 1,
    FRAMEWORK_FORMAT_YUV_420_888 = 2,              // (Y+)(U+)(V+)
};

#ifndef GL_RGBA16F
#define GL_RGBA16F                        0x881A
#endif // GL_RGBA16F

#ifndef GL_HALF_FLOAT
#define GL_HALF_FLOAT                     0x140B
#endif // GL_HALF_FLOAT

#ifndef GL_RGB10_A2
#define GL_RGB10_A2                       0x8059
#endif // GL_RGB10_A2

#ifndef GL_UNSIGNED_INT_2_10_10_10_REV
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#endif // GL_UNSIGNED_INT_2_10_10_10_REV

// defined in hardware/interfaces/graphics/common/1.0/types.hal
#ifndef GOLDFISH_GRALLOC_USAGE_GPU_DATA_BUFFER
#define GOLDFISH_GRALLOC_USAGE_GPU_DATA_BUFFER (1ULL << 24)
#endif // GOLDFISH_GRALLOC_USAGE_GPU_DATA_BUFFER

#endif //__GRALLOC_COMMON_H__
