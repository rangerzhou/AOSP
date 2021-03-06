/*
 * Copyright (C) 2012 The Android Open Source Project
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

#ifndef __ACCESSORY_H__
#define __ACCESSORY_H__

int init_audio(unsigned int ic, unsigned int id, unsigned int oc, unsigned int od);
void init_hid();
void usb_run(uintptr_t enable_accessory);

struct usb_device* usb_wait_for_device();

#endif /* __ACCESSORY_H__ */
