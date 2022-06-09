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

#ifndef _INIT_REBOOT_H
#define _INIT_REBOOT_H

#include <chrono>
#include <set>
#include <string>

namespace android {
namespace init {

// Like StopServices, but also logs all the services that failed to stop after the provided timeout.
// Returns number of violators.
int StopServicesAndLogViolations(const std::set<std::string>& services,
                                 std::chrono::milliseconds timeout, bool terminate);
// Parses and handles a setprop sys.powerctl message.
void HandlePowerctlMessage(const std::string& command);

bool IsShuttingDown();
}  // namespace init
}  // namespace android

#endif
