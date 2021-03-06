/*
* Copyright (C) 2016 The Android Open Source Project
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

#include <memory>

#include <jni.h>
#include <RenderScript.h>

#include "ScriptC_simple.h"

extern "C" void JNICALL
Java_com_android_rs_jninodebugwaitattach_MainActivity_nativeRS(
    JNIEnv * env,
    jclass,
    jstring pathObj)
{
    static const int size = 8;
    sp<RS> rs = new RS();

    const char * path = env->GetStringUTFChars(pathObj, nullptr);
    rs->init(path, RS_INIT_LOW_LATENCY | RS_INIT_WAIT_FOR_ATTACH);
    env->ReleaseStringUTFChars(pathObj, path);

    auto e = Element::RGBA_8888(rs);
    Type::Builder tb(rs, e);
    tb.setX(size);
    tb.setY(size);
    auto t = tb.create();

    auto a = Allocation::createTyped(rs, t);
    auto b = Allocation::createTyped(rs, t);

    // Script is executed once, then the data is copied back when finished
    sp<ScriptC_simple> s = new ScriptC_simple(rs);
    s->forEach_simple_kernel(a, b);
    uint32_t * output = new uint32_t[size*size];
    b->copy2DRangeTo(0, 0, size, size, output);
    delete [] output;

    rs->finish();
}

