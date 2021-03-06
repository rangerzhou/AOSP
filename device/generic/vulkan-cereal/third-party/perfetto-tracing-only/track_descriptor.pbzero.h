// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_TRACK_DESCRIPTOR_PROTO_H_
#define PERFETTO_PROTOS_TRACK_DESCRIPTOR_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class ChromeProcessDescriptor;
class ChromeThreadDescriptor;
class CounterDescriptor;
class ProcessDescriptor;
class ThreadDescriptor;

class TrackDescriptor_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/8, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  TrackDescriptor_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit TrackDescriptor_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit TrackDescriptor_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_uuid() const { return at<1>().valid(); }
  uint64_t uuid() const { return at<1>().as_uint64(); }
  bool has_parent_uuid() const { return at<5>().valid(); }
  uint64_t parent_uuid() const { return at<5>().as_uint64(); }
  bool has_name() const { return at<2>().valid(); }
  ::protozero::ConstChars name() const { return at<2>().as_string(); }
  bool has_process() const { return at<3>().valid(); }
  ::protozero::ConstBytes process() const { return at<3>().as_bytes(); }
  bool has_chrome_process() const { return at<6>().valid(); }
  ::protozero::ConstBytes chrome_process() const { return at<6>().as_bytes(); }
  bool has_thread() const { return at<4>().valid(); }
  ::protozero::ConstBytes thread() const { return at<4>().as_bytes(); }
  bool has_chrome_thread() const { return at<7>().valid(); }
  ::protozero::ConstBytes chrome_thread() const { return at<7>().as_bytes(); }
  bool has_counter() const { return at<8>().valid(); }
  ::protozero::ConstBytes counter() const { return at<8>().as_bytes(); }
};

class TrackDescriptor : public ::protozero::Message {
 public:
  using Decoder = TrackDescriptor_Decoder;
  enum : int32_t {
    kUuidFieldNumber = 1,
    kParentUuidFieldNumber = 5,
    kNameFieldNumber = 2,
    kProcessFieldNumber = 3,
    kChromeProcessFieldNumber = 6,
    kThreadFieldNumber = 4,
    kChromeThreadFieldNumber = 7,
    kCounterFieldNumber = 8,
  };
  void set_uuid(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_parent_uuid(uint64_t value) {
    AppendVarInt(5, value);
  }
  void set_name(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  template <typename T = ProcessDescriptor> T* set_process() {
    return BeginNestedMessage<T>(3);
  }

  template <typename T = ChromeProcessDescriptor> T* set_chrome_process() {
    return BeginNestedMessage<T>(6);
  }

  template <typename T = ThreadDescriptor> T* set_thread() {
    return BeginNestedMessage<T>(4);
  }

  template <typename T = ChromeThreadDescriptor> T* set_chrome_thread() {
    return BeginNestedMessage<T>(7);
  }

  template <typename T = CounterDescriptor> T* set_counter() {
    return BeginNestedMessage<T>(8);
  }

};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
