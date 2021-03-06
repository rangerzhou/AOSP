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

/****************************************************************************************/
/*                                                                                      */
/*  Includes                                                                            */
/*                                                                                      */
/****************************************************************************************/

#include <system/audio.h>
#include "LVREV_Private.h"
#include "Filter.h"

/****************************************************************************************/
/*                                                                                      */
/* FUNCTION:                LVREV_ApplyNewSettings                                      */
/*                                                                                      */
/* DESCRIPTION:                                                                         */
/*  Applies the new control parameters                                                  */
/*                                                                                      */
/* PARAMETERS:                                                                          */
/*  pPrivate                Pointer to the instance private parameters                  */
/*                                                                                      */
/* RETURNS:                                                                             */
/*  LVREV_Success           Succeeded                                                   */
/*  LVREV_NULLADDRESS       When pPrivate is NULL                                       */
/*                                                                                      */
/* NOTES:                                                                               */
/*                                                                                      */
/****************************************************************************************/

LVREV_ReturnStatus_en LVREV_ApplyNewSettings(LVREV_Instance_st* pPrivate) {
    LVM_Mode_en OperatingMode;
    LVM_INT32 NumberOfDelayLines;

    /* Check for NULL pointer */
    if (pPrivate == LVM_NULL) {
        return LVREV_NULLADDRESS;
    }

    OperatingMode = pPrivate->NewParams.OperatingMode;

    if (pPrivate->InstanceParams.NumDelays == LVREV_DELAYLINES_4) {
        NumberOfDelayLines = 4;
    } else if (pPrivate->InstanceParams.NumDelays == LVREV_DELAYLINES_2) {
        NumberOfDelayLines = 2;
    } else {
        NumberOfDelayLines = 1;
    }

    /*
     * Update the high pass filter coefficients
     */
    if ((pPrivate->NewParams.HPF != pPrivate->CurrentParams.HPF) ||
        (pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_FLOAT Omega;
        FO_FLOAT_Coefs_t Coeffs;

        Omega = LVM_GetOmega(pPrivate->NewParams.HPF, pPrivate->NewParams.SampleRate);
        LVM_FO_HPF(Omega, &Coeffs);
        const std::array<LVM_FLOAT, android::audio_utils::kBiquadNumCoefs> coefs = {
                Coeffs.A0, Coeffs.A1, 0.0, -(Coeffs.B1), 0.0};
        pPrivate->pRevHPFBiquad.reset(
                new android::audio_utils::BiquadFilter<LVM_FLOAT>(FCC_1, coefs));
    }

    /*
     * Update the low pass filter coefficients
     */
    if ((pPrivate->NewParams.LPF != pPrivate->CurrentParams.LPF) ||
        (pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_FLOAT Omega;
        FO_FLOAT_Coefs_t Coeffs;

        Coeffs.A0 = 1;
        Coeffs.A1 = 0;
        Coeffs.B1 = 0;
        if (pPrivate->NewParams.LPF <= (LVM_FsTable[pPrivate->NewParams.SampleRate] >> 1)) {
            Omega = LVM_GetOmega(pPrivate->NewParams.LPF, pPrivate->NewParams.SampleRate);

            /*
             * Do not apply filter if w =2*pi*fc/fs >= 2.9
             */
            if (Omega <= (LVM_FLOAT)LVREV_2_9_INQ29) {
                LVM_FO_LPF(Omega, &Coeffs);
            }
        }
        const std::array<LVM_FLOAT, android::audio_utils::kBiquadNumCoefs> coefs = {
                Coeffs.A0, Coeffs.A1, 0.0, -(Coeffs.B1), 0.0};
        pPrivate->pRevLPFBiquad.reset(
                new android::audio_utils::BiquadFilter<LVM_FLOAT>(FCC_1, coefs));
    }

    /*
     * Calculate the room size parameter
     */
    if (pPrivate->NewParams.RoomSize != pPrivate->CurrentParams.RoomSize) {
        /* Room size range is 10ms to 200ms
         * 0%   -- 10ms
         * 50%  -- 65ms
         * 100% -- 120ms
         */
        pPrivate->RoomSizeInms = 10 + (((pPrivate->NewParams.RoomSize * 11) + 5) / 10);
    }

    /*
     * Update the T delay number of samples and the all pass delay number of samples
     */
    if ((pPrivate->NewParams.RoomSize != pPrivate->CurrentParams.RoomSize) ||
        (pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_UINT32 Temp;
        LVM_INT32 APDelaySize;
        LVM_INT32 Fs = LVM_GetFsFromTable(pPrivate->NewParams.SampleRate);
        LVM_UINT32 DelayLengthSamples = (LVM_UINT32)(Fs * pPrivate->RoomSizeInms);
        LVM_INT16 i;
        LVM_FLOAT ScaleTable[] = {LVREV_T_3_Power_minus0_on_4, LVREV_T_3_Power_minus1_on_4,
                                  LVREV_T_3_Power_minus2_on_4, LVREV_T_3_Power_minus3_on_4};

        /*
         * For each delay line
         */
        for (i = 0; i < NumberOfDelayLines; i++) {
            if (i != 0) {
                LVM_FLOAT Temp1; /* to avoid QAC warning on type conversion */

                Temp1 = (LVM_FLOAT)DelayLengthSamples;
                Temp = (LVM_UINT32)(Temp1 * ScaleTable[i]);
            } else {
                Temp = DelayLengthSamples;
            }
            APDelaySize = Temp / 1500;

            /*
             * Set the fixed delay
             */

            Temp = (LVREV_MAX_T_DELAY[i] - LVREV_MAX_AP_DELAY[i]) * Fs / 192000;
            pPrivate->Delay_AP[i] = pPrivate->T[i] - Temp;

            /*
             * Set the tap selection
             */
            if (pPrivate->AB_Selection) {
                /* Smooth from tap A to tap B */
                pPrivate->pOffsetB[i] = &pPrivate->pDelay_T[i][pPrivate->T[i] - Temp - APDelaySize];
                pPrivate->B_DelaySize[i] = APDelaySize;
                pPrivate->Mixer_APTaps[i].Target1 = 0;
                pPrivate->Mixer_APTaps[i].Target2 = 1.0f;
            } else {
                /* Smooth from tap B to tap A */
                pPrivate->pOffsetA[i] = &pPrivate->pDelay_T[i][pPrivate->T[i] - Temp - APDelaySize];
                pPrivate->A_DelaySize[i] = APDelaySize;
                pPrivate->Mixer_APTaps[i].Target2 = 0;
                pPrivate->Mixer_APTaps[i].Target1 = 1.0f;
            }

            /*
             * Set the maximum block size to the smallest delay size
             */
            pPrivate->MaxBlkLen = Temp;
            if (pPrivate->MaxBlkLen > pPrivate->A_DelaySize[i]) {
                pPrivate->MaxBlkLen = pPrivate->A_DelaySize[i];
            }
            if (pPrivate->MaxBlkLen > pPrivate->B_DelaySize[i]) {
                pPrivate->MaxBlkLen = pPrivate->B_DelaySize[i];
            }
        }
        if (pPrivate->AB_Selection) {
            pPrivate->AB_Selection = 0;
        } else {
            pPrivate->AB_Selection = 1;
        }

        /*
         * Limit the maximum block length
         */
        /* Just as a precausion, but no problem if we remove this line      */
        pPrivate->MaxBlkLen = pPrivate->MaxBlkLen - 2;
        if (pPrivate->MaxBlkLen > pPrivate->InstanceParams.MaxBlockSize) {
            pPrivate->MaxBlkLen = (LVM_INT32)pPrivate->InstanceParams.MaxBlockSize;
        }
    }

    /*
     * Update the low pass filter coefficient
     */
    if ((pPrivate->NewParams.Damping != pPrivate->CurrentParams.Damping) ||
        (pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_INT32 Temp;
        LVM_FLOAT Omega;
        FO_FLOAT_Coefs_t Coeffs;
        LVM_INT16 i;
        LVM_INT16 Damping = (LVM_INT16)((pPrivate->NewParams.Damping * 100) + 1000);
        LVM_FLOAT ScaleTable[] = {LVREV_T_3_Power_0_on_4, LVREV_T_3_Power_1_on_4,
                                  LVREV_T_3_Power_2_on_4, LVREV_T_3_Power_3_on_4};

        /*
         * For each filter
         */
        for (i = 0; i < NumberOfDelayLines; i++) {
            if (i != 0) {
                Temp = (LVM_INT32)(ScaleTable[i] * Damping);
            } else {
                Temp = Damping;
            }
            if (Temp <= (LVM_INT32)(LVM_FsTable[pPrivate->NewParams.SampleRate] >> 1)) {
                Omega = LVM_GetOmega(Temp, pPrivate->NewParams.SampleRate);
                LVM_FO_LPF(Omega, &Coeffs);
            } else {
                Coeffs.A0 = 1;
                Coeffs.A1 = 0;
                Coeffs.B1 = 0;
            }
            const std::array<LVM_FLOAT, android::audio_utils::kBiquadNumCoefs> coefs = {
                    Coeffs.A0, Coeffs.A1, 0.0, -(Coeffs.B1), 0.0};
            pPrivate->revLPFBiquad[i].reset(
                    new android::audio_utils::BiquadFilter<LVM_FLOAT>(FCC_1, coefs));
        }
    }

    /*
     * Update All-pass filter mixer time constants
     */
    if ((pPrivate->NewParams.RoomSize != pPrivate->CurrentParams.RoomSize) ||
        (pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->NewParams.Density != pPrivate->CurrentParams.Density)) {
        LVM_INT16 i;
        LVM_FLOAT Alpha;
        LVM_FLOAT AlphaTap;

        Alpha = LVM_Mixer_TimeConstant(LVREV_ALLPASS_TC,
                                       LVM_GetFsFromTable(pPrivate->NewParams.SampleRate), 1);

        AlphaTap = LVM_Mixer_TimeConstant(LVREV_ALLPASS_TAP_TC,
                                          LVM_GetFsFromTable(pPrivate->NewParams.SampleRate), 1);

        for (i = 0; i < 4; i++) {
            pPrivate->Mixer_APTaps[i].Alpha1 = AlphaTap;
            pPrivate->Mixer_APTaps[i].Alpha2 = AlphaTap;
            pPrivate->Mixer_SGFeedback[i].Alpha = Alpha;
            pPrivate->Mixer_SGFeedforward[i].Alpha = Alpha;
        }
    }

    /*
     * Update the feed back gain
     */
    if ((pPrivate->NewParams.RoomSize != pPrivate->CurrentParams.RoomSize) ||
        (pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->NewParams.T60 != pPrivate->CurrentParams.T60) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_FLOAT G[4]; /* Feedback gain (Q7.24) */

        if (pPrivate->NewParams.T60 == 0) {
            G[3] = 0;
            G[2] = 0;
            G[1] = 0;
            G[0] = 0;
        } else {
            LVM_FLOAT Temp1;
            LVM_FLOAT Temp2;
            LVM_INT16 i;
            LVM_FLOAT ScaleTable[] = {LVREV_T_3_Power_minus0_on_4, LVREV_T_3_Power_minus1_on_4,
                                      LVREV_T_3_Power_minus2_on_4, LVREV_T_3_Power_minus3_on_4};

            /*
             * For each delay line
             */
            for (i = 0; i < NumberOfDelayLines; i++) {
                Temp1 = (3 * pPrivate->RoomSizeInms * ScaleTable[i]) / pPrivate->NewParams.T60;
                if (Temp1 >= (4)) {
                    G[i] = 0;
                } else if ((Temp1 >= (2))) {
                    Temp2 = LVM_Power10(-(Temp1 / 2.0f));
                    Temp1 = LVM_Power10(-(Temp1 / 2.0f));
                    Temp1 = Temp1 * Temp2;
                } else {
                    Temp1 = LVM_Power10(-(Temp1));
                }
                if (NumberOfDelayLines == 1) {
                    G[i] = Temp1;
                } else {
                    LVM_FLOAT TempG;
                    TempG = Temp1 * ONE_OVER_SQRT_TWO;
                    G[i] = TempG;
                }
            }
        }

        /* Set up the feedback mixers for four delay lines */
        pPrivate->FeedbackMixer[0].Target = G[0];
        pPrivate->FeedbackMixer[1].Target = G[1];
        pPrivate->FeedbackMixer[2].Target = G[2];
        pPrivate->FeedbackMixer[3].Target = G[3];
    }

    /*
     * Calculate the gain correction
     */
    if ((pPrivate->NewParams.RoomSize != pPrivate->CurrentParams.RoomSize) ||
        (pPrivate->NewParams.Level != pPrivate->CurrentParams.Level) ||
        (pPrivate->NewParams.T60 != pPrivate->CurrentParams.T60)) {
        LVM_INT32 Index = 0;
        LVM_FLOAT Index_FLOAT;
        LVM_INT32 i = 0;
        LVM_FLOAT Gain = 0;
        LVM_INT32 RoomSize = 0;
        LVM_FLOAT T60;
        LVM_FLOAT Coefs[5];

        if (pPrivate->NewParams.RoomSize == 0) {
            RoomSize = 1;
        } else {
            RoomSize = (LVM_INT32)pPrivate->NewParams.RoomSize;
        }

        if (pPrivate->NewParams.T60 < 100) {
            T60 = 100 * LVREV_T60_SCALE;
        } else {
            T60 = pPrivate->NewParams.T60 * LVREV_T60_SCALE;
        }

        /* Find the nearest room size in table */
        for (i = 0; i < 24; i++) {
            if (RoomSize <= LVREV_GainPolyTable[i][0]) {
                Index = i;
                break;
            }
        }

        if (RoomSize == LVREV_GainPolyTable[Index][0]) {
            /* Take table values if the room size is in table */
            for (i = 1; i < 5; i++) {
                Coefs[i - 1] = LVREV_GainPolyTable[Index][i];
            }
            Coefs[4] = 0;
            Gain = LVM_Polynomial(3, Coefs, T60); /* Q.24 result */
        } else {
            /* Interpolate the gain between nearest room sizes */

            LVM_FLOAT Gain1, Gain2;
            LVM_INT32 Tot_Dist, Dist;

            Tot_Dist = (LVM_UINT32)LVREV_GainPolyTable[Index][0] -
                       (LVM_UINT32)LVREV_GainPolyTable[Index - 1][0];
            Dist = RoomSize - (LVM_UINT32)LVREV_GainPolyTable[Index - 1][0];

            /* Get gain for first */
            for (i = 1; i < 5; i++) {
                Coefs[i - 1] = LVREV_GainPolyTable[Index - 1][i];
            }
            Coefs[4] = 0;

            Gain1 = LVM_Polynomial(3, Coefs, T60); /* Q.24 result */

            /* Get gain for second */
            for (i = 1; i < 5; i++) {
                Coefs[i - 1] = LVREV_GainPolyTable[Index][i];
            }
            Coefs[4] = 0;

            Gain2 = LVM_Polynomial(3, Coefs, T60); /* Q.24 result */

            /* Linear Interpolate the gain */
            Gain = Gain1 + (((Gain2 - Gain1) * Dist) / (Tot_Dist));
        }

        /*
         * Get the inverse of gain: Q.15
         * Gain is mostly above one except few cases, take only gains above 1
         */
        if (Gain < 1) {
            pPrivate->Gain = 1;
        } else {
            pPrivate->Gain = 1 / Gain;
        }

        Index_FLOAT = 100.0f / (LVM_FLOAT)(100 + pPrivate->NewParams.Level);
        pPrivate->Gain = pPrivate->Gain * Index_FLOAT;
        pPrivate->GainMixer.Target = (pPrivate->Gain * Index_FLOAT) / 2;
    }

    /*
     * Update the all pass comb filter coefficient
     */
    if ((pPrivate->NewParams.Density != pPrivate->CurrentParams.Density) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_INT16 i;
        LVM_FLOAT b = (LVM_FLOAT)pPrivate->NewParams.Density * LVREV_B_8_on_1000;

        for (i = 0; i < 4; i++) {
            pPrivate->Mixer_SGFeedback[i].Target = b;
            pPrivate->Mixer_SGFeedforward[i].Target = b;
        }
    }

    /*
     * Update the bypass mixer time constant
     */
    if ((pPrivate->NewParams.SampleRate != pPrivate->CurrentParams.SampleRate) ||
        (pPrivate->bFirstControl == LVM_TRUE)) {
        LVM_UINT16 NumChannels = 1; /* Assume MONO format */
        LVM_FLOAT Alpha;

        Alpha = LVM_Mixer_TimeConstant(LVREV_FEEDBACKMIXER_TC,
                                       LVM_GetFsFromTable(pPrivate->NewParams.SampleRate),
                                       NumChannels);
        pPrivate->FeedbackMixer[0].Alpha = Alpha;
        pPrivate->FeedbackMixer[1].Alpha = Alpha;
        pPrivate->FeedbackMixer[2].Alpha = Alpha;
        pPrivate->FeedbackMixer[3].Alpha = Alpha;

        NumChannels = 2; /* Always stereo output */
        pPrivate->BypassMixer.Alpha1 = LVM_Mixer_TimeConstant(
                LVREV_BYPASSMIXER_TC, LVM_GetFsFromTable(pPrivate->NewParams.SampleRate),
                NumChannels);
        pPrivate->BypassMixer.Alpha2 = pPrivate->BypassMixer.Alpha1;
        pPrivate->GainMixer.Alpha = pPrivate->BypassMixer.Alpha1;
    }

    /*
     * Update the bypass mixer targets
     */
    if ((pPrivate->NewParams.Level != pPrivate->CurrentParams.Level) &&
        (pPrivate->NewParams.OperatingMode == LVM_MODE_ON)) {
        pPrivate->BypassMixer.Target2 = (LVM_FLOAT)(pPrivate->NewParams.Level) / 100.0f;
        pPrivate->BypassMixer.Target1 = 0x00000000;
        if ((pPrivate->NewParams.Level == 0) && (pPrivate->bFirstControl == LVM_FALSE)) {
            pPrivate->BypassMixer.CallbackSet2 = LVM_TRUE;
        }
        if (pPrivate->NewParams.Level != 0) {
            pPrivate->bDisableReverb = LVM_FALSE;
        }
    }

    if (pPrivate->NewParams.OperatingMode != pPrivate->CurrentParams.OperatingMode) {
        if (pPrivate->NewParams.OperatingMode == LVM_MODE_ON) {
            pPrivate->BypassMixer.Target2 = (LVM_FLOAT)(pPrivate->NewParams.Level) / 100.0f;
            pPrivate->BypassMixer.Target1 = 0x00000000;

            pPrivate->BypassMixer.CallbackSet2 = LVM_FALSE;
            OperatingMode = LVM_MODE_ON;
            if (pPrivate->NewParams.Level == 0) {
                pPrivate->bDisableReverb = LVM_TRUE;
            } else {
                pPrivate->bDisableReverb = LVM_FALSE;
            }
        } else if (pPrivate->bFirstControl == LVM_FALSE) {
            pPrivate->BypassMixer.Target2 = 0x00000000;
            pPrivate->BypassMixer.Target1 = 0x00000000;
            pPrivate->BypassMixer.CallbackSet2 = LVM_TRUE;
            pPrivate->GainMixer.Target = 0.03125f;
            OperatingMode = LVM_MODE_ON;
        } else {
            OperatingMode = LVM_MODE_OFF;
        }
    }

    /*  If it is the first call to ApplyNew settings force the current to the target \
        to begin immediate playback of the effect */
    if (pPrivate->bFirstControl == LVM_TRUE) {
        pPrivate->BypassMixer.Current1 = pPrivate->BypassMixer.Target1;
        pPrivate->BypassMixer.Current2 = pPrivate->BypassMixer.Target2;
    }

    /*
     * Copy the new parameters
     */
    pPrivate->CurrentParams = pPrivate->NewParams;
    pPrivate->CurrentParams.OperatingMode = OperatingMode;

    /*
     * Update flag
     */
    if (pPrivate->bFirstControl == LVM_TRUE) {
        pPrivate->bFirstControl = LVM_FALSE;
    }

    return LVREV_SUCCESS;
}
/****************************************************************************************/
/*                                                                                      */
/* FUNCTION:                BypassMixer_Callback                                        */
/*                                                                                      */
/* DESCRIPTION:                                                                         */
/*  Controls the On to Off operating mode transition                                    */
/*                                                                                      */
/* PARAMETERS:                                                                          */
/*  pPrivate                Pointer to the instance private parameters                  */
/*                                                                                      */
/* RETURNS:                                                                             */
/*  LVREV_Success           Succeeded                                                   */
/*  LVREV_NULLADDRESS       When pPrivate is NULL                                       */
/*                                                                                      */
/* NOTES:                                                                               */
/*                                                                                      */
/****************************************************************************************/
LVM_INT32 BypassMixer_Callback(void* pCallbackData, void* pGeneralPurpose,
                               LVM_INT16 GeneralPurpose) {
    LVREV_Instance_st* pLVREV_Private = (LVREV_Instance_st*)pCallbackData;

    /*
     * Avoid build warnings
     */
    (void)pGeneralPurpose;
    (void)GeneralPurpose;

    /*
     * Turn off
     */
    pLVREV_Private->CurrentParams.OperatingMode = LVM_MODE_OFF;
    pLVREV_Private->bDisableReverb = LVM_TRUE;
    LVREV_ClearAudioBuffers((LVREV_Handle_t)pCallbackData);

    return 0;
}

/* End of file */
