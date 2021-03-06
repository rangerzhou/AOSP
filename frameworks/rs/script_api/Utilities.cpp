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

#include <algorithm>
#include <iostream>
#include <sstream>

#include "Utilities.h"

using namespace std;

const char LEGAL_NOTICE[] =
            "/*\n"
            " * Copyright (C) 2016 The Android Open Source Project\n"
            " *\n"
            " * Licensed under the Apache License, Version 2.0 (the \"License\");\n"
            " * you may not use this file except in compliance with the License.\n"
            " * You may obtain a copy of the License at\n"
            " *\n"
            " *      http://www.apache.org/licenses/LICENSE-2.0\n"
            " *\n"
            " * Unless required by applicable law or agreed to in writing, software\n"
            " * distributed under the License is distributed on an \"AS IS\" BASIS,\n"
            " * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
            " * See the License for the specific language governing permissions and\n"
            " * limitations under the License.\n"
            " */\n\n";

const char AUTO_GENERATED_WARNING[] =
            "Don't edit this file!  It is auto-generated by frameworks/rs/api/generate.sh.";

string capitalize(const string& source) {
    int length = source.length();
    string result;
    bool capitalize = true;
    for (int s = 0; s < length; s++) {
        if (source[s] == '_') {
            capitalize = true;
        } else if (capitalize) {
            result += toupper(source[s]);
            capitalize = false;
        } else {
            result += source[s];
        }
    }
    return result;
}

void trimSpaces(string* s) {
    const size_t end = s->find_last_not_of(" ");
    if (end == string::npos) {
        // All spaces
        s->erase();
        return;
    } else {
        s->erase(end + 1);
    }
    const size_t start = s->find_first_not_of(" ");
    if (start > 0) {
        s->erase(0, start);
    }
}

string stringReplace(string s, string match, string rep) {
    while (1) {
        // This is not efficient but we don't care, as this program runs very rarely.
        size_t p = s.find(match);
        if (p == string::npos) break;

        s.erase(p, match.size());
        s.insert(p, rep);
    }
    return s;
}

bool charRemoved(char c, string* s) {
    size_t p = s->find(c);
    if (p != string::npos) {
        s->erase(p, 1);
        return true;
    }
    return false;
}

string stripHtml(const string& html) {
    string in = stringReplace(html, "<li>", "- ");
    string out;
    for (size_t start = 0; start < in.size(); start++) {
        size_t lt = in.find('<', start);
        if (lt == string::npos) {
            out += in.substr(start);
            break;
        }
        out += in.substr(start, lt - start);
        if (isalpha(in[lt + 1]) || in[lt + 1] == '/') {
            // It's an HTML tag.  Search for the end.
            start = in.find('>', lt + 1);
            if (start == string::npos) {
                break;
            }
        } else {
            out += '<';
        }
    }
    out = stringReplace(out, "&gt;", ">");
    out = stringReplace(out, "&lt;", "<");
    out = stringReplace(out, "&nbsp;", " ");
    out = stringReplace(out, "&amp;", "&");
    return out;
}

string hashString(const string& s) {
    long hash = 0;
    for (size_t i = 0; i < s.length(); i++) {
        hash = hash * 43 + s[i];
    }
    stringstream stream;
    stream << "0x" << std::hex << hash << "l";
    return stream.str();
}

bool testAndSet(const string& flag, set<string>* set) {
    if (set->find(flag) == set->end()) {
        set->insert(flag);
        return false;
    }
    return true;
}

double maxDoubleForInteger(int numberOfIntegerBits, int mantissaSize) {
    /* Double has only 52 bits of precision (53 implied). So for longs, we want
     * to create smaller values to avoid a round up.  Same for floats and halfs.
     */
    int lowZeroBits = max(0, numberOfIntegerBits - mantissaSize);
    uint64_t l = (0xffffffffffffffff >> (64 - numberOfIntegerBits + lowZeroBits))
                 << lowZeroBits;
    return (double)l;
}

// Add the value to the stream, prefixed with a ", " if needed.
static void addCommaSeparated(const string& value, ostringstream* stream, bool* needComma) {
    if (value.empty()) {
        return;
    }
    if (*needComma) {
        *stream << ", ";
    }
    *stream << value;
    *needComma = true;
}

string makeAttributeTag(const string& userAttribute, const string& additionalAttribute,
                        unsigned int deprecatedApiLevel, const string& deprecatedMessage) {
    ostringstream stream;
    bool needComma = false;
    if (userAttribute[0] == '=') {
        /* If starts with an equal, we don't automatically add additionalAttribute.
         * This is because of the error we made defining rsUnpackColor8888().
         */
        addCommaSeparated(userAttribute.substr(1), &stream, &needComma);
    } else {
        addCommaSeparated(userAttribute, &stream, &needComma);
        addCommaSeparated(additionalAttribute, &stream, &needComma);
    }
    if (deprecatedApiLevel > 0) {
        stream << "\n#if (defined(RS_VERSION) && (RS_VERSION >= " << deprecatedApiLevel << "))\n";
        addCommaSeparated("deprecated", &stream, &needComma);
        if (!deprecatedMessage.empty()) {
            // Remove any @ that's used for generating documentation cross references.
            string s = deprecatedMessage;
            s.erase(std::remove(s.begin(), s.end(), '@'), s.end());
            stream << "(\"" << s << "\")";
        }
        stream << "\n#endif\n";
    }
    if (stream.tellp() == 0) {
        return "";
    }
    return " __attribute__((" + stream.str() + "))";
}

// Opens the stream.  Reports an error if it can't.
bool GeneratedFile::start(const string& directory, const string& name) {
    const string path = directory + "/" + name;
    open(path.c_str(), ios::out | ios::trunc);
    if (!is_open()) {
        cerr << "Error.  Can't open the output file: " << path << "\n";
        return false;
    }
    return true;
}

void GeneratedFile::writeNotices() {
    *this << LEGAL_NOTICE;
    *this << "// " << AUTO_GENERATED_WARNING << "\n\n";
}

void GeneratedFile::increaseIndent() {
    mIndent.append(string(TAB_SIZE, ' '));
}

void GeneratedFile::decreaseIndent() {
    mIndent.erase(0, TAB_SIZE);
}
