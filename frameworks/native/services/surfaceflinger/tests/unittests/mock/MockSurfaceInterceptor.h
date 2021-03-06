/*
 * Copyright (C) 2018 The Android Open Source Project
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

#include "SurfaceInterceptor.h"

namespace android::mock {

class SurfaceInterceptor : public android::SurfaceInterceptor {
public:
    SurfaceInterceptor();
    ~SurfaceInterceptor() override;

    MOCK_METHOD2(enable,
                 void(const SortedVector<sp<Layer>>&,
                      const DefaultKeyedVector<wp<IBinder>, DisplayDeviceState>&));
    MOCK_METHOD0(disable, void());
    MOCK_METHOD0(isEnabled, bool());
    MOCK_METHOD1(addTransactionTraceListener, void(const sp<gui::ITransactionTraceListener>&));
    MOCK_METHOD1(binderDied, void(const wp<IBinder>&));
    MOCK_METHOD7(saveTransaction,
                 void(const Vector<ComposerState>&,
                      const DefaultKeyedVector<wp<IBinder>, DisplayDeviceState>&,
                      const Vector<DisplayState>&, uint32_t, int, int, uint64_t));
    MOCK_METHOD1(saveSurfaceCreation, void(const sp<const Layer>&));
    MOCK_METHOD1(saveSurfaceDeletion, void(const sp<const Layer>&));
    MOCK_METHOD4(saveBufferUpdate, void(int32_t, uint32_t, uint32_t, uint64_t));
    MOCK_METHOD1(saveDisplayCreation, void(const DisplayDeviceState&));
    MOCK_METHOD1(saveDisplayDeletion, void(int32_t));
    MOCK_METHOD2(savePowerModeUpdate, void(int32_t, int32_t));
    MOCK_METHOD1(saveVSyncEvent, void(nsecs_t));
};

} // namespace android::mock
