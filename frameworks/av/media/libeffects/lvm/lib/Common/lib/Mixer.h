/*
 * Copyright (C) 2004-2010 NXP Software
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef __MIXER_H__
#define __MIXER_H__

#include "LVM_Types.h"

/**********************************************************************************
   INSTANCE MEMORY TYPE DEFINITION
***********************************************************************************/

typedef struct {
    LVM_FLOAT Alpha;         /* Time constant. Set by calling application. \
                                Can be changed at any time */
    LVM_FLOAT Target;        /* Target value.  Set by calling application. \
                                Can be changed at any time */
    LVM_FLOAT Current;       /* Current value.  Set by the mixer function. */
    LVM_INT16 CallbackSet;   /* Boolean.  Should be set by calling application \
                                each time the target value is updated */
    LVM_INT16 CallbackParam; /* Parameter that will be used in the calback function */
    void* pCallbackHandle;   /* Pointer to the instance of the callback function */
    void* pGeneralPurpose;   /* Pointer for general purpose usage */
    LVM_Callback pCallBack;  /* Pointer to the callback function */
} Mix_1St_Cll_FLOAT_t;
typedef struct {
    LVM_FLOAT Alpha1;
    LVM_FLOAT Target1;
    LVM_FLOAT Current1;
    LVM_INT16 CallbackSet1;
    LVM_INT16 CallbackParam1;
    void* pCallbackHandle1;
    void* pGeneralPurpose1;
    LVM_Callback pCallBack1;

    LVM_FLOAT Alpha2; /* Warning the address of this location is passed as a \
                         pointer to Mix_1St_Cll_t in some functions */
    LVM_FLOAT Target2;
    LVM_FLOAT Current2;
    LVM_INT16 CallbackSet2;
    LVM_INT16 CallbackParam2;
    void* pCallbackHandle2;
    void* pGeneralPurpose2;
    LVM_Callback pCallBack2;
} Mix_2St_Cll_FLOAT_t;

/*** General functions ************************************************************/

LVM_FLOAT LVM_Mixer_TimeConstant(LVM_UINT32 tc, LVM_UINT32 Fs, LVM_UINT16 NumChannels);

void MixSoft_1St_D32C31_WRA(Mix_1St_Cll_FLOAT_t* pInstance, const LVM_FLOAT* src, LVM_FLOAT* dst,
                            LVM_INT16 n);

void MixSoft_2St_D32C31_SAT(Mix_2St_Cll_FLOAT_t* pInstance, const LVM_FLOAT* src1,
                            const LVM_FLOAT* src2, LVM_FLOAT* dst, LVM_INT16 n);

void MixInSoft_D32C31_SAT(Mix_1St_Cll_FLOAT_t* pInstance, const LVM_FLOAT* src, LVM_FLOAT* dst,
                          LVM_INT16 n);

/**********************************************************************************
   FUNCTION PROTOTYPES (LOW LEVEL SUBFUNCTIONS)
***********************************************************************************/
void Core_MixSoft_1St_D32C31_WRA(Mix_1St_Cll_FLOAT_t* pInstance, const LVM_FLOAT* src,
                                 LVM_FLOAT* dst, LVM_INT16 n);
void Core_MixHard_2St_D32C31_SAT(Mix_2St_Cll_FLOAT_t* pInstance, const LVM_FLOAT* src1,
                                 const LVM_FLOAT* src2, LVM_FLOAT* dst, LVM_INT16 n);
void Core_MixInSoft_D32C31_SAT(Mix_1St_Cll_FLOAT_t* pInstance, const LVM_FLOAT* src, LVM_FLOAT* dst,
                               LVM_INT16 n);

/**********************************************************************************/

#endif /* __MIXER_H__ */
