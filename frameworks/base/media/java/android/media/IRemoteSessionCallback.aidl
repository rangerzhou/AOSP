/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.media;

import android.media.session.MediaSession;

/**
 * AIDL for the MediaSessionService to report interesting events on remote playback
 * to a volume control dialog. See also IVolumeController for the AudioService half.
 * TODO add in better support for multiple remote sessions.
 * @hide
 */
oneway interface IRemoteSessionCallback {
    void onVolumeChanged(in MediaSession.Token sessionToken, int flags);
    // sets the default session to use with the slider, replaces remoteSliderVisibility
    // on IVolumeController
    void onSessionChanged(in MediaSession.Token sessionToken);
}
