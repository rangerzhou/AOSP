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

package com.android.internal.telephony;

import static org.junit.Assert.fail;

import android.test.suitebuilder.annotation.SmallTest;

import org.junit.Test;

public class PhoneFactoryTest {
    @Test
    @SmallTest
    public void testBeforeMakePhone() {
        try {
            PhoneFactory.getDefaultPhone();
            fail("Expecting IllegalStateException");
        } catch (IllegalStateException e) {
        }

        try {
            PhoneFactory.getPhone(0);
            fail("Expecting IllegalStateException");
        } catch (IllegalStateException e) {
        }

        try {
            PhoneFactory.getPhones();
            fail("Expecting IllegalStateException");
        } catch (IllegalStateException e) {
        }

        try {
            PhoneFactory.getNetworkFactory(0);
            fail("Expecting IllegalStateException");
        } catch (IllegalStateException e) {
        }
    }

    //todo: add test for makeDefaultPhone(). will need some refactoring in PhoneFactory.
}
