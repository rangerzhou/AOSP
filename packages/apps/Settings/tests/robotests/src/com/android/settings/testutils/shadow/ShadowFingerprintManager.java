/*
 * Copyright (C) 2017 The Android Open Source Project
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

package com.android.settings.testutils.shadow;

import android.hardware.fingerprint.Fingerprint;
import android.hardware.fingerprint.FingerprintManager;
import android.hardware.fingerprint.FingerprintSensorPropertiesInternal;

import org.robolectric.annotation.Implementation;
import org.robolectric.annotation.Implements;

import java.util.List;

@Implements(FingerprintManager.class)
public class ShadowFingerprintManager extends org.robolectric.shadows.ShadowFingerprintManager {

    private static List<FingerprintSensorPropertiesInternal> sFingerprintSensorProperties;

    public static void setSensorProperties(List<FingerprintSensorPropertiesInternal> props) {
        sFingerprintSensorProperties = props;
    }

    @Implementation
    protected List<Fingerprint> getEnrolledFingerprints(int userId) {
        return getEnrolledFingerprints();
    }

    @Implementation
    protected List<FingerprintSensorPropertiesInternal> getSensorPropertiesInternal() {
        return sFingerprintSensorProperties;
    }
}
