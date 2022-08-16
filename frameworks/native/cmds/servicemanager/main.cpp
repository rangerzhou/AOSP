/*
 * Copyright (C) 2019 The Android Open Source Project
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

#include <android-base/logging.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/Status.h>
#include <sys/timerfd.h>
#include <utils/Looper.h>
#include <utils/StrongPointer.h>

#include "Access.h"
#include "ServiceManager.h"

using ::android::Access;
using ::android::sp;
using ::android::Looper;
using ::android::LooperCallback;
using ::android::ProcessState;
using ::android::IPCThreadState;
using ::android::ProcessState;
using ::android::ServiceManager;
using ::android::os::IServiceManager;
using ::android::sp;

class BinderCallback : public LooperCallback {
public:
    static sp<BinderCallback> setupTo(const sp<Looper>& looper) {
        sp<BinderCallback> cb = sp<BinderCallback>::make(); // 实例化 BinderCallback

        int binder_fd = -1;
        // 获取 binder_fd，并在其中开启 sm 的循环?，使其开始工作
        IPCThreadState::self()->setupPolling(&binder_fd);
        LOG_ALWAYS_FATAL_IF(binder_fd < 0, "Failed to setupPolling: %d", binder_fd);
        // 添加监听目标，通过 epoll 机制监听驱动的文件描述符 binder_fd，当 binder_fd
        // 可读时就会调用后面的 handleEvent()
        int ret = looper->addFd(binder_fd,
                                Looper::POLL_CALLBACK,
                                Looper::EVENT_INPUT,
                                cb,
                                nullptr /*data*/);
        LOG_ALWAYS_FATAL_IF(ret != 1, "Failed to add binder FD to Looper");

        return cb;
    }

    int handleEvent(int /* fd */, int /* events */, void* /* data */) override {
        // 调用 handlePolledCommands() 处理回调
        IPCThreadState::self()->handlePolledCommands();
        return 1;  // Continue receiving callbacks.
    }
};

// LooperCallback for IClientCallback
// 用于定时通知 client 变化
class ClientCallbackCallback : public LooperCallback {
public:
    static sp<ClientCallbackCallback> setupTo(const sp<Looper>& looper, const sp<ServiceManager>& manager) {
        sp<ClientCallbackCallback> cb = sp<ClientCallbackCallback>::make(manager);

        int fdTimer = timerfd_create(CLOCK_MONOTONIC, 0 /*flags*/);
        LOG_ALWAYS_FATAL_IF(fdTimer < 0, "Failed to timerfd_create: fd: %d err: %d", fdTimer, errno);

        itimerspec timespec {
            .it_interval = {
                .tv_sec = 5,
                .tv_nsec = 0,
            },
            .it_value = {
                .tv_sec = 5,
                .tv_nsec = 0,
            },
        };

        int timeRes = timerfd_settime(fdTimer, 0 /*flags*/, &timespec, nullptr);
        LOG_ALWAYS_FATAL_IF(timeRes < 0, "Failed to timerfd_settime: res: %d err: %d", timeRes, errno);

        int addRes = looper->addFd(fdTimer,
                                   Looper::POLL_CALLBACK,
                                   Looper::EVENT_INPUT,
                                   cb,
                                   nullptr);
        LOG_ALWAYS_FATAL_IF(addRes != 1, "Failed to add client callback FD to Looper");

        return cb;
    }

    int handleEvent(int fd, int /*events*/, void* /*data*/) override {
        uint64_t expirations;
        int ret = read(fd, &expirations, sizeof(expirations));
        if (ret != sizeof(expirations)) {
            ALOGE("Read failed to callback FD: ret: %d err: %d", ret, errno);
        }

        mManager->handleClientCallbacks();
        return 1;  // Continue receiving callbacks.
    }
private:
    friend sp<ClientCallbackCallback>;
    ClientCallbackCallback(const sp<ServiceManager>& manager) : mManager(manager) {}
    sp<ServiceManager> mManager;
};

int main(int argc, char** argv) {
    if (argc > 2) {
        LOG(FATAL) << "usage: " << argv[0] << " [binder driver]";
    }
    // 默认 /dev/binder，如果 argc == 2，则使用 /dev/vndbinder，这是供应商进程之间可以使用的 binder
    const char* driver = argc == 2 ? argv[1] : "/dev/binder";
    // open(), mmap()
    sp<ProcessState> ps = ProcessState::initWithDriver(driver);
    ps->setThreadPoolMaxThreadCount(0);
    ps->setCallRestriction(ProcessState::CallRestriction::FATAL_IF_NOT_ONEWAY);
    // 实例化 ServiceManager
    sp<ServiceManager> manager = sp<ServiceManager>::make(std::make_unique<Access>());
    // 将自身注册到 ServiceManager 中
    if (!manager->addService("manager", manager, false /*allowIsolated*/, IServiceManager::DUMP_FLAG_PRIORITY_DEFAULT).isOk()) {
        LOG(ERROR) << "Could not self register servicemanager";
    }
    // 将 ServiceManager 设置给 IPCThreadState 的全局变量
    // 即 IPCThreadState.cpp 中的 the_context_object == manager
    IPCThreadState::self()->setTheContextObject(manager);
    ps->becomeContextManager(); // 2. 注册到驱动，成为 Binder 管理员，handle 是 0
    // 准备 looper
    sp<Looper> looper = Looper::prepare(false /*allowNonCallbacks*/);
    // 通知驱动 BC_ENTER_LOOPER，监听驱动 fd ，有消息时回调到 handleEvent 处理 binder 调用
    BinderCallback::setupTo(looper);
    ClientCallbackCallback::setupTo(looper, manager); // 服务的注册监听相关

    while(true) {
        // -1: 一直阻塞，不会超时
        looper->pollAll(-1); // 无线循环监听
    }

    // should not be reached
    return EXIT_FAILURE;
}
