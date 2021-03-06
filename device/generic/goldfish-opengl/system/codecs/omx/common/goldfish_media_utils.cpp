// Copyright 2018 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "goldfish_media_utils.h"

#include "goldfish_address_space.h"

#include <log/log.h>

#define DEBUG  0
#if DEBUG
#  define  DDD(...)    ALOGD(__VA_ARGS__)
#else
#  define  DDD(...)    ((void)0)
#endif

#include <memory>
#include <vector>
#include <mutex>



std::mutex sSingletonMutex;
std::unique_ptr<GoldfishMediaTransport> sTransport;

class GoldfishMediaTransportImpl : public GoldfishMediaTransport {
public:
    GoldfishMediaTransportImpl();
    ~GoldfishMediaTransportImpl();

    virtual void writeParam(__u64 val, unsigned int num, unsigned int offSetToStartAddr = 0) override;
    virtual bool sendOperation(MediaCodecType type, MediaOperation op, unsigned int offSetToStartAddr = 0) override;
    virtual uint8_t* getBaseAddr() const override;
    virtual uint8_t* getInputAddr(unsigned int offSet = 0) const override;
    virtual uint8_t* getOutputAddr() const override;
    virtual uint8_t* getReturnAddr(unsigned int offSet = 0) const override;
    virtual __u64 offsetOf(uint64_t addr) const override;

public:
    // each lot has 2 M
    virtual int getMemorySlot() override {
        std::lock_guard<std::mutex> g{mMemoryMutex};
        // when there are just 1 decoder, it can pretty
        // much use all the memory starting from 0;
        // when there are two, each can use at least half
        // the total memory, etc.
        constexpr size_t search_order[] = {
                0, // use 32M
                16, // use 16M
                8, 24, // use 8M
                4, 12, 20, 28, // use 4M
                2, 6, 10, 12, 18, 22, 26, 30, // use 2M
                1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31 // use 1M
        };
        for (size_t i = 0; i < sizeof(search_order)/sizeof(search_order[0]); ++i) {
            int slot = search_order[i];
            if (mMemoryLotsAvailable[slot]) {
                mMemoryLotsAvailable[slot] = false;
                return slot;
            }
        }
        return -1;
    }
    virtual void returnMemorySlot(int lot) override {
        if (lot < 0 || lot >= mMemoryLotsAvailable.size()) {
            return;
        }
        std::lock_guard<std::mutex> g{mMemoryMutex};
        if (mMemoryLotsAvailable[lot] == false) {
            mMemoryLotsAvailable[lot] = true;
        } else {
            ALOGE("Error, cannot twice");
        }
    }
private:
    std::mutex mMemoryMutex;
    std::vector<bool> mMemoryLotsAvailable = std::vector<bool>(32,true);

    address_space_handle_t mHandle;
    uint64_t  mOffset;
    uint64_t  mPhysAddr;
    uint64_t  mSize;
    void* mStartPtr = nullptr;

    // MediaCodecType will be or'd together with the metadata, so the highest 8-bits
    // will have the type.
    static __u64 makeMetadata(MediaCodecType type,
                              MediaOperation op, uint64_t offset);

    // Chunk size for parameters/return data
    static constexpr size_t kParamSizeBytes = 4096; // 4K
    // Chunk size for input
    static constexpr size_t kInputSizeBytes = 4096 * 4096; // 16M
    // Chunk size for output
    static constexpr size_t kOutputSizeBytes = 4096 * 4096; // 16M
    // Maximum number of parameters that can be passed
    static constexpr size_t kMaxParams = 32;
    // Offset from the memory region for return data (8 is size of
    // a parameter in bytes)
    static constexpr size_t kReturnOffset = 8 * kMaxParams;
};

GoldfishMediaTransportImpl::~GoldfishMediaTransportImpl() {
  if(mHandle >= 0) {
    goldfish_address_space_close(mHandle);
    mHandle = -1;
  }
}

