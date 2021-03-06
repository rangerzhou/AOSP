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



 Filename: /audio/gsm_amr/c/include/preemph.h

     Date: 02/05/2002

------------------------------------------------------------------------------
 REVISION HISTORY

 Description: Placed header file in the proper template format.  Added
 parameter pOverflow for the basic math ops.

 Description:  Replaced "int" and/or "char" with OSCL defined types.

 Description: Moved _cplusplus #ifdef after Include section.

 Description:

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This file contains all the constant definitions and prototype definitions
 needed by the file, preemph.c

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef preemph_h
#define preemph_h "$Id $"


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/

#include "typedef.h"

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

    /*----------------------------------------------------------------------------
    ; MACROS
    ; Define module specific macros here
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES
    ; Include all pre-processor statements here.
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; EXTERNAL VARIABLES REFERENCES
    ; Declare variables used in this module but defined elsewhere
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
    typedef struct
    {
        Word16 mem_pre;          /* filter state */
    } preemphasisState;

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/

    Word16 preemphasis_reset(preemphasisState *st);
    /* reset of preemphasis filter (i.e. set state memory to zero)
       returns 0 on success
     */
    void preemphasis_exit(preemphasisState **st);
    /* de-initialize preemphasis filter (i.e. free status struct)
       stores NULL in *st
     */

    void preemphasis(
        preemphasisState *st, /* (i/o): preemphasis filter state                */
        Word16 *signal,    /* (i/o): input signal overwritten by the output     */
        Word16 g,          /* (i)  : preemphasis coefficient                    */
        Word16 L,          /* (i)  : size of filtering                          */
        Flag   *pOverflow  /* (o)  : overflow indicator                         */
    );

    /*----------------------------------------------------------------------------
    ; END
    ----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* preemph_H_ */


