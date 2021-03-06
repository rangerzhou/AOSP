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

#include "LVM_Types.h"
#include "LVM_Macros.h"
#include "ScalarArithmetic.h"
#include "BIQUAD.h"
#include "Filter.h"

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   void LVM_FO_LPF(   LVM_INT32       w ,                                */
/*                      FO_C32_Coefs_t  *pCoeffs);                         */
/*                                                                         */
/*                                                                         */
/* DESCRIPTION:                                                            */
/*    This function calculates the coefficient of first order low pass     */
/*    filter. It uses the equations:                                       */
/*                                                                         */
/*    B1    = (tan(w/2) - 1 )  /  (tan(w/2) + 1 )                          */
/*    A0    = (1 + B1) / 2                                                 */
/*    A1    = A0                                                           */
/*                                                                         */
/*    The value of B1 is then calculated directly from the value w by a    */
/*    polynomial expansion using a 9th order polynomial. It uses the       */
/*    following table of 32-bit integer polynomial coefficients:           */
/*                                                                         */
/*   Coefficient    Value                                                  */
/*   A0             -8388571                                               */
/*   A1             33547744                                               */
/*   A2             -66816791                                              */
/*   A3             173375308                                              */
/*   A4             -388437573                                             */
/*   A5             752975383                                              */
/*   A6             -1103016663                                            */
/*   A7             1121848567                                             */
/*   A8             -688078159                                             */
/*   A9             194669577                                              */
/*   A10            8                                                      */
/*                                                                         */
/*  Y = (A0 + A1*X + A2*X2 + A3*X3 + ???.. + AN*xN) << AN+1                  */
/*                                                                         */
/*                                                                         */
/* PARAMETERS:                                                             */
/*                                                                         */
/*  w               Sample rate in radians,  where:                        */
/*                  w = 2 * Pi * Fc / Fs                                   */
/*                  Fc   is the corner frequency in Hz                     */
/*                  Fs   is the sample rate in Hz                          */
/*                  w is in Q2.29 format and data range is [0 Pi]          */
/*  pCoeffs         Points to the filter coefficients calculated here      */
/*                  in Q1.30 format                                        */
/* RETURNS:                                                                */
/*                                                                         */
/*-------------------------------------------------------------------------*/
LVM_FLOAT LVM_FO_LPF(LVM_FLOAT w, FO_FLOAT_Coefs_t* pCoeffs) {
    LVM_FLOAT Y,
            Coefficients[13] = {-0.999996f, 0.999801f, -0.497824f, 0.322937f, -0.180880f, 0.087658f,
                                -0.032102f, 0.008163f, -0.001252f, 0.000089f, 0};
    Y = LVM_Polynomial((LVM_UINT16)9, Coefficients, w);
    pCoeffs->B1 = -Y;  // Store -B1 in filter structure instead of B1!
                       // A0=(1+B1)/2= B1/2 + 0.5
    Y = Y / 2.0f;      // A0=Y=B1/2
    Y = Y + 0.5f;      // A0=Y=(B1/2 + 0.5)

    pCoeffs->A0 = Y * FILTER_LOSS_FLOAT;
    pCoeffs->A1 = pCoeffs->A0;

    return 1;
}
