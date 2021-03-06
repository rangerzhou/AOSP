/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
package com.android.multidexlegacytestapp.test2;

import androidx.test.runner.AndroidJUnit4;

import com.android.multidexlegacytestapp.manymethods.Big001;
import com.android.multidexlegacytestapp.manymethods.Big079;

import junit.framework.Assert;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Run the tests with: <code>adb shell am instrument -w
 com.android.multidexlegacytestapp.test2/com.android.multidexlegacytestapp.test2.MultiDexAndroidJUnitRunner
</code>
 */
@RunWith(AndroidJUnit4.class)
public class InstrumentationTest {

    @Test
    public void exceptionInMainDex() {
      Assert.assertEquals(0, new Big001().get0());
      Assert.assertEquals(100, new Big079().get100());
    }

    @Test
    public void multidexedTest() {
      Assert.assertEquals(7, Intermediate.get());
    }

}
