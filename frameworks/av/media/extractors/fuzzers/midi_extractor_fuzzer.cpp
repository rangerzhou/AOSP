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

#include "ExtractorFuzzerBase.h"

#include "MidiExtractor.h"

using namespace android;

class MIDIExtractor : public ExtractorFuzzerBase {
 public:
  MIDIExtractor() = default;
  ~MIDIExtractor() = default;

  bool createExtractor();
};

bool MIDIExtractor::createExtractor() {
  mExtractor = new MidiExtractor(mDataSource->wrap());
  if (!mExtractor) {
    return false;
  }
  mExtractor->name();
  return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if ((!data) || (size == 0)) {
    return 0;
  }
  MIDIExtractor* extractor = new MIDIExtractor();
  if (extractor) {
    extractor->processData(data, size);
    delete extractor;
  }
  return 0;
}
