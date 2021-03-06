/*
 * Copyright (C) 2008 The Android Open Source Project
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

package com.android.tools.layoutlib.create;

import java.util.HashMap;

/**
 * Allows stub methods from LayoutLib to be overriden at runtime.
 * <p/>
 * Implementation note: all types required by this class(inner/outer classes & interfaces)
 * must be referenced by the injectClass argument to {@link AsmGenerator} in Main.java;
 * Otherwise they won't be accessible in layoutlib.jar at runtime.
 */
public final class OverrideMethod {

    /** Map of method overridden. */
    private static HashMap<String, MethodListener> sMethods = new HashMap<>();
    /** Default listener for all method not listed in sMethods. Nothing if null. */
    private static MethodListener sDefaultListener = null;
    
    /**
     * Sets the default listener for all methods not specifically handled.
     * Null means to do nothing.
     */
    @SuppressWarnings("UnusedDeclaration") // Used by Bridge by reflection for debug purposes.
    public static void setDefaultListener(MethodListener listener) {
        sDefaultListener = listener;
    }

    /**
     * Defines or reset a listener for the given method signature.
     * 
     * @param signature The signature of the method being invoked, composed of the
     *                  binary class name followed by the method descriptor (aka argument
     *                  types). Example: "com/foo/MyClass/InnerClass/printInt(I)V"
     * @param listener The new listener. Removes it if null.
     */
    public static void setMethodListener(String signature, MethodListener listener) {
        if (listener == null) {
            sMethods.remove(signature);
        } else {
            sMethods.put(signature, listener);
        }
    }
    
    /**
     * Invokes the specific listener for the given signature or the default one if defined.
     * <p/>
     * This version invokes the method listener for the void return type. 
     * <p/>
     * Note: this is not intended to be used by the LayoutLib Bridge. It is intended to be called
     * by the stubbed methods generated by the LayoutLib_create tool.
     * 
     * @param signature The signature of the method being invoked, composed of the
     *                  binary class name followed by the method descriptor (aka argument
     *                  types). Example: "com/foo/MyClass/InnerClass/printInt(I)V".
     * @param isNative True if the method was a native method.
     * @param caller The calling object. Null for static methods, "this" for instance methods.
     */
    public static void invokeV(String signature, boolean isNative, Object caller) {
        MethodListener i = sMethods.get(signature);
        if (i != null) {
            i.onInvokeV(signature, isNative, caller);
        } else if (sDefaultListener != null) {
            sDefaultListener.onInvokeV(signature, isNative, caller);
        }
    }
    
    /**
     * Invokes the specific listener for the int return type.
     * @see #invokeV(String, boolean, Object)
     */
    public static int invokeI(String signature, boolean isNative, Object caller) {
        MethodListener i = sMethods.get(signature);
        if (i != null) {
            return i.onInvokeI(signature, isNative, caller);
        } else if (sDefaultListener != null) {
            return sDefaultListener.onInvokeI(signature, isNative, caller);
        }
        return 0;
    }
    
    /**
     * Invokes the specific listener for the long return type.
     * @see #invokeV(String, boolean, Object)
     */
    public static long invokeL(String signature, boolean isNative, Object caller) {
        MethodListener i = sMethods.get(signature);
        if (i != null) {
            return i.onInvokeL(signature, isNative, caller);
        } else if (sDefaultListener != null) {
            return sDefaultListener.onInvokeL(signature, isNative, caller);
        }
        return 0;
    }
    
    /**
     * Invokes the specific listener for the float return type.
     * @see #invokeV(String, boolean, Object)
     */
    public static float invokeF(String signature, boolean isNative, Object caller) {
        MethodListener i = sMethods.get(signature);
        if (i != null) {
            return i.onInvokeF(signature, isNative, caller);
        } else if (sDefaultListener != null) {
            return sDefaultListener.onInvokeF(signature, isNative, caller);
        }
        return 0;
    }
    
    /**
     * Invokes the specific listener for the double return type.
     * @see #invokeV(String, boolean, Object)
     */
    public static double invokeD(String signature, boolean isNative, Object caller) {
        MethodListener i = sMethods.get(signature);
        if (i != null) {
            return i.onInvokeD(signature, isNative, caller);
        } else if (sDefaultListener != null) {
            return sDefaultListener.onInvokeD(signature, isNative, caller);
        }
        return 0;
    }
    
    /**
     * Invokes the specific listener for the object return type.
     * @see #invokeV(String, boolean, Object)
     */
    public static Object invokeA(String signature, boolean isNative, Object caller) {
        MethodListener i = sMethods.get(signature);
        if (i != null) {
            return i.onInvokeA(signature, isNative, caller);
        } else if (sDefaultListener != null) {
            return sDefaultListener.onInvokeA(signature, isNative, caller);
        }
        return null;
    }
}
