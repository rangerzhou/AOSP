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

/************************************************************************/
/*                                                                      */
/*     %created_by:    sra % (CM/S)*/
/*     %name:          dB_to_Lin32.c % (CM/S)*/
/*     %version:       2 % (CM/S)*/
/*     %date_created:  Wed Jun 18 11:27:46 2008 % (CM/S)*/
/*                                                                      */
/************************************************************************/

/*######################################################################################*/
/*  Include files                                                                       */
/*######################################################################################*/

#include "ScalarArithmetic.h"
#include <math.h>

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
 *  Description :
 *  Remarks     :  Makes an approximation to the conversion by counting the number
 *                 of 6dB steps for use as shifts and then interpolates with a remainder
 *                 with the equation:
 *
 *                 Correction = (Remainder / 1.5029) - (Remainder^2 / 6)
 *
 *                 The two coefficients are scaled from 0x40000000 in 96 steps and calculated
 *                 as follows:
 *
 *                 FIRST_COEF  = 0x80000000 / (96 * 1.5029)
 *                 SECOND_COEF = 0x80000000 / (96^2 * 6)
 *
 ****************************************************************************************/

#define FOUR_OVER_SIX 21846 /* (4 / 6) * 2^15 */
#define SIX_DB 96           /* 6 * 16 or 6dB in Q11.4 format */
#define FIRST_COEF_NEG 14884305
#define FIRST_COEF_POS 7442152 /* FIRST_COEF_NEG / 2 */
#define SECOND_COEF 38836
#define MAX_VALUE 1536 /* 96 * 16 */

LVM_FLOAT dB_to_LinFloat(LVM_INT16 db_fix) {
    LVM_FLOAT dB_Float;
    LVM_FLOAT LinFloat;

    dB_Float = (LVM_FLOAT)((LVM_FLOAT)db_fix / 16.0f);
    LinFloat = pow(10, dB_Float / 20.0);

    return LinFloat;
}
