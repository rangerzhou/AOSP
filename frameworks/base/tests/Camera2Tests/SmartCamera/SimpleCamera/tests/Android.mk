# Copyright (C) 2013 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

# LOCAL_SDK_VERSION := current
LOCAL_PRIVATE_PLATFORM_APIS := true

LOCAL_PACKAGE_NAME := SmartCamera-tests
LOCAL_LICENSE_KINDS := SPDX-license-identifier-Apache-2.0
LOCAL_LICENSE_CONDITIONS := notice
LOCAL_NOTICE_FILE  := $(LOCAL_PATH)/../../../../../NOTICE

LOCAL_SRC_FILES += $(call all-java-files-under, src)

LOCAL_JAVA_LIBRARIES := android.test.base
LOCAL_STATIC_JAVA_LIBRARIES := guava junit

LOCAL_PROGUARD_ENABLED := disabled

LOCAL_INSTRUMENTATION_FOR := SmartCamera

include $(BUILD_PACKAGE)
