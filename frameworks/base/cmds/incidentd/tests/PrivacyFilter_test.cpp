// Copyright (C) 2017 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#define DEBUG false
#include "Log.h"

#include "FdBuffer.h"
#include "PrivacyFilter.h"

#include <android-base/file.h>
#include <android-base/test_utils.h>
#include <android/os/IncidentReportArgs.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string.h>

using namespace android;
using namespace android::base;
using namespace android::os;
using namespace android::os::incidentd;
using ::testing::StrEq;
using ::testing::Test;
using ::testing::internal::CaptureStdout;
using ::testing::internal::GetCapturedStdout;

const uint8_t OTHER_TYPE = 1;
const uint8_t STRING_TYPE = 9;
const uint8_t MESSAGE_TYPE = 11;
const std::string STRING_FIELD_0 = "\x02\viamtestdata";
const std::string VARINT_FIELD_1 = "\x08\x96\x01";  // 150
const std::string STRING_FIELD_2 = "\x12\vandroidwins";
const std::string FIX64_FIELD_3 = "\x19\xff\xff\xff\xff\xff\xff\xff\xff";  // -1
const std::string FIX32_FIELD_4 = "\x25\xff\xff\xff\xff";                  // -1
const std::string MESSAGE_FIELD_5 = "\x2a\x10" + VARINT_FIELD_1 + STRING_FIELD_2;
const std::string NEGATIVE_VARINT_FIELD_6 = "\x30\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01";  // -1

#if 0
class PrivacyFilterTest : public Test {
public:
    virtual ~PrivacyFilterTest() {
        // Delete in reverse order of construction, to be consistent with
        // regular allocation/deallocation.
        while (!privacies.empty()) {
            delete privacies.back();
            privacies.pop_back();
        }
    }

    virtual void SetUp() override { ASSERT_NE(tf.fd, -1); }

    void writeToFdBuffer(std::string str) {
        ASSERT_TRUE(WriteStringToFile(str, tf.path));
        ASSERT_EQ(NO_ERROR, buffer.read(tf.fd, 10000));
        ASSERT_EQ(str.size(), buffer.size());
    }

    void assertBuffer(PrivacyFilter& buf, std::string expected) {
        ASSERT_EQ(buf.size(), expected.size());
        CaptureStdout();
        ASSERT_EQ(buf.flush(STDOUT_FILENO), NO_ERROR);
        ASSERT_THAT(GetCapturedStdout(), StrEq(expected));
    }

    void assertStrip(uint8_t privacyPolicy, std::string expected, Privacy* policy) {
        PrivacySpec spec = PrivacySpec::new_spec(privacyPolicy);
        EncodedBuffer::iterator bufData = buffer.data();
        PrivacyFilter filter(policy, bufData);
        ASSERT_EQ(filter.strip(spec), NO_ERROR);
        assertBuffer(filter, expected);
    }

    void assertStripByFields(uint8_t privacyPolicy, std::string expected, int size,
            Privacy* privacy, ...) {
        Privacy* list[size + 1];
        list[0] = privacy;
        va_list args;
        va_start(args, privacy);
        for (int i = 1; i < size; i++) {
            Privacy* p = va_arg(args, Privacy*);
            list[i] = pPrivacyFilter
        }
        va_end(args);
        list[size] = NULL;
        assertStrip(privacyPolicy, expected, create_message_privacy(300, list));
    }

    Privacy* create_privacy(uint32_t field_id, uint8_t type, uint8_t privacyPolicy) {
        Privacy* p = new_uninit_privacy();
        p->field_id = field_id;
        p->type = type;
        p->children = NULL;
        p->policy = privacyPolicy;
        p->patterns = NULL;
        return p;
    }

    Privacy* create_message_privacy(uint32_t field_id, Privacy** children) {
        Privacy* p = new_uninit_privacy();
        p->field_id = field_id;
        p->type = MESSAGE_TYPE;
        p->children = children;
        p->policy = PRIVACY_POLICY_UNSET;
        p->patterns = NULL;
        return p;
    }

    FdBuffer buffer;

private:
    TemporaryFile tf;
    // Littering this code with unique_ptr (or similar) is ugly, so we just
    // mass-free everything after the test completes.
    std::vector<Privacy*> privacies;

