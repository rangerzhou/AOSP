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

/**********************************************************************************
   INCLUDE FILES
***********************************************************************************/
#include "LVC_Mixer_Private.h"
#include "ScalarArithmetic.h"

/**********************************************************************************
   FUNCTION LVCore_MIXHARD_2ST_D16C31_SAT
***********************************************************************************/
void LVC_Core_MixHard_2St_D16C31_SAT(LVMixer3_FLOAT_st* ptrInstance1,
                                     LVMixer3_FLOAT_st* ptrInstance2, const LVM_FLOAT* src1,
                                     const LVM_FLOAT* src2, LVM_FLOAT* dst, LVM_INT16 n) {
    LVM_FLOAT Temp;
    LVM_INT16 ii;
    LVM_FLOAT Current1;
    LVM_FLOAT Current2;
    Mix_Private_FLOAT_st* pInstance1 = (Mix_Private_FLOAT_st*)(ptrInstance1->PrivateParams);
    Mix_Private_FLOAT_st* pInstance2 = (Mix_Private_FLOAT_st*)(ptrInstance2->PrivateParams);

    Current1 = pInstance1->Current;
    Current2 = pInstance2->Current;

    for (ii = n; ii != 0; ii--) {
        Temp =  *src1++ * Current1 + *src2++ * Current2;
        *dst++ = LVM_Clamp(Temp);
    }
}
/**********************************************************************************/
