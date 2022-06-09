/*
 * Copyright (C) 2013 The Android Open Source Project
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

package android.renderscript;

import java.util.BitSet;

/**
 * Utility class for packing arguments and structures from Android system objects to
 * RenderScript objects.
 *
 * This class is only intended to be used to support the
 * reflected code generated by the RS tool chain.  It should not
 * be called directly.
 *
 * @deprecated Renderscript has been deprecated in API level 31. Please refer to the <a
 * href="https://developer.android.com/guide/topics/renderscript/migration-guide">migration
 * guide</a> for the proposed alternatives.
 **/
@Deprecated
public class FieldPacker {
    public FieldPacker(int len) {
        mPos = 0;
        mLen = len;
        mData = new byte[len];
        mAlignment = new BitSet();
    }

    public FieldPacker(byte[] data) {
        // Advance mPos to the end of the buffer, since we are copying in the
        // full data input.
        mPos = data.length;
        mLen = data.length;
        mData = data;
        mAlignment = new BitSet();
        // TODO: We should either have an actual FieldPacker copy constructor
        // or drop support for computing alignment like this. As it stands,
        // subAlign() can never work correctly for copied FieldPacker objects.
    }

    static FieldPacker createFromArray(Object[] args) {
        FieldPacker fp = new FieldPacker(RenderScript.sPointerSize * 8);
        for (Object arg : args) {
            fp.addSafely(arg);
        }
        fp.resize(fp.mPos);
        return fp;
    }

    public void align(int v) {
        if ((v <= 0) || ((v & (v - 1)) != 0)) {
            throw new RSIllegalArgumentException("argument must be a non-negative non-zero power of 2: " + v);
        }

        while ((mPos & (v - 1)) != 0) {
            mAlignment.flip(mPos);
            mData[mPos++] = 0;
        }
    }

    public void subalign(int v) {
        if ((v & (v - 1)) != 0) {
            throw new RSIllegalArgumentException("argument must be a non-negative non-zero power of 2: " + v);
        }

        while ((mPos & (v - 1)) != 0) {
            mPos--;
        }

        if (mPos > 0) {
            while (mAlignment.get(mPos - 1) == true) {
                mPos--;
                mAlignment.flip(mPos);
            }
        }

    }

    public void reset() {
        mPos = 0;
    }
    public void reset(int i) {
        if ((i < 0) || (i > mLen)) {
            throw new RSIllegalArgumentException("out of range argument: " + i);
        }
        mPos = i;
    }

    public void skip(int i) {
        int res = mPos + i;
        if ((res < 0) || (res > mLen)) {
            throw new RSIllegalArgumentException("out of range argument: " + i);
        }
        mPos = res;
    }

    public void addI8(byte v) {
        mData[mPos++] = v;
    }

    public byte subI8() {
        subalign(1);
        return mData[--mPos];
    }

    public void addI16(short v) {
        align(2);
        mData[mPos++] = (byte)(v & 0xff);
        mData[mPos++] = (byte)(v >> 8);
    }

    public short subI16() {
        subalign(2);
        short v = 0;
        v = (short)((mData[--mPos] & 0xff) << 8);
        v = (short)(v | (short)(mData[--mPos] & 0xff));
        return v;
    }


    public void addI32(int v) {
        align(4);
        mData[mPos++] = (byte)(v & 0xff);
        mData[mPos++] = (byte)((v >> 8) & 0xff);
        mData[mPos++] = (byte)((v >> 16) & 0xff);
        mData[mPos++] = (byte)((v >> 24) & 0xff);
    }

    public int subI32() {
        subalign(4);
        int v = 0;
        v = ((mData[--mPos] & 0xff) << 24);
        v = v | ((mData[--mPos] & 0xff) << 16);
        v = v | ((mData[--mPos] & 0xff) << 8);
        v = v | ((mData[--mPos] & 0xff));
        return v;
    }


    public void addI64(long v) {
        align(8);
        mData[mPos++] = (byte)(v & 0xff);
        mData[mPos++] = (byte)((v >> 8) & 0xff);
        mData[mPos++] = (byte)((v >> 16) & 0xff);
        mData[mPos++] = (byte)((v >> 24) & 0xff);
        mData[mPos++] = (byte)((v >> 32) & 0xff);
        mData[mPos++] = (byte)((v >> 40) & 0xff);
        mData[mPos++] = (byte)((v >> 48) & 0xff);
        mData[mPos++] = (byte)((v >> 56) & 0xff);
    }

