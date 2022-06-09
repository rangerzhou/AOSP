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

package com.android.preload.check;

/**
 * Test that a helper class is first seen as uninitialized, then initialized after forced.
 */
public class IntegrityCheck {
    public static void main(String[] args) throws Exception {
        ClassLoader loader = IntegrityCheck.class.getClassLoader();

        Util.assertNotInitialized("com.android.preload.check.IntegrityCheck$StatusHelper", loader);

        Class.forName("com.android.preload.check.IntegrityCheck$StatusHelper",
                /* initialize */ true, loader);

        Util.assertInitialized("com.android.preload.check.IntegrityCheck$StatusHelper", loader);

        System.out.println("OK");
    }

    @SuppressWarnings("unused")
    private static class StatusHelper {
        private final static Object defer = new Object();
    }
}
