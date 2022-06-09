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

#include <fuzzer/FuzzedDataProvider.h>
#include <gtest/gtest.h>

#include "avrcp_test_packets.h"
#include "get_element_attributes_packet.h"
#include "packet_test_helper.h"

namespace bluetooth {
namespace avrcp {

using TestGetElemAttrReqPacket = TestPacketType<GetElementAttributesRequest>;

extern "C" int LLVMFuzzerTestOneInput(uint8_t* data, size_t size) {
  auto builder = GetElementAttributesResponseBuilder::MakeBuilder(0xFFFF);
  FuzzedDataProvider data_provider(data, size);
  std::string s = data_provider.ConsumeRemainingBytesAsString();
  builder->AddAttributeEntry(Attribute::TITLE, s);
  builder->AddAttributeEntry(Attribute::ARTIST_NAME, s);
  builder->AddAttributeEntry(Attribute::ALBUM_NAME, s);
  builder->AddAttributeEntry(Attribute::TRACK_NUMBER, s);
  builder->AddAttributeEntry(Attribute::TOTAL_NUMBER_OF_TRACKS, s);
  builder->AddAttributeEntry(Attribute::GENRE, s);
  builder->AddAttributeEntry(Attribute::PLAYING_TIME, s);

  auto test_packet = TestGetElemAttrReqPacket::Make();
  builder->Serialize(test_packet);
  test_packet->GetData();

  return 0;
}

}  // namespace avrcp
}  // namespace bluetooth
