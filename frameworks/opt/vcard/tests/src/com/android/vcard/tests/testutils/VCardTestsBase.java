/*
 * Copyright (C) 2009 The Android Open Source Project
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
package com.android.vcard.tests.testutils;

import android.content.ContentValues;
import android.test.AndroidTestCase;

import com.android.vcard.VCardConfig;
import com.android.vcard.tests.testutils.VCardVerifier;

/**
 * BaseClass for vCard unit tests with utility classes.
 * Please do not add each unit test here.
 */
public abstract class VCardTestsBase extends AndroidTestCase {
    public static final int V21 = VCardConfig.VCARD_TYPE_V21_GENERIC;
    public static final int V30 = VCardConfig.VCARD_TYPE_V30_GENERIC;
    public static final int V40 = VCardConfig.VCARD_TYPE_V40_GENERIC;

    // Do not modify these during tests.
    protected final ContentValues mContentValuesForQP;
    protected final ContentValues mContentValuesForSJis;
    protected final ContentValues mContentValuesForUtf8;
    protected final ContentValues mContentValuesForQPAndSJis;
    protected final ContentValues mContentValuesForQPAndUtf8;
    protected final ContentValues mContentValuesForBase64V21;
    protected final ContentValues mContentValuesForBase64V30;

    protected VCardVerifier mVerifier;
    /**
     * true when we shouldn't call {@link VCardVerifier#verify()}.
     */
    private boolean mSkipVerification;

    public VCardTestsBase() {
        super();
        // Not using constants in vCard code since it may be wrong.
        mContentValuesForQP = new ContentValues();
        mContentValuesForQP.put("ENCODING", "QUOTED-PRINTABLE");
        mContentValuesForSJis = new ContentValues();
        mContentValuesForSJis.put("CHARSET", "SHIFT_JIS");
        mContentValuesForUtf8 = new ContentValues();
        mContentValuesForUtf8.put("CHARSET", "UTF-8");
        mContentValuesForQPAndSJis = new ContentValues();
        mContentValuesForQPAndSJis.put("ENCODING", "QUOTED-PRINTABLE");
        mContentValuesForQPAndSJis.put("CHARSET", "SHIFT_JIS");
        mContentValuesForQPAndUtf8 = new ContentValues();
        mContentValuesForQPAndUtf8.put("ENCODING", "QUOTED-PRINTABLE");
        mContentValuesForQPAndUtf8.put("CHARSET", "UTF-8");
        mContentValuesForBase64V21 = new ContentValues();
        mContentValuesForBase64V21.put("ENCODING", "BASE64");
        mContentValuesForBase64V30 = new ContentValues();
        mContentValuesForBase64V30.put("ENCODING", "b");
    }

    @Override
    public void testAndroidTestCaseSetupProperly() {
        super.testAndroidTestCaseSetupProperly();
        mSkipVerification = true;
    }

    /**
     * Calls super's {@link #setUp()} and prepares {@link VCardVerifier}. We call
     * {@link VCardVerifier#verify()} on {@link #tearDown()}.
     */
    @Override
    public final void setUp() throws Exception{
        super.setUp();
        mVerifier = new VCardVerifier(this);
        mSkipVerification = false;
    }

    /**
     * Calls super's {@link #tearDown()} and {@link VCardVerifier#verify()}.
     */
    @Override
    public final void tearDown() throws Exception {
        // We don't want to forget to call verify() as it makes unit test successful silently even
        // when it shouldn't be, while each test case tends become so large to manage and sometimes
        // we had forgotten to call the method. That is why we override setUp()/tearDown() here.
        if (!mSkipVerification) {
            mVerifier.verify();
        }
        super.tearDown();
    }
}
