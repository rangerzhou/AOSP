// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_INTERNED_DATA_PROTO_H_
#define PERFETTO_PROTOS_INTERNED_DATA_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class Callstack;
class DebugAnnotationName;
class EventCategory;
class EventName;
class Frame;
class InternedGpuRenderStageSpecification;
class InternedGraphicsContext;
class InternedString;
class LogMessageBody;
class Mapping;
class ProfiledFrameSymbols;
class SourceLocation;

class InternedData_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/24, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  InternedData_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit InternedData_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit InternedData_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_event_categories() const { return at<1>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> event_categories() const { return GetRepeated<::protozero::ConstBytes>(1); }
  bool has_event_names() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> event_names() const { return GetRepeated<::protozero::ConstBytes>(2); }
  bool has_debug_annotation_names() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> debug_annotation_names() const { return GetRepeated<::protozero::ConstBytes>(3); }
  bool has_source_locations() const { return at<4>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> source_locations() const { return GetRepeated<::protozero::ConstBytes>(4); }
  bool has_log_message_body() const { return at<20>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> log_message_body() const { return GetRepeated<::protozero::ConstBytes>(20); }
  bool has_build_ids() const { return at<16>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> build_ids() const { return GetRepeated<::protozero::ConstBytes>(16); }
  bool has_mapping_paths() const { return at<17>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> mapping_paths() const { return GetRepeated<::protozero::ConstBytes>(17); }
  bool has_source_paths() const { return at<18>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> source_paths() const { return GetRepeated<::protozero::ConstBytes>(18); }
  bool has_function_names() const { return at<5>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> function_names() const { return GetRepeated<::protozero::ConstBytes>(5); }
  bool has_profiled_frame_symbols() const { return at<21>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> profiled_frame_symbols() const { return GetRepeated<::protozero::ConstBytes>(21); }
  bool has_mappings() const { return at<19>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> mappings() const { return GetRepeated<::protozero::ConstBytes>(19); }
  bool has_frames() const { return at<6>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> frames() const { return GetRepeated<::protozero::ConstBytes>(6); }
  bool has_callstacks() const { return at<7>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> callstacks() const { return GetRepeated<::protozero::ConstBytes>(7); }
  bool has_vulkan_memory_keys() const { return at<22>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> vulkan_memory_keys() const { return GetRepeated<::protozero::ConstBytes>(22); }
  bool has_graphics_contexts() const { return at<23>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> graphics_contexts() const { return GetRepeated<::protozero::ConstBytes>(23); }
  bool has_gpu_specifications() const { return at<24>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> gpu_specifications() const { return GetRepeated<::protozero::ConstBytes>(24); }
};

class InternedData : public ::protozero::Message {
 public:
  using Decoder = InternedData_Decoder;
  enum : int32_t {
    kEventCategoriesFieldNumber = 1,
    kEventNamesFieldNumber = 2,
    kDebugAnnotationNamesFieldNumber = 3,
    kSourceLocationsFieldNumber = 4,
    kLogMessageBodyFieldNumber = 20,
    kBuildIdsFieldNumber = 16,
    kMappingPathsFieldNumber = 17,
    kSourcePathsFieldNumber = 18,
    kFunctionNamesFieldNumber = 5,
    kProfiledFrameSymbolsFieldNumber = 21,
    kMappingsFieldNumber = 19,
    kFramesFieldNumber = 6,
    kCallstacksFieldNumber = 7,
    kVulkanMemoryKeysFieldNumber = 22,
    kGraphicsContextsFieldNumber = 23,
    kGpuSpecificationsFieldNumber = 24,
  };
  template <typename T = EventCategory> T* add_event_categories() {
    return BeginNestedMessage<T>(1);
  }

  template <typename T = EventName> T* add_event_names() {
    return BeginNestedMessage<T>(2);
  }

  template <typename T = DebugAnnotationName> T* add_debug_annotation_names() {
    return BeginNestedMessage<T>(3);
  }

  template <typename T = SourceLocation> T* add_source_locations() {
    return BeginNestedMessage<T>(4);
  }

  template <typename T = LogMessageBody> T* add_log_message_body() {
    return BeginNestedMessage<T>(20);
  }

  template <typename T = InternedString> T* add_build_ids() {
    return BeginNestedMessage<T>(16);
  }

  template <typename T = InternedString> T* add_mapping_paths() {
    return BeginNestedMessage<T>(17);
  }

  template <typename T = InternedString> T* add_source_paths() {
    return BeginNestedMessage<T>(18);
  }

  template <typename T = InternedString> T* add_function_names() {
    return BeginNestedMessage<T>(5);
  }

  template <typename T = ProfiledFrameSymbols> T* add_profiled_frame_symbols() {
    return BeginNestedMessage<T>(21);
  }

  template <typename T = Mapping> T* add_mappings() {
    return BeginNestedMessage<T>(19);
  }

  template <typename T = Frame> T* add_frames() {
    return BeginNestedMessage<T>(6);
  }

  template <typename T = Callstack> T* add_callstacks() {
    return BeginNestedMessage<T>(7);
  }

  template <typename T = InternedString> T* add_vulkan_memory_keys() {
    return BeginNestedMessage<T>(22);
  }

  template <typename T = InternedGraphicsContext> T* add_graphics_contexts() {
    return BeginNestedMessage<T>(23);
  }

  template <typename T = InternedGpuRenderStageSpecification> T* add_gpu_specifications() {
    return BeginNestedMessage<T>(24);
  }

};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
