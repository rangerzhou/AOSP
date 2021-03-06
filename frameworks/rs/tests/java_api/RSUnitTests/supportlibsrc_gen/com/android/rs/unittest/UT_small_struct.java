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
import androidx.renderscript.Allocation;
import androidx.renderscript.RenderScript;
import androidx.renderscript.Type;

// Same as UT_small_struct_2.java except for names of classes and of test.

public class UT_small_struct extends UnitTest {
    private Allocation A;
    private Allocation B;
    private static final int dimX = 3;
    private static final int dimY = 2;

    public UT_small_struct(Context ctx) {
        super("Small Structs", ctx);
    }

    private void initializeGlobals(RenderScript RS, ScriptC_small_struct s) {
        s.set_gDimX(dimX);
        s.set_gDimY(dimY);

        Type.Builder builderA = new Type.Builder(RS, ScriptField_small_struct.createElement(RS));
        builderA.setX(dimX);
        builderA.setY(dimY);

        A = Allocation.createTyped(RS, builderA.create());
        s.set_A(A);

        Type.Builder builderB = new Type.Builder(RS, ScriptField_struct_of_struct.createElement(RS));
        builderB.setX(dimX);
        builderB.setY(dimY);

        B = Allocation.createTyped(RS, builderB.create());
        s.set_B(B);
        return;
    }

    public void run() {
        RenderScript pRS = createRenderScript(true);
        ScriptC_small_struct s = new ScriptC_small_struct(pRS);

        initializeGlobals(pRS, s);
        s.forEach_setStruct(A);
        s.forEach_setArrayOfStruct(B);
        s.invoke_test();

        pRS.finish();
        pRS.destroy();
    }
}
