/*
 * Copyright (C) 2011 The Android Open Source Project
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
package com.android.vcard.tests;

import com.android.vcard.tests.testutils.VCardTestsBase;

/**
 * Test cases specific for nested vCard.
 */
public class VCardImporterNestTests extends VCardTestsBase {
    public void testSimpleNest() {
        mVerifier.initForImportTest(V21, R.raw.v21_nest);
        mVerifier.addPropertyNodesVerifierElem()
                .addExpectedNodeWithOrder("N", "nest1");
        mVerifier.addPropertyNodesVerifierElem()
                .addExpectedNodeWithOrder("N", "nest2");
        // Parent comes last.
        mVerifier.addPropertyNodesVerifierElem()
                .addExpectedNodeWithOrder("N", "parent")
                .addExpectedNodeWithOrder("TEL", "1");
    }

    public void testSimpleNestWithMime() {
        mVerifier.initForImportTest(V21, R.raw.v21_nest_with_mime);
        mVerifier.addPropertyNodesVerifierElem()
                .addExpectedNodeWithOrder("N", "nest1");
        mVerifier.addPropertyNodesVerifierElem()
                .addExpectedNodeWithOrder("N", "nest2");
        // Parent comes last.
        mVerifier.addPropertyNodesVerifierElem()
                .addExpectedNodeWithOrder("N", "parent")
                .addExpectedNodeWithOrder("TEL", "1");
    }
}
