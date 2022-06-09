#
# Copyright (C) 2021 The Android Open-Source Project
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

# Contents of this file were copied from device/google/raviole/raven/BoardConfig.mk,
# except for:
#
# * TARGET_SCREEN_DENSITY is scaled down by 1.75x

TARGET_BOARD_INFO_FILE := device/google/raviole/board-info.txt
TARGET_BOOTLOADER_BOARD_NAME := raviole
TARGET_SCREEN_DENSITY := 240
USES_DEVICE_GOOGLE_RAVIOLE := true

include device/google/gs101/BoardConfig-common.mk
-include vendor/google_devices/gs101/prebuilts/BoardConfigVendor.mk
-include vendor/google_devices/oriole/proprietary/BoardConfigVendor.mk
