/*
 * Copyright (C) 2011 The Android Open Source Project
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
#define LOG_TAG "time_util"

#include "time_util.h"
#include "utilities.h"

#include <sys/time.h>
#include <map>

#include <log/log.h>

namespace android {
namespace filterfw {

uint64_t getTimeUs() {
    static long basesec;
    struct timeval tv;
    uint64_t nowtime;
    gettimeofday(&tv, 0);
    if (basesec == 0) {
        basesec = tv.tv_sec;
    }
    nowtime = (uint64_t)(tv.tv_sec - basesec) * (uint64_t)1000000 +
              (uint64_t)tv.tv_usec;
    return nowtime;
}

const uint64_t NamedStopWatch::kDefaultLoggingPeriodInFrames = 100;

NamedStopWatch::NamedStopWatch(const std::string& name)
      : mName(name),
        mLoggingPeriodInFrames(kDefaultLoggingPeriodInFrames),
        mStartUSec(0),
        mNumCalls(0),
        mTotalUSec(0) {
}

void NamedStopWatch::Start() {
    mStartUSec = getTimeUs();
}

void NamedStopWatch::Stop() {
    if (!mStartUSec) {
        return;
    }
    uint64_t stopUSec = getTimeUs();
    if (stopUSec > mStartUSec) {
        ++mNumCalls;
        mTotalUSec += stopUSec - mStartUSec;
        if (mNumCalls % mLoggingPeriodInFrames == 0) {
            const float mSec = TotalUSec() * 1.0E-3f / NumCalls();
            ALOGE("%s: %f ms", Name().c_str(), mSec);
        }
    }
    mStartUSec = 0;
}

namespace {
static NamedStopWatch* GetWatchForName(const std::string& watch_name) {
    // TODO: this leaks the NamedStopWatch objects. Replace it with a
    // singleton to avoid that and make it thread safe.
    static std::map<std::string, NamedStopWatch*> watches;
    NamedStopWatch* watch = FindPtrOrNull(watches, watch_name);
    if (!watch) {
        watch = new NamedStopWatch(watch_name);
        watches[watch_name] = watch;
    }
    return watch;
};
}  // namespace

ScopedTimer::ScopedTimer(const std::string& stop_watch_name) {
    mWatch = GetWatchForName(stop_watch_name);
    mWatch->Start();
}

} // namespace filterfw
} // namespace android
