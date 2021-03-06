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

 Pathname: .audio/gsm-amr/c/src/bitreorder.c

------------------------------------------------------------------------------
 REVISION HISTORY

 Description: Changed file name to bitreorder_tab.c and .h. Also, updated the
              module description.

 Description: Define "const Word16 *reorderBits[NUM_MODES-1]" as
              "const Word16 *const reorderBits[NUM_MODES-1]".

 Description: Added #ifdef __cplusplus and removed "extern" from table
              definition. Removed corresponding header file from Include
              section.

 Description: Put "extern" back.

 Who:                       Date:
 Description:

------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS

 Inputs:
    None

 Local Stores/Buffers/Pointers Needed:
    None

 Global Stores/Buffers/Pointers Needed:
    None

 Outputs:
    None

 Pointers and Buffers Modified:
    None

 Local Stores Modified:
    None

 Global Stores Modified:
    None

------------------------------------------------------------------------------
 FUNCTION DESCRIPTION

 This function contains tables needed to reformat the encoded speech bits
 into IF2, WMF, and ETS.

------------------------------------------------------------------------------
 REQUIREMENTS

 None

------------------------------------------------------------------------------
 REFERENCES

 AMR Speech Codec Frame Structure,
 3GPP TS 26.101 version 4.1.0 Release 4, June 2001

------------------------------------------------------------------------------
 PSEUDO-CODE


------------------------------------------------------------------------------
 RESOURCES USED
   When the code is written for a specific target processor the
     the resources used should be documented below.

 STACK USAGE: [stack count for this module] + [variable to represent
          stack usage for each subroutine called]

     where: [stack usage variable] = stack usage for [subroutine
         name] (see [filename].ext)

 DATA MEMORY USED: x words

 PROGRAM MEMORY USED: x words

 CLOCK CYCLES: [cycle count equation for this module] + [variable
           used to represent cycle count for each subroutine
           called]

     where: [cycle count variable] = cycle count for [subroutine
        name] (see [filename].ext)

------------------------------------------------------------------------------
*/


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "typedef.h"
#include "bitreorder_tab.h"

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
    ; Include all pre-processor statements here. Include conditional
    ; compile variables also.
    ----------------------------------------------------------------------------*/
#define NUM_MODES           16
#define NUMBIT_MR475        95
#define NUMBIT_MR515       103
#define NUMBIT_MR59        118
#define NUMBIT_MR67        134
#define NUMBIT_MR74        148
#define NUMBIT_MR795       159
#define NUMBIT_MR102       204
#define NUMBIT_MR122       244
#define NUMBIT_AMR_SID      39
#define NUMBIT_GSMEFR_SID   43
#define NUMBIT_TDMAEFR_SID  38
#define NUMBIT_PDCEFR_SID   37
#define NUMBIT_UNUSED1       0
#define NUMBIT_UNUSED2       0
#define NUMBIT_UNUSED3       0
#define NUMBIT_NO_DATA       0

