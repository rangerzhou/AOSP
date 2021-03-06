/*
 * Copyright (C) 2007 The Android Open Source Project
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

package android.widget.layout.linear;

import android.app.Activity;
import android.test.ActivityInstrumentationTestCase;
import android.view.View;

import androidx.test.filters.MediumTest;

import com.android.frameworks.coretests.R;

public class FillInWrapTest extends ActivityInstrumentationTestCase<FillInWrap> {
    private View mChild;
    private View mContainer;

    public FillInWrapTest() {
        super("com.android.frameworks.coretests", FillInWrap.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();

        final Activity activity = getActivity();
        mChild = activity.findViewById(R.id.data);
        mContainer = activity.findViewById(R.id.layout);
    }

    @MediumTest
    public void testPreconditions() {
        assertNotNull(mChild);
        assertNotNull(mContainer);
    }

    @MediumTest
    public void testLayout() {
        assertTrue("the child's height should be less than the parent's",
                mChild.getMeasuredHeight() < mContainer.getMeasuredHeight());
    }
}
