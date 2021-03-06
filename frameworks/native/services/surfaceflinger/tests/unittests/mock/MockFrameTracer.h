/*
 * Copyright 2019 The Android Open Source Project
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

#pragma once

#include <gmock/gmock.h>

#include "FrameTracer/FrameTracer.h"

namespace android::mock {

class FrameTracer : public android::FrameTracer {
public:
    FrameTracer();
    ~FrameTracer();

    MOCK_METHOD0(initialize, void());
    MOCK_METHOD0(registerDataSource, void());
    MOCK_METHOD2(traceNewLayer, void(int32_t, const std::string&));
    MOCK_METHOD6(traceTimestamp,
                 void(int32_t, uint64_t, uint64_t, nsecs_t, FrameEvent::BufferEventType, nsecs_t));
    MOCK_METHOD6(traceFence,
                 void(int32_t, uint64_t, uint64_t, const std::shared_ptr<FenceTime>&,
                      FrameEvent::BufferEventType, nsecs_t));
    MOCK_METHOD0(miniDump, std::string());
};

} // namespace android::mock