GoldfishMediaTransportImpl::GoldfishMediaTransportImpl() {
    // Allocate host memory; the contiguous memory region will be laid out as
    // follows:
    // ========================================================
    // | kParamSizeBytes | kInputSizeBytes | kOutputSizeBytes |
    // ========================================================
    mHandle = goldfish_address_space_open();
    if (mHandle < 0) {
        ALOGE("Failed to ping host to allocate memory");
        abort();
    }
    mSize = kParamSizeBytes + kInputSizeBytes + kOutputSizeBytes;
    bool success = goldfish_address_space_allocate(mHandle, mSize, &mPhysAddr, &mOffset);
    if (success) {
        ALOGI("successfully allocated %d bytes in goldfish_address_block", (int)mSize);
        mStartPtr = goldfish_address_space_map(mHandle, mOffset, mSize);
        ALOGI("guest address is %p", mStartPtr);

        struct address_space_ping pingInfo;
        pingInfo.metadata = GoldfishAddressSpaceSubdeviceType::Media;
        pingInfo.offset = mOffset;
        if (goldfish_address_space_ping(mHandle, &pingInfo) == false) {
            ALOGE("Failed to ping host to allocate memory");
            abort();
            return;
        } else {
            ALOGI("successfully pinged host to allocate memory");
        }
    } else {
        ALOGE("failed to allocate %d bytes in goldfish_address_block", (int)mSize);
        abort();
    }
}

// static
GoldfishMediaTransport* GoldfishMediaTransport::getInstance() {
    std::lock_guard<std::mutex> g{sSingletonMutex};
    if (sTransport == nullptr) {
        sTransport.reset(new GoldfishMediaTransportImpl());
    }
    return sTransport.get();
}

// static
__u64 GoldfishMediaTransportImpl::makeMetadata(MediaCodecType type,
                                               MediaOperation op, uint64_t offset) {
    // Shift |type| into the highest 8-bits, leaving the lower bits for other
    // metadata.
    offset = offset >> 20;
    if (offset < 0 || offset >= 32) {
        ALOGE("offset %d is wrong", (int)offset);
        abort();
    }
    return ((__u64)type << (64 - 8)) | (offset << 8) | static_cast<uint8_t>(op);
}

uint8_t* GoldfishMediaTransportImpl::getInputAddr(unsigned int offSet) const {
    return (uint8_t*)mStartPtr + kParamSizeBytes + offSet;
}

uint8_t* GoldfishMediaTransportImpl::getOutputAddr() const {
    return getInputAddr() + kInputSizeBytes;
}

uint8_t* GoldfishMediaTransportImpl::getBaseAddr() const {
    return (uint8_t*)mStartPtr;
}

uint8_t* GoldfishMediaTransportImpl::getReturnAddr(unsigned int offSet) const {
    return (uint8_t*)mStartPtr + kReturnOffset + offSet;
}

__u64 GoldfishMediaTransportImpl::offsetOf(uint64_t addr) const {
    return addr - (uint64_t)mStartPtr;
}

void GoldfishMediaTransportImpl::writeParam(__u64 val, unsigned int num, unsigned int offSetToStartAddr) {
    uint8_t* p = (uint8_t*)mStartPtr + (offSetToStartAddr);
    uint64_t* pint = (uint64_t*)(p + 8 * num);
    *pint = val;
}

bool GoldfishMediaTransportImpl::sendOperation(MediaCodecType type,
                                               MediaOperation op, unsigned int offSetToStartAddr) {
    struct address_space_ping pingInfo;
    pingInfo.metadata = makeMetadata(type, op, offSetToStartAddr);
    pingInfo.offset = mOffset; // + (offSetToStartAddr);
    if (goldfish_address_space_ping(mHandle, &pingInfo) == false) {
        ALOGE("failed to ping host");
        abort();
        return false;
    } else {
        DDD("successfully pinged host for operation type=%d, op=%d", (int)type, (int)op);
    }

    return true;
}
