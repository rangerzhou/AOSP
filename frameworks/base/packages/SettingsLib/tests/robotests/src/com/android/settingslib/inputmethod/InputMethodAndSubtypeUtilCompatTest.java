/*
 * Copyright (C) 2018 The Android Open Source Project
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

package com.android.settingslib.inputmethod;

import static com.google.common.truth.Truth.assertThat;

import android.content.pm.ApplicationInfo;
import android.content.pm.ResolveInfo;
import android.content.pm.ServiceInfo;
import android.view.inputmethod.InputMethodInfo;
import android.view.inputmethod.InputMethodSubtype;
import android.view.inputmethod.InputMethodSubtype.InputMethodSubtypeBuilder;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

@RunWith(RobolectricTestRunner.class)
public class InputMethodAndSubtypeUtilCompatTest {

    private static final HashSet<String> EMPTY_STRING_SET = new HashSet<>();

    private static HashSet<String> asHashSet(String... strings) {
        return new HashSet<>(Arrays.asList(strings));
    }

    @Test
    public void parseInputMethodsAndSubtypesString_EmptyString() {
        assertThat(InputMethodAndSubtypeUtilCompat.
                parseInputMethodsAndSubtypesString("")).isEmpty();
        assertThat(InputMethodAndSubtypeUtilCompat.
                parseInputMethodsAndSubtypesString(null)).isEmpty();
    }

    @Test
    public void parseInputMethodsAndSubtypesString_SingleImeNoSubtype() {
        HashMap<String, HashSet<String>> r =
                InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString("ime0");
        assertThat(r).containsExactly("ime0", EMPTY_STRING_SET);
    }

    @Test
    public void parseInputMethodsAndSubtypesString_MultipleImesNoSubtype() {
        HashMap<String, HashSet<String>> r =
                InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString("ime0:ime1");
        assertThat(r).containsExactly("ime0", EMPTY_STRING_SET, "ime1", EMPTY_STRING_SET);
    }

    @Test
    public void parseInputMethodsAndSubtypesString_SingleImeSingleSubtype() {
        HashMap<String, HashSet<String>> r =
                InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString("ime0;subtype0");
        assertThat(r).containsExactly("ime0", asHashSet("subtype0"));
    }

    @Test
    public void parseInputMethodsAndSubtypesString_SingleImeDuplicateSameSubtypes() {
        HashMap<String, HashSet<String>> r =
                InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString(
                        "ime0;subtype0;subtype0");
        assertThat(r).containsExactly("ime0", asHashSet("subtype0"));
    }

    @Test
    public void parseInputMethodsAndSubtypesString_SingleImeMultipleSubtypes() {
        HashMap<String, HashSet<String>> r =
                InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString(
                        "ime0;subtype0;subtype1");
        assertThat(r).containsExactly("ime0", asHashSet("subtype0", "subtype1"));
    }

    @Test
    public void parseInputMethodsAndSubtypesString_MultiplePairsOfImeSubtype() {
        assertThat(InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString(
                "ime0;subtype0:ime1;subtype1"))
                .containsExactly("ime0", asHashSet("subtype0"), "ime1", asHashSet("subtype1"));
        assertThat(InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString(
                "ime0;subtype0;subtype1:ime1;subtype2"))
                .containsExactly("ime0", asHashSet("subtype0", "subtype1"),
                        "ime1", asHashSet("subtype2"));
        assertThat(InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString(
                "ime0;subtype0;subtype1:ime1;subtype1;subtype2"))
                .containsExactly("ime0", asHashSet("subtype0", "subtype1"),
                        "ime1", asHashSet("subtype1", "subtype2"));
    }

    @Test
    public void parseInputMethodsAndSubtypesString_MixedImeSubtypePairsAndImeNoSubtype() {
        HashMap<String, HashSet<String>> r =
                InputMethodAndSubtypeUtilCompat.parseInputMethodsAndSubtypesString(
                        "ime0;subtype0;subtype1:ime1;subtype1;subtype2:ime2");
        assertThat(r).containsExactly("ime0", asHashSet("subtype0", "subtype1"),
                "ime1", asHashSet("subtype1", "subtype2"),
                "ime2", EMPTY_STRING_SET);
    }

    @Test
    public void buildInputMethodsAndSubtypesString_EmptyInput() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        assertThat(map).isEmpty();
    }

    @Test
    public void buildInputMethodsAndSubtypesString_SingleIme() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        map.put("ime0", new HashSet<>());
        String result = InputMethodAndSubtypeUtilCompat.buildInputMethodsAndSubtypesString(map);
        assertThat(result).isEqualTo("ime0");
    }

    @Test
    public void buildInputMethodsAndSubtypesString_SingleImeSingleSubtype() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        map.put("ime0", asHashSet("subtype0"));
        String result = InputMethodAndSubtypeUtilCompat.buildInputMethodsAndSubtypesString(map);
        assertThat(result).isEqualTo("ime0;subtype0");
    }

    @Test
    public void buildInputMethodsAndSubtypesString_SingleImeMultipleSubtypes() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        map.put("ime0", asHashSet("subtype0", "subtype1"));
        String result = InputMethodAndSubtypeUtilCompat.buildInputMethodsAndSubtypesString(map);

        // We do not expect what order will be used to concatenate items in
        // InputMethodAndSubtypeUtil.buildInputMethodsAndSubtypesString() hence accept all possible
        // permutations here.
        assertThat(result).matches("ime0;subtype0;subtype1|ime0;subtype1;subtype0");
    }

    @Test
    public void buildInputMethodsAndSubtypesString_MultipleImesNoSubtypes() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        map.put("ime0", EMPTY_STRING_SET);
        map.put("ime1", EMPTY_STRING_SET);
        String result = InputMethodAndSubtypeUtilCompat.buildInputMethodsAndSubtypesString(map);

        // We do not expect what order will be used to concatenate items in
        // InputMethodAndSubtypeUtil.buildInputMethodsAndSubtypesString() hence accept all possible
        // permutations here.
        assertThat(result).matches("ime0:ime1|ime1:ime0");
    }

    @Test
    public void buildInputMethodsAndSubtypesString_MultipleImesWithAndWithoutSubtypes() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        map.put("ime0", asHashSet("subtype0", "subtype1"));
        map.put("ime1", EMPTY_STRING_SET);
        String result = InputMethodAndSubtypeUtilCompat.buildInputMethodsAndSubtypesString(map);

        // We do not expect what order will be used to concatenate items in
        // InputMethodAndSubtypeUtil.buildInputMethodsAndSubtypesString() hence accept all possible
        // permutations here.
        assertThat(result).matches("ime0;subtype0;subtype1:ime1|ime0;subtype1;subtype0:ime1"
                + "|ime1:ime0;subtype0;subtype1|ime1:ime0;subtype1;subtype0");
    }

    @Test
    public void buildInputMethodsAndSubtypesString_MultipleImesWithSubtypes() {
        HashMap<String, HashSet<String>> map = new HashMap<>();
        map.put("ime0", asHashSet("subtype0", "subtype1"));
        map.put("ime1", asHashSet("subtype2", "subtype3"));
        String result = InputMethodAndSubtypeUtilCompat.buildInputMethodsAndSubtypesString(map);

        // We do not expect what order will be used to concatenate items in
        // InputMethodAndSubtypeUtil.buildInputMethodsAndSubtypesString() hence accept all possible
        // permutations here.
        assertThat(result).matches("ime0;subtype0;subtype1:ime1;subtype2;subtype3"
                + "|ime0;subtype1;subtype0:ime1;subtype2;subtype3"
                + "|ime0;subtype0;subtype1:ime1;subtype3;subtype2"
                + "|ime0;subtype1;subtype0:ime1;subtype3;subtype2"
                + "|ime1;subtype2;subtype3:ime0;subtype0;subtype1"
                + "|ime2;subtype3;subtype2:ime0;subtype0;subtype1"
                + "|ime3;subtype2;subtype3:ime0;subtype1;subtype0"
                + "|ime4;subtype3;subtype2:ime0;subtype1;subtype0");
    }

    @Test
    public void isValidSystemNonAuxAsciiCapableIme() {
        // System IME w/ no subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(true, false)))
                .isFalse();

        // System IME w/ non-Aux and non-ASCII-capable "keyboard" subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(true, false, createFakeSubtype("keyboard", false, false))))
                .isFalse();

        // System IME w/ non-Aux and ASCII-capable "keyboard" subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(true, false, createFakeSubtype("keyboard", false, true))))
                .isTrue();

        // System IME w/ Aux and ASCII-capable "keyboard" subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(true, true, createFakeSubtype("keyboard", true, true))))
                .isFalse();

        // System IME w/ non-Aux and ASCII-capable "voice" subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(true, false, createFakeSubtype("voice", false, true))))
                .isFalse();

        // System IME w/ non-Aux and non-ASCII-capable subtype + Non-Aux and ASCII-capable subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(true, false,
                        createFakeSubtype("keyboard", false, true),
                        createFakeSubtype("keyboard", false, false))))
                .isTrue();

        // Non-system IME w/ non-Aux and ASCII-capable "keyboard" subtype
        assertThat(InputMethodAndSubtypeUtilCompat.isValidSystemNonAuxAsciiCapableIme(
                createFakeIme(false, false, createFakeSubtype("keyboard", false, true))))
                .isFalse();
    }

    private static InputMethodInfo createFakeIme(boolean isSystem, boolean isAuxIme,
            InputMethodSubtype... subtypes) {
        final ResolveInfo ri = new ResolveInfo();
        final ServiceInfo si = new ServiceInfo();
        final ApplicationInfo ai = new ApplicationInfo();
        ai.packageName = "com.example.android.fakeime";
        ai.enabled = true;
        ai.flags |= (isSystem ? ApplicationInfo.FLAG_SYSTEM : 0);
        si.applicationInfo = ai;
        si.enabled = true;
        si.packageName = "com.example.android.fakeime";
        si.name = "Fake IME";
        si.exported = true;
        si.nonLocalizedLabel = "Fake IME";
        ri.serviceInfo = si;
        return new InputMethodInfo(ri, isAuxIme, "", Arrays.asList(subtypes), 1, false);
    }

    private static InputMethodSubtype createFakeSubtype(
            String mode, boolean isAuxiliary, boolean isAsciiCapable) {
        return new InputMethodSubtypeBuilder()
                .setSubtypeNameResId(0)
                .setSubtypeIconResId(0)
                .setSubtypeLocale("en_US")
                .setLanguageTag("en-US")
                .setSubtypeMode(mode)
                .setIsAuxiliary(isAuxiliary)
                .setIsAsciiCapable(isAsciiCapable)
                .build();
    }
}
