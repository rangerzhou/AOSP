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

#ifndef DATA_SOURCE_FACTORY_H_

#define DATA_SOURCE_FACTORY_H_

#include <media/DataSource.h>
#include <sys/types.h>
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>

namespace android {

struct MediaHTTPService;
class String8;
struct HTTPBase;

class DataSourceFactory : public RefBase {
public:
    static sp<DataSourceFactory> getInstance();
    sp<DataSource> CreateFromURI(
            const sp<MediaHTTPService> &httpService,
            const char *uri,
            const KeyedVector<String8, String8> *headers = NULL,
            String8 *contentType = NULL,
            HTTPBase *httpSource = NULL);

    virtual sp<DataSource> CreateMediaHTTP(const sp<MediaHTTPService> &httpService);
    sp<DataSource> CreateFromFd(int fd, int64_t offset, int64_t length);

protected:
    virtual sp<DataSource> CreateFileSource(const char *uri);
    DataSourceFactory() {};
    virtual ~DataSourceFactory() {};

private:
    static sp<DataSourceFactory> sInstance;
    static Mutex sInstanceLock;
};

}  // namespace android

#endif  // DATA_SOURCE_FACTORY_H_
