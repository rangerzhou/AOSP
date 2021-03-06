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

package com.android.media.benchmark.library;

public class Native {
    static { System.loadLibrary("mediabenchmark_jni"); }

    public native int Extract(String inputFilePath, String inputFileName, String statsFile);

    public native int Mux(String inputFilePath, String inputFileName, String outputFilePath,
            String statsFile, String format);

    public native int Decode(String inputFilePath, String inputFileName, String statsFile,
            String codecName, boolean asyncMode);

    public native int Encode(String inputFilePath, String inputFileName, String statsFile,
            String codecName, String mime, int bitRate, int colorFormat, int frameInterval,
            int width, int height, int profile, int level, int sampleRate, int numChannel);
}
