/*
 * Copyright (C) 2011 The Android Open Source Project
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
#include <assert.h>
#include <inttypes.h>
#include <iterator>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <audio_utils/channels.h>
#include <audio_utils/primitives.h>
#include <log/log.h>
#include <system/audio.h>

#include "EffectBundle.h"
#include "LVM_Private.h"

#ifdef VERY_VERY_VERBOSE_LOGGING
#define ALOGVV ALOGV
#else
#define ALOGVV(a...) \
    do {             \
    } while (false)
#endif

#define CHECK_ARG(cond)                                      \
    {                                                        \
        if (!(cond)) {                                       \
            ALOGE("\tLVM_ERROR : Invalid argument: " #cond); \
            return -EINVAL;                                  \
        }                                                    \
    }

#define LVM_ERROR_CHECK(LvmStatus, callingFunc, calledFunc)             \
    {                                                                   \
        if ((LvmStatus) == LVM_NULLADDRESS) {                           \
            ALOGE("\tLVM_ERROR : Parameter error - "                    \
                  "null pointer returned by %s in %s\n\n\n\n",          \
                  callingFunc, calledFunc);                             \
        }                                                               \
        if ((LvmStatus) == LVM_ALIGNMENTERROR) {                        \
            ALOGE("\tLVM_ERROR : Parameter error - "                    \
                  "bad alignment returned by %s in %s\n\n\n\n",         \
                  callingFunc, calledFunc);                             \
        }                                                               \
        if ((LvmStatus) == LVM_INVALIDNUMSAMPLES) {                     \
            ALOGE("\tLVM_ERROR : Parameter error - "                    \
                  "bad number of samples returned by %s in %s\n\n\n\n", \
                  callingFunc, calledFunc);                             \
        }                                                               \
        if ((LvmStatus) == LVM_OUTOFRANGE) {                            \
            ALOGE("\tLVM_ERROR : Parameter error - "                    \
                  "out of range returned by %s in %s\n",                \
                  callingFunc, calledFunc);                             \
        }                                                               \
    }

struct lvmConfigParams_t {
    int samplingFreq = 44100;
    int nrChannels = 2;
    int chMask = AUDIO_CHANNEL_OUT_STEREO;
    int vcBal = 0;
    int fChannels = 2;
    bool monoMode = false;
    int bassEffectLevel = 0;
    int eqPresetLevel = 0;
    int frameLength = 256;
    int trebleEffectLevel = 0;
    LVM_BE_Mode_en bassEnable = LVM_BE_OFF;
    LVM_TE_Mode_en trebleEnable = LVM_TE_OFF;
    LVM_EQNB_Mode_en eqEnable = LVM_EQNB_OFF;
    LVM_Mode_en csEnable = LVM_MODE_OFF;
};

constexpr audio_channel_mask_t lvmConfigChMask[] = {
        AUDIO_CHANNEL_OUT_MONO,
        AUDIO_CHANNEL_OUT_STEREO,
        AUDIO_CHANNEL_OUT_2POINT1,
        AUDIO_CHANNEL_OUT_2POINT0POINT2,
        AUDIO_CHANNEL_OUT_QUAD,
        AUDIO_CHANNEL_OUT_QUAD_BACK,
        AUDIO_CHANNEL_OUT_QUAD_SIDE,
        AUDIO_CHANNEL_OUT_SURROUND,
        AUDIO_CHANNEL_INDEX_MASK_4,
        AUDIO_CHANNEL_OUT_2POINT1POINT2,
        AUDIO_CHANNEL_OUT_3POINT0POINT2,
        AUDIO_CHANNEL_OUT_PENTA,
        AUDIO_CHANNEL_INDEX_MASK_5,
        AUDIO_CHANNEL_OUT_3POINT1POINT2,
        AUDIO_CHANNEL_OUT_5POINT1,
        AUDIO_CHANNEL_OUT_5POINT1_BACK,
        AUDIO_CHANNEL_OUT_5POINT1_SIDE,
        AUDIO_CHANNEL_INDEX_MASK_6,
        AUDIO_CHANNEL_OUT_6POINT1,
        AUDIO_CHANNEL_INDEX_MASK_7,
        AUDIO_CHANNEL_OUT_5POINT1POINT2,
        AUDIO_CHANNEL_OUT_7POINT1,
        AUDIO_CHANNEL_INDEX_MASK_8,
        AUDIO_CHANNEL_INDEX_MASK_9,
        AUDIO_CHANNEL_INDEX_MASK_10,
        AUDIO_CHANNEL_INDEX_MASK_11,
        AUDIO_CHANNEL_INDEX_MASK_12,
        AUDIO_CHANNEL_INDEX_MASK_13,
        AUDIO_CHANNEL_INDEX_MASK_14,
        AUDIO_CHANNEL_INDEX_MASK_15,
        AUDIO_CHANNEL_INDEX_MASK_16,
        AUDIO_CHANNEL_INDEX_MASK_17,
        AUDIO_CHANNEL_INDEX_MASK_18,
        AUDIO_CHANNEL_INDEX_MASK_19,
        AUDIO_CHANNEL_INDEX_MASK_20,
        AUDIO_CHANNEL_INDEX_MASK_21,
        AUDIO_CHANNEL_INDEX_MASK_22,
        AUDIO_CHANNEL_INDEX_MASK_23,
        AUDIO_CHANNEL_INDEX_MASK_24,
};

void printUsage() {
    printf("\nUsage: ");
    printf("\n     <executable> -i:<input_file> -o:<out_file> [options]\n");
    printf("\nwhere, \n     <inputfile>  is the input file name");
    printf("\n                  on which LVM effects are applied");
    printf("\n     <outputfile> processed output file");
    printf("\n     and options are mentioned below");
    printf("\n");
    printf("\n     -help (or) -h");
    printf("\n           Prints this usage information");
    printf("\n");
    printf("\n     -chMask:<channel_mask>\n");
    printf("\n         0  - AUDIO_CHANNEL_OUT_MONO");
    printf("\n         1  - AUDIO_CHANNEL_OUT_STEREO");
    printf("\n         2  - AUDIO_CHANNEL_OUT_2POINT1");
    printf("\n         3  - AUDIO_CHANNEL_OUT_2POINT0POINT2");
    printf("\n         4  - AUDIO_CHANNEL_OUT_QUAD");
    printf("\n         5  - AUDIO_CHANNEL_OUT_QUAD_BACK");
    printf("\n         6  - AUDIO_CHANNEL_OUT_QUAD_SIDE");
    printf("\n         7  - AUDIO_CHANNEL_OUT_SURROUND");
    printf("\n         8  - canonical channel index mask for 4 ch: (1 << 4) - 1");
    printf("\n         9  - AUDIO_CHANNEL_OUT_2POINT1POINT2");
    printf("\n         10 - AUDIO_CHANNEL_OUT_3POINT0POINT2");
    printf("\n         11 - AUDIO_CHANNEL_OUT_PENTA");
    printf("\n         12 - canonical channel index mask for 5 ch: (1 << 5) - 1");
    printf("\n         13 - AUDIO_CHANNEL_OUT_3POINT1POINT2");
    printf("\n         14 - AUDIO_CHANNEL_OUT_5POINT1");
    printf("\n         15 - AUDIO_CHANNEL_OUT_5POINT1_BACK");
    printf("\n         16 - AUDIO_CHANNEL_OUT_5POINT1_SIDE");
    printf("\n         17 - canonical channel index mask for 6 ch: (1 << 6) - 1");
    printf("\n         18 - AUDIO_CHANNEL_OUT_6POINT1");
    printf("\n         19 - canonical channel index mask for 7 ch: (1 << 7) - 1");
    printf("\n         20 - AUDIO_CHANNEL_OUT_5POINT1POINT2");
    printf("\n         21 - AUDIO_CHANNEL_OUT_7POINT1");
    printf("\n         22 - canonical channel index mask for 8 ch: (1 << 8) - 1");
    printf("\n         default 0");
    printf("\n     -vcBal:<Left Right Balance control in dB [-96 to 96 dB]>");
    printf("\n            -ve values reduce Right channel while +ve value reduces Left channel");
    printf("\n                 default 0");
    printf("\n     -fch:<file_channels> (1 through 8)\n\n");
    printf("\n     -M");
    printf("\n           Mono mode (force all input audio channels to be identical)");
    printf("\n     -basslvl:<effect_level>");
    printf("\n           A value that ranges between %d - %d default 0", LVM_BE_MIN_EFFECTLEVEL,
           LVM_BE_MAX_EFFECTLEVEL);
    printf("\n");
    printf("\n     -eqPreset:<preset Value>");
    const size_t numPresetLvls = std::size(gEqualizerPresets);
    for (size_t i = 0; i < numPresetLvls; ++i) {
        printf("\n           %zu - %s", i, gEqualizerPresets[i].name);
    }
    printf("\n           default - 0");
    printf("\n     -bE ");
    printf("\n           Enable Dynamic Bass Enhancement");
    printf("\n");
    printf("\n     -tE ");
    printf("\n           Enable Treble Boost");
    printf("\n");
    printf("\n     -csE ");
    printf("\n           Enable Concert Surround");
    printf("\n");
    printf("\n     -eqE ");
    printf("\n           Enable Equalizer");
}

//----------------------------------------------------------------------------
// LvmBundle_init()
//----------------------------------------------------------------------------
// Purpose: Initialize engine with default configuration, creates instance
// with all effects disabled.
//
// Inputs:
//  pContext:   effect engine context
//
// Outputs:
//
//----------------------------------------------------------------------------

int LvmBundle_init(struct EffectContext* pContext, LVM_ControlParams_t* params) {
    ALOGV("\tLvmBundle_init start");

    pContext->config.inputCfg.accessMode = EFFECT_BUFFER_ACCESS_READ;
    pContext->config.inputCfg.channels = AUDIO_CHANNEL_OUT_STEREO;
    pContext->config.inputCfg.format = EFFECT_BUFFER_FORMAT;
    pContext->config.inputCfg.samplingRate = 44100;
    pContext->config.inputCfg.bufferProvider.getBuffer = NULL;
    pContext->config.inputCfg.bufferProvider.releaseBuffer = NULL;
    pContext->config.inputCfg.bufferProvider.cookie = NULL;
    pContext->config.inputCfg.mask = EFFECT_CONFIG_ALL;
    pContext->config.outputCfg.accessMode = EFFECT_BUFFER_ACCESS_ACCUMULATE;
    pContext->config.outputCfg.channels = AUDIO_CHANNEL_OUT_STEREO;
    pContext->config.outputCfg.format = EFFECT_BUFFER_FORMAT;
    pContext->config.outputCfg.samplingRate = 44100;
    pContext->config.outputCfg.bufferProvider.getBuffer = NULL;
    pContext->config.outputCfg.bufferProvider.releaseBuffer = NULL;
    pContext->config.outputCfg.bufferProvider.cookie = NULL;
    pContext->config.outputCfg.mask = EFFECT_CONFIG_ALL;

    if (pContext->pBundledContext->hInstance != NULL) {
        ALOGV("\tLvmBundle_init pContext->pBassBoost != NULL "
              "-> Calling pContext->pBassBoost->free()");
        LVM_DelInstanceHandle(&pContext->pBundledContext->hInstance);

        ALOGV("\tLvmBundle_init pContext->pBassBoost != NULL "
              "-> Called pContext->pBassBoost->free()");
    }

    LVM_ReturnStatus_en LvmStatus = LVM_SUCCESS; /* Function call status */
    LVM_InstParams_t InstParams;                 /* Instance parameters */
    LVM_EQNB_BandDef_t BandDefs[MAX_NUM_BANDS];  /* Equaliser band definitions */
    LVM_HeadroomParams_t HeadroomParams;         /* Headroom parameters */
    LVM_HeadroomBandDef_t HeadroomBandDef[LVM_HEADROOM_MAX_NBANDS];

    /* Set the capabilities */
    InstParams.BufferMode = LVM_UNMANAGED_BUFFERS;
    InstParams.MaxBlockSize = MAX_CALL_SIZE;
    InstParams.EQNB_NumBands = MAX_NUM_BANDS;
    InstParams.PSA_Included = LVM_PSA_ON;

    LvmStatus = LVM_GetInstanceHandle(&pContext->pBundledContext->hInstance, &InstParams);

    LVM_ERROR_CHECK(LvmStatus, "LVM_GetInstanceHandle", "LvmBundle_init");
    if (LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tLvmBundle_init CreateInstance Successfully called "
          "LVM_GetInstanceHandle\n");

    /* Set the initial process parameters */
    /* General parameters */
    params->OperatingMode = LVM_MODE_ON;
    params->SampleRate = LVM_FS_44100;
    params->SourceFormat = LVM_STEREO;
    params->ChMask = AUDIO_CHANNEL_OUT_STEREO;
    params->SpeakerType = LVM_HEADPHONES;

    pContext->pBundledContext->SampleRate = LVM_FS_44100;

    /* Concert Sound parameters */
    params->VirtualizerOperatingMode = LVM_MODE_OFF;
    params->VirtualizerType = LVM_CONCERTSOUND;
    params->VirtualizerReverbLevel = 100;
    params->CS_EffectLevel = LVM_CS_EFFECT_NONE;

    /* N-Band Equaliser parameters */
    params->EQNB_OperatingMode = LVM_EQNB_ON;
    params->EQNB_NBands = FIVEBAND_NUMBANDS;
    params->pEQNB_BandDefinition = &BandDefs[0];

    for (int i = 0; i < FIVEBAND_NUMBANDS; i++) {
        BandDefs[i].Frequency = EQNB_5BandPresetsFrequencies[i];
        BandDefs[i].QFactor = EQNB_5BandPresetsQFactors[i];
        BandDefs[i].Gain = EQNB_5BandSoftPresets[i];
    }

    /* Volume Control parameters */
    params->VC_EffectLevel = 0;
    params->VC_Balance = 0;

    /* Treble Enhancement parameters */
    params->TE_OperatingMode = LVM_TE_OFF;
    params->TE_EffectLevel = 0;

    /* PSA Control parameters */
    params->PSA_Enable = LVM_PSA_OFF;
    params->PSA_PeakDecayRate = (LVM_PSA_DecaySpeed_en)0;

    /* Bass Enhancement parameters */
    params->BE_OperatingMode = LVM_BE_ON;
    params->BE_EffectLevel = 0;
    params->BE_CentreFreq = LVM_BE_CENTRE_90Hz;
    params->BE_HPF = LVM_BE_HPF_ON;

    /* PSA Control parameters */
    params->PSA_Enable = LVM_PSA_OFF;
    params->PSA_PeakDecayRate = LVM_PSA_SPEED_MEDIUM;

    /* Activate the initial settings */
    LvmStatus = LVM_SetControlParameters(pContext->pBundledContext->hInstance, params);

    LVM_ERROR_CHECK(LvmStatus, "LVM_SetControlParameters", "LvmBundle_init");
    if (LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tLvmBundle_init CreateInstance Successfully called "
          "LVM_SetControlParameters\n");

    /* Set the headroom parameters */
    HeadroomBandDef[0].Limit_Low = 20;
    HeadroomBandDef[0].Limit_High = 4999;
    HeadroomBandDef[0].Headroom_Offset = 0;
    HeadroomBandDef[1].Limit_Low = 5000;
    HeadroomBandDef[1].Limit_High = 24000;
    HeadroomBandDef[1].Headroom_Offset = 0;
    HeadroomParams.pHeadroomDefinition = &HeadroomBandDef[0];
    HeadroomParams.Headroom_OperatingMode = LVM_HEADROOM_ON;
    HeadroomParams.NHeadroomBands = 2;

    LvmStatus = LVM_SetHeadroomParams(pContext->pBundledContext->hInstance, &HeadroomParams);

    LVM_ERROR_CHECK(LvmStatus, "LVM_SetHeadroomParams", "LvmBundle_init");
    if (LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tLvmBundle_init CreateInstance Successfully called "
          "LVM_SetHeadroomParams\n");
    ALOGV("\tLvmBundle_init End");
    return 0;
} /* end LvmBundle_init */

