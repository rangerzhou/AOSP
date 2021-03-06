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
import androidx.renderscript.Element;
import androidx.renderscript.Element.DataKind;
import androidx.renderscript.Element.DataType;
import androidx.renderscript.RenderScript;

public class UT_element extends UnitTest {
    Element simpleElem;
    Element complexElem;

    final String subElemNames[] = {
            "subElem0",
            "subElem1",
            "subElem2",
            "arrayElem0",
            "arrayElem1",
            "subElem3",
            "subElem4",
            "subElem5",
            "subElem6",
            "subElem_7",
    };

    final int subElemArraySizes[] = {
            1,
            1,
            1,
            2,
            5,
            1,
            1,
            1,
            1,
            1,
    };

    final int subElemOffsets[] = {
            0,
            4,
            8,
            12,
            20,
            40,
            44,
            48,
            64,
            80,
    };

    public UT_element(Context ctx) {
        super("Element", ctx);
    }

    private void initializeGlobals(RenderScript RS, ScriptC_element s) {
        simpleElem = Element.F32_3(RS);
        complexElem = ScriptField_ComplexStruct.createElement(RS);
        s.set_simpleElem(simpleElem);
        s.set_complexElem(complexElem);

        ScriptField_ComplexStruct data = new ScriptField_ComplexStruct(RS, 1);
        s.bind_complexStruct(data);
    }

    private void testScriptSide(RenderScript pRS) {
        ScriptC_element s = new ScriptC_element(pRS);
        initializeGlobals(pRS, s);
        s.invoke_element_test();
        pRS.finish();
        s.get_complexStruct().getAllocation().destroy();
        s.get_complexStruct().getElement().destroy();
        s.destroy();
    }

    private void testJavaSide(RenderScript RS) {

        int subElemCount = simpleElem.getSubElementCount();
        _RS_ASSERT("subElemCount == 0", subElemCount == 0);
        _RS_ASSERT("simpleElem.getDataKind() == USER",
                simpleElem.getDataKind() == DataKind.USER);
        _RS_ASSERT("simpleElem.getDataType() == FLOAT_32",
                simpleElem.getDataType() == DataType.FLOAT_32);

        subElemCount = complexElem.getSubElementCount();
        _RS_ASSERT("subElemCount == 10", subElemCount == 10);
        _RS_ASSERT("complexElem.getDataKind() == USER",
                complexElem.getDataKind() == DataKind.USER);
        _RS_ASSERT("complexElemsimpleElem.getDataType() == NONE",
                complexElem.getDataType() == DataType.NONE);

        for (int i = 0; i < subElemCount; i++) {
            _RS_ASSERT("complexElem.getSubElement(i) != null",
                    complexElem.getSubElement(i) != null);
            _RS_ASSERT("complexElem.getSubElementName(i).equals(subElemNames[i])",
                    complexElem.getSubElementName(i).equals(subElemNames[i]));
            _RS_ASSERT("complexElem.getSubElementArraySize(i) == subElemArraySizes[i]",
                    complexElem.getSubElementArraySize(i) == subElemArraySizes[i]);
            _RS_ASSERT("complexElem.getSubElementOffsetBytes(i) == subElemOffsets[i]",
                    complexElem.getSubElementOffsetBytes(i) == subElemOffsets[i]);
        }
    }

    public void run() {
        RenderScript pRS = createRenderScript(true);
        testScriptSide(pRS);
        testJavaSide(pRS);
        passTest();
        pRS.destroy();
    }
}
