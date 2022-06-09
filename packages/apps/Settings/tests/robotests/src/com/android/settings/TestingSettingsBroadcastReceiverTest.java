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

package com.android.settings;

import static com.google.common.truth.Truth.assertThat;

import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.telephony.TelephonyManager;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;

@RunWith(RobolectricTestRunner.class)
public class TestingSettingsBroadcastReceiverTest {

    private Context mContext;
    private Application mApplication;
    private TestingSettingsBroadcastReceiver mReceiver;

    @Before
    public void setUp() {
        mContext = RuntimeEnvironment.application;
        mApplication = RuntimeEnvironment.application;
        mReceiver = new TestingSettingsBroadcastReceiver();
    }

    @Test
    public void onReceive_nullIntent_shouldNotCrash() {
        final Intent intent = new Intent();

        mReceiver.onReceive(mContext, null);
        mReceiver.onReceive(mContext, intent);

        final Intent next = Shadows.shadowOf(mApplication).getNextStartedActivity();
        assertThat(next).isNull();
    }

    @Test
    public void onReceive_wrongIntent_shouldNotStartActivity() {
        final Intent intent = new Intent();
        intent.setAction("");

        mReceiver.onReceive(mContext, intent);

        final Intent next = Shadows.shadowOf(mApplication).getNextStartedActivity();
        assertThat(next).isNull();
    }

    @Test
    public void onReceive_correctIntent_shouldStartActivity() {
        final Intent intent = new Intent();
        intent.setAction(TelephonyManager.ACTION_SECRET_CODE);

        mReceiver.onReceive(mContext, intent);

        final Intent next = Shadows.shadowOf(mApplication).getNextStartedActivity();
        assertThat(next).isNotNull();
        final String dest = next.getComponent().getClassName();
        assertThat(dest).isEqualTo(Settings.TestingSettingsActivity.class.getName());
    }
}