int lvmCreate(struct EffectContext* pContext, lvmConfigParams_t* plvmConfigParams,
              LVM_ControlParams_t* params) {
    int ret = 0;
    pContext->pBundledContext = NULL;
    pContext->pBundledContext = (BundledEffectContext*)malloc(sizeof(struct BundledEffectContext));
    if (NULL == pContext->pBundledContext) {
        return -EINVAL;
    }

    pContext->pBundledContext->SessionNo = 0;
    pContext->pBundledContext->SessionId = 0;
    pContext->pBundledContext->hInstance = NULL;
    pContext->pBundledContext->bVolumeEnabled = LVM_FALSE;
    pContext->pBundledContext->bEqualizerEnabled = LVM_FALSE;
    pContext->pBundledContext->bBassEnabled = LVM_FALSE;
    pContext->pBundledContext->bBassTempDisabled = LVM_FALSE;
    pContext->pBundledContext->bVirtualizerEnabled = LVM_FALSE;
    pContext->pBundledContext->bVirtualizerTempDisabled = LVM_FALSE;
    pContext->pBundledContext->nOutputDevice = AUDIO_DEVICE_NONE;
    pContext->pBundledContext->nVirtualizerForcedDevice = AUDIO_DEVICE_NONE;
    pContext->pBundledContext->NumberEffectsEnabled = 0;
    pContext->pBundledContext->NumberEffectsCalled = 0;
    pContext->pBundledContext->firstVolume = LVM_TRUE;
    pContext->pBundledContext->volume = 0;

    /* Saved strength is used to return the exact strength that was used in the
     * set to the get
     * because we map the original strength range of 0:1000 to 1:15, and this will
     * avoid
     * quantisation like effect when returning
     */
    pContext->pBundledContext->BassStrengthSaved = 0;
    pContext->pBundledContext->VirtStrengthSaved = 0;
    pContext->pBundledContext->CurPreset = PRESET_CUSTOM;
    pContext->pBundledContext->levelSaved = 0;
    pContext->pBundledContext->bMuteEnabled = LVM_FALSE;
    pContext->pBundledContext->bStereoPositionEnabled = LVM_FALSE;
    pContext->pBundledContext->positionSaved = 0;
    pContext->pBundledContext->workBuffer = NULL;
    pContext->pBundledContext->frameCount = -1;
    pContext->pBundledContext->SamplesToExitCountVirt = 0;
    pContext->pBundledContext->SamplesToExitCountBb = 0;
    pContext->pBundledContext->SamplesToExitCountEq = 0;
    for (int i = 0; i < FIVEBAND_NUMBANDS; i++) {
        pContext->pBundledContext->bandGaindB[i] = EQNB_5BandSoftPresets[i];
    }
    pContext->config.inputCfg.channels = plvmConfigParams->nrChannels;
    ALOGV("\tEffectCreate - Calling LvmBundle_init");
    ret = LvmBundle_init(pContext, params);

    if (ret < 0) {
        ALOGE("\tLVM_ERROR : lvmCreate() Bundle init failed");
        return ret;
    }
    return 0;
}

