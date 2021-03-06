/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/****************************************************************************************
Portions of this file are derived from the following 3GPP standard:

    3GPP TS 26.073
    ANSI-C code for the Adaptive Multi-Rate (AMR) speech codec
    Available from http://www.3gpp.org

(C) 2004, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TTA, TTC)
Permission to distribute, modify and use this file under the standard license
terms listed above has been obtained from the copyright holder.
****************************************************************************************/
/*

 Pathname: ./audio/gsm-amr/c/src/weight_a.c

------------------------------------------------------------------------------
 REVISION HISTORY

 Description: Put file into template and first pass at optimization.

 Description: Made changes based on comments from the review meeting. Used
    pointers instead of index addressing in the arrays.

 Description: Synchronized file with UMTS version 3.2.0. Updated coding
              template. Removed unnecessary include files.

 Description: Fixed typecasting issue with TI C compiler.

 Description: Made the following changes per comments from Phase 2/3 review:
              1. Modified FOR loop to count down.
              2. Used address pre-increment instead of address offsets.

 Description:  Replaced "int" and/or "char" with OSCL defined types.

 Description: Changed round function name to pv_round to avoid conflict with
              round function in C standard library.

 Who:                           Date:
 Description:

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include    "weight_a.h"
#include    "typedef.h"
#include    "cnst.h"

/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here. Include conditional
; compile variables also.
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; LOCAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; LOCAL STORE/BUFFER/POINTER DEFINITIONS
; Variable declaration - defined here and used outside this module
----------------------------------------------------------------------------*/


/*
------------------------------------------------------------------------------
 FUNCTION NAME: Weight_Ai
------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:
    a = LPC coefficients (Word16)
    fac = Spectral expansion factors (Word16)
    a_exp = Spectral expanded LPC coefficients (Word16)

 Outputs:
    a_exp points to the updated spectral expanded LPC coefficients

 Returns:
    None.

 Global Variables Used:
    None.

 Local Variables Needed:
    None.

------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 This function calculates the spectral expansion for the LP coefficients of
 order M.
    a_exp[i] = a[i] * fac[i-1]    ; i=1..M

------------------------------------------------------------------------------
 REQUIREMENTS

 None.

------------------------------------------------------------------------------
 REFERENCES

 weight_a.c, UMTS GSM AMR speech codec, R99 - Version 3.2.0, March 2, 2001

------------------------------------------------------------------------------
 PSEUDO-CODE

void Weight_Ai (
    Word16 a[],         // (i)     : a[M+1]  LPC coefficients   (M=10)
    const Word16 fac[], // (i)     : Spectral expansion factors.
    Word16 a_exp[]      // (o)     : Spectral expanded LPC coefficients
)
{
    Word16 i;
    a_exp[0] = a[0];

    for (i = 1; i <= M; i++)
    {
        a_exp[i] = pv_round (L_mult (a[i], fac[i - 1]));
    }
    return;
}

------------------------------------------------------------------------------
 RESOURCES USED [optional]

 When the code is written for a specific target processor the
 the resources used should be documented below.

 HEAP MEMORY USED: x bytes

 STACK MEMORY USED: x bytes

 CLOCK CYCLES: (cycle count equation for this function) + (variable
                used to represent cycle count for each subroutine
                called)
     where: (cycle count variable) = cycle count for [subroutine
                                     name]

------------------------------------------------------------------------------
 CAUTION [optional]
 [State any special notes, constraints or cautions for users of this function]

------------------------------------------------------------------------------
*/

void Weight_Ai(
    Word16 a[],         /* (i)   : a[M+1]  LPC coefficients   (M=10)    */
    const Word16 fac[], /* (i)   : Spectral expansion factors.          */
    Word16 a_exp[]      /* (o)   : Spectral expanded LPC coefficients   */
)
{
    Word16 i;

    *(a_exp) = *(a);

    for (i = M; i >= 1; i--)
    {
        a_exp += 1;
        a += 1;
        fac += 1;
        *(a_exp) = (Word16)((((Word32) * (a)) * *(fac - 1)
                             + 0x00004000L) >> 15);
    }

    return;
}

