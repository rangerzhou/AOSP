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

#ifndef __SCALARARITHMETIC_H__
#define __SCALARARITHMETIC_H__

/*######################################################################################*/
/*  Include files                                                                       */
/*######################################################################################*/
#include <math.h>
#include "LVM_Types.h"

/*######################################################################################*/
/*  Extern function prototypes                                                          */
/*######################################################################################*/

/* Absolute value including the corner case for the extreme negative value */

static inline LVM_FLOAT Abs_Float(LVM_FLOAT input) {
    return fabs(input);
}

static inline LVM_FLOAT LVM_Clamp(LVM_FLOAT val) {
    return fmin(fmax(val, -1.0f), 1.0f);
}

/****************************************************************************************
 *  Name        : dB_to_Lin32()
 *  Input       : Signed 16-bit integer
 *                  MSB (16) = sign bit
 *                  (15->05) = integer part
 *                  (04->01) = decimal part
 *  Output      : Signed 32-bit integer
 *                  MSB (32) = sign bit
 *                  (31->16) = integer part
 *                  (15->01) = decimal part
 *  Returns     : Lin value format 1.16.15
 ****************************************************************************************/
LVM_FLOAT dB_to_LinFloat(LVM_INT16 db_fix);

#endif /* __SCALARARITHMETIC_H__ */
