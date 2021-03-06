/******************************************************************************
 *
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *****************************************************************************
 * Originally developed and contributed by Ittiam Systems Pvt. Ltd, Bangalore
 */

#include "WriterFuzzerBase.h"

#include <media/stagefright/OggWriter.h>

using namespace android;

class OGGWriterFuzzer : public WriterFuzzerBase {
   public:
    bool createWriter();
};

bool OGGWriterFuzzer::createWriter() {
    mWriter = new OggWriter(mFd);
    if (!mWriter) {
        return false;
    }
    mFileMeta = new MetaData;
    mFileMeta->setInt32(kKeyFileType, output_format::OUTPUT_FORMAT_OGG);
    return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    OGGWriterFuzzer writerFuzzer;
    writerFuzzer.initFileWriterAndProcessData(data, size);
    return 0;
}
