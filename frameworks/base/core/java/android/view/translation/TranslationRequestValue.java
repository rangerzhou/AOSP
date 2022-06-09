/*
 * Copyright (C) 2021 The Android Open Source Project
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

package android.view.translation;

import android.annotation.NonNull;
import android.annotation.Nullable;
import android.os.Parcel;
import android.os.Parcelable;

import com.android.internal.util.DataClass;

import java.util.Objects;

/**
 * A value to be translated via {@link android.view.translation.Translator}.
 */
@DataClass(genHiddenConstructor = true, genToString = true, genEqualsHashCode = true)
public final class TranslationRequestValue implements Parcelable {

    @Nullable
    private final CharSequence mText;

    /**
     * Creates a {@link TranslationRequestValue} with a {@link CharSequence} value;
     *
     * @param text the text to be translated.
     */
    @NonNull
    public static TranslationRequestValue forText(@NonNull CharSequence text) {
        Objects.requireNonNull(text, "text should not be null");
        return new TranslationRequestValue(text);
    }

    /**
     * @return the text value as a {@link CharSequence} or {@code null} if the value is not of type
     * text.
     */
    @Nullable
    public CharSequence getText() {
        return mText;
    }



    // Code below generated by codegen v1.0.23.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/view/translation/TranslationRequestValue.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    /**
     * Creates a new TranslationRequestValue.
     *
     * @hide
     */
    @DataClass.Generated.Member
    public TranslationRequestValue(
            @Nullable CharSequence text) {
        this.mText = text;

        // onConstructed(); // You can define this method to get a callback
    }

    @Override
    @DataClass.Generated.Member
    public String toString() {
        // You can override field toString logic by defining methods like:
        // String fieldNameToString() { ... }

        return "TranslationRequestValue { " +
                "text = " + mText +
        " }";
    }

    @Override
    @DataClass.Generated.Member
    public boolean equals(@Nullable Object o) {
        // You can override field equality logic by defining either of the methods like:
        // boolean fieldNameEquals(TranslationRequestValue other) { ... }
        // boolean fieldNameEquals(FieldType otherValue) { ... }

        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        @SuppressWarnings("unchecked")
        TranslationRequestValue that = (TranslationRequestValue) o;
        //noinspection PointlessBooleanExpression
        return true
                && Objects.equals(mText, that.mText);
    }

    @Override
    @DataClass.Generated.Member
    public int hashCode() {
        // You can override field hashCode logic by defining methods like:
        // int fieldNameHashCode() { ... }

        int _hash = 1;
        _hash = 31 * _hash + Objects.hashCode(mText);
        return _hash;
    }

    @Override
    @DataClass.Generated.Member
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        // You can override field parcelling by defining methods like:
        // void parcelFieldName(Parcel dest, int flags) { ... }

        byte flg = 0;
        if (mText != null) flg |= 0x1;
        dest.writeByte(flg);
        if (mText != null) dest.writeCharSequence(mText);
    }

    @Override
    @DataClass.Generated.Member
    public int describeContents() { return 0; }

    /** @hide */
    @SuppressWarnings({"unchecked", "RedundantCast"})
    @DataClass.Generated.Member
    /* package-private */ TranslationRequestValue(@NonNull Parcel in) {
        // You can override field unparcelling by defining methods like:
        // static FieldType unparcelFieldName(Parcel in) { ... }

        byte flg = in.readByte();
        CharSequence text = (flg & 0x1) == 0 ? null : (CharSequence) in.readCharSequence();

        this.mText = text;

        // onConstructed(); // You can define this method to get a callback
    }

    @DataClass.Generated.Member
    public static final @NonNull Parcelable.Creator<TranslationRequestValue> CREATOR
            = new Parcelable.Creator<TranslationRequestValue>() {
        @Override
        public TranslationRequestValue[] newArray(int size) {
            return new TranslationRequestValue[size];
        }

        @Override
        public TranslationRequestValue createFromParcel(@NonNull Parcel in) {
            return new TranslationRequestValue(in);
        }
    };

    @DataClass.Generated(
            time = 1620259864154L,
            codegenVersion = "1.0.23",
            sourceFile = "frameworks/base/core/java/android/view/translation/TranslationRequestValue.java",
            inputSignatures = "private final @android.annotation.Nullable java.lang.CharSequence mText\npublic static @android.annotation.NonNull android.view.translation.TranslationRequestValue forText(java.lang.CharSequence)\npublic @android.annotation.Nullable java.lang.CharSequence getText()\nclass TranslationRequestValue extends java.lang.Object implements [android.os.Parcelable]\n@com.android.internal.util.DataClass(genHiddenConstructor=true, genToString=true, genEqualsHashCode=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
