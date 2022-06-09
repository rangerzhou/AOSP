/*
 * Copyright (C) 2021 The Android Open Source Project
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

package com.android.server.biometrics.sensors.fingerprint.hidl;

import android.annotation.NonNull;
import android.content.Context;
import android.hardware.biometrics.BiometricsProtoEnums;

import com.android.server.biometrics.BiometricsProto;
import com.android.server.biometrics.sensors.BaseClientMonitor;

/**
 * Clears lockout, which is handled in the framework (and not the HAL) for the
 * IBiometricsFingerprint@2.1 interface.
 */
public class FingerprintResetLockoutClient extends BaseClientMonitor {

    @NonNull final LockoutFrameworkImpl mLockoutTracker;

    public FingerprintResetLockoutClient(@NonNull Context context, int userId,
            @NonNull String owner, int sensorId, @NonNull LockoutFrameworkImpl lockoutTracker) {
        super(context, null /* token */, null /* listener */, userId, owner, 0 /* cookie */,
                sensorId, BiometricsProtoEnums.MODALITY_UNKNOWN,
                BiometricsProtoEnums.ACTION_UNKNOWN, BiometricsProtoEnums.CLIENT_UNKNOWN);
        mLockoutTracker = lockoutTracker;
    }

    @Override
    public void start(@NonNull Callback callback) {
        super.start(callback);
        mLockoutTracker.resetFailedAttemptsForUser(true /* clearAttemptCounter */,
                getTargetUserId());
        callback.onClientFinished(this, true /* success */);
    }

    @Override
    public int getProtoEnum() {
        return BiometricsProto.CM_RESET_LOCKOUT;
    }
}