#define MAX_NUM_BITS       244
    /*----------------------------------------------------------------------------
    ; LOCAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/


    /*----------------------------------------------------------------------------
    ; LOCAL STORE/BUFFER/POINTER DEFINITIONS
    ; Variable declaration - defined here and used outside this module
    ----------------------------------------------------------------------------*/
    /* number of parameters per modes (values must be <= MAX_PRM_SIZE!) */
    const Word16 numOfBits[NUM_MODES] =
    {
        NUMBIT_MR475,
        NUMBIT_MR515,
        NUMBIT_MR59,
        NUMBIT_MR67,
        NUMBIT_MR74,
        NUMBIT_MR795,
        NUMBIT_MR102,
        NUMBIT_MR122,
        NUMBIT_AMR_SID,
        NUMBIT_GSMEFR_SID,
        NUMBIT_TDMAEFR_SID,
        NUMBIT_PDCEFR_SID,
        NUMBIT_UNUSED1,
        NUMBIT_UNUSED2,
        NUMBIT_UNUSED3,
        NUMBIT_NO_DATA
    };

    const Word16 reorderBits_MR475[NUMBIT_MR475] =
    {
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
        10, 11, 12, 13, 14, 15, 23, 24, 25, 26,
        27, 28, 48, 49, 61, 62, 82, 83, 47, 46,
        45, 44, 81, 80, 79, 78, 17, 18, 20, 22,
        77, 76, 75, 74, 29, 30, 43, 42, 41, 40,
        38, 39, 16, 19, 21, 50, 51, 59, 60, 63,
        64, 72, 73, 84, 85, 93, 94, 32, 33, 35,
        36, 53, 54, 56, 57, 66, 67, 69, 70, 87,
        88, 90, 91, 34, 55, 68, 89, 37, 58, 71,
        92, 31, 52, 65, 86
    };

    const Word16 reorderBits_MR515[NUMBIT_MR515] =
    {
        7,  6,  5,  4,  3,  2,  1,  0, 15, 14,
        13, 12, 11, 10,  9,  8, 23, 24, 25, 26,
        27, 46, 65, 84, 45, 44, 43, 64, 63, 62,
        83, 82, 81, 102, 101, 100, 42, 61, 80, 99,
        28, 47, 66, 85, 18, 41, 60, 79, 98, 29,
        48, 67, 17, 20, 22, 40, 59, 78, 97, 21,
        30, 49, 68, 86, 19, 16, 87, 39, 38, 58,
        57, 77, 35, 54, 73, 92, 76, 96, 95, 36,
        55, 74, 93, 32, 51, 33, 52, 70, 71, 89,
        90, 31, 50, 69, 88, 37, 56, 75, 94, 34,
        53, 72, 91
    };

    const Word16 reorderBits_MR59[NUMBIT_MR59] =
    {
        0,  1,  4,  5,  3,  6,  7,  2, 13, 15,
        8,  9, 11, 12, 14, 10, 16, 28, 74, 29,
        75, 27, 73, 26, 72, 30, 76, 51, 97, 50,
        71, 96, 117, 31, 77, 52, 98, 49, 70, 95,
        116, 53, 99, 32, 78, 33, 79, 48, 69, 94,
        115, 47, 68, 93, 114, 46, 67, 92, 113, 19,
        21, 23, 22, 18, 17, 20, 24, 111, 43, 89,
        110, 64, 65, 44, 90, 25, 45, 66, 91, 112,
        54, 100, 40, 61, 86, 107, 39, 60, 85, 106,
        36, 57, 82, 103, 35, 56, 81, 102, 34, 55,
        80, 101, 42, 63, 88, 109, 41, 62, 87, 108,
        38, 59, 84, 105, 37, 58, 83, 104
    };

    const Word16 reorderBits_MR67[NUMBIT_MR67] =
    {
        0,  1,  4,  3,  5,  6, 13,  7,  2,  8,
        9, 11, 15, 12, 14, 10, 28, 82, 29, 83,
        27, 81, 26, 80, 30, 84, 16, 55, 109, 56,
        110, 31, 85, 57, 111, 48, 73, 102, 127, 32,
        86, 51, 76, 105, 130, 52, 77, 106, 131, 58,
        112, 33, 87, 19, 23, 53, 78, 107, 132, 21,
        22, 18, 17, 20, 24, 25, 50, 75, 104, 129,
        47, 72, 101, 126, 54, 79, 108, 133, 46, 71,
        100, 125, 128, 103, 74, 49, 45, 70, 99, 124,
        42, 67, 96, 121, 39, 64, 93, 118, 38, 63,
        92, 117, 35, 60, 89, 114, 34, 59, 88, 113,
        44, 69, 98, 123, 43, 68, 97, 122, 41, 66,
        95, 120, 40, 65, 94, 119, 37, 62, 91, 116,
        36, 61, 90, 115
    };

    const Word16 reorderBits_MR74[NUMBIT_MR74] =
    {
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
        10, 11, 12, 13, 14, 15, 16, 26, 87, 27,
        88, 28, 89, 29, 90, 30, 91, 51, 80, 112,
        141, 52, 81, 113, 142, 54, 83, 115, 144, 55,
        84, 116, 145, 58, 119, 59, 120, 21, 22, 23,
        17, 18, 19, 31, 60, 92, 121, 56, 85, 117,
        146, 20, 24, 25, 50, 79, 111, 140, 57, 86,
        118, 147, 49, 78, 110, 139, 48, 77, 53, 82,
        114, 143, 109, 138, 47, 76, 108, 137, 32, 33,
        61, 62, 93, 94, 122, 123, 41, 42, 43, 44,
        45, 46, 70, 71, 72, 73, 74, 75, 102, 103,
        104, 105, 106, 107, 131, 132, 133, 134, 135, 136,
        34, 63, 95, 124, 35, 64, 96, 125, 36, 65,
        97, 126, 37, 66, 98, 127, 38, 67, 99, 128,
        39, 68, 100, 129, 40, 69, 101, 130
    };

    const Word16 reorderBits_MR795[NUMBIT_MR795] =
    {
        8,  7,  6,  5,  4,  3,  2, 14, 16,  9,
        10, 12, 13, 15, 11, 17, 20, 22, 24, 23,
        19, 18, 21, 56, 88, 122, 154, 57, 89, 123,
        155, 58, 90, 124, 156, 52, 84, 118, 150, 53,
        85, 119, 151, 27, 93, 28, 94, 29, 95, 30,
        96, 31, 97, 61, 127, 62, 128, 63, 129, 59,
        91, 125, 157, 32, 98, 64, 130,  1,  0, 25,
        26, 33, 99, 34, 100, 65, 131, 66, 132, 54,
        86, 120, 152, 60, 92, 126, 158, 55, 87, 121,
        153, 117, 116, 115, 46, 78, 112, 144, 43, 75,
        109, 141, 40, 72, 106, 138, 36, 68, 102, 134,
        114, 149, 148, 147, 146, 83, 82, 81, 80, 51,
        50, 49, 48, 47, 45, 44, 42, 39, 35, 79,
        77, 76, 74, 71, 67, 113, 111, 110, 108, 105,
        101, 145, 143, 142, 140, 137, 133, 41, 73, 107,
        139, 37, 69, 103, 135, 38, 70, 104, 136
    };

    const Word16 reorderBits_MR102[NUMBIT_MR102] =
    {
        7,  6,  5,  4,  3,  2,  1,  0, 16, 15,
        14, 13, 12, 11, 10,  9,  8, 26, 27, 28,
        29, 30, 31, 115, 116, 117, 118, 119, 120, 72,
        73, 161, 162, 65, 68, 69, 108, 111, 112, 154,
        157, 158, 197, 200, 201, 32, 33, 121, 122, 74,
        75, 163, 164, 66, 109, 155, 198, 19, 23, 21,
        22, 18, 17, 20, 24, 25, 37, 36, 35, 34,
        80, 79, 78, 77, 126, 125, 124, 123, 169, 168,
        167, 166, 70, 67, 71, 113, 110, 114, 159, 156,
        160, 202, 199, 203, 76, 165, 81, 82, 92, 91,
        93, 83, 95, 85, 84, 94, 101, 102, 96, 104,
        86, 103, 87, 97, 127, 128, 138, 137, 139, 129,
        141, 131, 130, 140, 147, 148, 142, 150, 132, 149,
        133, 143, 170, 171, 181, 180, 182, 172, 184, 174,
        173, 183, 190, 191, 185, 193, 175, 192, 176, 186,
        38, 39, 49, 48, 50, 40, 52, 42, 41, 51,
        58, 59, 53, 61, 43, 60, 44, 54, 194, 179,
        189, 196, 177, 195, 178, 187, 188, 151, 136, 146,
        153, 134, 152, 135, 144, 145, 105, 90, 100, 107,
        88, 106, 89, 98, 99, 62, 47, 57, 64, 45,
        63, 46, 55, 56
    };

    const Word16 reorderBits_MR122[NUMBIT_MR122] =
    {
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
        10, 11, 12, 13, 14, 23, 15, 16, 17, 18,
        19, 20, 21, 22, 24, 25, 26, 27, 28, 38,
        141, 39, 142, 40, 143, 41, 144, 42, 145, 43,
        146, 44, 147, 45, 148, 46, 149, 47, 97, 150,
        200, 48, 98, 151, 201, 49, 99, 152, 202, 86,
        136, 189, 239, 87, 137, 190, 240, 88, 138, 191,
        241, 91, 194, 92, 195, 93, 196, 94, 197, 95,
        198, 29, 30, 31, 32, 33, 34, 35, 50, 100,
        153, 203, 89, 139, 192, 242, 51, 101, 154, 204,
        55, 105, 158, 208, 90, 140, 193, 243, 59, 109,
        162, 212, 63, 113, 166, 216, 67, 117, 170, 220,
        36, 37, 54, 53, 52, 58, 57, 56, 62, 61,
        60, 66, 65, 64, 70, 69, 68, 104, 103, 102,
        108, 107, 106, 112, 111, 110, 116, 115, 114, 120,
        119, 118, 157, 156, 155, 161, 160, 159, 165, 164,
        163, 169, 168, 167, 173, 172, 171, 207, 206, 205,
        211, 210, 209, 215, 214, 213, 219, 218, 217, 223,
        222, 221, 73, 72, 71, 76, 75, 74, 79, 78,
        77, 82, 81, 80, 85, 84, 83, 123, 122, 121,
        126, 125, 124, 129, 128, 127, 132, 131, 130, 135,
        134, 133, 176, 175, 174, 179, 178, 177, 182, 181,
        180, 185, 184, 183, 188, 187, 186, 226, 225, 224,
        229, 228, 227, 232, 231, 230, 235, 234, 233, 238,
        237, 236, 96, 199
    };

    /* overall table with all parameter sizes for all modes */
    const Word16 * const reorderBits[NUM_MODES-1] =
    {
        reorderBits_MR475,
        reorderBits_MR515,
        reorderBits_MR59,
        reorderBits_MR67,
        reorderBits_MR74,
        reorderBits_MR795,
        reorderBits_MR102,
        reorderBits_MR122
    };

    /* Number of Frames (16-bit segments sent for each mode */
    const Word16 numCompressedBytes[16] =
    {
        13, /*4.75*/
        14, /*5.15*/
        16, /*5.90*/
        18, /*6.70*/
        19, /*7.40*/
        21, /*7.95*/
        26, /*10.2*/
        31, /*12.2*/
        6, /*GsmAmr comfort noise*/
        6, /*Gsm-Efr comfort noise*/
        6, /*IS-641 comfort noise*/
        6, /*Pdc-Efr comfort noise*/
        0, /*future use*/
        0, /*future use*/
        0, /*future use*/
        1  /*No transmission*/
    };
    /*----------------------------------------------------------------------------
    ; EXTERNAL FUNCTION REFERENCES
    ; Declare functions defined elsewhere and referenced in this module
    ----------------------------------------------------------------------------*/


    /*----------------------------------------------------------------------------
    ; EXTERNAL GLOBAL STORE/BUFFER/POINTER REFERENCES
    ; Declare variables used in this module but defined elsewhere
    ----------------------------------------------------------------------------*/

    /*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; Define all local variables
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; Function body here
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; Return nothing or data or data pointer
----------------------------------------------------------------------------*/





