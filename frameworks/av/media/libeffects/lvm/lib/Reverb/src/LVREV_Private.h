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

#ifndef __LVREV_PRIVATE_H__
#define __LVREV_PRIVATE_H__

/****************************************************************************************/
/*                                                                                      */
/*  Includes                                                                            */
/*                                                                                      */
/****************************************************************************************/

#include <audio_utils/BiquadFilter.h>
#include "LVREV.h"
#include "LVREV_Tables.h"
#include "BIQUAD.h"
#include "Filter.h"
#include "VectorArithmetic.h"
#include "Mixer.h"
#include "LVM_Macros.h"

/****************************************************************************************/
/*                                                                                      */
/*  Defines                                                                             */
/*                                                                                      */
/****************************************************************************************/
/* General */
#define ONE_OVER_SQRT_TWO 0.707107f /* 1/sqrt(2) * 2^15 */
#define LVREV_B_8_on_1000 0.008f    /* 0.8 * 2^31 */
#define LVREV_HEADROOM 0.25f        /* -12dB * 2^15 */
#define LVREV_2_9_INQ29 2.9f        /* 2.9 in Q29 format */
#define LVREV_MIN3DB 0.7079457f     /* -3dB in Q15 format */

/* Intenal constants */
#define LVREV_LP_Poly_Order 4
#define LVREV_LP_Poly_Shift 5

#define LVREV_T60_SCALE 0.000142f /*(1/7000) */

#define LVREV_T_3_Power_0_on_4 1.0f
#define LVREV_T_3_Power_1_on_4 1.316074f
#define LVREV_T_3_Power_2_on_4 1.732051f
#define LVREV_T_3_Power_3_on_4 2.279507f
#define LVREV_T_3_Power_minus0_on_4 1.0f      /* 3^(-0/4) * 2^15 */
#define LVREV_T_3_Power_minus1_on_4 0.759836f /* 3^(-1/4) * 2^15 */
#define LVREV_T_3_Power_minus2_on_4 0.577350f /* 3^(-2/4) * 2^15 */
#define LVREV_T_3_Power_minus3_on_4 0.438691f /* 3^(-3/4) * 2^15 */

/* ((192000 * 120 * LVREV_T_3_Power_minus3_on_4) >> 15) / 1000 */
#define LVREV_MAX_T3_DELAY 10108
/* ((192000 * 120 * LVREV_T_3_Power_minus2_on_4) >> 15) / 1000 */
#define LVREV_MAX_T2_DELAY 13304
/* ((192000 * 120 * LVREV_T_3_Power_minus1_on_4) >> 15) / 1000 */
#define LVREV_MAX_T1_DELAY 17508
/* ((192000 * 120 * LVREV_T_3_Power_minus0_on_4) >> 15) / 1000 */
#define LVREV_MAX_T0_DELAY 23040
/* ((192000 * 120 * LVREV_T_3_Power_minus3_on_4) >> 15) / 1500 */
#define LVREV_MAX_AP3_DELAY 6740
/* ((192000 * 120 * LVREV_T_3_Power_minus2_on_4) >> 15) / 1500 */
#define LVREV_MAX_AP2_DELAY 8872
/* ((192000 * 120 * LVREV_T_3_Power_minus1_on_4) >> 15) / 1500 */
#define LVREV_MAX_AP1_DELAY 11672
/* ((192000 * 120 * LVREV_T_3_Power_minus0_on_4) >> 15) / 1500 */
#define LVREV_MAX_AP0_DELAY 15360

#define LVREV_BYPASSMIXER_TC 1000  /* Bypass mixer time constant*/
#define LVREV_ALLPASS_TC 1000      /* All-pass filter time constant */
#define LVREV_ALLPASS_TAP_TC 10000 /* All-pass filter dely tap change */
#define LVREV_FEEDBACKMIXER_TC 100 /* Feedback mixer time constant*/
#define LVREV_OUTPUTGAIN_SHIFT 5   /* Bits shift for output gain correction */

/* Parameter limits */
#define LVREV_NUM_FS 13 /* Number of supported sample rates */

#define LVREV_MAXBLKSIZE_LIMIT 64 /* Maximum block size low limit */
#define LVREV_MAX_LEVEL 100       /* Maximum level, 100% */
#define LVREV_MIN_LPF_CORNER 50   /* Low pass filter limits */
#define LVREV_MAX_LPF_CORNER 23999
#define LVREV_MIN_HPF_CORNER 20 /* High pass filrer limits */
#define LVREV_MAX_HPF_CORNER 1000
#define LVREV_MAX_T60 7000     /* Maximum T60 time in ms */
#define LVREV_MAX_DENSITY 100  /* Maximum density, 100% */
#define LVREV_MAX_DAMPING 100  /* Maximum damping, 100% */
#define LVREV_MAX_ROOMSIZE 100 /* Maximum room size, 100% */

