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

package com.android.internal.telephony;

import static com.android.internal.telephony.ProxyController.EVENT_MULTI_SIM_CONFIG_CHANGED;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyInt;
import static org.mockito.Mockito.verify;

import android.os.Handler;
import android.os.Message;
import android.test.suitebuilder.annotation.SmallTest;
import android.testing.AndroidTestingRunner;
import android.testing.TestableLooper;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Mock;

@RunWith(AndroidTestingRunner.class)
@TestableLooper.RunWithLooper
public class ProxyControllerTest extends TelephonyTest {
    @Mock
    Phone mPhone2;

    ProxyController mProxyController;

    @Before
    public void setUp() throws Exception {
        super.setUp(getClass().getSimpleName());
        replaceInstance(ProxyController.class, "sProxyController", null, null);
        mProxyController = ProxyController.getInstance(mContext);
    }

    @After
    public void tearDown() throws Exception {
        // Restore system properties.
        super.tearDown();
    }

    @Test
    @SmallTest
    public void testMultiSimConfigChange() throws Exception {
        ArgumentCaptor<Handler> handlerCaptor = ArgumentCaptor.forClass(Handler.class);
        ArgumentCaptor<Integer> intCaptor = ArgumentCaptor.forClass(int.class);

        // Switch to dual-SIM and send multi sim config change callback.
        replaceInstance(PhoneFactory.class, "sPhones", null, new Phone[] {mPhone, mPhone2});
        Message.obtain(mProxyController.mHandler, EVENT_MULTI_SIM_CONFIG_CHANGED).sendToTarget();
        processAllMessages();
        verify(mPhone2).registerForRadioCapabilityChanged(any(), anyInt(), any());

        // Switch to single-SIM and verify there's at least no crash.
        replaceInstance(PhoneFactory.class, "sPhones", null, new Phone[] {mPhone});
        Message.obtain(mProxyController.mHandler, EVENT_MULTI_SIM_CONFIG_CHANGED).sendToTarget();
        processAllMessages();
    }
}
