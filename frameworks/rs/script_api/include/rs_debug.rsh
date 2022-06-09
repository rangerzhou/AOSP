/*
 * Copyright (C) 2016 The Android Open Source Project
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

// Don't edit this file!  It is auto-generated by frameworks/rs/api/generate.sh.

/*
 * rs_debug.rsh: Debugging Functions
 *
 * The functions below are intended to be used during application developement.
 * They should not be used in shipping applications.
 */

#ifndef RENDERSCRIPT_RS_DEBUG_RSH
#define RENDERSCRIPT_RS_DEBUG_RSH

#define RS_DEBUG(a) rsDebug(#a, a)
#define RS_DEBUG_MARKER rsDebug(__FILE__, __LINE__)

/*
 * rsDebug: Log a message and values
 *
 * This function prints a message to the standard log, followed by the provided values.
 *
 * This function is intended for debugging only and should not be used in shipping
 * applications.
 */
extern void __attribute__((overloadable))
    rsDebug(const char* message, double a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, int a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, uint a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, long a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, ulong a);

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, int2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, int3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, int4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uint2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uint3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uint4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, long2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, long3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, long4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ulong2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ulong3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ulong4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 23))
extern void __attribute__((overloadable))
    rsDebug(const char* message, double2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 23))
extern void __attribute__((overloadable))
    rsDebug(const char* message, double3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 23))
extern void __attribute__((overloadable))
    rsDebug(const char* message, double4 a);
#endif

extern void __attribute__((overloadable))
    rsDebug(const char* message, float a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, float2 a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, float3 a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, float4 a);

#if (defined(RS_VERSION) && (RS_VERSION >= 24))
extern void __attribute__((overloadable))
    rsDebug(const char* message, half a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 24))
extern void __attribute__((overloadable))
    rsDebug(const char* message, half2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 24))
extern void __attribute__((overloadable))
    rsDebug(const char* message, half3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 24))
extern void __attribute__((overloadable))
    rsDebug(const char* message, half4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, char a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, char2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, char3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, char4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uchar a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uchar2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uchar3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, uchar4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, short a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, short2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, short3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, short4 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ushort a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ushort2 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ushort3 a);
#endif

#if (defined(RS_VERSION) && (RS_VERSION >= 17))
extern void __attribute__((overloadable))
    rsDebug(const char* message, ushort4 a);
#endif

extern void __attribute__((overloadable))
    rsDebug(const char* message, float a, float b);

extern void __attribute__((overloadable))
    rsDebug(const char* message, float a, float b, float c);

extern void __attribute__((overloadable))
    rsDebug(const char* message, float a, float b, float c, float d);

extern void __attribute__((overloadable))
    rsDebug(const char* message, long long a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, unsigned long long a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, const void* a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, const rs_matrix4x4* a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, const rs_matrix3x3* a);

extern void __attribute__((overloadable))
    rsDebug(const char* message, const rs_matrix2x2* a);

#endif // RENDERSCRIPT_RS_DEBUG_RSH
