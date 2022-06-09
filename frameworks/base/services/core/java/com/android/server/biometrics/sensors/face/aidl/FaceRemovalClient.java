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

package com.android.server.biometrics.sensors.face.aidl;

import android.annotation.NonNull;
import android.content.Context;
import android.hardware.biometrics.BiometricsProtoEnums;
import android.hardware.biometrics.face.IFace;
import android.hardware.biometrics.face.ISession;
import android.hardware.face.Face;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Slog;

import com.android.server.biometrics.sensors.BiometricUtils;
import com.android.server.biometrics.sensors.ClientMonitorCallbackConverter;
import com.android.server.biometrics.sensors.RemovalClient;

import java.util.Map;

/**
 * Face-specific removal client for the {@link IFace} AIDL HAL interface.
 */
class FaceRemovalClient extends RemovalClient<Face, ISession> {
    private static final String TAG = "FaceRemovalClient";

    final int[] mBiometricIds;

    FaceRemovalClient(@NonNull Context context, @NonNull LazyDaemon<ISession> lazyDaemon,
            @NonNull IBinder token, @NonNull ClientMonitorCallbackConverter listener,
            int[] biometricIds, int userId, @NonNull String owner,
            @NonNull BiometricUtils<Face> utils, int sensorId,
            @NonNull Map<Integer, Long> authenticatorIds) {
        super(context, lazyDaemon, token, listener, userId, owner, utils, sensorId,
                authenticatorIds, BiometricsProtoEnums.MODALITY_FACE);
        mBiometricIds = biometricIds;
    }

    @Override
    protected void startHalOperation() {
        try {
            getFreshDaemon().removeEnrollments(mBiometricIds);
        } catch (RemoteException e) {
            Slog.e(TAG, "Remote exception when requesting remove", e);
            mCallback.onClientFinished(this, false /* success */);
        }
    }
}
