/*
 * Copyright (C) 2009 The Android Open Source Project
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

#ifndef OMX_CLIENT_H_

#define OMX_CLIENT_H_

namespace android {

class IOMX;

class OMXClient {
public:
    OMXClient();

    status_t connect();
    status_t connect(const char* name);
    void disconnect();

    sp<IOMX> interface();

private:
    sp<IOMX> mOMX;

    OMXClient(const OMXClient &) = delete;
    OMXClient &operator=(const OMXClient &) = delete;
};

}  // namespace android

#endif  // OMX_CLIENT_H_