    Privacy* new_uninit_privacy() {
        Privacy* p = new Privacy;
        privacies.push_back(p);
        return p;
    }
};

TEST_F(PrivacyFilterTest, NullPolicy) {
    writeToFdBuffer(STRING_FIELD_0);
    assertStrip(PRIVACY_POLICY_EXPLICIT, STRING_FIELD_0, NULL);
}

TEST_F(PrivacyFilterTest, StripUnsetField) {
    writeToFdBuffer(STRING_FIELD_0);
    assertStripByFields(PRIVACY_POLICY_AUTOMATIC, "", 1,
            create_privacy(0, STRING_TYPE, PRIVACY_POLICY_UNSET));
}

TEST_F(PrivacyFilterTest, StripVarintField) {
    writeToFdBuffer(VARINT_FIELD_1);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, "", 1,
            create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripLengthDelimitedField_String) {
    writeToFdBuffer(STRING_FIELD_2);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, "", 1,
            create_privacy(2, STRING_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripFixed64Field) {
    writeToFdBuffer(FIX64_FIELD_3);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, "", 1,
            create_privacy(3, OTHER_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripFixed32Field) {
    writeToFdBuffer(FIX32_FIELD_4);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, "", 1,
            create_privacy(4, OTHER_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripLengthDelimitedField_Message) {
    writeToFdBuffer(MESSAGE_FIELD_5);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, "", 1,
            create_privacy(5, MESSAGE_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripNegativeVarint) {
    writeToFdBuffer(NEGATIVE_VARINT_FIELD_6);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, "", 1,
            create_privacy(6, OTHER_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, NoStripVarintField) {
    writeToFdBuffer(VARINT_FIELD_1);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, VARINT_FIELD_1, 1,
            create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_AUTOMATIC));
}

TEST_F(PrivacyFilterTest, NoStripLengthDelimitedField_String) {
    writeToFdBuffer(STRING_FIELD_2);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, STRING_FIELD_2, 1,
            create_privacy(2, STRING_TYPE, PRIVACY_POLICY_AUTOMATIC));
}

TEST_F(PrivacyFilterTest, NoStripFixed64Field) {
    writeToFdBuffer(FIX64_FIELD_3);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, FIX64_FIELD_3, 1,
            create_privacy(3, OTHER_TYPE, PRIVACY_POLICY_AUTOMATIC));
}

TEST_F(PrivacyFilterTest, NoStripFixed32Field) {
    writeToFdBuffer(FIX32_FIELD_4);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, FIX32_FIELD_4, 1,
            create_privacy(4, OTHER_TYPE, PRIVACY_POLICY_AUTOMATIC));
}

TEST_F(PrivacyFilterTest, NoStripLengthDelimitedField_Message) {
    writeToFdBuffer(MESSAGE_FIELD_5);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, MESSAGE_FIELD_5, 1,
            create_privacy(5, MESSAGE_TYPE, PRIVACY_POLICY_AUTOMATIC));
}

TEST_F(PrivacyFilterTest, NoStripNegativeVarintField) {
    writeToFdBuffer(NEGATIVE_VARINT_FIELD_6);
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, NEGATIVE_VARINT_FIELD_6, 1,
            create_privacy(6, OTHER_TYPE, PRIVACY_POLICY_AUTOMATIC));
}

TEST_F(PrivacyFilterTest, StripVarintAndString) {
    writeToFdBuffer(STRING_FIELD_0 + VARINT_FIELD_1 + STRING_FIELD_2 + FIX64_FIELD_3 +
                    FIX32_FIELD_4);
    std::string expected = STRING_FIELD_0 + FIX64_FIELD_3 + FIX32_FIELD_4;
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, expected, 2,
            create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL),
            create_privacy(2, STRING_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripVarintAndFixed64) {
    writeToFdBuffer(STRING_FIELD_0 + VARINT_FIELD_1 + STRING_FIELD_2 + FIX64_FIELD_3 +
                    FIX32_FIELD_4);
    std::string expected = STRING_FIELD_0 + STRING_FIELD_2 + FIX32_FIELD_4;
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, expected, 2,
            create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL),
            create_privacy(3, OTHER_TYPE, PRIVACY_POLICY_LOCAL));
}

