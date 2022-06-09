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

package com.android.settings.widget;

import static android.view.HapticFeedbackConstants.CLOCK_TICK;
import static android.view.HapticFeedbackConstants.CONTEXT_CLICK;

import static com.google.common.truth.Truth.assertThat;

import static org.robolectric.Shadows.shadowOf;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.SeekBar;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import org.robolectric.RuntimeEnvironment;

@RunWith(RobolectricTestRunner.class)
public class LabeledSeekBarTest {

    private Context mContext;
    private AttributeSet mAttrs;
    private SeekBar mSeekBar;
    private LabeledSeekBar mLabeledSeekBar;
    private SeekBar.OnSeekBarChangeListener mProxySeekBarListener;

    @Before
    public void setUp() {
        mContext = RuntimeEnvironment.application;
        mSeekBar = new SeekBar(mContext, mAttrs);
        mLabeledSeekBar = new LabeledSeekBar(mContext, mAttrs);
        mProxySeekBarListener = shadowOf(mLabeledSeekBar).getOnSeekBarChangeListener();
    }

    @Test
    public void onProgressChanged_minimumValue_clockTickFeedbackPerformed() {
        mSeekBar.performHapticFeedback(CONTEXT_CLICK);
        mProxySeekBarListener.onProgressChanged(mSeekBar, 0, true);

        assertThat(shadowOf(mSeekBar).lastHapticFeedbackPerformed()).isEqualTo(CLOCK_TICK);
    }
}
