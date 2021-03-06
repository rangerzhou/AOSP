/*
 * Copyright (C) 2013 The Android Open Source Project
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

#ifndef SHARED_LIBRARY_H_
#define SHARED_LIBRARY_H_

#include <utils/RefBase.h>
#include <utils/String8.h>
#include <media/stagefright/foundation/ABase.h>

namespace android {
    class SharedLibrary : public RefBase {
    public:
        explicit SharedLibrary(const String8 &path);
        ~SharedLibrary();

        bool operator!() const;
        void *lookup(const char *symbol) const;
        const char *lastError() const;

    private:
        void *mLibHandle;
        DISALLOW_EVIL_CONSTRUCTORS(SharedLibrary);
    };
};

#endif // SHARED_LIBRARY_H_
