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


#define LOG_TAG "AAudioBinderClient"
//#define LOG_NDEBUG 0
#include <utils/Log.h>

#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/Mutex.h>
#include <utils/RefBase.h>
#include <utils/Singleton.h>
#include <aaudio/AAudio.h>

#include "AudioEndpointParcelable.h"

#include "binding/AAudioBinderClient.h"

#define AAUDIO_SERVICE_NAME  "media.aaudio"

using android::String16;
using android::IServiceManager;
using android::defaultServiceManager;
using android::interface_cast;
using android::IInterface;
using android::Mutex;
using android::ProcessState;
using android::sp;
using android::status_t;
using android::wp;
using android::binder::Status;

using namespace aaudio;

ANDROID_SINGLETON_STATIC_INSTANCE(AAudioBinderClient);

// If we don't keep a strong pointer here then this singleton can get deleted!
android::sp<AAudioBinderClient> gKeepBinderClient;

AAudioBinderClient::AAudioBinderClient()
        : AAudioServiceInterface()
        , Singleton<AAudioBinderClient>() {
    gKeepBinderClient = this; // so this singleton won't get deleted
    mAAudioClient = new AAudioClient(this);
    ALOGV("%s - this = %p, created mAAudioClient = %p", __func__, this, mAAudioClient.get());
}

AAudioBinderClient::~AAudioBinderClient() {
    ALOGV("%s - destroying %p", __func__, this);
    Mutex::Autolock _l(mServiceLock);
}

// TODO Share code with other service clients.
// Helper function to get access to the "AAudioService" service.
// This code was modeled after frameworks/av/media/libaudioclient/AudioSystem.cpp
std::shared_ptr<AAudioServiceInterface> AAudioBinderClient::getAAudioService() {
    std::shared_ptr<AAudioServiceInterface> result;
    sp<IAAudioService> aaudioService;
    bool needToRegister = false;
    {
        Mutex::Autolock _l(mServiceLock);
        if (mAdapter == nullptr) {
            sp<IBinder> binder;
            sp<IServiceManager> sm = defaultServiceManager();
            // Try several times to get the service.
            int retries = 4;
            do {
                binder = sm->getService(String16(AAUDIO_SERVICE_NAME)); // This will wait a while.
                if (binder.get() != nullptr) {
                    break;
                }
            } while (retries-- > 0);

            if (binder.get() != nullptr) {
                // Ask for notification if the service dies.
                status_t status = binder->linkToDeath(mAAudioClient);
                // TODO review what we should do if this fails
                if (status != NO_ERROR) {
                    ALOGE("%s() - linkToDeath() returned %d", __func__, status);
                }
                aaudioService = interface_cast<IAAudioService>(binder);
                mAdapter.reset(new Adapter(aaudioService, mAAudioClient));
                needToRegister = true;
                // Make sure callbacks can be received by mAAudioClient
                ProcessState::self()->startThreadPool();
            } else {
                ALOGE("AAudioBinderClient could not connect to %s", AAUDIO_SERVICE_NAME);
            }
        }
        result = mAdapter;
    }
    // Do this outside the mutex lock.
    if (needToRegister && aaudioService.get() != nullptr) { // new client?
        aaudioService->registerClient(mAAudioClient);
    }
    return result;
}

void AAudioBinderClient::dropAAudioService() {
    Mutex::Autolock _l(mServiceLock);
    mAdapter.reset();
}

/**
* @param request info needed to create the stream
* @param configuration contains information about the created stream
* @return handle to the stream or a negative error
*/
aaudio_handle_t AAudioBinderClient::openStream(const AAudioStreamRequest &request,
                                               AAudioStreamConfiguration &configuration) {
    aaudio_handle_t stream;
    for (int i = 0; i < 2; i++) {
        std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
        if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

        stream = service->openStream(request, configuration);

        if (stream == AAUDIO_ERROR_NO_SERVICE) {
            ALOGE("openStream lost connection to AAudioService.");
            dropAAudioService(); // force a reconnect
        } else {
            break;
        }
    }
    return stream;
}

aaudio_result_t AAudioBinderClient::closeStream(aaudio_handle_t streamHandle) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->closeStream(streamHandle);
}

/* Get an immutable description of the in-memory queues
* used to communicate with the underlying HAL or Service.
*/
aaudio_result_t AAudioBinderClient::getStreamDescription(aaudio_handle_t streamHandle,
                                                         AudioEndpointParcelable& endpointOut) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->getStreamDescription(streamHandle, endpointOut);
}

aaudio_result_t AAudioBinderClient::startStream(aaudio_handle_t streamHandle) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->startStream(streamHandle);
}

aaudio_result_t AAudioBinderClient::pauseStream(aaudio_handle_t streamHandle) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->pauseStream(streamHandle);
}

aaudio_result_t AAudioBinderClient::stopStream(aaudio_handle_t streamHandle) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->stopStream(streamHandle);
}

aaudio_result_t AAudioBinderClient::flushStream(aaudio_handle_t streamHandle) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->flushStream(streamHandle);
}

/**
* Manage the specified thread as a low latency audio thread.
*/
aaudio_result_t AAudioBinderClient::registerAudioThread(aaudio_handle_t streamHandle,
                                                        pid_t clientThreadId,
                                                        int64_t periodNanoseconds) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->registerAudioThread(streamHandle, clientThreadId, periodNanoseconds);
}

aaudio_result_t AAudioBinderClient::unregisterAudioThread(aaudio_handle_t streamHandle,
                                                          pid_t clientThreadId) {
    std::shared_ptr<AAudioServiceInterface> service = getAAudioService();
    if (service.get() == nullptr) return AAUDIO_ERROR_NO_SERVICE;

    return service->unregisterAudioThread(streamHandle, clientThreadId);
}
