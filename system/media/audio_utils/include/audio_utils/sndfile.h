/*
 * Copyright (C) 2012 The Android Open Source Project
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

#ifndef __AUDIO_UTIL_SNDFILE_H
#define __AUDIO_UTIL_SNDFILE_H

// This is a C library for reading and writing PCM .wav files.  It is
// influenced by other libraries such as libsndfile and audiofile, except is
// much smaller and has an Apache 2.0 license.
// The API should be familiar to clients of similar libraries, but there is
// no guarantee that it will stay exactly source-code compatible with other libraries.

#include <stdint.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <system/audio.h>

/** \cond */
__BEGIN_DECLS
/** \endcond */

// visible to clients
typedef int sf_count_t;

typedef struct {
    sf_count_t frames;
    int samplerate;
    int channels;
    int format;
} SF_INFO;

// opaque to clients
typedef struct SNDFILE_ SNDFILE;

// Access modes
#define SFM_READ    1
#define SFM_WRITE   2

// Format
#define SF_FORMAT_TYPEMASK  1
#define SF_FORMAT_WAV       1
#define SF_FORMAT_SUBMASK   14
#define SF_FORMAT_PCM_16    2
#define SF_FORMAT_PCM_U8    4
#define SF_FORMAT_FLOAT     6
#define SF_FORMAT_PCM_32    8
#define SF_FORMAT_PCM_24    10

/** Open stream */
SNDFILE *sf_open(const char *path, int mode, SF_INFO *info);

/** Close stream */
void sf_close(SNDFILE *handle);

/**
 * Read interleaved frames
 * \return actual number of frames read
 */
sf_count_t sf_readf_short(SNDFILE *handle, int16_t *ptr, sf_count_t desired);
sf_count_t sf_readf_float(SNDFILE *handle, float *ptr, sf_count_t desired);
sf_count_t sf_readf_int(SNDFILE *handle, int *ptr, sf_count_t desired);

/**
 * Write interleaved frames
 * \return actual number of frames written
 */
sf_count_t sf_writef_short(SNDFILE *handle, const int16_t *ptr, sf_count_t desired);
sf_count_t sf_writef_float(SNDFILE *handle, const float *ptr, sf_count_t desired);
sf_count_t sf_writef_int(SNDFILE *handle, const int *ptr, sf_count_t desired);

/**
 * Map SF_FORMAT to PCM format
 */
static inline audio_format_t SF_format_to_audio_format (int format) {
    // Ignore FORMAT_WAV bit
    switch (format & (~SF_FORMAT_WAV)) {
    case SF_FORMAT_PCM_16:
        return AUDIO_FORMAT_PCM_16_BIT;
    case SF_FORMAT_PCM_U8:
        return AUDIO_FORMAT_PCM_8_BIT;
    case SF_FORMAT_FLOAT:
        return AUDIO_FORMAT_PCM_FLOAT;
    case SF_FORMAT_PCM_32:
        return AUDIO_FORMAT_PCM_32_BIT;
    case SF_FORMAT_PCM_24:
        return AUDIO_FORMAT_PCM_24_BIT_PACKED;
    default:
        return AUDIO_FORMAT_INVALID;
    }
}

/** \cond */
__END_DECLS
/** \endcond */

#endif /* __AUDIO_UTIL_SNDFILE_H */
