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

package com.android.settings.deviceinfo;

import static android.content.Context.CLIPBOARD_SERVICE;

import static com.google.common.truth.Truth.assertThat;

import static org.mockito.ArgumentMatchers.anyInt;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import android.content.ClipboardManager;
import android.content.Context;
import android.telephony.SubscriptionInfo;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyManager;

import androidx.preference.Preference;
import androidx.preference.PreferenceCategory;
import androidx.preference.PreferenceScreen;

import com.android.settings.R;
import com.android.settings.core.BasePreferenceController;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;

import java.util.ArrayList;
import java.util.List;

@RunWith(RobolectricTestRunner.class)
public class PhoneNumberPreferenceControllerTest {

    @Mock
    private Preference mPreference;
    @Mock
    private Preference mSecondPreference;
    @Mock
    private TelephonyManager mTelephonyManager;
    @Mock
    private SubscriptionInfo mSubscriptionInfo;
    @Mock
    private SubscriptionManager mSubscriptionManager;
    @Mock
    private PreferenceScreen mScreen;
    @Mock
    private PreferenceCategory mCategory;

    private Context mContext;
    private PhoneNumberPreferenceController mController;

    @Before
    public void setup() {
        MockitoAnnotations.initMocks(this);
        mContext = spy(RuntimeEnvironment.application);
        when(mContext.getSystemService(SubscriptionManager.class)).thenReturn(mSubscriptionManager);
        when(mContext.getSystemService(TelephonyManager.class)).thenReturn(mTelephonyManager);
        mController = spy(new PhoneNumberPreferenceController(mContext, "phone_number"));
        final String prefKey = mController.getPreferenceKey();
        when(mScreen.findPreference(prefKey)).thenReturn(mPreference);
        when(mScreen.getContext()).thenReturn(mContext);
        final String categoryKey = "basic_info_category";
        when(mScreen.findPreference(categoryKey)).thenReturn(mCategory);
        doReturn(mSubscriptionInfo).when(mController).getSubscriptionInfo(anyInt());
        doReturn(mSecondPreference).when(mController).createNewPreference(mContext);
        when(mPreference.isVisible()).thenReturn(true);
    }

    @Test
    public void getAvailabilityStatus_isVoiceCapable_shouldBeAVAILABLE() {
        when(mTelephonyManager.isVoiceCapable()).thenReturn(true);

        assertThat(mController.getAvailabilityStatus()).isEqualTo(
                BasePreferenceController.AVAILABLE);
    }

    @Test
    public void getAvailabilityStatus_isNotVoiceCapable_shouldBeUNSUPPORTED_ON_DEVICE() {
        when(mTelephonyManager.isVoiceCapable()).thenReturn(false);

        assertThat(mController.getAvailabilityStatus()).isEqualTo(
                BasePreferenceController.UNSUPPORTED_ON_DEVICE);
    }

    @Test
    public void displayPreference_multiSim_shouldAddSecondPreference() {
        when(mTelephonyManager.getPhoneCount()).thenReturn(2);

        mController.displayPreference(mScreen);

        verify(mCategory).addPreference(mSecondPreference);
    }

    @Test
    public void updateState_singleSim_shouldUpdateTitleAndPhoneNumber() {
        final String phoneNumber = "1111111111";
        doReturn(phoneNumber).when(mController).getFormattedPhoneNumber(mSubscriptionInfo);
        when(mTelephonyManager.getPhoneCount()).thenReturn(1);
        mController.displayPreference(mScreen);

        mController.updateState(mPreference);

        verify(mPreference).setTitle(mContext.getString(R.string.status_number));
        verify(mPreference).setSummary(phoneNumber);
    }

    @Test
    public void updateState_multiSim_shouldUpdateTitleAndPhoneNumberOfMultiplePreferences() {
        final String phoneNumber = "1111111111";
        doReturn(phoneNumber).when(mController).getFormattedPhoneNumber(mSubscriptionInfo);
        when(mTelephonyManager.getPhoneCount()).thenReturn(2);
        mController.displayPreference(mScreen);

        mController.updateState(mPreference);

        verify(mPreference).setTitle(
                mContext.getString(R.string.status_number_sim_slot, 1 /* sim slot */));
        verify(mPreference).setSummary(phoneNumber);
        verify(mSecondPreference).setTitle(
                mContext.getString(R.string.status_number_sim_slot, 2 /* sim slot */));
        verify(mSecondPreference).setSummary(phoneNumber);
    }

    @Test
    public void getSummary_cannotGetActiveSubscriptionInfo_shouldShowUnknown() {
        when(mSubscriptionManager.getActiveSubscriptionInfoList()).thenReturn(null);

        CharSequence primaryNumber = mController.getSummary();

        assertThat(primaryNumber).isNotNull();
        assertThat(primaryNumber).isEqualTo(mContext.getString(R.string.device_info_default));
    }

    @Test
    public void getSummary_getEmptySubscriptionInfo_shouldShowUnknown() {
        List<SubscriptionInfo> infos = new ArrayList<>();
        when(mSubscriptionManager.getActiveSubscriptionInfoList()).thenReturn(infos);

        CharSequence primaryNumber = mController.getSummary();

        assertThat(primaryNumber).isEqualTo(mContext.getString(R.string.device_info_default));
    }

    @Test
    public void copy_shouldCopyPhoneNumberToClipboard() {
        final List<SubscriptionInfo> list = new ArrayList<>();
        list.add(mSubscriptionInfo);
        when(mSubscriptionManager.getActiveSubscriptionInfoList()).thenReturn(list);
        final String phoneNumber = "1111111111";
        doReturn(phoneNumber).when(mController).getFormattedPhoneNumber(mSubscriptionInfo);

        mController.copy();

        final ClipboardManager clipboard = (ClipboardManager) mContext.getSystemService(
                CLIPBOARD_SERVICE);
        final CharSequence data = clipboard.getPrimaryClip().getItemAt(0).getText();
        assertThat(phoneNumber.contentEquals(data)).isTrue();
    }
}
