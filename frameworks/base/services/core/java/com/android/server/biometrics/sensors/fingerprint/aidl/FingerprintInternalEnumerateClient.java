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

package com.android.server.biometrics.sensors.fingerprint.aidl;

import android.annotation.NonNull;
import android.content.Context;
import android.hardware.biometrics.BiometricsProtoEnums;
import android.hardware.biometrics.fingerprint.ISession;
import android.hardware.fingerprint.Fingerprint;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Slog;

import com.android.server.biometrics.sensors.BiometricUtils;
import com.android.server.biometrics.sensors.InternalEnumerateClient;

import java.util.List;

/**
 * Fingerprint-specific internal client supporting the
 * {@link android.hardware.biometrics.fingerprint.IFingerprint} AIDL interface.
 */
class FingerprintInternalEnumerateClient extends InternalEnumerateClient<ISession> {
    private static final String TAG = "FingerprintInternalEnumerateClient";

    protected FingerprintInternalEnumerateClient(@NonNull Context context,
            @NonNull LazyDaemon<ISession> lazyDaemon, @NonNull IBinder token, int userId,
            @NonNull String owner, @NonNull List<Fingerprint> enrolledList,
            @NonNull BiometricUtils<Fingerprint> utils, int sensorId) {
        super(context, lazyDaemon, token, userId, owner, enrolledList, utils, sensorId,
                BiometricsProtoEnums.MODALITY_FINGERPRINT);
    }

    @Override
    protected void startHalOperation() {
        try {
            getFreshDaemon().enumerateEnrollments();
        } catch (RemoteException e) {
            Slog.e(TAG, "Remote exception when requesting enumerate", e);
            mCallback.onClientFinished(this, false /* success */);
        }
    }
}
