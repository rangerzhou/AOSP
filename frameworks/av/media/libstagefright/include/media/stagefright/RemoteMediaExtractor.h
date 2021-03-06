/*
 * Copyright 2017, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef REMOTE_MEDIA_EXTRACTOR_H_
#define REMOTE_MEDIA_EXTRACTOR_H_

#include <android/IMediaExtractor.h>
#include <media/MediaMetricsItem.h>
#include <media/stagefright/MediaExtractor.h>
#include <media/stagefright/foundation/ABase.h>

namespace android {


// IMediaExtractor wrapper to the MediaExtractor.
class RemoteMediaExtractor : public BnMediaExtractor {
public:
    static sp<IMediaExtractor> wrap(
            MediaExtractor *extractor,
            const sp<DataSource> &source,
            const sp<RefBase> &plugin);

    virtual ~RemoteMediaExtractor();
    virtual size_t countTracks();
    virtual sp<IMediaSource> getTrack(size_t index);
    virtual sp<MetaData> getTrackMetaData(size_t index, uint32_t flags = 0);
    virtual sp<MetaData> getMetaData();
    virtual status_t getMetrics(Parcel *reply);
    virtual uint32_t flags() const;
    virtual status_t setMediaCas(const HInterfaceToken &casToken);
    virtual String8 name();
    virtual status_t setEntryPoint(EntryPoint entryPoint);
    virtual status_t setLogSessionId(const String8& logSessionId);

private:
    MediaExtractor *mExtractor;
    sp<DataSource> mSource;
    sp<RefBase> mExtractorPlugin;

    mediametrics::Item *mMetricsItem;

    explicit RemoteMediaExtractor(
            MediaExtractor *extractor,
            const sp<DataSource> &source,
            const sp<RefBase> &plugin);

    DISALLOW_EVIL_CONSTRUCTORS(RemoteMediaExtractor);
};

}  // namespace android

#endif  // REMOTE_MEDIA_EXTRACTOR_H_
