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

package com.android.settings.development;

import android.annotation.Nullable;
import android.content.Context;
import android.hardware.dumpstate.V1_0.IDumpstateDevice;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.VisibleForTesting;
import androidx.preference.Preference;
import androidx.preference.SwitchPreference;

import com.android.settings.core.PreferenceControllerMixin;
import com.android.settingslib.development.DeveloperOptionsPreferenceController;

import java.util.NoSuchElementException;

public class EnableVerboseVendorLoggingPreferenceController
        extends DeveloperOptionsPreferenceController
        implements Preference.OnPreferenceChangeListener, PreferenceControllerMixin {

    private static final String TAG = "EnableVerboseVendorLoggingPreferenceController";
    private static final boolean DBG = Log.isLoggable(TAG, Log.DEBUG);

    private static final String ENABLE_VERBOSE_VENDOR_LOGGING_KEY = "enable_verbose_vendor_logging";
    private static final int DUMPSTATE_HAL_VERSION_UNKNOWN = -1;
    private static final int DUMPSTATE_HAL_VERSION_1_0 = 0;
    private static final int DUMPSTATE_HAL_VERSION_1_1 = 1;

    private int mDumpstateHalVersion;

    public EnableVerboseVendorLoggingPreferenceController(Context context) {
        super(context);
        mDumpstateHalVersion = DUMPSTATE_HAL_VERSION_UNKNOWN;
    }

    @Override
    public String getPreferenceKey() {
        return ENABLE_VERBOSE_VENDOR_LOGGING_KEY;
    }

    @Override
    public boolean isAvailable() {
        // Only show preference when IDumpstateDevice v1.1 is avalaible
        // This is temperary strategy that may change later.
        return isIDumpstateDeviceV1_1ServiceAvailable();
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        final boolean isEnabled = (Boolean) newValue;
        setVerboseLoggingEnabled(isEnabled);
        return true;
    }

    @Override
    public void updateState(Preference preference) {
        final boolean enabled = getVerboseLoggingEnabled();
        ((SwitchPreference) mPreference).setChecked(enabled);
    }

    @Override
    protected void onDeveloperOptionsSwitchDisabled() {
        super.onDeveloperOptionsSwitchDisabled();
        setVerboseLoggingEnabled(false);
        ((SwitchPreference) mPreference).setChecked(false);
    }

    @VisibleForTesting
    boolean isIDumpstateDeviceV1_1ServiceAvailable() {
        IDumpstateDevice service = getDumpstateDeviceService();
        if (service == null) {
            if (DBG) Log.d(TAG, "IDumpstateDevice service is not available.");
        }
        return service != null && mDumpstateHalVersion >= DUMPSTATE_HAL_VERSION_1_1;
    }

    @VisibleForTesting
    void setVerboseLoggingEnabled(boolean enable) {
        IDumpstateDevice service = getDumpstateDeviceService();

        if (service == null || mDumpstateHalVersion < DUMPSTATE_HAL_VERSION_1_1) {
            if (DBG) Log.d(TAG, "setVerboseLoggingEnabled not supported.");
            return;
        }

        try {
            android.hardware.dumpstate.V1_1.IDumpstateDevice service11 =
                    (android.hardware.dumpstate.V1_1.IDumpstateDevice) service;
            if (service11 != null) {
                service11.setVerboseLoggingEnabled(enable);
            }
        } catch (RemoteException | RuntimeException e) {
            if (DBG) Log.e(TAG, "setVerboseLoggingEnabled fail: " + e);
        }
    }

    @VisibleForTesting
    boolean getVerboseLoggingEnabled() {
        IDumpstateDevice service = getDumpstateDeviceService();

        if (service == null || mDumpstateHalVersion < DUMPSTATE_HAL_VERSION_1_1) {
            if (DBG) Log.d(TAG, "getVerboseLoggingEnabled not supported.");
            return false;
        }

        try {
            android.hardware.dumpstate.V1_1.IDumpstateDevice service11 =
                    (android.hardware.dumpstate.V1_1.IDumpstateDevice) service;
            if (service11 != null) {
                return service11.getVerboseLoggingEnabled();
            }
        } catch (RemoteException | RuntimeException e) {
            if (DBG) Log.e(TAG, "getVerboseLoggingEnabled fail: " + e);
        }
        return false;
    }

    /** Return a {@IDumpstateDevice} instance or null if service is not available. */
    @VisibleForTesting
    @Nullable IDumpstateDevice getDumpstateDeviceService() {
        IDumpstateDevice service = null;
        try {
            service = android.hardware.dumpstate.V1_1.IDumpstateDevice
                    .getService(true /* retry */);
            mDumpstateHalVersion = DUMPSTATE_HAL_VERSION_1_1;
        } catch (NoSuchElementException | RemoteException e) {
        }

        if (service == null) {
            try {
                service = android.hardware.dumpstate.V1_0.IDumpstateDevice
                        .getService(true /* retry */);
                mDumpstateHalVersion = DUMPSTATE_HAL_VERSION_1_0;
            } catch (NoSuchElementException | RemoteException e) {
            }
        }

        if (service == null) {
            mDumpstateHalVersion = DUMPSTATE_HAL_VERSION_UNKNOWN;
        }
        return service;
    }
}