    public long subI64() {
        subalign(8);
        long v = 0;
        byte x = 0;
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 56l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 48l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 40l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 32l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 24l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 16l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff) << 8l);
        x = ((mData[--mPos]));
        v = (long)(v | (((long)x) & 0xff));
        return v;
    }

    public void addU8(short v) {
        if ((v < 0) || (v > 0xff)) {
            android.util.Log.e("rs", "FieldPacker.addU8( " + v + " )");
            throw new IllegalArgumentException("Saving value out of range for type");
        }
        mData[mPos++] = (byte)v;
    }

    public void addU16(int v) {
        if ((v < 0) || (v > 0xffff)) {
            android.util.Log.e("rs", "FieldPacker.addU16( " + v + " )");
            throw new IllegalArgumentException("Saving value out of range for type");
        }
        align(2);
        mData[mPos++] = (byte)(v & 0xff);
        mData[mPos++] = (byte)(v >> 8);
    }

    public void addU32(long v) {
        if ((v < 0) || (v > 0xffffffffL)) {
            android.util.Log.e("rs", "FieldPacker.addU32( " + v + " )");
            throw new IllegalArgumentException("Saving value out of range for type");
        }
        align(4);
        mData[mPos++] = (byte)(v & 0xff);
        mData[mPos++] = (byte)((v >> 8) & 0xff);
        mData[mPos++] = (byte)((v >> 16) & 0xff);
        mData[mPos++] = (byte)((v >> 24) & 0xff);
    }

    public void addU64(long v) {
        if (v < 0) {
            android.util.Log.e("rs", "FieldPacker.addU64( " + v + " )");
            throw new IllegalArgumentException("Saving value out of range for type");
        }
        align(8);
        mData[mPos++] = (byte)(v & 0xff);
        mData[mPos++] = (byte)((v >> 8) & 0xff);
        mData[mPos++] = (byte)((v >> 16) & 0xff);
        mData[mPos++] = (byte)((v >> 24) & 0xff);
        mData[mPos++] = (byte)((v >> 32) & 0xff);
        mData[mPos++] = (byte)((v >> 40) & 0xff);
        mData[mPos++] = (byte)((v >> 48) & 0xff);
        mData[mPos++] = (byte)((v >> 56) & 0xff);
    }

    public void addF32(float v) {
        addI32(Float.floatToRawIntBits(v));
    }

    public float subF32() {
        return Float.intBitsToFloat(subI32());
    }

    public void addF64(double v) {
        addI64(Double.doubleToRawLongBits(v));
    }

    public double subF64() {
        return Double.longBitsToDouble(subI64());
    }

    public void addObj(BaseObj obj) {
        if (obj != null) {
            if (RenderScript.sPointerSize == 8) {
                addI64(obj.getID(null));
                addI64(0);
                addI64(0);
                addI64(0);
            } else {
                addI32((int)obj.getID(null));
            }
        } else {
            if (RenderScript.sPointerSize == 8) {
                addI64(0);
                addI64(0);
                addI64(0);
                addI64(0);
            } else {
                addI32(0);
            }
        }
    }

    public void addF32(Float2 v) {
        addF32(v.x);
        addF32(v.y);
    }
    public void addF32(Float3 v) {
        addF32(v.x);
        addF32(v.y);
        addF32(v.z);
    }
    public void addF32(Float4 v) {
        addF32(v.x);
        addF32(v.y);
        addF32(v.z);
        addF32(v.w);
    }

    public void addF64(Double2 v) {
        addF64(v.x);
        addF64(v.y);
    }
    public void addF64(Double3 v) {
        addF64(v.x);
        addF64(v.y);
        addF64(v.z);
    }
    public void addF64(Double4 v) {
        addF64(v.x);
        addF64(v.y);
        addF64(v.z);
        addF64(v.w);
    }

    public void addI8(Byte2 v) {
        addI8(v.x);
        addI8(v.y);
    }
    public void addI8(Byte3 v) {
        addI8(v.x);
        addI8(v.y);
        addI8(v.z);
    }
    public void addI8(Byte4 v) {
        addI8(v.x);
        addI8(v.y);
        addI8(v.z);
        addI8(v.w);
    }

    public void addU8(Short2 v) {
        addU8(v.x);
        addU8(v.y);
    }
    public void addU8(Short3 v) {
        addU8(v.x);
        addU8(v.y);
        addU8(v.z);
    }
    public void addU8(Short4 v) {
        addU8(v.x);
        addU8(v.y);
        addU8(v.z);
        addU8(v.w);
    }

    public void addI16(Short2 v) {
        addI16(v.x);
        addI16(v.y);
    }
    public void addI16(Short3 v) {
        addI16(v.x);
        addI16(v.y);
        addI16(v.z);
    }
    public void addI16(Short4 v) {
        addI16(v.x);
        addI16(v.y);
        addI16(v.z);
        addI16(v.w);
    }

    public void addU16(Int2 v) {
        addU16(v.x);
        addU16(v.y);
    }
    public void addU16(Int3 v) {
        addU16(v.x);
        addU16(v.y);
        addU16(v.z);
    }
    public void addU16(Int4 v) {
        addU16(v.x);
        addU16(v.y);
        addU16(v.z);
        addU16(v.w);
    }

    public void addI32(Int2 v) {
        addI32(v.x);
        addI32(v.y);
    }
    public void addI32(Int3 v) {
        addI32(v.x);
        addI32(v.y);
        addI32(v.z);
    }
    public void addI32(Int4 v) {
        addI32(v.x);
        addI32(v.y);
        addI32(v.z);
        addI32(v.w);
    }

    public void addU32(Long2 v) {
        addU32(v.x);
        addU32(v.y);
    }
    public void addU32(Long3 v) {
        addU32(v.x);
        addU32(v.y);
        addU32(v.z);
    }
    public void addU32(Long4 v) {
        addU32(v.x);
        addU32(v.y);
        addU32(v.z);
        addU32(v.w);
    }

    public void addI64(Long2 v) {
        addI64(v.x);
        addI64(v.y);
    }
    public void addI64(Long3 v) {
        addI64(v.x);
        addI64(v.y);
        addI64(v.z);
    }
    public void addI64(Long4 v) {
        addI64(v.x);
        addI64(v.y);
        addI64(v.z);
        addI64(v.w);
    }

    public void addU64(Long2 v) {
        addU64(v.x);
        addU64(v.y);
    }
    public void addU64(Long3 v) {
        addU64(v.x);
        addU64(v.y);
        addU64(v.z);
    }
    public void addU64(Long4 v) {
        addU64(v.x);
        addU64(v.y);
        addU64(v.z);
        addU64(v.w);
    }


    public Float2 subFloat2() {
        Float2 v = new Float2();
        v.y = subF32();
        v.x = subF32();
        return v;
    }
    public Float3 subFloat3() {
        Float3 v = new Float3();
        v.z = subF32();
        v.y = subF32();
        v.x = subF32();
        return v;
    }
    public Float4 subFloat4() {
        Float4 v = new Float4();
        v.w = subF32();
        v.z = subF32();
        v.y = subF32();
        v.x = subF32();
        return v;
    }

    public Double2 subDouble2() {
        Double2 v = new Double2();
        v.y = subF64();
        v.x = subF64();
        return v;
    }
    public Double3 subDouble3() {
        Double3 v = new Double3();
        v.z = subF64();
        v.y = subF64();
        v.x = subF64();
        return v;
    }
    public Double4 subDouble4() {
        Double4 v = new Double4();
        v.w = subF64();
        v.z = subF64();
        v.y = subF64();
        v.x = subF64();
        return v;
    }

    public Byte2 subByte2() {
        Byte2 v = new Byte2();
        v.y = subI8();
        v.x = subI8();
        return v;
    }
    public Byte3 subByte3() {
        Byte3 v = new Byte3();
        v.z = subI8();
        v.y = subI8();
        v.x = subI8();
        return v;
    }
    public Byte4 subByte4() {
        Byte4 v = new Byte4();
        v.w = subI8();
        v.z = subI8();
        v.y = subI8();
        v.x = subI8();
        return v;
    }

    public Short2 subShort2() {
        Short2 v = new Short2();
        v.y = subI16();
        v.x = subI16();
        return v;
    }
    public Short3 subShort3() {
        Short3 v = new Short3();
        v.z = subI16();
        v.y = subI16();
        v.x = subI16();
        return v;
    }
    public Short4 subShort4() {
        Short4 v = new Short4();
        v.w = subI16();
        v.z = subI16();
        v.y = subI16();
        v.x = subI16();
        return v;
    }

    public Int2 subInt2() {
        Int2 v = new Int2();
        v.y = subI32();
        v.x = subI32();
        return v;
    }
    public Int3 subInt3() {
        Int3 v = new Int3();
        v.z = subI32();
        v.y = subI32();
        v.x = subI32();
        return v;
    }
    public Int4 subInt4() {
        Int4 v = new Int4();
        v.w = subI32();
        v.z = subI32();
        v.y = subI32();
        v.x = subI32();
        return v;
    }

    public Long2 subLong2() {
        Long2 v = new Long2();
        v.y = subI64();
        v.x = subI64();
        return v;
    }
    public Long3 subLong3() {
        Long3 v = new Long3();
        v.z = subI64();
        v.y = subI64();
        v.x = subI64();
        return v;
    }
    public Long4 subLong4() {
        Long4 v = new Long4();
        v.w = subI64();
        v.z = subI64();
        v.y = subI64();
        v.x = subI64();
        return v;
    }



    public void addMatrix(Matrix4f v) {
        for (int i=0; i < v.mMat.length; i++) {
            addF32(v.mMat[i]);
        }
    }

    public Matrix4f subMatrix4f() {
        Matrix4f v = new Matrix4f();
        for (int i = v.mMat.length - 1; i >= 0; i--) {
            v.mMat[i] = subF32();
        }
        return v;
    }

    public void addMatrix(Matrix3f v) {
        for (int i=0; i < v.mMat.length; i++) {
            addF32(v.mMat[i]);
        }
    }

    public Matrix3f subMatrix3f() {
        Matrix3f v = new Matrix3f();
        for (int i = v.mMat.length - 1; i >= 0; i--) {
            v.mMat[i] = subF32();
        }
        return v;
    }

    public void addMatrix(Matrix2f v) {
        for (int i=0; i < v.mMat.length; i++) {
            addF32(v.mMat[i]);
        }
    }

    public Matrix2f subMatrix2f() {
        Matrix2f v = new Matrix2f();
        for (int i = v.mMat.length - 1; i >= 0; i--) {
            v.mMat[i] = subF32();
        }
        return v;
    }

    public void addBoolean(boolean v) {
        addI8((byte)(v ? 1 : 0));
    }

    public boolean subBoolean() {
        byte v = subI8();
        if (v == 1) {
            return true;
        }
        return false;
    }

    public final byte[] getData() {
        return mData;
    }

    /**
     * Get the actual length used for the FieldPacker.
     *
     * @hide
     */
    public int getPos() {
        return mPos;
    }

    private void add(Object obj) {
        if (obj instanceof Boolean) {
            addBoolean((Boolean)obj);
            return;
        }

        if (obj instanceof Byte) {
            addI8((Byte)obj);
            return;
        }

        if (obj instanceof Short) {
            addI16((Short)obj);
            return;
        }

        if (obj instanceof Integer) {
            addI32((Integer)obj);
            return;
        }

        if (obj instanceof Long) {
            addI64((Long)obj);
            return;
        }

        if (obj instanceof Float) {
            addF32((Float)obj);
            return;
        }

        if (obj instanceof Double) {
            addF64((Double)obj);
            return;
        }

        if (obj instanceof Byte2) {
            addI8((Byte2)obj);
            return;
        }

        if (obj instanceof Byte3) {
            addI8((Byte3)obj);
            return;
        }

        if (obj instanceof Byte4) {
            addI8((Byte4)obj);
            return;
        }

        if (obj instanceof Short2) {
            addI16((Short2)obj);
            return;
        }

        if (obj instanceof Short3) {
            addI16((Short3)obj);
            return;
        }

        if (obj instanceof Short4) {
            addI16((Short4)obj);
            return;
        }

        if (obj instanceof Int2) {
            addI32((Int2)obj);
            return;
        }

        if (obj instanceof Int3) {
            addI32((Int3)obj);
            return;
        }

        if (obj instanceof Int4) {
            addI32((Int4)obj);
            return;
        }

        if (obj instanceof Long2) {
            addI64((Long2)obj);
            return;
        }

        if (obj instanceof Long3) {
            addI64((Long3)obj);
            return;
        }

        if (obj instanceof Long4) {
            addI64((Long4)obj);
            return;
        }

        if (obj instanceof Float2) {
            addF32((Float2)obj);
            return;
        }

        if (obj instanceof Float3) {
            addF32((Float3)obj);
            return;
        }

        if (obj instanceof Float4) {
            addF32((Float4)obj);
            return;
        }

        if (obj instanceof Double2) {
            addF64((Double2)obj);
            return;
        }

        if (obj instanceof Double3) {
            addF64((Double3)obj);
            return;
        }

        if (obj instanceof Double4) {
            addF64((Double4)obj);
            return;
        }

        if (obj instanceof Matrix2f) {
            addMatrix((Matrix2f)obj);
            return;
        }

        if (obj instanceof Matrix3f) {
            addMatrix((Matrix3f)obj);
            return;
        }

        if (obj instanceof Matrix4f) {
            addMatrix((Matrix4f)obj);
            return;
        }

        if (obj instanceof BaseObj) {
            addObj((BaseObj)obj);
            return;
        }
    }

    private boolean resize(int newSize) {
        if (newSize == mLen) {
            return false;
        }

        byte[] newData = new byte[newSize];
        System.arraycopy(mData, 0, newData, 0, mPos);
        mData = newData;
        mLen = newSize;
        return true;
    }

    private void addSafely(Object obj) {
        boolean retry;
        final int oldPos = mPos;
        do {
            retry = false;
            try {
                add(obj);
            } catch (ArrayIndexOutOfBoundsException e) {
                mPos = oldPos;
                resize(mLen * 2);
                retry = true;
            }
        } while (retry);
    }

    private byte mData[];
    private int mPos;
    private int mLen;
    private BitSet mAlignment;
}
