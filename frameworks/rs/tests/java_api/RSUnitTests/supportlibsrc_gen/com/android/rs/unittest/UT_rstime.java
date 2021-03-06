// This file is automatically generated from
// frameworks/rs/tests/java_api/RSUnitTests/RSUnitTests.py
/*
 * Copyright (C) 2017 The Android Open Source Project
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

package com.android.rs.unittest;

import android.content.Context;
import androidx.renderscript.RenderScript;

public class UT_rstime extends UnitTest {

    public UT_rstime(Context ctx) {
        super("rsTime", ctx);
    }

    public void run() {
        RenderScript pRS = createRenderScript(true);
        ScriptC_rstime s = new ScriptC_rstime(pRS);
        s.setTimeZone("America/Los_Angeles");
        s.invoke_test_rstime(0, 0);
        pRS.finish();
        s.destroy();
        pRS.destroy();
    }
}
