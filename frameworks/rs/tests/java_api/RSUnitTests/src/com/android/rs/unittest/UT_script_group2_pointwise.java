/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

package com.android.rs.unittest;

import android.content.Context;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.ScriptGroup;
import android.renderscript.Type;
import android.util.Log;

public class UT_script_group2_pointwise extends UnitTest {
    private static final int ARRAY_SIZE = 256;

    private static final String TAG = "ScriptGroup2 (Pointwise)";

    public UT_script_group2_pointwise(Context ctx) {
        super(TAG, ctx);
    }

    public void run() {
        RenderScript pRS = createRenderScript(false);
        ScriptC_increment s_inc = new ScriptC_increment(pRS);
        ScriptC_double s_double = new ScriptC_double(pRS);

        int[] array = new int[ARRAY_SIZE * 4];

        for (int i = 0; i < ARRAY_SIZE * 4; i++) {
            array[i] = i;
        }

        Allocation input = Allocation.createSized(pRS, Element.I32_4(pRS), ARRAY_SIZE);
        input.copyFrom(array);

        ScriptGroup.Builder2 builder = new ScriptGroup.Builder2(pRS);

        ScriptGroup.Input unbound = builder.addInput();

        Type T = Type.createX(pRS, Element.I32_4(pRS), ARRAY_SIZE);

        ScriptGroup.Closure c0 =
                builder.addKernel(s_inc.getKernelID_increment(),
                                  T,
                                  unbound);

        ScriptGroup.Closure c1 =
                builder.addKernel(s_double.getKernelID_doubleKernel(),
                                  T,
                                  c0.getReturn());

        ScriptGroup group = builder.create("AddDouble", c1.getReturn());

        int[] a = new int[ARRAY_SIZE * 4];
        ((Allocation) group.execute(input)[0]).copyTo(a);

        pRS.finish();
        group.destroy();
        T.destroy();
        input.destroy();
        s_double.destroy();
        s_inc.destroy();
        pRS.destroy();

        boolean failed = false;
        for (int i = 0; i < ARRAY_SIZE * 4; i++) {
            if (a[i] != (i + 1) * 2) {
                Log.e(TAG, "a[" + i + "]=" + a[i] + ", should be " + ((i + 1) * 2));
                failed = true;
            }
        }
        if (failed) {
            failTest();
            return;
        }
        passTest();
    }
}
