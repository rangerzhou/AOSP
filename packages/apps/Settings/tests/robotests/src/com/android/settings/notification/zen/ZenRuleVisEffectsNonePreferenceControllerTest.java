/*
 * Copyright (C) 2018 The Android Open Source Project
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

package com.android.settings.notification.zen;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import android.app.NotificationManager;
import android.content.Context;
import android.service.notification.ZenPolicy;

import androidx.preference.PreferenceScreen;

import com.android.settingslib.core.lifecycle.Lifecycle;
import com.android.settingslib.widget.RadioButtonPreference;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.shadows.ShadowApplication;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
public class ZenRuleVisEffectsNonePreferenceControllerTest extends
        ZenRuleCustomPrefContrTestBase {

    @Mock
    private ZenModeBackend mBackend;
    @Mock
    private NotificationManager mNotificationManager;
    @Mock
    private RadioButtonPreference mMockPref;
    @Mock
    private PreferenceScreen mScreen;

    private ZenRuleVisEffectsNonePreferenceController mController;
    private Context mContext;

    @Override
    AbstractZenCustomRulePreferenceController getController() {
        return mController;
    }

    @Before
    public void setup() {
        MockitoAnnotations.initMocks(this);
        ShadowApplication shadowApplication = ShadowApplication.getInstance();
        shadowApplication.setSystemService(Context.NOTIFICATION_SERVICE, mNotificationManager);
        mContext = RuntimeEnvironment.application;
        mController = new ZenRuleVisEffectsNonePreferenceController(mContext, mock(Lifecycle.class),
                PREF_KEY);
        ReflectionHelpers.setField(mController, "mBackend", mBackend);
        when(mBackend.getAutomaticZenRule(RULE_ID)).thenReturn(mRule);
        when(mScreen.findPreference(mController.getPreferenceKey())).thenReturn(mMockPref);
        mController.displayPreference(mScreen);
    }

    @Test
    public void updateState_noVisEffects() {
        updateControllerZenPolicy(new ZenPolicy.Builder()
                .hideAllVisualEffects()
                .build());
        mController.updateState(mMockPref);
        verify(mMockPref).setChecked(true);
    }

    @Test
    public void updateState_showAllVisualEffects() {
        updateControllerZenPolicy(new ZenPolicy.Builder()
                .showAllVisualEffects()
                .build());
        mController.updateState(mMockPref);
        verify(mMockPref).setChecked(false);
    }

    @Test
    public void updateState_custom() {
        updateControllerZenPolicy(new ZenPolicy.Builder()
                .showPeeking(true)
                .showBadges(false)
                .build());
        mController.updateState(mMockPref);

        verify(mMockPref).setChecked(false);
    }
}
