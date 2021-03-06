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

/* This is a much simpler version of UT_reduce.java that
 * exercises pragmas after the functions (backward reference),
 * whereas the other test case exercises the pragmas before the
 * functions (forward reference).
 */

package com.android.rs.unittest;

import android.content.Context;
import android.renderscript.Allocation;
import android.renderscript.Element;
import android.renderscript.Float2;
import android.renderscript.Int2;
import android.renderscript.Int3;
import android.renderscript.RenderScript;
import android.renderscript.ScriptIntrinsicHistogram;
import android.renderscript.Type;
import android.util.Log;

import java.util.Random;

public class UT_reduce_backward extends UnitTest {
    private static final String TAG = "reduce_backward";

    public UT_reduce_backward(Context ctx) {
        super("reduce_backward", ctx);
    }

    private byte[] createInputArrayByte(int len, int seed) {
        byte[] array = new byte[len];
        (new Random(seed)).nextBytes(array);
        return array;
    }

    private float[] createInputArrayFloat(int len, int seed) {
        Random rand = new Random(seed);
        float[] array = new float[len];
        for (int i = 0; i < len; ++i)
            array[i] = rand.nextFloat();
        return array;
    }

    private int[] createInputArrayInt(int len, int seed) {
        Random rand = new Random(seed);
        int[] array = new int[len];
        for (int i = 0; i < len; ++i)
            array[i] = rand.nextInt();
        return array;
    }

    private int[] createInputArrayInt(int len, int seed, int eltRange) {
        Random rand = new Random(seed);
        int[] array = new int[len];
        for (int i = 0; i < len; ++i)
            array[i] = rand.nextInt(eltRange);
        return array;
    }

    private <T extends Number> boolean result(String testName, T javaRslt, T rsRslt) {
        final boolean success = javaRslt.equals(rsRslt);
        Log.i(TAG,
                testName + ": java " + javaRslt + ", rs " + rsRslt + ": " +
                        (success ? "PASSED" : "FAILED"));
        return success;
    }

    private boolean result(String testName, Float2 javaRslt, Float2 rsRslt) {
        final boolean success = (javaRslt.x == rsRslt.x) && (javaRslt.y == rsRslt.y);
        Log.i(TAG,
                testName +
                        ": java (" + javaRslt.x + ", " + javaRslt.y + ")" +
                        ", rs (" + rsRslt.x + ", " + rsRslt.y + ")" +
                        ": " + (success ? "PASSED" : "FAILED"));
        return success;
    }

    private boolean result(String testName, Int2 javaRslt, Int2 rsRslt) {
        final boolean success = (javaRslt.x == rsRslt.x) && (javaRslt.y == rsRslt.y);
        Log.i(TAG,
                testName +
                        ": java (" + javaRslt.x + ", " + javaRslt.y + ")" +
                        ", rs (" + rsRslt.x + ", " + rsRslt.y + ")" +
                        ": " + (success ? "PASSED" : "FAILED"));
        return success;
    }

    ///////////////////////////////////////////////////////////////////

    private int addint(int[] input) {
        int rslt = 0;
        for (int idx = 0; idx < input.length; ++idx)
            rslt += input[idx];
        return rslt;
    }

    private boolean addint1D(RenderScript RS, ScriptC_reduce_backward s) {
        final int[] input = createInputArrayInt(100000, 0, 1 << 13);

        final int javaRslt = addint(input);
        final int rsRslt = s.reduce_addint(input).get();

        return result("addint1D", javaRslt, rsRslt);
    }

    private boolean addint2D(RenderScript RS, ScriptC_reduce_backward s) {
        final int dimX = 450, dimY = 225;

        final int[] inputArray = createInputArrayInt(dimX * dimY, 1, 1 << 13);
        Type.Builder typeBuilder = new Type.Builder(RS, Element.I32(RS));
        typeBuilder.setX(dimX).setY(dimY);
        Allocation inputAllocation = Allocation.createTyped(RS, typeBuilder.create());
        inputAllocation.copy2DRangeFrom(0, 0, dimX, dimY, inputArray);

        final int javaRslt = addint(inputArray);
        final int rsRslt = s.reduce_addint(inputAllocation).get();

        return result("addint2D", javaRslt, rsRslt);
    }

