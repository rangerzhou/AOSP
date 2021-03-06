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

/************************************************************************************/
/*                                                                                  */
/*  Includes                                                                        */
/*                                                                                  */
/************************************************************************************/

#include "LVCS.h"
#include "LVCS_Private.h"
#include "VectorArithmetic.h"
#include "CompLim.h"

/************************************************************************************/
/*                                                                                  */
/* FUNCTION:                LVCS_Process_CS                                         */
/*                                                                                  */
/* DESCRIPTION:                                                                     */
/*  Process function for the Concert Sound module based on the following block      */
/*  diagram:                                                                        */
/*            _________    ________    _____    _______     ___   ______            */
/*           |         |  |        |  |     |  |       |   |   | |      |           */
/*     ----->| Stereo  |->| Reverb |->| Equ |->| Alpha |-->| + |-| Gain |---->      */
/*        |  | Enhance |  |________|  |_____|  |_______|   |___| |______|           */
/*        |  |_________|                                     |                      */
/*        |                                 ___________      |                      */
/*        |                                |           |     |                      */
/*        |------------------------------->| 1 - Alpha |-----|                      */
/*                                         |___________|                            */
/*                                                                                  */
/*  The Stereo Enhancer, Reverb and Equaliser blocks are each configured to have    */
/*  their gain to give a near peak to peak output (-0.1dBFS) with a worst case      */
/*  input signal. The gains of these blocks are re-combined in the Alpha mixer and  */
/*  the gain block folloing the sum.                                                */
/*                                                                                  */
/*  The processing uses the output buffer for data storage after each processing    */
/*  block. When processing is inplace a copy of the input signal is made in scratch */
/*  memory for the 1-Alpha path.                                                    */
/*                                                                                  */
/*                                                                                  */
/* PARAMETERS:                                                                      */
/*  hInstance               Instance handle                                         */
/*  pInData                 Pointer to the input data                               */
/*  pOutData                Pointer to the output data                              */
/*  NumSamples              Number of samples in the input buffer                   */
/*                                                                                  */
/* RETURNS:                                                                         */
/*  LVCS_Success            Succeeded                                               */
/*                                                                                  */
/* NOTES:                                                                           */
/*                                                                                  */
/************************************************************************************/
LVCS_ReturnStatus_en LVCS_Process_CS(LVCS_Handle_t hInstance, const LVM_FLOAT* pInData,
                                     LVM_FLOAT* pOutData, LVM_UINT16 NumSamples) {
    const LVM_FLOAT* pInput;
    LVCS_Instance_t* pInstance = (LVCS_Instance_t*)hInstance;
    LVM_FLOAT* pScratch;
    LVCS_ReturnStatus_en err;
    LVM_FLOAT* pStIn;
    LVM_INT32 channels = pInstance->Params.NrChannels;
#define NrFrames NumSamples  // alias for clarity

    pScratch = (LVM_FLOAT*)pInstance->pScratch;

    /*
     * Check if the processing is inplace
     */
    /*
     * The pInput buffer holds the first 2 (Left, Right) channels information.
     * Hence the memory required by this buffer is 2 * NumFrames.
     * The Concert Surround module carries out processing only on L, R.
     */
    pInput = pScratch + (2 * NrFrames);
    pStIn = pScratch + ((LVCS_SCRATCHBUFFERS - 2) * NrFrames);
    if (channels == FCC_1) {
        Copy_Float((LVM_FLOAT*)pInData, (LVM_FLOAT*)pInput, (LVM_INT16)NrFrames);
        Copy_Float((LVM_FLOAT*)pInput, (LVM_FLOAT*)pStIn, (LVM_INT16)NrFrames);
    } else {
        /* The first two channel data is extracted from the input data and
         * copied into pInput buffer
         */
        Copy_Float_Mc_Stereo((LVM_FLOAT*)pInData, (LVM_FLOAT*)pInput, NrFrames, channels);
        Copy_Float((LVM_FLOAT*)pInput, (LVM_FLOAT*)pStIn, (LVM_INT16)(FCC_2 * NrFrames));
    }
    /*
     * Call the stereo enhancer
     */
    err = LVCS_StereoEnhancer(hInstance, /* Instance handle */
                              pStIn,     /* Pointer to the input data */
                              pOutData,  /* Pointer to the output data */
                              NrFrames); /* Number of frames to process */

    /*
     * Call the reverb generator
     */
    err = LVCS_ReverbGenerator(hInstance,   /* Instance handle */
                               pOutData,    /* Pointer to the input data */
                               pOutData,    /* Pointer to the output data */
                               NumSamples); /* Number of samples to process */

    /*
     * Call the equaliser
     */
    err = LVCS_Equaliser(hInstance,   /* Instance handle */
                         pOutData,    /* Pointer to the input data */
                         NumSamples); /* Number of samples to process */

    /*
     * Call the bypass mixer
     */
    err = LVCS_BypassMixer(hInstance,   /* Instance handle */
                           pOutData,    /* Pointer to the processed data */
                           pInput,      /* Pointer to the input (unprocessed) data */
                           pOutData,    /* Pointer to the output data */
                           NumSamples); /* Number of samples to process */

    if (err != LVCS_SUCCESS) {
        return err;
    }

    return (LVCS_SUCCESS);
}
/************************************************************************************/
/*                                                                                  */
/* FUNCTION:                LVCS_Process                                            */
/*                                                                                  */
/* DESCRIPTION:                                                                     */
/*  Process function for the Concert Sound module. The implementation supports two  */
/*  variants of the algorithm, one for headphones and one for mobile speakers.      */
/*                                                                                  */
/*  Data can be processed in two formats, stereo or mono-in-stereo. Data in mono    */
/*  format is not supported, the calling routine must convert the mono stream to    */
/*  mono-in-stereo.                                                                 */
/*                                                                                  */
/*                                                                                  */
/* PARAMETERS:                                                                      */
/*  hInstance               Instance handle                                         */
/*  pInData                 Pointer to the input data                               */
/*  pOutData                Pointer to the output data                              */
/*  NumSamples              Number of samples in the input buffer                   */
/*                                                                                  */
/* RETURNS:                                                                         */
/*  LVCS_Success            Succeeded                                               */
/*  LVCS_TooManySamples     NumSamples was larger than the maximum block size       */
/*                                                                                  */
/* NOTES:                                                                           */
/*                                                                                  */
/************************************************************************************/
LVCS_ReturnStatus_en LVCS_Process(LVCS_Handle_t hInstance, const LVM_FLOAT* pInData,
                                  LVM_FLOAT* pOutData, LVM_UINT16 NumSamples) {
    LVCS_Instance_t* pInstance = (LVCS_Instance_t*)hInstance;
    LVCS_ReturnStatus_en err;
    /*Extract number of Channels info*/
    LVM_INT32 channels = pInstance->Params.NrChannels;
    LVM_UINT16 destNumSamples = (channels == FCC_1) ? NumSamples : FCC_2 * NumSamples;
    LVM_INT32 compGainInterval =
            (channels == FCC_1) ? LVCS_COMPGAINFRAME : FCC_2 * LVCS_COMPGAINFRAME;
#define NrFrames NumSamples  // alias for clarity
    /*
     * Check the number of samples is not too large
     */
    if (NumSamples > pInstance->Capabilities.MaxBlockSize) {
        return (LVCS_TOOMANYSAMPLES);
    }

    /*
     * Check if the algorithm is enabled
     */
    if (pInstance->Params.OperatingMode != LVCS_OFF) {
        LVM_FLOAT* pStereoOut;
        /*
         * LVCS_Process_CS uses output buffer to store intermediate outputs of StereoEnhancer,
         * Equalizer, ReverbGenerator and BypassMixer.
         * So, to avoid i/o data overlapping, when i/o buffers are common, use scratch buffer
         * to store intermediate outputs.
         */
        if (pOutData == pInData) {
            /*
             * Scratch memory is used in 4 chunks of (2 * NrFrames) size.
             * First chunk of memory is used by LVCS_StereoEnhancer and LVCS_ReverbGenerator,
             * second and fourth are used as input buffers by pInput and pStIn in LVCS_Process_CS.
             * Hence, pStereoOut is pointed to use unused third portion of scratch memory.
             */
            pStereoOut = (LVM_FLOAT*)pInstance->pScratch + ((LVCS_SCRATCHBUFFERS - 4) * NrFrames);
        } else {
            pStereoOut = pOutData;
        }

        /*
         * Call CS process function
         */
        err = LVCS_Process_CS(hInstance, pInData, pStereoOut, NrFrames);

        /*
         * Compress to reduce expansion effect of Concert Sound and correct volume
         * differences for difference settings. Not applied in test modes
         */
        if ((pInstance->Params.OperatingMode == LVCS_ON) &&
            (pInstance->Params.CompressorMode == LVM_MODE_ON)) {
            LVM_FLOAT Gain = pInstance->VolCorrect.CompMin;
            LVM_FLOAT Current1;

            Current1 = LVC_Mixer_GetCurrent(&pInstance->BypassMix.Mixer_Instance.MixerStream[0]);
            Gain = (LVM_FLOAT)(pInstance->VolCorrect.CompMin -
                               (((LVM_FLOAT)pInstance->VolCorrect.CompMin * (Current1))) +
                               (((LVM_FLOAT)pInstance->VolCorrect.CompFull * (Current1))));

            if (NumSamples < LVCS_COMPGAINFRAME) {
                NonLinComp_Float(Gain, /* Compressor gain setting */
                                 pStereoOut, pStereoOut, (LVM_INT32)destNumSamples);
            } else {
                LVM_FLOAT GainStep;
                LVM_FLOAT FinalGain;
                LVM_INT16 SampleToProcess = NumSamples;
                LVM_FLOAT* pOutPtr;

                /* Large changes in Gain can cause clicks in output
                   Split data into small blocks and use interpolated gain values */

                GainStep = (LVM_FLOAT)(((Gain - pInstance->CompressGain) * LVCS_COMPGAINFRAME) /
                                       NumSamples);

                if ((GainStep == 0) && (pInstance->CompressGain < Gain)) {
                    GainStep = 1;
                } else {
                    if ((GainStep == 0) && (pInstance->CompressGain > Gain)) {
                        GainStep = -1;
                    }
                }

                FinalGain = Gain;
                Gain = pInstance->CompressGain;
                pOutPtr = pStereoOut;

                while (SampleToProcess > 0) {
                    Gain = (LVM_FLOAT)(Gain + GainStep);
                    if ((GainStep > 0) && (FinalGain <= Gain)) {
                        Gain = FinalGain;
                        GainStep = 0;
                    }

                    if ((GainStep < 0) && (FinalGain > Gain)) {
                        Gain = FinalGain;
                        GainStep = 0;
                    }

                    if (SampleToProcess > LVCS_COMPGAINFRAME) {
                        NonLinComp_Float(Gain, /* Compressor gain setting */
                                         pOutPtr, pOutPtr, compGainInterval);
                        pOutPtr += compGainInterval;
                        SampleToProcess = (LVM_INT16)(SampleToProcess - LVCS_COMPGAINFRAME);
                    } else {
                        NonLinComp_Float(Gain, /* Compressor gain setting */
                                         pOutPtr, pOutPtr,
                                         (channels == FCC_1)
                                                 ? (LVM_INT32)(SampleToProcess)
                                                 : (LVM_INT32)(FCC_2 * SampleToProcess));
                        SampleToProcess = 0;
                    }
                }
            }

            /* Store gain value*/
            pInstance->CompressGain = Gain;
        }

        if (pInstance->bInOperatingModeTransition == LVM_TRUE) {
            /*
             * Re-init bypass mix when timer has completed
             */
            if ((pInstance->bTimerDone == LVM_TRUE) &&
                (pInstance->BypassMix.Mixer_Instance.MixerStream[1].CallbackSet == 0)) {
                err = LVCS_BypassMixInit(hInstance, &pInstance->Params);

                if (err != LVCS_SUCCESS) {
                    return err;
                }

            } else {
                LVM_Timer(&pInstance->TimerInstance, (LVM_INT16)NumSamples);
            }
        }
        Copy_Float_Stereo_Mc(pInData, (const LVM_FLOAT*)pStereoOut, pOutData, NrFrames, channels);
    } else {
        if (pInData != pOutData) {
            /*
             * The algorithm is disabled so just copy the data
             */
            Copy_Float((LVM_FLOAT*)pInData,               /* Source */
                       (LVM_FLOAT*)pOutData,              /* Destination */
                       (LVM_INT16)(channels * NrFrames)); /* All Channels*/
        }
    }

    return (LVCS_SUCCESS);
}
