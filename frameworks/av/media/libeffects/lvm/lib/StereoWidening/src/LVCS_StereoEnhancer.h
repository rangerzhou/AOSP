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

#ifndef __LVCS_STEREOENHANCER_H__
#define __LVCS_STEREOENHANCER_H__

/************************************************************************************/
/*                                                                                  */
/*    Includes                                                                      */
/*                                                                                  */
/************************************************************************************/

#include "Filters.h"               /* Filter definitions */
#include "LVCS_Headphone_Coeffs.h" /* Headphone coefficients */
#include "BIQUAD.h"

/************************************************************************************/
/*                                                                                  */
/*    Structures                                                                    */
/*                                                                                  */
/************************************************************************************/

/* Stereo enhancer structure */
typedef struct {
    LVM_FLOAT MidGain; /* Middle gain in mobile speaker mode */
} LVCS_StereoEnhancer_t;

/************************************************************************************/
/*                                                                                  */
/*    Function prototypes                                                           */
/*                                                                                  */
/************************************************************************************/

LVCS_ReturnStatus_en LVCS_SEnhancerInit(LVCS_Handle_t hInstance, LVCS_Params_t* pParams);

LVCS_ReturnStatus_en LVCS_StereoEnhancer(LVCS_Handle_t hInstance, const LVM_FLOAT* pInData,
                                         LVM_FLOAT* pOutData, LVM_UINT16 NumSamples);

#endif /* STEREOENHANCE_H */