int lvmControl(struct EffectContext* pContext, lvmConfigParams_t* plvmConfigParams,
               LVM_ControlParams_t* params) {
    LVM_ReturnStatus_en LvmStatus = LVM_SUCCESS; /* Function call status */

    /* Set the initial process parameters */
    /* General parameters */
    params->OperatingMode = LVM_MODE_ON;
    params->SpeakerType = LVM_HEADPHONES;

    params->ChMask = plvmConfigParams->chMask;
    params->NrChannels = plvmConfigParams->nrChannels;
    if (params->NrChannels == 1) {
        params->SourceFormat = LVM_MONO;
    } else if (params->NrChannels == 2) {
        params->SourceFormat = LVM_STEREO;
    } else if (params->NrChannels > FCC_2 && params->NrChannels <= FCC_24) {
        params->SourceFormat = LVM_MULTICHANNEL;
    } else {
        return -EINVAL;
    }
    params->SampleRate = lvmFsForSampleRate(plvmConfigParams->samplingFreq);
    if (params->SampleRate == LVM_FS_INVALID) {
        ALOGE("lvmControl invalid sampling rate %d", plvmConfigParams->samplingFreq);
        return -EINVAL;
    }

    /* Concert Sound parameters */
    params->VirtualizerOperatingMode = plvmConfigParams->csEnable;
    params->VirtualizerType = LVM_CONCERTSOUND;
    params->VirtualizerReverbLevel = 100;
    params->CS_EffectLevel = LVM_CS_EFFECT_NONE;

    /* N-Band Equaliser parameters */
    const int eqPresetLevel = plvmConfigParams->eqPresetLevel;
    LVM_EQNB_BandDef_t BandDefs[MAX_NUM_BANDS]; /* Equaliser band definitions */
    for (int i = 0; i < FIVEBAND_NUMBANDS; i++) {
        BandDefs[i].Frequency = EQNB_5BandPresetsFrequencies[i];
        BandDefs[i].QFactor = EQNB_5BandPresetsQFactors[i];
        BandDefs[i].Gain = EQNB_5BandSoftPresets[(FIVEBAND_NUMBANDS * eqPresetLevel) + i];
    }
    params->EQNB_OperatingMode = plvmConfigParams->eqEnable;
    // Caution: raw pointer to stack data, stored in instance by LVM_SetControlParameters.
    params->pEQNB_BandDefinition = &BandDefs[0];

    /* Volume Control parameters */
    params->VC_EffectLevel = 0;
    params->VC_Balance = plvmConfigParams->vcBal;

    /* Treble Enhancement parameters */
    params->TE_OperatingMode = plvmConfigParams->trebleEnable;
    params->TE_EffectLevel = plvmConfigParams->trebleEffectLevel;

    /* PSA Control parameters */
    params->PSA_Enable = LVM_PSA_ON;

    /* Bass Enhancement parameters */
    params->BE_OperatingMode = plvmConfigParams->bassEnable;

    /* Activate the initial settings */
    LvmStatus = LVM_SetControlParameters(pContext->pBundledContext->hInstance, params);

    LVM_ERROR_CHECK(LvmStatus, "LVM_SetControlParameters", "LvmBundle_init");
    if (LvmStatus != LVM_SUCCESS) return -EINVAL;

    LvmStatus = LVM_ApplyNewSettings(pContext->pBundledContext->hInstance);

    if (LvmStatus != LVM_SUCCESS) return -EINVAL;

    return 0;
}