/****************************************************************************************/
/*                                                                                      */
/*  Structures                                                                          */
/*                                                                                      */
/****************************************************************************************/

typedef struct {
    /* General */
    LVREV_InstanceParams_st InstanceParams; /* Initialisation time instance parameters */
    LVREV_ControlParams_st CurrentParams;   /* Parameters being used */
    LVREV_ControlParams_st NewParams;       /* New parameters from the \
                                               calling application */
    LVM_CHAR bControlPending;               /* Flag to indicate new parameters \
                                               are available */
    LVM_CHAR bFirstControl;                 /* Flag to indicate that the control \
                                               function is called for the first time */
    LVM_CHAR bDisableReverb;                /* Flag to indicate that the mix level is
                                               0% and the reverb can be disabled */
    LVM_INT32 RoomSizeInms;                 /* Room size in msec */
    LVM_INT32 MaxBlkLen;                    /* Maximum block size for internal
                                               processing */

    /* Aligned memory pointers */
    std::unique_ptr<android::audio_utils::BiquadFilter<LVM_FLOAT>>
            pRevHPFBiquad; /* Biquad filter instance for HPF */
    std::unique_ptr<android::audio_utils::BiquadFilter<LVM_FLOAT>>
            pRevLPFBiquad; /* Biquad filter instance for LPF */
    std::array<std::unique_ptr<android::audio_utils::BiquadFilter<LVM_FLOAT>>, LVREV_DELAYLINES_4>
            revLPFBiquad; /* Biquad filter instance for Reverb LPF */
    LVM_FLOAT* pScratchDelayLine[LVREV_DELAYLINES_4]; /* Delay line scratch memory */
    LVM_FLOAT* pScratch;             /* Multi ussge scratch */
    LVM_FLOAT* pInputSave;           /* Reverb block input save for dry/wet
                                        mixing*/

    /* Feedback matrix */
    Mix_1St_Cll_FLOAT_t FeedbackMixer[LVREV_DELAYLINES_4]; /* Mixer for Pop and Click Suppression \
                                             caused by feedback Gain */

    /* All-Pass Filter */
    LVM_INT32 T[LVREV_DELAYLINES_4];                          /* Maximum delay size of buffer */
    LVM_FLOAT* pDelay_T[LVREV_DELAYLINES_4];                  /* Pointer to delay buffers */
    LVM_INT32 Delay_AP[LVREV_DELAYLINES_4];                   /* Offset to AP delay buffer start */
    LVM_INT16 AB_Selection;                     /* Smooth from tap A to B when 1 \
                                                   otherwise B to A */
    LVM_INT32 A_DelaySize[LVREV_DELAYLINES_4];                /* A delay length in samples */
    LVM_INT32 B_DelaySize[LVREV_DELAYLINES_4];                /* B delay length in samples */
    LVM_FLOAT* pOffsetA[LVREV_DELAYLINES_4];                  /* Offset for the A delay tap */
    LVM_FLOAT* pOffsetB[LVREV_DELAYLINES_4];                  /* Offset for the B delay tap */
    Mix_2St_Cll_FLOAT_t Mixer_APTaps[LVREV_DELAYLINES_4];     /* Smoothed AP delay mixer */
    Mix_1St_Cll_FLOAT_t Mixer_SGFeedback[LVREV_DELAYLINES_4]; /* Smoothed SAfeedback gain */
    Mix_1St_Cll_FLOAT_t Mixer_SGFeedforward[LVREV_DELAYLINES_4]; /* Smoothed AP feedforward gain */

    /* Output gain */
    Mix_2St_Cll_FLOAT_t BypassMixer; /* Dry/wet mixer */
    LVM_FLOAT Gain;                  /* Gain applied to output to maintain
                                        average signal power */
    Mix_1St_Cll_FLOAT_t GainMixer;   /* Gain smoothing */

} LVREV_Instance_st;

/****************************************************************************************/
/*                                                                                      */
/*  Function prototypes                                                                 */
/*                                                                                      */
/****************************************************************************************/

LVREV_ReturnStatus_en LVREV_ApplyNewSettings(LVREV_Instance_st* pPrivate);
void ReverbBlock(LVM_FLOAT* pInput, LVM_FLOAT* pOutput, LVREV_Instance_st* pPrivate,
                 LVM_UINT16 NumSamples);
LVM_INT32 BypassMixer_Callback(void* pCallbackData, void* pGeneralPurpose,
                               LVM_INT16 GeneralPurpose);

#endif /** __LVREV_PRIVATE_H__ **/

/* End of file */
