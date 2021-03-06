/*
 * Copyright (C) 2019 The Android Open Source Project
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

package com.android.settings.accessibility;

import static com.android.internal.accessibility.AccessibilityShortcutController.ACCESSIBILITY_BUTTON_COMPONENT_NAME;
import static com.android.internal.accessibility.AccessibilityShortcutController.MAGNIFICATION_COMPONENT_NAME;

import static com.google.common.truth.Truth.assertThat;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.verify;

import android.accessibilityservice.AccessibilityServiceInfo;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.ResolveInfo;
import android.content.pm.ServiceInfo;
import android.os.Bundle;
import android.view.accessibility.AccessibilityManager;

import androidx.fragment.app.FragmentActivity;

import com.android.settings.SettingsActivity;
import com.android.settings.testutils.shadow.ShadowFragment;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Captor;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import org.robolectric.shadow.api.Shadow;
import org.robolectric.shadows.ShadowAccessibilityManager;
import org.xmlpull.v1.XmlPullParserException;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@Config(shadows = ShadowFragment.class)
@RunWith(RobolectricTestRunner.class)
public class AccessibilityDetailsSettingsFragmentTest {
    private final static String PACKAGE_NAME = "com.foo.bar";
    private final static String CLASS_NAME = PACKAGE_NAME + ".fake_a11y_service";
    private final static String COMPONENT_NAME = PACKAGE_NAME + "/" + CLASS_NAME;

    private Context mContext;
    private AccessibilityDetailsSettingsFragment mFragment;
    private ShadowAccessibilityManager mShadowAccessibilityManager;
    @Captor
    private ArgumentCaptor<Intent> mIntentArgumentCaptor;
    @Mock private FragmentActivity mActivity;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mContext = spy(RuntimeEnvironment.application);
        mFragment = spy(new AccessibilityDetailsSettingsFragment());
        mShadowAccessibilityManager = Shadow.extract(AccessibilityManager.getInstance(mContext));
        mShadowAccessibilityManager.setInstalledAccessibilityServiceList(getMockServiceList());

        doReturn(mActivity).when(mFragment).getActivity();
        doReturn(mContext).when(mFragment).getContext();
    }

    @Test
    public void onCreate_afterSuccessfullyLaunch_shouldBeFinished() {
        final Intent intent = new Intent();
        intent.putExtra(Intent.EXTRA_COMPONENT_NAME, COMPONENT_NAME);
        doReturn(intent).when(mActivity).getIntent();

        mFragment.onCreate(Bundle.EMPTY);

        verify(mActivity).finish();
    }

    @Test
    public void onCreate_hasValidExtraComponentName_launchExpectedFragment() {
        final Intent intent = new Intent();
        intent.putExtra(Intent.EXTRA_COMPONENT_NAME, COMPONENT_NAME);
        doReturn(intent).when(mActivity).getIntent();

        mFragment.onCreate(Bundle.EMPTY);

        assertStartActivityWithExpectedFragment(mActivity,
                ToggleAccessibilityServicePreferenceFragment.class.getName());
    }

    @Test
    public void onCreate_hasInvalidExtraComponentName_launchAccessibilitySettings() {
        final Intent intent = new Intent();
        intent.putExtra(Intent.EXTRA_COMPONENT_NAME, PACKAGE_NAME + "/.service");
        doReturn(intent).when(mActivity).getIntent();

        mFragment.onCreate(Bundle.EMPTY);

        assertStartActivityWithExpectedFragment(mActivity, AccessibilitySettings.class.getName());
    }

    @Test
    public void onCreate_hasNoExtraComponentName_launchAccessibilitySettings() {
        final Intent intent = new Intent();
        doReturn(intent).when(mActivity).getIntent();

        mFragment.onCreate(Bundle.EMPTY);

        assertStartActivityWithExpectedFragment(mActivity, AccessibilitySettings.class.getName());
    }

    @Test
    public void onCreate_extraComponentNameIsDisallowed_launchAccessibilitySettings() {
        final Intent intent = new Intent();
        intent.putExtra(Intent.EXTRA_COMPONENT_NAME, COMPONENT_NAME);
        doReturn(intent).when(mActivity).getIntent();
        doReturn(false).when(mFragment).isServiceAllowed(any());

        mFragment.onCreate(Bundle.EMPTY);

        assertStartActivityWithExpectedFragment(mActivity, AccessibilitySettings.class.getName());
    }

    @Test
    public void onCreate_magnificationComponentName_launchMagnificationFragment() {
        final Intent intent = new Intent();
        intent.putExtra(Intent.EXTRA_COMPONENT_NAME,
                MAGNIFICATION_COMPONENT_NAME.flattenToString());
        doReturn(intent).when(mActivity).getIntent();

        mFragment.onCreate(Bundle.EMPTY);


        assertStartActivityWithExpectedFragment(mActivity,
                ToggleScreenMagnificationPreferenceFragment.class.getName());
    }

    @Test
    public void onCreate_accessibilityButton_launchAccessibilityButtonFragment() {
        final Intent intent = new Intent();
        intent.putExtra(Intent.EXTRA_COMPONENT_NAME,
                ACCESSIBILITY_BUTTON_COMPONENT_NAME.flattenToString());
        doReturn(intent).when(mActivity).getIntent();

        mFragment.onCreate(Bundle.EMPTY);

        assertStartActivityWithExpectedFragment(mActivity,
                AccessibilityButtonFragment.class.getName());
    }

    private AccessibilityServiceInfo getMockAccessibilityServiceInfo() {
        final ApplicationInfo applicationInfo = new ApplicationInfo();
        final ServiceInfo serviceInfo = new ServiceInfo();
        applicationInfo.packageName = PACKAGE_NAME;
        serviceInfo.packageName = PACKAGE_NAME;
        serviceInfo.name = CLASS_NAME;
        serviceInfo.applicationInfo = applicationInfo;

        final ResolveInfo resolveInfo = new ResolveInfo();
        resolveInfo.serviceInfo = serviceInfo;

        try {
            final AccessibilityServiceInfo info = new AccessibilityServiceInfo(resolveInfo,
                    mContext);
            ComponentName componentName = ComponentName.unflattenFromString(COMPONENT_NAME);
            info.setComponentName(componentName);
            return info;
        } catch (XmlPullParserException | IOException e) {
            // Do nothing
        }

        return null;
    }

    private List<AccessibilityServiceInfo> getMockServiceList() {
        final List<AccessibilityServiceInfo> infoList = new ArrayList<>();
        infoList.add(getMockAccessibilityServiceInfo());
        return infoList;
    }

    private void assertStartActivityWithExpectedFragment(Context mockContext, String fragmentName) {
        verify(mockContext).startActivity(mIntentArgumentCaptor.capture());
        assertThat(mIntentArgumentCaptor.getValue()
                .getStringExtra(SettingsActivity.EXTRA_SHOW_FRAGMENT))
                .isEqualTo(fragmentName);
    }
}
