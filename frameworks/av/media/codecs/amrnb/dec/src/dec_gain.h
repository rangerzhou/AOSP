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
------------------------------------------------------------------------------



 Filename: /audio/gsm_amr/c/src/include/dec_gain.h

     Date: 01/31/2002

------------------------------------------------------------------------------
 REVISION HISTORY

 Description: Moved _cplusplus #ifdef after Include section.

 Description:

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

      File             : dec_gain.h
      Purpose          : Decode the pitch and codebook gains

------------------------------------------------------------------------------
*/

#ifndef _DEC_GAIN_H_
#define _DEC_GAIN_H_
#define dec_gain_h "$Id $"

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "typedef.h"
#include "gc_pred.h"
#include "mode.h"

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

    /*----------------------------------------------------------------------------
    ; MACROS
    ; [Define module specific macros here]
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES
    ; [Include all pre-processor statements here.]
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; EXTERNAL VARIABLES REFERENCES
    ; [Declare variables used in this module but defined elsewhere]
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; SIMPLE TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; ENUMERATED TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; STRUCTURES TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; [List function prototypes here]
    ----------------------------------------------------------------------------*/

    /*
     *   FUNCTION:  Dec_gain()
     *   PURPOSE: Decode the pitch and codebook gains
     */
    void Dec_gain(
        gc_predState *pred_state, /* i/o: MA predictor state           */
        enum Mode mode,           /* i  : AMR mode                     */
        Word16 index,             /* i  : index of quantization.       */
        Word16 code[],            /* i  : Innovative vector.           */
        Word16 evenSubfr,         /* i  : Flag for even subframes      */
        Word16 * gain_pit,        /* o  : Pitch gain.                  */
        Word16 * gain_cod,        /* o  : Code gain.                   */
        Flag   * pOverflow
    );



#ifdef __cplusplus
}
#endif

#endif  /* _DEC_GAIN_H_ */



