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

package com.android.settings.panel;

import static android.view.WindowManager.LayoutParams.SYSTEM_FLAG_HIDE_NON_SYSTEM_OVERLAY_WINDOWS;

import static com.google.common.truth.Truth.assertThat;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import android.content.res.Configuration;
import android.os.Build;
import android.view.Window;
import android.view.WindowManager;

import androidx.fragment.app.FragmentManager;

import com.android.settings.R;
import com.android.settings.testutils.FakeFeatureFactory;
import com.android.settingslib.core.lifecycle.HideNonSystemOverlayMixin;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.android.controller.ActivityController;
import org.robolectric.util.ReflectionHelpers;

@RunWith(RobolectricTestRunner.class)
public class SettingsPanelActivityTest {

    private FakeFeatureFactory mFakeFeatureFactory;
    private FakeSettingsPanelActivity mSettingsPanelActivity;
    private PanelFeatureProvider mPanelFeatureProvider;
    private FakePanelContent mFakePanelContent;
    @Mock
    private PanelFragment mPanelFragment;
    @Mock
    private FragmentManager mFragmentManager;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mFakeFeatureFactory = FakeFeatureFactory.setupForTest();
        mSettingsPanelActivity = spy(
                Robolectric.buildActivity(FakeSettingsPanelActivity.class).create().get());
        mPanelFeatureProvider = spy(new PanelFeatureProviderImpl());
        mFakeFeatureFactory.panelFeatureProvider = mPanelFeatureProvider;
        mFakePanelContent = new FakePanelContent();
        doReturn(mFakePanelContent).when(mPanelFeatureProvider).getPanel(any(), any());

        mSettingsPanelActivity.mPanelFragment = mPanelFragment;
        when(mFragmentManager.findFragmentById(R.id.main_content)).thenReturn(mPanelFragment);
        when(mSettingsPanelActivity.getSupportFragmentManager()).thenReturn(mFragmentManager);
    }

    @Test
    public void onStart_isNotDebuggable_shouldHideSystemOverlay() {
        ReflectionHelpers.setStaticField(Build.class, "IS_DEBUGGABLE", false);

        final ActivityController<SettingsPanelActivity> activityController =
                Robolectric.buildActivity(SettingsPanelActivity.class).create();
        final SettingsPanelActivity activity = spy(activityController.get());
        final Window window = mock(Window.class);
        when(activity.getWindow()).thenReturn(window);
        activity.getLifecycle().addObserver(new HideNonSystemOverlayMixin(activity));

        activityController.start();

        verify(window).addSystemFlags(SYSTEM_FLAG_HIDE_NON_SYSTEM_OVERLAY_WINDOWS);
    }

    @Test
    public void onStop_isNotDebuggable_shouldRemoveHideSystemOverlay() {
        ReflectionHelpers.setStaticField(Build.class, "IS_DEBUGGABLE", false);

        final ActivityController<SettingsPanelActivity> activityController =
                Robolectric.buildActivity(SettingsPanelActivity.class).create();
        final SettingsPanelActivity activity = spy(activityController.get());
        final Window window = mock(Window.class);
        when(activity.getWindow()).thenReturn(window);
        activity.getLifecycle().addObserver(new HideNonSystemOverlayMixin(activity));

        activityController.start();

        verify(window).addSystemFlags(SYSTEM_FLAG_HIDE_NON_SYSTEM_OVERLAY_WINDOWS);

        final WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams();
        when(window.getAttributes()).thenReturn(layoutParams);

        activityController.stop();
        final ArgumentCaptor<WindowManager.LayoutParams> paramCaptor = ArgumentCaptor.forClass(
                WindowManager.LayoutParams.class);

        verify(window).setAttributes(paramCaptor.capture());
        assertThat(paramCaptor.getValue().privateFlags
                & SYSTEM_FLAG_HIDE_NON_SYSTEM_OVERLAY_WINDOWS).isEqualTo(0);
    }

    @Test
    public void onStop_panelIsNotCreating_shouldForceUpdate() {
        mSettingsPanelActivity.mForceCreation = false;
        when(mPanelFragment.isPanelCreating()).thenReturn(false);
        mSettingsPanelActivity.mPanelFragment = mPanelFragment;

        mSettingsPanelActivity.onStop();

        assertThat(mSettingsPanelActivity.mForceCreation).isTrue();
    }

    @Test
    public void onStop_panelIsCreating_shouldNotForceUpdate() {
        mSettingsPanelActivity.mForceCreation = false;
        when(mPanelFragment.isPanelCreating()).thenReturn(true);
        mSettingsPanelActivity.mPanelFragment = mPanelFragment;

        mSettingsPanelActivity.onStop();

        assertThat(mSettingsPanelActivity.mForceCreation).isFalse();
    }

    @Test
    public void onConfigurationChanged_shouldForceUpdate() {
        mSettingsPanelActivity.mForceCreation = false;

        mSettingsPanelActivity.onConfigurationChanged(new Configuration());

        assertThat(mSettingsPanelActivity.mForceCreation).isTrue();
    }

    @Test
    public void onNewIntent_panelIsNotCreating_shouldUpdatePanel() {
        when(mPanelFragment.isPanelCreating()).thenReturn(false);

        mSettingsPanelActivity.onNewIntent(mSettingsPanelActivity.getIntent());

        verify(mPanelFragment).updatePanelWithAnimation();
    }

    @Test
    public void onNewIntent_panelIsCreating_shouldNotUpdatePanel() {
        when(mPanelFragment.isPanelCreating()).thenReturn(true);

        mSettingsPanelActivity.onNewIntent(mSettingsPanelActivity.getIntent());

        verify(mPanelFragment, never()).updatePanelWithAnimation();
    }

    @Test
    public void onNewIntent_panelIsShowingTheSameAction_shouldNotUpdatePanel() {
        when(mPanelFragment.isPanelCreating()).thenReturn(false);
        when(mPanelFragment.getArguments()).thenReturn(mSettingsPanelActivity.mBundle);

        mSettingsPanelActivity.onNewIntent(mSettingsPanelActivity.getIntent());

        verify(mPanelFragment, never()).updatePanelWithAnimation();
    }
}