    ///////////////////////////////////////////////////////////////////

    private Int2 findMinAndMax(float[] input) {
        float minVal = Float.POSITIVE_INFINITY;
        int minIdx = -1;
        float maxVal = Float.NEGATIVE_INFINITY;
        int maxIdx = -1;

        for (int idx = 0; idx < input.length; ++idx) {
            if (input[idx] < minVal) {
                minVal = input[idx];
                minIdx = idx;
            }
            if (input[idx] > maxVal) {
                maxVal = input[idx];
                maxIdx = idx;
            }
        }

        return new Int2(minIdx, maxIdx);
    }

    private boolean findMinAndMax(RenderScript RS, ScriptC_reduce_backward s) {
        final float[] input = createInputArrayFloat(100000, 4);

        final Int2 javaRslt = findMinAndMax(input);
        final Int2 rsRslt = s.reduce_findMinAndMax(input).get();

        // Note that the Java and RenderScript algorithms are not
        // guaranteed to find the same cells -- but they should
        // find cells of the same value.
        final Float2 javaVal = new Float2(input[javaRslt.x], input[javaRslt.y]);
        final Float2 rsVal = new Float2(input[rsRslt.x], input[rsRslt.y]);

        return result("findMinAndMax", javaVal, rsVal);
    }

    ///////////////////////////////////////////////////////////////////

    private boolean fz(RenderScript RS, ScriptC_reduce_backward s) {
        final int inputLen = 100000;
        int[] input = createInputArrayInt(inputLen, 5);
        // just in case we got unlucky
        input[(new Random(6)).nextInt(inputLen)] = 0;

        final int rsRslt = s.reduce_fz(input).get();

        final boolean success = (input[rsRslt] == 0);
        Log.i(TAG,
                "fz: input[" + rsRslt + "] == " + input[rsRslt] + ": " +
                        (success ? "PASSED" : "FAILED"));
        return success;
    }

    ///////////////////////////////////////////////////////////////////

    private boolean fz2(RenderScript RS, ScriptC_reduce_backward s) {
        final int dimX = 225, dimY = 450;
        final int inputLen = dimX * dimY;

        int[] inputArray = createInputArrayInt(inputLen, 7);
        // just in case we got unlucky
        inputArray[(new Random(8)).nextInt(inputLen)] = 0;

        Type.Builder typeBuilder = new Type.Builder(RS, Element.I32(RS));
        typeBuilder.setX(dimX).setY(dimY);
        Allocation inputAllocation = Allocation.createTyped(RS, typeBuilder.create());
        inputAllocation.copy2DRangeFrom(0, 0, dimX, dimY, inputArray);

        final Int2 rsRslt = s.reduce_fz2(inputAllocation).get();

        final int cellVal = inputArray[rsRslt.x + dimX * rsRslt.y];
        final boolean success = (cellVal == 0);
        Log.i(TAG,
                "fz2: input[" + rsRslt.x + ", " + rsRslt.y + "] == " + cellVal + ": " +
                        (success ? "PASSED" : "FAILED"));
        return success;
    }

    ///////////////////////////////////////////////////////////////////

    private boolean fz3(RenderScript RS, ScriptC_reduce_backward s) {
        final int dimX = 59, dimY = 48, dimZ = 37;
        final int inputLen = dimX * dimY * dimZ;

        int[] inputArray = createInputArrayInt(inputLen, 9);
        // just in case we got unlucky
        inputArray[(new Random(10)).nextInt(inputLen)] = 0;

        Type.Builder typeBuilder = new Type.Builder(RS, Element.I32(RS));
        typeBuilder.setX(dimX).setY(dimY).setZ(dimZ);
        Allocation inputAllocation = Allocation.createTyped(RS, typeBuilder.create());
        inputAllocation.copy3DRangeFrom(0, 0, 0, dimX, dimY, dimZ, inputArray);

        final Int3 rsRslt = s.reduce_fz3(inputAllocation).get();

        final int cellVal = inputArray[rsRslt.x + dimX * rsRslt.y + dimX * dimY * rsRslt.z];
        final boolean success = (cellVal == 0);
        Log.i(TAG,
                "fz3: input[" + rsRslt.x + ", " + rsRslt.y + ", " + rsRslt.z + "] == " + cellVal + ": " +
                        (success ? "PASSED" : "FAILED"));
        return success;
    }

