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

package com.android.settings.network;

import static com.android.settings.core.BasePreferenceController.CONDITIONALLY_UNAVAILABLE;

import static com.google.common.truth.Truth.assertThat;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.when;

import android.content.Context;
import android.os.Looper;
import android.telephony.SubscriptionInfo;

import com.android.settings.testutils.ResourcesUtils;
import com.android.settingslib.core.lifecycle.Lifecycle;

import androidx.preference.Preference;
import androidx.preference.PreferenceCategory;
import androidx.preference.PreferenceManager;
import androidx.preference.PreferenceScreen;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.ArrayList;
import java.util.Arrays;

@RunWith(AndroidJUnit4.class)
public class NetworkProviderDownloadedSimsCategoryControllerTest {

    private static final String KEY_PREFERENCE_CATEGORY_DOWNLOADED_SIM =
            "provider_model_downloaded_sim_category";
    private static final String KEY_ADD_MORE = "add_more";
    private static final String SUB_1 = "SUB_1";
    private static final String SUB_2 = "SUB_2";
    private static final int SUB_ID_1 = 1;
    private static final int SUB_ID_2 = 2;

    @Mock
    private Lifecycle mLifecycle;
    @Mock
    private SubscriptionInfo mSubscriptionInfo1;
    @Mock
    private SubscriptionInfo mSubscriptionInfo2;

    private Context mContext;
    private NetworkProviderDownloadedSimsCategoryController mCategoryController;
    private PreferenceCategory mPreferenceCategory;
    private PreferenceManager mPreferenceManager;
    private PreferenceScreen mPreferenceScreen;
    private Preference mAddMorePreference;

    @Before
    public void setUp() throws Exception {
        MockitoAnnotations.initMocks(this);

        mContext = spy(ApplicationProvider.getApplicationContext());

        if (Looper.myLooper() == null) {
            Looper.prepare();
        }

        mPreferenceManager = new PreferenceManager(mContext);
        mPreferenceScreen = mPreferenceManager.createPreferenceScreen(mContext);
        mPreferenceCategory = new PreferenceCategory(mContext);
        mPreferenceCategory.setKey(KEY_PREFERENCE_CATEGORY_DOWNLOADED_SIM);
        mAddMorePreference = new Preference(mContext);
        mAddMorePreference.setKey(KEY_ADD_MORE);
        mAddMorePreference.setVisible(true);
        mPreferenceScreen.addPreference(mPreferenceCategory);
        mPreferenceScreen.addPreference(mAddMorePreference);

        mCategoryController = new NetworkProviderDownloadedSimsCategoryController(mContext,
                KEY_PREFERENCE_CATEGORY_DOWNLOADED_SIM, mLifecycle);
    }

    @Test
    public void getAvailabilityStatus_returnUnavailable() {
        SubscriptionUtil.setAvailableSubscriptionsForTesting(new ArrayList<>());

        assertThat(mCategoryController.getAvailabilityStatus()).isEqualTo(
                CONDITIONALLY_UNAVAILABLE);
    }

    @Test
    public void displayPreference_isVisible() {
        setUpSubscriptionInfoForDownloadedSim(SUB_ID_1, SUB_1, mSubscriptionInfo1);
        SubscriptionUtil.setAvailableSubscriptionsForTesting(Arrays.asList(mSubscriptionInfo1));
        mCategoryController.displayPreference(mPreferenceScreen);

        assertEquals(mPreferenceCategory.isVisible(), true);
    }


    @Test
    public void updateState_setTitle_withTwoDownloadedSims_returnDownloadedSims() {
        setUpSubscriptionInfoForDownloadedSim(SUB_ID_1, SUB_1, mSubscriptionInfo1);
        setUpSubscriptionInfoForDownloadedSim(SUB_ID_2, SUB_2, mSubscriptionInfo2);
        SubscriptionUtil.setAvailableSubscriptionsForTesting(
                Arrays.asList(mSubscriptionInfo1, mSubscriptionInfo2));

        mCategoryController.displayPreference(mPreferenceScreen);
        mCategoryController.updateState(mPreferenceCategory);

        assertThat(mPreferenceCategory.getPreferenceCount()).isEqualTo(2);
        assertThat(mPreferenceCategory.getTitle()).isEqualTo(
                ResourcesUtils.getResourcesString(mContext, "downloaded_sims_category_title"));
    }

    @Test
    public void updateState_setTitle_withOneDownloadedSim_returnDownloadedSim() {
        setUpSubscriptionInfoForDownloadedSim(SUB_ID_1, SUB_1, mSubscriptionInfo1);
        SubscriptionUtil.setAvailableSubscriptionsForTesting(Arrays.asList(mSubscriptionInfo1));

        mCategoryController.displayPreference(mPreferenceScreen);
        mCategoryController.updateState(mPreferenceCategory);

        assertThat(mPreferenceCategory.getPreferenceCount()).isEqualTo(1);
        assertThat(mPreferenceCategory.getTitle()).isEqualTo(
                ResourcesUtils.getResourcesString(mContext, "downloaded_sim_category_title"));
    }

    private void setUpSubscriptionInfoForDownloadedSim(int subId, String displayName,
            SubscriptionInfo subscriptionInfo) {
        when(subscriptionInfo.isEmbedded()).thenReturn(true);
        when(subscriptionInfo.getSubscriptionId()).thenReturn(subId);
        when(subscriptionInfo.getDisplayName()).thenReturn(displayName);
    }
}