int lvmExecute(float* floatIn, float* floatOut, struct EffectContext* pContext,
               lvmConfigParams_t* plvmConfigParams) {
    const int frameLength = plvmConfigParams->frameLength;
    return LVM_Process(pContext->pBundledContext->hInstance, /* Instance handle */
                       floatIn,                              /* Input buffer */
                       floatOut,                             /* Output buffer */
                       (LVM_UINT16)frameLength,              /* Number of samples to read */
                       0);                                   /* Audio Time */
}

int lvmMainProcess(EffectContext* pContext, LVM_ControlParams_t* pParams,
                   lvmConfigParams_t* plvmConfigParams, FILE* finp, FILE* fout) {
    int errCode = lvmControl(pContext, plvmConfigParams, pParams);
    if (errCode) {
        ALOGE("Error: lvmControl returned with %d\n", errCode);
        return errCode;
    }

    const int channelCount = plvmConfigParams->nrChannels;
    const int frameLength = plvmConfigParams->frameLength;
    const int frameSize = channelCount * sizeof(float);  // processing size
    const int ioChannelCount = plvmConfigParams->fChannels;
    const int ioFrameSize = ioChannelCount * sizeof(short);  // file load size
    const int maxChannelCount = std::max(channelCount, ioChannelCount);

    std::vector<short> in(frameLength * maxChannelCount);
    std::vector<short> out(frameLength * maxChannelCount);
    std::vector<float> floatIn(frameLength * channelCount);
    std::vector<float> floatOut(frameLength * channelCount);

    int frameCounter = 0;
    while (fread(in.data(), ioFrameSize, frameLength, finp) == (size_t)frameLength) {
        if (ioChannelCount != channelCount) {
            adjust_channels(in.data(), ioChannelCount, in.data(), channelCount, sizeof(short),
                            frameLength * ioFrameSize);
        }
        memcpy_to_float_from_i16(floatIn.data(), in.data(), frameLength * channelCount);

        // Mono mode will replicate the first channel to all other channels.
        // This ensures all audio channels are identical. This is useful for testing
        // Bass Boost, which extracts a mono signal for processing.
        if (plvmConfigParams->monoMode && channelCount > 1) {
            for (int i = 0; i < frameLength; ++i) {
                auto* fp = &floatIn[i * channelCount];
                std::fill(fp + 1, fp + channelCount, *fp);  // replicate ch 0
            }
        }
#ifndef BYPASS_EXEC
        errCode = lvmExecute(floatIn.data(), floatOut.data(), pContext, plvmConfigParams);
        if (errCode) {
            printf("\nError: lvmExecute returned with %d\n", errCode);
            return errCode;
        }

        (void)frameSize;  // eliminate warning
#else
        memcpy(floatOut.data(), floatIn.data(), frameLength * frameSize);
#endif
        memcpy_to_i16_from_float(out.data(), floatOut.data(), frameLength * channelCount);
        if (ioChannelCount != channelCount) {
            adjust_channels(out.data(), channelCount, out.data(), ioChannelCount, sizeof(short),
                            frameLength * channelCount * sizeof(short));
        }
        (void)fwrite(out.data(), ioFrameSize, frameLength, fout);
        frameCounter += frameLength;
    }
    printf("frameCounter: [%d]\n", frameCounter);
    return 0;
}

