/*
 * Copyright (C) 2016 The Android Open Source Project
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

package com.android.internal.widget;

import static org.junit.Assert.assertTrue;

import android.content.Context;
import android.text.Layout;
import android.view.View.MeasureSpec;
import android.widget.TextView;

import androidx.test.InstrumentationRegistry;
import androidx.test.filters.SmallTest;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

@SmallTest
public class ImageFloatingTextViewTest {

    private Context mContext;
    private ImageFloatingTextView mView;
    private TextView mTextView;

    @Before
    public void setup() {
        mContext = InstrumentationRegistry.getTargetContext();
        mView = new ImageFloatingTextView(mContext, null, 0, 0);
        mView.setMaxLines(9);
        mTextView = new TextView(mContext, null, 0, 0);
        mTextView.setMaxLines(9);
    }

    @Test
    public void testEmpty() {
        parametrizedTest("");
    }

    @Test
    public void testSingleLine() {
        parametrizedTest("Hello, World!");
    }

    @Test
    public void testTwoLine() {
        parametrizedTest("Hello, World!\nWhat a nice day!");
    }

    @Test
    public void testShort() {
        parametrizedTest("Hello, World! What a nice day! Let's try some more text. "
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet.");
    }

    @Test
    public void testLong() {
        parametrizedTest("Hello, World! What a nice day! Let's try some more text. "
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet."
                + "Yada yada, yada yada. Lorem ipsum dolor sit amet.");
    }

    @Test
    public void usesTransformationMethod() {
        mView.setSingleLine();
        String text = "Test \n Test";
        parametrizedTest(text);
        Layout layout = mView.getLayout();
        Assert.assertFalse("The transformation method wasn't used, string is still the same",
                text.equals(layout.getText()));
    }

    private void parametrizedTest(CharSequence text) {
        int heightMeasureSpec = MeasureSpec.makeMeasureSpec(500, MeasureSpec.AT_MOST);
        int widthMeasureSpec = MeasureSpec.makeMeasureSpec(500, MeasureSpec.EXACTLY);

        mTextView.setText(text);
        mView.setText(text);

        mTextView.measure(widthMeasureSpec, heightMeasureSpec);
        mView.measure(widthMeasureSpec, heightMeasureSpec);

        // We're at most allowed to be the same height as the regular textview and maybe a bit
        // smaller since our layout snaps to full textlines.
        assertTrue("The measured view should never be taller then the normal textview!",
                mView.getMeasuredHeight() <= mTextView.getMeasuredHeight());
    }
}
