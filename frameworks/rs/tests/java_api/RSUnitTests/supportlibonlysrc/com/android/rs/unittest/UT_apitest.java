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
import android.content.res.Resources;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.RenderScript;
import android.renderscript.Sampler;
import android.renderscript.Type;

public class UT_apitest extends UnitTest {

    public UT_apitest(Context ctx) {
        super("API Test", ctx);
    }

    public void run() {
        RenderScript pRS = createRenderScript(true);
        ScriptC_apitest s = new ScriptC_apitest(pRS);
        Element elem = Element.I8(pRS);
        Type.Builder typeBuilder = new Type.Builder(pRS, elem);

        int x = 5;
        int y = 7;
        int z = 0;  // Don't actually setZ()
        s.set_x(x);
        s.set_y(y);
        s.set_z(z);
        typeBuilder.setX(x).setY(y);
        Type type = typeBuilder.create();
        Allocation alloc = Allocation.createTyped(pRS, type);
        Allocation allocDst = Allocation.createTyped(pRS, type);
        Sampler sampler = Sampler.CLAMP_NEAREST(pRS);
        s.set_elemNonNull(elem);
        s.set_typeNonNull(type);
        s.set_allocNonNull(alloc);
        s.set_allocDst(allocDst);
        s.set_samplerNonNull(sampler);
        s.set_scriptNonNull(s);
        s.bind_allocPtr(alloc);

        s.invoke_api_test();
        pRS.finish();
        pRS.destroy();
    }
}