TEST_F(PrivacyFilterTest, StripVarintInNestedMessage) {
    writeToFdBuffer(STRING_FIELD_0 + MESSAGE_FIELD_5);
    Privacy* list[] = {create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL), NULL};
    std::string expected = STRING_FIELD_0 + "\x2a\xd" + STRING_FIELD_2;
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, expected, 1, create_message_privacy(5, list));
}

TEST_F(PrivacyFilterTest, StripFix64AndVarintInNestedMessage) {
    writeToFdBuffer(STRING_FIELD_0 + FIX64_FIELD_3 + MESSAGE_FIELD_5);
    Privacy* list[] = {create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL), NULL};
    std::string expected = STRING_FIELD_0 + "\x2a\xd" + STRING_FIELD_2;
    assertStripByFields(PRIVACY_POLICY_EXPLICIT, expected, 2,
            create_privacy(3, OTHER_TYPE, PRIVACY_POLICY_LOCAL),
            create_message_privacy(5, list));
}

TEST_F(PrivacyFilterTest, ClearAndStrip) {
    string data = STRING_FIELD_0 + VARINT_FIELD_1;
    writeToFdBuffer(data);
    Privacy* list[] = {create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL), NULL};
    EncodedBuffer::iterator bufData = buffer.data();
    PrivacyFilter filter(create_message_privacy(300, list), bufData);
    PrivacySpec spec1 = PrivacySpec::new_spec(PRIVACY_POLICY_EXPLICIT);
    PrivacySpec spec2 = PrivacySpec::new_spec(PRIVACY_POLICY_LOCAL);

    ASSERT_EQ(filter.strip(spec1), NO_ERROR);
    assertBuffer(filter, STRING_FIELD_0);
    ASSERT_EQ(filter.strip(spec2), NO_ERROR);
    assertBuffer(filter, data);
}

TEST_F(PrivacyFilterTest, BadDataInFdBuffer) {
    writeToFdBuffer("iambaddata");
    Privacy* list[] = {create_privacy(4, OTHER_TYPE, PRIVACY_POLICY_AUTOMATIC), NULL};
    EncodedBuffer::iterator bufData = buffer.data();
    PrivacyFilter filter(create_message_privacy(300, list), bufData);
    PrivacySpec spec;
    ASSERT_EQ(filter.strip(spec), BAD_VALUE);
}

TEST_F(PrivacyFilterTest, BadDataInNestedMessage) {
    writeToFdBuffer(STRING_FIELD_0 + MESSAGE_FIELD_5 + "aoeoe");
    Privacy* list[] = {create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL), NULL};
    Privacy* field5[] = {create_message_privacy(5, list), NULL};
    EncodedBuffer::iterator bufData = buffer.data();
    PrivacyFilter filter(create_message_privacy(300, field5), bufData);
    PrivacySpec spec;
    ASSERT_EQ(filter.strip(spec), BAD_VALUE);
}

TEST_F(PrivacyFilterTest, SelfRecursionMessage) {
    string input = "\x2a\"" + VARINT_FIELD_1 + STRING_FIELD_2 + MESSAGE_FIELD_5;
    writeToFdBuffer(input);
    Privacy* field5 = create_message_privacy(5, NULL);
    Privacy* list[] = {create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL), field5, NULL};
    field5->children = list;
    std::string expected = "\x2a\x1c" + STRING_FIELD_2 + "\x2a\xd" + STRING_FIELD_2;
    assertStrip(PRIVACY_POLICY_EXPLICIT, expected, field5);
}

TEST_F(PrivacyFilterTest, AutoMessage) {
    writeToFdBuffer(STRING_FIELD_2 + MESSAGE_FIELD_5);
    Privacy* list[] = {create_privacy(1, OTHER_TYPE, PRIVACY_POLICY_LOCAL), NULL};
    Privacy* autoMsg = create_privacy(5, MESSAGE_TYPE, PRIVACY_POLICY_AUTOMATIC);
    autoMsg->children = list;
    std::string expected = "\x2a\xd" + STRING_FIELD_2;
    assertStripByFields(PRIVACY_POLICY_AUTOMATIC, expected, 1, autoMsg);
}

#endif
