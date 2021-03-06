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

package android.widget.listview;

import android.test.ActivityInstrumentationTestCase;
import android.widget.ListView;

import androidx.test.filters.MediumTest;

public class ListBottomGravityManyTest extends ActivityInstrumentationTestCase<ListBottomGravityMany> {
    private ListBottomGravityMany mActivity;
    private ListView mListView;

    public ListBottomGravityManyTest() {
        super("com.android.frameworks.coretests", ListBottomGravityMany.class);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();

        mActivity = getActivity();
        mListView = getActivity().getListView();
    }

    @MediumTest
    public void testPreconditions() {
        assertNotNull(mActivity);
        assertNotNull(mListView);
        
        // Last item should be selected
        assertEquals(mListView.getAdapter().getCount() - 1, mListView.getSelectedItemPosition());
    }
}
