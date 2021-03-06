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

package android.graphics;

import com.android.layoutlib.bridge.impl.DelegateManager;
import com.android.tools.layoutlib.annotations.LayoutlibDelegate;

import libcore.util.NativeAllocationRegistry_Delegate;

/**
 * Delegate implementing the native methods of android.graphics.ColorSpace
 *
 * Through the layoutlib_create tool, the original native methods of ColorSpace have been replaced
 * by calls to methods of the same name in this delegate class.
 */
public class ColorSpace_Rgb_Delegate {

    // ---- delegate manager ----
    private static final DelegateManager<ColorSpace_Rgb_Delegate> sManager =
            new DelegateManager<>(ColorSpace_Rgb_Delegate.class);
    private static long sFinalizer = -1;

    @LayoutlibDelegate
    /*package*/ static long nativeGetNativeFinalizer() {
        synchronized (ColorSpace_Rgb_Delegate.class) {
            if (sFinalizer == -1) {
                sFinalizer = NativeAllocationRegistry_Delegate.createFinalizer(sManager::removeJavaReferenceFor);
            }
        }
        return sFinalizer;
    }

    @LayoutlibDelegate
    /*package*/ static long nativeCreate(float a, float b, float c, float d,
            float e, float f, float g, float[] xyz) {
        // Layoutlib does not support color spaces, but a native object is required
        // for ColorSpace$Rgb. This creates an empty delegate for it.
        return sManager.addNewDelegate(new ColorSpace_Rgb_Delegate());
    }
}
