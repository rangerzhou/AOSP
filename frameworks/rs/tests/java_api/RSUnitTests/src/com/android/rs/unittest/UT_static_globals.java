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
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.Type;

public class UT_static_globals extends UnitTest {

    public UT_static_globals(Context ctx) {
        super("Static Globals", ctx);
    }

    public void run() {
        RenderScript pRS = createRenderScript(true);
        ScriptC_static_globals s = new ScriptC_static_globals(pRS);
        Type.Builder typeBuilder = new Type.Builder(pRS, Element.I32(pRS));
        Type t = typeBuilder.setX(1).create();
        Allocation A = Allocation.createTyped(pRS, t);
        s.forEach_root(A);
        s.invoke_static_globals_test();
        pRS.finish();
        A.destroy();
        t.destroy();
        s.destroy();
        pRS.destroy();
    }
}
