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

package com.android.settings.applications.appinfo;

import static com.google.common.truth.Truth.assertThat;

import android.content.Context;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;

@RunWith(RobolectricTestRunner.class)
public class ExtraAppInfoFeatureProviderImplTest {
    private Context mContext;
    private ExtraAppInfoFeatureProviderImpl mController;

    @Before
    public void setUp() {
        mContext = RuntimeEnvironment.application;
        mController = new ExtraAppInfoFeatureProviderImpl();
    }

    @Test
    public void isSupported_notSupportedByDefault() {
        assertThat(mController.isSupported(mContext)).isEqualTo(false);
    }

    @Test
    public void isEnabled_notEnabledByDefault() {
        assertThat(mController.isEnabled(mContext)).isEqualTo(false);
    }

    @Test
    public void getSummary_emptyByDefault() {
        assertThat(mController.getSummary(mContext)).isEqualTo("");
    }
}
