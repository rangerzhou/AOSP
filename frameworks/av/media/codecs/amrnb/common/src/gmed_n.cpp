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
 Pathname: ./audio/gsm-amr/c/src/gmed_n.c

------------------------------------------------------------------------------
 REVISION HISTORY

 Description: Put file into template and first pass at optimization.

 Description: Made changes based on comments from the review meeting. Used
    pointers instead of index addressing in the arrays.

 Description: Synchronized file with UMTS version 3.2.0. Updated coding
              template. Removed unncessary include files.

 Description:  Replaced "int" and/or "char" with OSCL defined types.

 Who:                           Date:
 Description:

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include    "gmed_n.h"
#include    "typedef.h"

/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here. Include conditional
; compile variables also.
----------------------------------------------------------------------------*/
#define NMAX    9   /* largest N used in median calculation */

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
 FUNCTION NAME: gmed_n
------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:
    ind = input values (Word16)
    n = number of inputs to find the median (Word16)

 Returns:
    median value.

 Outputs:
    None.

 Global Variables Used:
    None.

 Local Variables Needed:
    None.

------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 This function calculates N-point median of a data set. This routine is only
 valid for a odd number of gains (n <= NMAX).

------------------------------------------------------------------------------
 REQUIREMENTS

 None.

------------------------------------------------------------------------------
 REFERENCES

 gmed_n.c, UMTS GSM AMR speech codec, R99 - Version 3.2.0, March 2, 2001

------------------------------------------------------------------------------
 PSEUDO-CODE

Word16 gmed_n (   // o : The median value (0...N-1)
    Word16 ind[], // i : Past gain values
    Word16 n      // i : The number of gains; this routine
                  //     is only valid for a odd number of gains
                  //     (n <= NMAX)
)
{
    Word16 i, j, ix = 0;
    Word16 max;
    Word16 medianIndex;
    Word16 tmp[NMAX];
    Word16 tmp2[NMAX];

    for (i = 0; i < n; i++)
    {
        tmp2[i] = ind[i];
    }

    for (i = 0; i < n; i++)
    {
        max = -32767;
        for (j = 0; j < n; j++)
        {
            if (sub (tmp2[j], max) >= 0)
            {
                max = tmp2[j];
                ix = j;
            }
        }
        tmp2[ix] = -32768;
        tmp[i] = ix;
    }

    medianIndex=tmp[ shr(n,1) ];  // account for complex addressing
    return (ind[medianIndex]);
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

Word16 gmed_n(            /* o : the median value    */
    Word16 ind[],   /* i : input values        */
    Word16 n        /* i : number of inputs    */
)
{
    Word16 i, j, ix = 0;
    Word16 max;
    Word16 medianIndex;
    Word16  tmp[NMAX];
    Word16  tmp2[NMAX];

    for (i = 0; i < n; i++)
    {
        *(tmp2 + i) = *(ind + i);
    }

    for (i = 0; i < n; i++)
    {
        max = -32767;
        for (j = 0; j < n; j++)
        {
            if (*(tmp2 + j) >= max)
            {
                max = *(tmp2 + j);
                ix = j;
            }
        }
        *(tmp2 + ix) = -32768;
        *(tmp + i) = ix;
    }

    medianIndex = *(tmp + (n >> 1));  /* account for complex addressing */

    return (*(ind + medianIndex));
}

