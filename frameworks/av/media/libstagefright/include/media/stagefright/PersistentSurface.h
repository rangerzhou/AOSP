/*
 * Copyright 2015 The Android Open Source Project
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

#ifndef PERSISTENT_SURFACE_H_

#define PERSISTENT_SURFACE_H_

#include <binder/Parcel.h>
#include <hidl/HidlSupport.h>
#include <hidl/HybridInterface.h>
#include <gui/IGraphicBufferProducer.h>
#include <media/stagefright/foundation/ABase.h>

namespace android {

struct PersistentSurface : public RefBase {
    PersistentSurface() {}

    // create a persistent surface
    PersistentSurface(
            const sp<IGraphicBufferProducer>& bufferProducer,
            const sp<hidl::base::V1_0::IBase>& hidlTarget) :
        mBufferProducer(bufferProducer),
        mHidlTarget(hidlTarget) { }

    sp<IGraphicBufferProducer> getBufferProducer() const {
        return mBufferProducer;
    }

    sp<hidl::base::V1_0::IBase> getHidlTarget() const {
        return mHidlTarget;
    }

    status_t writeToParcel(Parcel *parcel) const {
        parcel->writeStrongBinder(IInterface::asBinder(mBufferProducer));
        // write hidl target
        if (mHidlTarget != nullptr) {
            HalToken token;
            bool result = createHalToken(mHidlTarget, &token);
            parcel->writeBool(result);
            if (result) {
                parcel->writeByteArray(token.size(), token.data());
            }
        } else {
            parcel->writeBool(false);
        }
        return NO_ERROR;
    }

    status_t readFromParcel(const Parcel *parcel) {
        mBufferProducer = interface_cast<IGraphicBufferProducer>(
                parcel->readStrongBinder());
        // read hidl target
        bool haveHidlTarget = parcel->readBool();
        if (haveHidlTarget) {
            std::vector<uint8_t> tokenVector;
            parcel->readByteVector(&tokenVector);
            HalToken token = HalToken(tokenVector);
            mHidlTarget = retrieveHalInterface(token);
            deleteHalToken(token);
        } else {
            mHidlTarget.clear();
        }
        return NO_ERROR;
    }

private:
    sp<IGraphicBufferProducer> mBufferProducer;
    sp<hidl::base::V1_0::IBase> mHidlTarget;

    DISALLOW_EVIL_CONSTRUCTORS(PersistentSurface);
};

}  // namespace android

#endif  // PERSISTENT_SURFACE_H_
