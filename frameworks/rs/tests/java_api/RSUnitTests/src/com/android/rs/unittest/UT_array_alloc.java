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

public class UT_array_alloc extends UnitTest {

    public UT_array_alloc(Context ctx) {
        super("Array Allocation", ctx);
    }

    public void run() {
        RenderScript pRS = createRenderScript(true);
        ScriptC_array_alloc s = new ScriptC_array_alloc(pRS);

        int dimX = s.get_dimX();
        Allocation[] Arr = new Allocation[dimX];
        Type.Builder typeBuilder = new Type.Builder(pRS, Element.I32(pRS));
        Type T = typeBuilder.setX(1).create();
        for (int i = 0; i < dimX; i++) {
            Allocation A = Allocation.createTyped(pRS, T);
            Arr[i] = A;
        }
        s.set_a(Arr);

        s.invoke_array_alloc_test();
        pRS.finish();
        for (int i = 0; i < dimX; i++) {
            Arr[i].destroy();
        }
        T.destroy();
        s.destroy();
        pRS.destroy();
        passTest();
    }
}
