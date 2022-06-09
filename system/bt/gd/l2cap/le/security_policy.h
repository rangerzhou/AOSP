/*
 * Copyright 2020 The Android Open Source Project
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

#pragma once

#include <cstdint>

namespace bluetooth {
namespace l2cap {
namespace le {

enum class SecurityPolicy {
  // Predefined security policies for user to pick

  // No security enforced
  NO_SECURITY_WHATSOEVER_PLAINTEXT_TRANSPORT_OK,

  // Just encryption, but no MITM
  ENCRYPTED_TRANSPORT,

  // Implicitly MITM protected
  AUTHENTICATED_ENCRYPTED_TRANSPORT,

  // Same as AUTHENTICATED_ENCRYPTED_TRANSPORT
  BEST,

  _NOT_FOR_YOU__AUTHENTICATED_PAIRING_WITH_128_BIT_KEY,
  _NOT_FOR_YOU__AUTHORIZATION,
};

}  // namespace le
}  // namespace l2cap
}  // namespace bluetooth
