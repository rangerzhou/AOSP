/*
 * Copyright (C) 2019 The Android Open Source Project
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

package android.view.inputmethod;

import android.annotation.NonNull;
import android.annotation.Nullable;
import android.annotation.TestApi;
import android.os.Parcelable;

import com.android.internal.util.DataClass;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents an inline suggestion response. See {@link InlineSuggestion} for more
 * information.
 */
@DataClass(genEqualsHashCode = true, genToString = true, genHiddenConstructor = true)
public final class InlineSuggestionsResponse implements Parcelable {
    /**
     * List of {@link InlineSuggestion}s returned as a part of this response.
     *
     * <p>When the host app requests to inflate this <b>ordered</b> list of inline suggestions by
     * calling {@link InlineSuggestion#inflate}, it is the host's responsibility to track the
     * order of the inflated {@link android.view.View}s. These views are to be added in
     * order to the view hierarchy, because the inflation calls will return asynchronously.</p>
     *
     * <p>The inflation ordering does not apply to the pinned icon.</p>
     */
    @NonNull
    private final List<InlineSuggestion> mInlineSuggestions;

    /**
     * Creates a new {@link InlineSuggestionsResponse}, for testing purpose.
     *
     * @hide
     */
    @TestApi
    @NonNull
    public static InlineSuggestionsResponse newInlineSuggestionsResponse(
            @NonNull List<InlineSuggestion> inlineSuggestions) {
        return new InlineSuggestionsResponse(inlineSuggestions);
    }



    // Code below generated by codegen v1.0.15.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/view/inputmethod/InlineSuggestionsResponse.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    /**
     * Creates a new InlineSuggestionsResponse.
     *
     * @param inlineSuggestions
     *   List of {@link InlineSuggestion}s returned as a part of this response.
     *
     *   <p>When the host app requests to inflate this <b>ordered</b> list of inline suggestions by
     *   calling {@link InlineSuggestion#inflate}, it is the host's responsibility to track the
     *   order of the inflated {@link android.view.View}s. These views are to be added in
     *   order to the view hierarchy, because the inflation calls will return asynchronously.</p>
     *
     *   <p>The inflation ordering does not apply to the pinned icon.</p>
     * @hide
     */
    @DataClass.Generated.Member
    public InlineSuggestionsResponse(
            @NonNull List<InlineSuggestion> inlineSuggestions) {
        this.mInlineSuggestions = inlineSuggestions;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mInlineSuggestions);

        // onConstructed(); // You can define this method to get a callback
    }

    /**
     * List of {@link InlineSuggestion}s returned as a part of this response.
     *
     * <p>When the host app requests to inflate this <b>ordered</b> list of inline suggestions by
     * calling {@link InlineSuggestion#inflate}, it is the host's responsibility to track the
     * order of the inflated {@link android.view.View}s. These views are to be added in
     * order to the view hierarchy, because the inflation calls will return asynchronously.</p>
     *
     * <p>The inflation ordering does not apply to the pinned icon.</p>
     */
    @DataClass.Generated.Member
    public @NonNull List<InlineSuggestion> getInlineSuggestions() {
        return mInlineSuggestions;
    }

    @Override
    @DataClass.Generated.Member
    public String toString() {
        // You can override field toString logic by defining methods like:
        // String fieldNameToString() { ... }

        return "InlineSuggestionsResponse { " +
                "inlineSuggestions = " + mInlineSuggestions +
        " }";
    }

    @Override
    @DataClass.Generated.Member
    public boolean equals(@Nullable Object o) {
        // You can override field equality logic by defining either of the methods like:
        // boolean fieldNameEquals(InlineSuggestionsResponse other) { ... }
        // boolean fieldNameEquals(FieldType otherValue) { ... }

        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        @SuppressWarnings("unchecked")
        InlineSuggestionsResponse that = (InlineSuggestionsResponse) o;
        //noinspection PointlessBooleanExpression
        return true
                && java.util.Objects.equals(mInlineSuggestions, that.mInlineSuggestions);
    }

    @Override
    @DataClass.Generated.Member
    public int hashCode() {
        // You can override field hashCode logic by defining methods like:
        // int fieldNameHashCode() { ... }

        int _hash = 1;
        _hash = 31 * _hash + java.util.Objects.hashCode(mInlineSuggestions);
        return _hash;
    }

    @Override
    @DataClass.Generated.Member
    public void writeToParcel(@NonNull android.os.Parcel dest, int flags) {
        // You can override field parcelling by defining methods like:
        // void parcelFieldName(Parcel dest, int flags) { ... }

        dest.writeParcelableList(mInlineSuggestions, flags);
    }

    @Override
    @DataClass.Generated.Member
    public int describeContents() { return 0; }

    /** @hide */
    @SuppressWarnings({"unchecked", "RedundantCast"})
    @DataClass.Generated.Member
    /* package-private */ InlineSuggestionsResponse(@NonNull android.os.Parcel in) {
        // You can override field unparcelling by defining methods like:
        // static FieldType unparcelFieldName(Parcel in) { ... }

        List<InlineSuggestion> inlineSuggestions = new ArrayList<>();
        in.readParcelableList(inlineSuggestions, InlineSuggestion.class.getClassLoader());

        this.mInlineSuggestions = inlineSuggestions;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mInlineSuggestions);

        // onConstructed(); // You can define this method to get a callback
    }

    @DataClass.Generated.Member
    public static final @NonNull Parcelable.Creator<InlineSuggestionsResponse> CREATOR
            = new Parcelable.Creator<InlineSuggestionsResponse>() {
        @Override
        public InlineSuggestionsResponse[] newArray(int size) {
            return new InlineSuggestionsResponse[size];
        }

        @Override
        public InlineSuggestionsResponse createFromParcel(@NonNull android.os.Parcel in) {
            return new InlineSuggestionsResponse(in);
        }
    };

    @DataClass.Generated(
            time = 1595891876037L,
            codegenVersion = "1.0.15",
            sourceFile = "frameworks/base/core/java/android/view/inputmethod/InlineSuggestionsResponse.java",
            inputSignatures = "private final @android.annotation.NonNull java.util.List<android.view.inputmethod.InlineSuggestion> mInlineSuggestions\npublic static @android.annotation.TestApi @android.annotation.NonNull android.view.inputmethod.InlineSuggestionsResponse newInlineSuggestionsResponse(java.util.List<android.view.inputmethod.InlineSuggestion>)\nclass InlineSuggestionsResponse extends java.lang.Object implements [android.os.Parcelable]\n@com.android.internal.util.DataClass(genEqualsHashCode=true, genToString=true, genHiddenConstructor=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
