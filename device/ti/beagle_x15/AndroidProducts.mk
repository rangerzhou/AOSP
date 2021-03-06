#
# Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
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

PRODUCT_MAKEFILES := \
    beagle_x15:$(LOCAL_DIR)/beagle_x15.mk \
    beagle_x15_auto:$(LOCAL_DIR)/auto/beagle_x15.mk \

COMMON_LUNCH_CHOICES := \
    beagle_x15-userdebug \
    beagle_x15_auto-userdebug \