int main(int argc, const char* argv[]) {
    if (argc == 1) {
        printUsage();
        return -1;
    }

    lvmConfigParams_t lvmConfigParams{};  // default initialize
    const char* infile = nullptr;
    const char* outfile = nullptr;

    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
        if (!strncmp(argv[i], "-i:", 3)) {
            infile = argv[i] + 3;
        } else if (!strncmp(argv[i], "-o:", 3)) {
            outfile = argv[i] + 3;
        } else if (!strncmp(argv[i], "-fs:", 4)) {
            const int samplingFreq = atoi(argv[i] + 4);
            if (samplingFreq != 8000 && samplingFreq != 11025 && samplingFreq != 12000 &&
                samplingFreq != 16000 && samplingFreq != 22050 && samplingFreq != 24000 &&
                samplingFreq != 32000 && samplingFreq != 44100 && samplingFreq != 48000 &&
                samplingFreq != 88200 && samplingFreq != 96000 && samplingFreq != 176400 &&
                samplingFreq != 192000) {
                printf("Error: Unsupported Sampling Frequency : %d\n", samplingFreq);
                return -1;
            }
            lvmConfigParams.samplingFreq = samplingFreq;
        } else if (!strncmp(argv[i], "-chMask:", 8)) {
            const int chMaskConfigIdx = atoi(argv[i] + 8);
            if (chMaskConfigIdx < 0 || (size_t)chMaskConfigIdx >= std::size(lvmConfigChMask)) {
                ALOGE("\nError: Unsupported Channel Mask : %d\n", chMaskConfigIdx);
                return -1;
            }
            const audio_channel_mask_t chMask = lvmConfigChMask[chMaskConfigIdx];
            lvmConfigParams.chMask = chMask;
            lvmConfigParams.nrChannels = audio_channel_count_from_out_mask(chMask);
        } else if (!strncmp(argv[i], "-vcBal:", 7)) {
            const int vcBalance = atoi(argv[i] + 7);
            if (vcBalance > 96 || vcBalance < -96) {
                ALOGE("\nError: Unsupported volume balance value: %d\n", vcBalance);
            }
            lvmConfigParams.vcBal = vcBalance;
        } else if (!strncmp(argv[i], "-fch:", 5)) {
            const int fChannels = atoi(argv[i] + 5);
            if (fChannels > 8 || fChannels < 1) {
                printf("Error: Unsupported number of file channels : %d\n", fChannels);
                return -1;
            }
            lvmConfigParams.fChannels = fChannels;
        } else if (!strcmp(argv[i], "-M")) {
            lvmConfigParams.monoMode = true;
        } else if (!strncmp(argv[i], "-basslvl:", 9)) {
            const int bassEffectLevel = atoi(argv[i] + 9);
            if (bassEffectLevel > LVM_BE_MAX_EFFECTLEVEL ||
                bassEffectLevel < LVM_BE_MIN_EFFECTLEVEL) {
                printf("Error: Unsupported Bass Effect Level : %d\n", bassEffectLevel);
                printUsage();
                return -1;
            }
            lvmConfigParams.bassEffectLevel = bassEffectLevel;
        } else if (!strncmp(argv[i], "-eqPreset:", 10)) {
            const int eqPresetLevel = atoi(argv[i] + 10);
            const int numPresetLvls = std::size(gEqualizerPresets);
            if (eqPresetLevel >= numPresetLvls || eqPresetLevel < 0) {
                printf("Error: Unsupported Equalizer Preset : %d\n", eqPresetLevel);
                printUsage();
                return -1;
            }
            lvmConfigParams.eqPresetLevel = eqPresetLevel;
        } else if (!strncmp(argv[i], "-trebleLvl:", 11)) {
            const int trebleEffectLevel = atoi(argv[i] + 11);
            if (trebleEffectLevel > LVM_TE_MAX_EFFECTLEVEL ||
                trebleEffectLevel < LVM_TE_MIN_EFFECTLEVEL) {
                printf("Error: Unsupported Treble Effect Level : %d\n", trebleEffectLevel);
                printUsage();
                return -1;
            }
            lvmConfigParams.trebleEffectLevel = trebleEffectLevel;
        } else if (!strcmp(argv[i], "-bE")) {
            lvmConfigParams.bassEnable = LVM_BE_ON;
        } else if (!strcmp(argv[i], "-eqE")) {
            lvmConfigParams.eqEnable = LVM_EQNB_ON;
        } else if (!strcmp(argv[i], "-tE")) {
            lvmConfigParams.trebleEnable = LVM_TE_ON;
        } else if (!strcmp(argv[i], "-csE")) {
            lvmConfigParams.csEnable = LVM_MODE_ON;
        } else if (!strcmp(argv[i], "-h")) {
            printUsage();
            return 0;
        }
    }

    if (infile == nullptr || outfile == nullptr) {
        printf("Error: missing input/output files\n");
        printUsage();
        return -1;
    }

    FILE* finp = fopen(infile, "rb");
    if (finp == nullptr) {
        printf("Cannot open input file %s", infile);
        return -1;
    }

    FILE* fout = fopen(outfile, "wb");
    if (fout == nullptr) {
        printf("Cannot open output file %s", outfile);
        fclose(finp);
        return -1;
    }

    EffectContext context;
    LVM_ControlParams_t params;
    int errCode = lvmCreate(&context, &lvmConfigParams, &params);
    if (errCode == 0) {
        errCode = lvmMainProcess(&context, &params, &lvmConfigParams, finp, fout);
        if (errCode != 0) {
            printf("Error: lvmMainProcess returned with the error: %d", errCode);
        }
    } else {
        printf("Error: lvmCreate returned with the error: %d", errCode);
    }
    fclose(finp);
    fclose(fout);
    /* Free the allocated buffers */
    if (context.pBundledContext != nullptr) {
        if (context.pBundledContext->hInstance != nullptr) {
            LVM_DelInstanceHandle(&context.pBundledContext->hInstance);
        }
        free(context.pBundledContext);
    }

    if (errCode) {
        return -1;
    }
    return 0;
}
