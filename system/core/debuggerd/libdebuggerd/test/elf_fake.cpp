/*
 * Copyright (C) 2015 The Android Open Source Project
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

#include "elf_fake.h"

#include <stdint.h>

#include <string>

namespace unwindstack {
class Memory;
}

std::string g_build_id;

void elf_set_fake_build_id(const std::string& build_id) {
  g_build_id = build_id;
}

bool elf_get_build_id(unwindstack::Memory*, uintptr_t, std::string* build_id) {
  if (g_build_id != "") {
    *build_id = g_build_id;
    return true;
  }
  return false;
}
