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

package android.content.pm.permission;

import android.annotation.IntRange;
import android.annotation.NonNull;
import android.annotation.Nullable;
import android.os.Parcel;
import android.os.Parcelable;

import com.android.internal.util.DataClass;
import com.android.internal.util.Preconditions;

import java.util.List;
import java.util.Objects;

/**
 * Parcelable version of {@link android.permission.PermissionManager.SplitPermissionInfo}
 * @hide
 */
@DataClass(genEqualsHashCode = true)
public class SplitPermissionInfoParcelable implements Parcelable {

    /**
     * The permission that is split.
     */
    @NonNull
    private final String mSplitPermission;

    /**
     * The permissions that are added.
     */
    @NonNull
    private final List<String> mNewPermissions;

    /**
     * The target API level when the permission was split.
     */
    @IntRange(from = 0)
    private final int mTargetSdk;

    private void onConstructed() {
        Preconditions.checkCollectionElementsNotNull(mNewPermissions, "newPermissions");
    }



    // Code below generated by codegen v1.0.20.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/content/pm/permission/SplitPermissionInfoParcelable.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    /**
     * Creates a new SplitPermissionInfoParcelable.
     *
     * @param splitPermission
     *   The permission that is split.
     * @param newPermissions
     *   The permissions that are added.
     * @param targetSdk
     *   The target API level when the permission was split.
     */
    @DataClass.Generated.Member
    public SplitPermissionInfoParcelable(
            @NonNull String splitPermission,
            @NonNull List<String> newPermissions,
            @IntRange(from = 0) int targetSdk) {
        this.mSplitPermission = splitPermission;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mSplitPermission);
        this.mNewPermissions = newPermissions;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mNewPermissions);
        this.mTargetSdk = targetSdk;
        com.android.internal.util.AnnotationValidations.validate(
                IntRange.class, null, mTargetSdk,
                "from", 0);

        onConstructed();
    }

    /**
     * The permission that is split.
     */
    @DataClass.Generated.Member
    public @NonNull String getSplitPermission() {
        return mSplitPermission;
    }

    /**
     * The permissions that are added.
     */
    @DataClass.Generated.Member
    public @NonNull List<String> getNewPermissions() {
        return mNewPermissions;
    }

    /**
     * The target API level when the permission was split.
     */
    @DataClass.Generated.Member
    public @IntRange(from = 0) int getTargetSdk() {
        return mTargetSdk;
    }

    @Override
    @DataClass.Generated.Member
    public boolean equals(@Nullable Object o) {
        // You can override field equality logic by defining either of the methods like:
        // boolean fieldNameEquals(SplitPermissionInfoParcelable other) { ... }
        // boolean fieldNameEquals(FieldType otherValue) { ... }

        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        @SuppressWarnings("unchecked")
        SplitPermissionInfoParcelable that = (SplitPermissionInfoParcelable) o;
        //noinspection PointlessBooleanExpression
        return true
                && Objects.equals(mSplitPermission, that.mSplitPermission)
                && Objects.equals(mNewPermissions, that.mNewPermissions)
                && mTargetSdk == that.mTargetSdk;
    }

    @Override
    @DataClass.Generated.Member
    public int hashCode() {
        // You can override field hashCode logic by defining methods like:
        // int fieldNameHashCode() { ... }

        int _hash = 1;
        _hash = 31 * _hash + Objects.hashCode(mSplitPermission);
        _hash = 31 * _hash + Objects.hashCode(mNewPermissions);
        _hash = 31 * _hash + mTargetSdk;
        return _hash;
    }

    @Override
    @DataClass.Generated.Member
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        // You can override field parcelling by defining methods like:
        // void parcelFieldName(Parcel dest, int flags) { ... }

        dest.writeString(mSplitPermission);
        dest.writeStringList(mNewPermissions);
        dest.writeInt(mTargetSdk);
    }

    @Override
    @DataClass.Generated.Member
    public int describeContents() { return 0; }

    /** @hide */
    @SuppressWarnings({"unchecked", "RedundantCast"})
    @DataClass.Generated.Member
    protected SplitPermissionInfoParcelable(@NonNull Parcel in) {
        // You can override field unparcelling by defining methods like:
        // static FieldType unparcelFieldName(Parcel in) { ... }

        String splitPermission = in.readString();
        List<String> newPermissions = new java.util.ArrayList<>();
        in.readStringList(newPermissions);
        int targetSdk = in.readInt();

        this.mSplitPermission = splitPermission;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mSplitPermission);
        this.mNewPermissions = newPermissions;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mNewPermissions);
        this.mTargetSdk = targetSdk;
        com.android.internal.util.AnnotationValidations.validate(
                IntRange.class, null, mTargetSdk,
                "from", 0);

        onConstructed();
    }

    @DataClass.Generated.Member
    public static final @NonNull Parcelable.Creator<SplitPermissionInfoParcelable> CREATOR
            = new Parcelable.Creator<SplitPermissionInfoParcelable>() {
        @Override
        public SplitPermissionInfoParcelable[] newArray(int size) {
            return new SplitPermissionInfoParcelable[size];
        }

        @Override
        public SplitPermissionInfoParcelable createFromParcel(@NonNull Parcel in) {
            return new SplitPermissionInfoParcelable(in);
        }
    };

    @DataClass.Generated(
            time = 1604456266666L,
            codegenVersion = "1.0.20",
            sourceFile = "frameworks/base/core/java/android/content/pm/permission/SplitPermissionInfoParcelable.java",
            inputSignatures = "private final @android.annotation.NonNull java.lang.String mSplitPermission\nprivate final @android.annotation.NonNull java.util.List<java.lang.String> mNewPermissions\nprivate final @android.annotation.IntRange int mTargetSdk\nprivate  void onConstructed()\nclass SplitPermissionInfoParcelable extends java.lang.Object implements [android.os.Parcelable]\n@com.android.internal.util.DataClass(genEqualsHashCode=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
