/*
 * Copyright (c) 2015-2016 The Khronos Group Inc.
 * Copyright (c) 2015-2016 Valve Corporation
 * Copyright (c) 2015-2016 LunarG, Inc.
 * Copyright (c) 2016 Google Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and/or associated documentation files (the "Materials"), to
 * deal in the Materials without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Materials, and to permit persons to whom the Materials are
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice(s) and this permission notice shall be included in
 * all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE
 * USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 */
#pragma once

#include <vulkan/vulkan.h>

// ------------------------------------------------------------------------------------------------
// CreateInstance and CreateDevice support structures

typedef enum VkLayerFunction_ {
    VK_LAYER_FUNCTION_LINK = 0,
    VK_LAYER_FUNCTION_DATA_CALLBACK = 1
} VkLayerFunction;

typedef struct VkLayerInstanceLink_ {
    struct VkLayerInstanceLink_* pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
} VkLayerInstanceLink;

typedef VkResult(VKAPI_PTR* PFN_vkSetInstanceLoaderData)(VkInstance instance,
                                                         void* object);
typedef VkResult(VKAPI_PTR* PFN_vkSetDeviceLoaderData)(VkDevice device,
                                                       void* object);

typedef struct {
    VkStructureType sType;  // VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO
    const void* pNext;
    VkLayerFunction function;
    union {
        VkLayerInstanceLink* pLayerInfo;
        PFN_vkSetInstanceLoaderData pfnSetInstanceLoaderData;
    } u;
} VkLayerInstanceCreateInfo;

typedef struct VkLayerDeviceLink_ {
    struct VkLayerDeviceLink_* pNext;
    PFN_vkGetInstanceProcAddr pfnNextGetInstanceProcAddr;
    PFN_vkGetDeviceProcAddr pfnNextGetDeviceProcAddr;
} VkLayerDeviceLink;

typedef struct {
    VkStructureType sType;  // VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO
    const void* pNext;
    VkLayerFunction function;
    union {
        VkLayerDeviceLink* pLayerInfo;
        PFN_vkSetDeviceLoaderData pfnSetDeviceLoaderData;
    } u;
} VkLayerDeviceCreateInfo;
