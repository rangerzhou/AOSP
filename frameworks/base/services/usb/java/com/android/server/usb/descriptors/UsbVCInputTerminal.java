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
package com.android.server.usb.descriptors;

import android.util.Log;

import com.android.server.usb.descriptors.report.ReportCanvas;

/**
 * @hide
 * A video class-specific Input terminal interface.
 * see USB_Video_Class_1.1.pdf section 3.7.2.1 Input Terminal Descriptor
 */
public final class UsbVCInputTerminal extends UsbVCInterface {
    private static final String TAG = "UsbVCInputTerminal";

    // TODO Define members to hold the data from this descriptor
    public UsbVCInputTerminal(int length, byte type, byte subtype) {
        super(length, type, subtype);
    }

    @Override
    public int parseRawDescriptors(ByteStream stream) {
        // TODO Parse the data from this descriptor
        if (UsbDescriptorParser.DEBUG) {
            Log.d(TAG, " ---> parseRawDescriptors()");
        }
        return super.parseRawDescriptors(stream);
    }

    @Override
    public void report(ReportCanvas canvas) {
        // TODO Add reporting specific to this descriptor
        super.report(canvas);
    }
};
