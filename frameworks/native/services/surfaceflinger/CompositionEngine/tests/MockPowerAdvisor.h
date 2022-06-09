/*
 * Copyright 2019 The Android Open Source Project

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

#include "DisplayHardware/PowerAdvisor.h"

namespace android {
namespace Hwc2 {
namespace mock {

class PowerAdvisor : public android::Hwc2::PowerAdvisor {
public:
    PowerAdvisor();
    ~PowerAdvisor() override;

    MOCK_METHOD0(init, void());
    MOCK_METHOD0(onBootFinished, void());
    MOCK_METHOD2(setExpensiveRenderingExpected, void(DisplayId displayId, bool expected));
    MOCK_METHOD0(isUsingExpensiveRendering, bool());
    MOCK_METHOD0(notifyDisplayUpdateImminent, void());
};

} // namespace mock
} // namespace Hwc2
} // namespace android
