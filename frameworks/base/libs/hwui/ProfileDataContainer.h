/*
 * Copyright (C) 2017 The Android Open Source Project
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

#include "ProfileData.h"
#include "utils/Macros.h"

#include <mutex>
#include <utils/Mutex.h>

namespace android {
namespace uirenderer {

class ProfileDataContainer {
    PREVENT_COPY_AND_ASSIGN(ProfileDataContainer);

public:
    explicit ProfileDataContainer(std::mutex& jankDataMutex)
            : mData(new ProfileData()), mJankDataMutex(jankDataMutex) {}

    ~ProfileDataContainer() { freeData(); }

    void rotateStorage();
    void switchStorageToAshmem(int ashmemfd);

    ProfileData* get() NO_THREAD_SAFETY_ANALYSIS { return mData; }

    ProfileData* operator->() NO_THREAD_SAFETY_ANALYSIS { return mData; }

    std::mutex& getDataMutex() { return mJankDataMutex; }

private:
    void freeData();

    // By default this will use malloc memory. It may be moved later to ashmem
    // if there is shared space for it and a request comes in to do that.
    ProfileData* mData GUARDED_BY(mJankDataMutex);
    bool mIsMapped = false;
    std::mutex& mJankDataMutex;
};

} /* namespace uirenderer */
} /* namespace android */