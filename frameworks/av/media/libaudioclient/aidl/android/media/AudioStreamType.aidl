/*
 * Copyright (C) 2020 The Android Open Source Project
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
package android.media;

/**
 * {@hide}
 */
@Backing(type="int")
enum AudioStreamType {
    DEFAULT = -1,
    VOICE_CALL = 0,
    SYSTEM = 1,
    RING = 2,
    MUSIC = 3,
    ALARM = 4,
    NOTIFICATION = 5,
    BLUETOOTH_SCO = 6,
    ENFORCED_AUDIBLE = 7,
    DTMF = 8,
    TTS = 9,
    ACCESSIBILITY = 10,
    ASSISTANT = 11,
    /** For dynamic policy output mixes. Only used by the audio policy */
    REROUTING = 12,
    /** For audio flinger tracks volume. Only used by the audioflinger */
    PATCH = 13,
    /** stream for corresponding to AUDIO_USAGE_CALL_ASSISTANT */
    CALL_ASSISTANT = 14,
}
