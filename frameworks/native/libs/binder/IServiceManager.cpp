/*
 * Copyright (C) 2005 The Android Open Source Project
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

#define LOG_TAG "ServiceManager"

#include <binder/IServiceManager.h>

#include <inttypes.h>
#include <unistd.h>

#include <android/os/BnServiceCallback.h>
#include <android/os/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/Parcel.h>
#include <utils/Log.h>
#include <utils/String8.h>
#include <utils/SystemClock.h>

#ifndef __ANDROID_VNDK__
#include <binder/IPermissionController.h>
#endif

#ifdef __ANDROID__
#include <cutils/properties.h>
#endif

#include "Static.h"

namespace android {

using AidlServiceManager = android::os::IServiceManager;
using android::binder::Status;

// libbinder's IServiceManager.h can't rely on the values generated by AIDL
// because many places use its headers via include_dirs (meaning, without
// declaring the dependency in the build system). So, for now, we can just check
// the values here.
static_assert(AidlServiceManager::DUMP_FLAG_PRIORITY_CRITICAL == IServiceManager::DUMP_FLAG_PRIORITY_CRITICAL);
static_assert(AidlServiceManager::DUMP_FLAG_PRIORITY_HIGH == IServiceManager::DUMP_FLAG_PRIORITY_HIGH);
static_assert(AidlServiceManager::DUMP_FLAG_PRIORITY_NORMAL == IServiceManager::DUMP_FLAG_PRIORITY_NORMAL);
static_assert(AidlServiceManager::DUMP_FLAG_PRIORITY_DEFAULT == IServiceManager::DUMP_FLAG_PRIORITY_DEFAULT);
static_assert(AidlServiceManager::DUMP_FLAG_PRIORITY_ALL == IServiceManager::DUMP_FLAG_PRIORITY_ALL);
static_assert(AidlServiceManager::DUMP_FLAG_PROTO == IServiceManager::DUMP_FLAG_PROTO);

const String16& IServiceManager::getInterfaceDescriptor() const {
    return AidlServiceManager::descriptor;
}
IServiceManager::IServiceManager() {}
IServiceManager::~IServiceManager() {}

// From the old libbinder IServiceManager interface to IServiceManager.
class ServiceManagerShim : public IServiceManager
{
public:
    explicit ServiceManagerShim (const sp<AidlServiceManager>& impl);

    sp<IBinder> getService(const String16& name) const override;
    sp<IBinder> checkService(const String16& name) const override;
    status_t addService(const String16& name, const sp<IBinder>& service,
                        bool allowIsolated, int dumpsysPriority) override;
    Vector<String16> listServices(int dumpsysPriority) override;
    sp<IBinder> waitForService(const String16& name16) override;
    bool isDeclared(const String16& name) override;
    Vector<String16> getDeclaredInstances(const String16& interface) override;
    std::optional<String16> updatableViaApex(const String16& name) override;

    // for legacy ABI
    const String16& getInterfaceDescriptor() const override {
        return mTheRealServiceManager->getInterfaceDescriptor();
    }
    IBinder* onAsBinder() override {
        return IInterface::asBinder(mTheRealServiceManager).get();
    }
private:
    sp<AidlServiceManager> mTheRealServiceManager;
};

[[clang::no_destroy]] static std::once_flag gSmOnce;
[[clang::no_destroy]] static sp<IServiceManager> gDefaultServiceManager;

sp<IServiceManager> defaultServiceManager()
{
    std::call_once(gSmOnce, []() {
        sp<AidlServiceManager> sm = nullptr;
        while (sm == nullptr) {
            sm = interface_cast<AidlServiceManager>(ProcessState::self()->getContextObject(nullptr));
            if (sm == nullptr) {
                ALOGE("Waiting 1s on context object on %s.", ProcessState::self()->getDriverName().c_str());
                sleep(1);
            }
        }

        gDefaultServiceManager = sp<ServiceManagerShim>::make(sm);
    });

    return gDefaultServiceManager;
}

void setDefaultServiceManager(const sp<IServiceManager>& sm) {
    bool called = false;
    std::call_once(gSmOnce, [&]() {
        gDefaultServiceManager = sm;
        called = true;
    });

    if (!called) {
        LOG_ALWAYS_FATAL("setDefaultServiceManager() called after defaultServiceManager().");
    }
}

#if !defined(__ANDROID_VNDK__) && defined(__ANDROID__)
// IPermissionController is not accessible to vendors

bool checkCallingPermission(const String16& permission)
{
    return checkCallingPermission(permission, nullptr, nullptr);
}

static String16 _permission("permission");


bool checkCallingPermission(const String16& permission, int32_t* outPid, int32_t* outUid)
{
    IPCThreadState* ipcState = IPCThreadState::self();
    pid_t pid = ipcState->getCallingPid();
    uid_t uid = ipcState->getCallingUid();
    if (outPid) *outPid = pid;
    if (outUid) *outUid = uid;
    return checkPermission(permission, pid, uid);
}

bool checkPermission(const String16& permission, pid_t pid, uid_t uid)
{
    static Mutex gPermissionControllerLock;
    static sp<IPermissionController> gPermissionController;

    sp<IPermissionController> pc;
    gPermissionControllerLock.lock();
    pc = gPermissionController;
    gPermissionControllerLock.unlock();

    int64_t startTime = 0;

    while (true) {
        if (pc != nullptr) {
            bool res = pc->checkPermission(permission, pid, uid);
            if (res) {
                if (startTime != 0) {
                    ALOGI("Check passed after %d seconds for %s from uid=%d pid=%d",
                            (int)((uptimeMillis()-startTime)/1000),
                            String8(permission).string(), uid, pid);
                }
                return res;
            }

            // Is this a permission failure, or did the controller go away?
            if (IInterface::asBinder(pc)->isBinderAlive()) {
                ALOGW("Permission failure: %s from uid=%d pid=%d",
                        String8(permission).string(), uid, pid);
                return false;
            }

            // Object is dead!
            gPermissionControllerLock.lock();
            if (gPermissionController == pc) {
                gPermissionController = nullptr;
            }
            gPermissionControllerLock.unlock();
        }

        // Need to retrieve the permission controller.
        sp<IBinder> binder = defaultServiceManager()->checkService(_permission);
        if (binder == nullptr) {
            // Wait for the permission controller to come back...
            if (startTime == 0) {
                startTime = uptimeMillis();
                ALOGI("Waiting to check permission %s from uid=%d pid=%d",
                        String8(permission).string(), uid, pid);
            }
            sleep(1);
        } else {
            pc = interface_cast<IPermissionController>(binder);
            // Install the new permission controller, and try again.
            gPermissionControllerLock.lock();
            gPermissionController = pc;
            gPermissionControllerLock.unlock();
        }
    }
}

#endif //__ANDROID_VNDK__

// ----------------------------------------------------------------------

ServiceManagerShim::ServiceManagerShim(const sp<AidlServiceManager>& impl)
 : mTheRealServiceManager(impl)
{}

// This implementation could be simplified and made more efficient by delegating
// to waitForService. However, this changes the threading structure in some
// cases and could potentially break prebuilts. Once we have higher logistical
// complexity, this could be attempted.
sp<IBinder> ServiceManagerShim::getService(const String16& name) const
{
    static bool gSystemBootCompleted = false;

    sp<IBinder> svc = checkService(name);
    if (svc != nullptr) return svc;

    const bool isVendorService =
        strcmp(ProcessState::self()->getDriverName().c_str(), "/dev/vndbinder") == 0;
    constexpr int64_t timeout = 5000;
    int64_t startTime = uptimeMillis();
    // Vendor code can't access system properties
    if (!gSystemBootCompleted && !isVendorService) {
#ifdef __ANDROID__
        char bootCompleted[PROPERTY_VALUE_MAX];
        property_get("sys.boot_completed", bootCompleted, "0");
        gSystemBootCompleted = strcmp(bootCompleted, "1") == 0 ? true : false;
#else
        gSystemBootCompleted = true;
#endif
    }
    // retry interval in millisecond; note that vendor services stay at 100ms
    const useconds_t sleepTime = gSystemBootCompleted ? 1000 : 100;

    ALOGI("Waiting for service '%s' on '%s'...", String8(name).string(),
          ProcessState::self()->getDriverName().c_str());

    int n = 0;
    while (uptimeMillis() - startTime < timeout) {
        n++;
        usleep(1000*sleepTime);

        sp<IBinder> svc = checkService(name);
        if (svc != nullptr) {
            ALOGI("Waiting for service '%s' on '%s' successful after waiting %" PRIi64 "ms",
                  String8(name).string(), ProcessState::self()->getDriverName().c_str(),
                  uptimeMillis() - startTime);
            return svc;
        }
    }
    ALOGW("Service %s didn't start. Returning NULL", String8(name).string());
    return nullptr;
}

sp<IBinder> ServiceManagerShim::checkService(const String16& name) const
{
    sp<IBinder> ret;
    if (!mTheRealServiceManager->checkService(String8(name).c_str(), &ret).isOk()) {
        return nullptr;
    }
    return ret;
}

status_t ServiceManagerShim::addService(const String16& name, const sp<IBinder>& service,
                                        bool allowIsolated, int dumpsysPriority)
{
    Status status = mTheRealServiceManager->addService(
        String8(name).c_str(), service, allowIsolated, dumpsysPriority);
    return status.exceptionCode();
}

Vector<String16> ServiceManagerShim::listServices(int dumpsysPriority)
{
    std::vector<std::string> ret;
    if (!mTheRealServiceManager->listServices(dumpsysPriority, &ret).isOk()) {
        return {};
    }

    Vector<String16> res;
    res.setCapacity(ret.size());
    for (const std::string& name : ret) {
        res.push(String16(name.c_str()));
    }
    return res;
}

sp<IBinder> ServiceManagerShim::waitForService(const String16& name16)
{
    class Waiter : public android::os::BnServiceCallback {
        Status onRegistration(const std::string& /*name*/,
                              const sp<IBinder>& binder) override {
            std::unique_lock<std::mutex> lock(mMutex);
            mBinder = binder;
            lock.unlock();
            // Flushing here helps ensure the service's ref count remains accurate
            IPCThreadState::self()->flushCommands();
            mCv.notify_one();
            return Status::ok();
        }
    public:
        sp<IBinder> mBinder;
        std::mutex mMutex;
        std::condition_variable mCv;
    };

    // Simple RAII object to ensure a function call immediately before going out of scope
    class Defer {
    public:
        explicit Defer(std::function<void()>&& f) : mF(std::move(f)) {}
        ~Defer() { mF(); }
    private:
        std::function<void()> mF;
    };

    const std::string name = String8(name16).c_str();

    sp<IBinder> out;
    if (!mTheRealServiceManager->getService(name, &out).isOk()) {
        return nullptr;
    }
    if (out != nullptr) return out;

    sp<Waiter> waiter = sp<Waiter>::make();
    if (!mTheRealServiceManager->registerForNotifications(
            name, waiter).isOk()) {
        return nullptr;
    }
    Defer unregister ([&] {
        mTheRealServiceManager->unregisterForNotifications(name, waiter);
    });

    while(true) {
        {
            // It would be really nice if we could read binder commands on this
            // thread instead of needing a threadpool to be started, but for
            // instance, if we call getAndExecuteCommand, it might be the case
            // that another thread serves the callback, and we never get a
            // command, so we hang indefinitely.
            std::unique_lock<std::mutex> lock(waiter->mMutex);
            using std::literals::chrono_literals::operator""s;
            waiter->mCv.wait_for(lock, 1s, [&] {
                return waiter->mBinder != nullptr;
            });
            if (waiter->mBinder != nullptr) return waiter->mBinder;
        }

        ALOGW("Waited one second for %s (is service started? are binder threads started and available?)", name.c_str());

        // Handle race condition for lazy services. Here is what can happen:
        // - the service dies (not processed by init yet).
        // - sm processes death notification.
        // - sm gets getService and calls init to start service.
        // - init gets the start signal, but the service already appears
        //   started, so it does nothing.
        // - init gets death signal, but doesn't know it needs to restart
        //   the service
        // - we need to request service again to get it to start
        if (!mTheRealServiceManager->getService(name, &out).isOk()) {
            return nullptr;
        }
        if (out != nullptr) return out;
    }
}

bool ServiceManagerShim::isDeclared(const String16& name) {
    bool declared;
    if (!mTheRealServiceManager->isDeclared(String8(name).c_str(), &declared).isOk()) {
        return false;
    }
    return declared;
}

Vector<String16> ServiceManagerShim::getDeclaredInstances(const String16& interface) {
    std::vector<std::string> out;
    if (!mTheRealServiceManager->getDeclaredInstances(String8(interface).c_str(), &out).isOk()) {
        return {};
    }

    Vector<String16> res;
    res.setCapacity(out.size());
    for (const std::string& instance : out) {
        res.push(String16(instance.c_str()));
    }
    return res;
}

std::optional<String16> ServiceManagerShim::updatableViaApex(const String16& name) {
    std::optional<std::string> declared;
    if (!mTheRealServiceManager->updatableViaApex(String8(name).c_str(), &declared).isOk()) {
        return std::nullopt;
    }
    return declared ? std::optional<String16>(String16(declared.value().c_str())) : std::nullopt;
}

} // namespace android