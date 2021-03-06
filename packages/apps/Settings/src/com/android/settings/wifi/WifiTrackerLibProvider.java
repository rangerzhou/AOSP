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

package com.android.settings.wifi;

import android.content.Context;
import android.os.Handler;

import androidx.lifecycle.Lifecycle;

import com.android.wifitrackerlib.NetworkDetailsTracker;
import com.android.wifitrackerlib.WifiPickerTracker;

import java.time.Clock;

/**
 * Provides the objects instances from the AOSP WifiTrackerLib.
 */
public interface WifiTrackerLibProvider {

    /** Create a new instance of WifiPickerTracker */
    WifiPickerTracker createWifiPickerTracker(
            Lifecycle lifecycle, Context context,
            Handler mainHandler, Handler workerHandler, Clock clock,
            long maxScanAgeMillis, long scanIntervalMillis,
            WifiPickerTracker.WifiPickerTrackerCallback listener);

    /** Create a new instance of NetworkDetailsTracker */
    NetworkDetailsTracker createNetworkDetailsTracker(
            Lifecycle lifecycle, Context context,
            Handler mainHandler, Handler workerHandler, Clock clock,
            long maxScanAgeMillis, long scanIntervalMillis,
            String key);

}
