// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_STRUCT_TESTING_H_
#define FLATBUFFERS_GENERATED_STRUCT_TESTING_H_

#include "flatbuffers/flatbuffers.h"

namespace testing {

struct TestSubTable;
struct TestSubTableBuilder;

struct TestTableStruct;
struct TestTableStructBuilder;

struct TestSubTable FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TestSubTableBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE { VT_PLACEHOLDER = 4 };
  int32_t placeholder() const {
    return GetField<int32_t>(VT_PLACEHOLDER, 0);
  }
  bool Verify(flatbuffers::Verifier& verifier) const {
    return VerifyTableStart(verifier) && VerifyField<int32_t>(verifier, VT_PLACEHOLDER) && verifier.EndTable();
  }
};

struct TestSubTableBuilder {
  typedef TestSubTable Table;
  flatbuffers::FlatBufferBuilder& fbb_;
  flatbuffers::uoffset_t start_;
  void add_placeholder(int32_t placeholder) {
    fbb_.AddElement<int32_t>(TestSubTable::VT_PLACEHOLDER, placeholder, 0);
  }
  explicit TestSubTableBuilder(flatbuffers::FlatBufferBuilder& _fbb) : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TestSubTableBuilder& operator=(const TestSubTableBuilder&);
  flatbuffers::Offset<TestSubTable> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TestSubTable>(end);
    return o;
  }
};

inline flatbuffers::Offset<TestSubTable> CreateTestSubTable(
    flatbuffers::FlatBufferBuilder& _fbb, int32_t placeholder = 0) {
  TestSubTableBuilder builder_(_fbb);
  builder_.add_placeholder(placeholder);
  return builder_.Finish();
}

struct TestTableStruct FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TestTableStructBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE { VT_SUB_TABLE = 4 };
  const testing::TestSubTable* sub_table() const {
    return GetPointer<const testing::TestSubTable*>(VT_SUB_TABLE);
  }
  bool Verify(flatbuffers::Verifier& verifier) const {
    return VerifyTableStart(verifier) && VerifyOffset(verifier, VT_SUB_TABLE) && verifier.VerifyTable(sub_table()) &&
           verifier.EndTable();
  }
};

struct TestTableStructBuilder {
  typedef TestTableStruct Table;
  flatbuffers::FlatBufferBuilder& fbb_;
  flatbuffers::uoffset_t start_;
  void add_sub_table(flatbuffers::Offset<testing::TestSubTable> sub_table) {
    fbb_.AddOffset(TestTableStruct::VT_SUB_TABLE, sub_table);
  }
  explicit TestTableStructBuilder(flatbuffers::FlatBufferBuilder& _fbb) : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TestTableStructBuilder& operator=(const TestTableStructBuilder&);
  flatbuffers::Offset<TestTableStruct> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TestTableStruct>(end);
    return o;
  }
};

inline flatbuffers::Offset<TestTableStruct> CreateTestTableStruct(
    flatbuffers::FlatBufferBuilder& _fbb, flatbuffers::Offset<testing::TestSubTable> sub_table = 0) {
  TestTableStructBuilder builder_(_fbb);
  builder_.add_sub_table(sub_table);
  return builder_.Finish();
}

inline const testing::TestTableStruct* GetTestTableStruct(const void* buf) {
  return flatbuffers::GetRoot<testing::TestTableStruct>(buf);
}

inline const testing::TestTableStruct* GetSizePrefixedTestTableStruct(const void* buf) {
  return flatbuffers::GetSizePrefixedRoot<testing::TestTableStruct>(buf);
}

inline bool VerifyTestTableStructBuffer(flatbuffers::Verifier& verifier) {
  return verifier.VerifyBuffer<testing::TestTableStruct>(nullptr);
}

inline bool VerifySizePrefixedTestTableStructBuffer(flatbuffers::Verifier& verifier) {
  return verifier.VerifySizePrefixedBuffer<testing::TestTableStruct>(nullptr);
}

inline const char* TestTableStructExtension() {
  return "bfbs";
}

inline void FinishTestTableStructBuffer(
    flatbuffers::FlatBufferBuilder& fbb, flatbuffers::Offset<testing::TestTableStruct> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedTestTableStructBuffer(
    flatbuffers::FlatBufferBuilder& fbb, flatbuffers::Offset<testing::TestTableStruct> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace testing

#endif  // FLATBUFFERS_GENERATED_STRUCT_TESTING_H_