    ///////////////////////////////////////////////////////////////////

    private static final int histogramBucketCount = 256;

    private long[] histogram(RenderScript RS, final byte[] inputArray) {
        Allocation inputAllocation = Allocation.createSized(RS, Element.U8(RS), inputArray.length);
        inputAllocation.copyFrom(inputArray);

        Allocation outputAllocation = Allocation.createSized(RS, Element.U32(RS), histogramBucketCount);

        ScriptIntrinsicHistogram scriptHsg = ScriptIntrinsicHistogram.create(RS, Element.U8(RS));
        scriptHsg.setOutput(outputAllocation);
        scriptHsg.forEach(inputAllocation);

        int[] outputArrayMistyped = new int[histogramBucketCount];
        outputAllocation.copyTo(outputArrayMistyped);

        long[] outputArray = new long[histogramBucketCount];
        for (int i = 0; i < histogramBucketCount; ++i)
            outputArray[i] = outputArrayMistyped[i] & (long) 0xffffffff;
        return outputArray;
    }

    private boolean histogram(RenderScript RS, ScriptC_reduce_backward s) {
        final byte[] inputArray = createInputArrayByte(100000, 11);

        final long[] javaRslt = histogram(RS, inputArray);
        _RS_ASSERT("javaRslt unexpected length: " + javaRslt.length, javaRslt.length == histogramBucketCount);
        final long[] rsRslt = s.reduce_histogram(inputArray).get();
        _RS_ASSERT("rsRslt unexpected length: " + rsRslt.length, rsRslt.length == histogramBucketCount);

        for (int i = 0; i < histogramBucketCount; ++i) {
            if (javaRslt[i] != rsRslt[i]) {
                Log.i(TAG,
                        "histogram[" + i + "]: java " + javaRslt[i] + ", rs " + rsRslt[i] + ": FAILED");
                return false;
            }
        }

        Log.i(TAG, "histogram: PASSED");
        return true;
    }

    //-----------------------------------------------------------------

    private Int2 mode(RenderScript RS, final byte[] inputArray) {
        long[] hsg = histogram(RS, inputArray);

        int modeIdx = 0;
        for (int i = 1; i < hsg.length; ++i)
            if (hsg[i] > hsg[modeIdx]) modeIdx = i;
        return new Int2(modeIdx, (int) hsg[modeIdx]);
    }

    private boolean mode(RenderScript RS, ScriptC_reduce_backward s) {
        final byte[] inputArray = createInputArrayByte(100000, 12);

        final Int2 javaRslt = mode(RS, inputArray);
        final Int2 rsRslt = s.reduce_mode(inputArray).get();

        return result("mode", javaRslt, rsRslt);
    }

    ///////////////////////////////////////////////////////////////////

    public void run() {
        RenderScript pRS = createRenderScript(false);
        ScriptC_reduce_backward s = new ScriptC_reduce_backward(pRS);
        s.set_negInf(Float.NEGATIVE_INFINITY);
        s.set_posInf(Float.POSITIVE_INFINITY);

        boolean pass = true;
        pass &= addint1D(pRS, s);
        pass &= addint2D(pRS, s);
        pass &= findMinAndMax(pRS, s);
        pass &= fz(pRS, s);
        pass &= fz2(pRS, s);
        pass &= fz3(pRS, s);
        pass &= histogram(pRS, s);
        pass &= mode(pRS, s);

        pRS.finish();
        pRS.destroy();

        Log.i(TAG, pass ? "PASSED" : "FAILED");
        if (pass)
            passTest();
        else
            failTest();
    }
}
