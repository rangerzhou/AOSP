/*
 * Copyright (C) 2010 The Android Open Source Project
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

#include "include/ThrottledSource.h"

#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/ALooper.h>

namespace android {

ThrottledSource::ThrottledSource(
        const sp<DataSource> &source,
        int32_t bandwidthLimitBytesPerSecond)
    : mSource(source),
      mBandwidthLimitBytesPerSecond(bandwidthLimitBytesPerSecond),
      mStartTimeUs(-1),
      mTotalTransferred(0) {
    CHECK(mBandwidthLimitBytesPerSecond > 0);
}

ssize_t ThrottledSource::readAt(off64_t offset, void *data, size_t size) {
    Mutex::Autolock autoLock(mLock);

    ssize_t n = mSource->readAt(offset, data, size);

    if (n <= 0) {
        return n;
    }

    mTotalTransferred += n;

    int64_t nowUs = ALooper::GetNowUs();

    if (mStartTimeUs < 0) {
        mStartTimeUs = nowUs;
    }

    // How long would it have taken to transfer everything we ever
    // transferred given the limited bandwidth.
    int64_t durationUs =
        mTotalTransferred * 1000000LL / mBandwidthLimitBytesPerSecond;

    int64_t whenUs = mStartTimeUs + durationUs;

    if (whenUs > nowUs) {
        usleep(whenUs - nowUs);
    }
    return n;
}


}  // namespace android

