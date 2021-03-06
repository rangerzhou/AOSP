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

package android.service.rotationresolver;

import android.annotation.DurationMillisLong;
import android.annotation.NonNull;
import android.annotation.SystemApi;
import android.os.Parcel;
import android.os.Parcelable;
import android.view.Surface;

import com.android.internal.util.DataClass;

/**
 * This class represents a request to an {@link RotationResolverService}. The request contains
 * information from the system that can help RotationResolverService to determine the appropriate
 * screen rotation.
 *
 * @see RotationResolverService#resolveRotation(IRotationResolverCallback,
 * RotationResolutionRequest, ICancellationSignal)
 *
 * @hide
 */
@SystemApi
@DataClass (
        genParcelable = true,
        genToString = true
)
public final class RotationResolutionRequest implements Parcelable {
    /** The Name of the package of the current fore-ground activity. */
    @NonNull private final String mForegroundPackageName;

    /** The current rotation of the screen. */
    @Surface.Rotation private final int mCurrentRotation;

    /** The proposed screen rotation in the system. */
    @Surface.Rotation private final int mProposedRotation;

    /** Whether should use the camera sensor to resolve screen rotation. */
    private final boolean mShouldUseCamera;

    /** The timeout of the request. */
    @DurationMillisLong private final long mTimeoutMillis;




    // Code below generated by codegen v1.0.23.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/service/rotationresolver/RotationResolutionRequest.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    /**
     * Creates a new RotationResolutionRequest.
     *
     * @param foregroundPackageName
     *   The Name of the package of the current fore-ground activity.
     * @param currentRotation
     *   The current rotation of the screen.
     * @param proposedRotation
     *   The proposed screen rotation in the system.
     * @param shouldUseCamera
     *   Whether should use the camera sensor to resolve screen rotation.
     * @param timeoutMillis
     *   The timeout of the request.
     */
    @DataClass.Generated.Member
    public RotationResolutionRequest(
            @NonNull String foregroundPackageName,
            @Surface.Rotation int currentRotation,
            @Surface.Rotation int proposedRotation,
            boolean shouldUseCamera,
            @DurationMillisLong long timeoutMillis) {
        this.mForegroundPackageName = foregroundPackageName;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mForegroundPackageName);
        this.mCurrentRotation = currentRotation;
        com.android.internal.util.AnnotationValidations.validate(
                Surface.Rotation.class, null, mCurrentRotation);
        this.mProposedRotation = proposedRotation;
        com.android.internal.util.AnnotationValidations.validate(
                Surface.Rotation.class, null, mProposedRotation);
        this.mShouldUseCamera = shouldUseCamera;
        this.mTimeoutMillis = timeoutMillis;
        com.android.internal.util.AnnotationValidations.validate(
                DurationMillisLong.class, null, mTimeoutMillis);

        // onConstructed(); // You can define this method to get a callback
    }

    /**
     * The Name of the package of the current fore-ground activity.
     */
    @DataClass.Generated.Member
    public @NonNull String getForegroundPackageName() {
        return mForegroundPackageName;
    }

    /**
     * The current rotation of the screen.
     */
    @DataClass.Generated.Member
    public @Surface.Rotation int getCurrentRotation() {
        return mCurrentRotation;
    }

    /**
     * The proposed screen rotation in the system.
     */
    @DataClass.Generated.Member
    public @Surface.Rotation int getProposedRotation() {
        return mProposedRotation;
    }

    /**
     * Whether should use the camera sensor to resolve screen rotation.
     */
    @DataClass.Generated.Member
    public boolean shouldUseCamera() {
        return mShouldUseCamera;
    }

    /**
     * The timeout of the request.
     */
    @DataClass.Generated.Member
    public @DurationMillisLong long getTimeoutMillis() {
        return mTimeoutMillis;
    }

    @Override
    @DataClass.Generated.Member
    public String toString() {
        // You can override field toString logic by defining methods like:
        // String fieldNameToString() { ... }

        return "RotationResolutionRequest { " +
                "foregroundPackageName = " + mForegroundPackageName + ", " +
                "currentRotation = " + mCurrentRotation + ", " +
                "proposedRotation = " + mProposedRotation + ", " +
                "shouldUseCamera = " + mShouldUseCamera + ", " +
                "timeoutMillis = " + mTimeoutMillis +
        " }";
    }

    @Override
    @DataClass.Generated.Member
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        // You can override field parcelling by defining methods like:
        // void parcelFieldName(Parcel dest, int flags) { ... }

        byte flg = 0;
        if (mShouldUseCamera) flg |= 0x8;
        dest.writeByte(flg);
        dest.writeString(mForegroundPackageName);
        dest.writeInt(mCurrentRotation);
        dest.writeInt(mProposedRotation);
        dest.writeLong(mTimeoutMillis);
    }

    @Override
    @DataClass.Generated.Member
    public int describeContents() { return 0; }

    /** @hide */
    @SuppressWarnings({"unchecked", "RedundantCast"})
    @DataClass.Generated.Member
    /* package-private */ RotationResolutionRequest(@NonNull Parcel in) {
        // You can override field unparcelling by defining methods like:
        // static FieldType unparcelFieldName(Parcel in) { ... }

        byte flg = in.readByte();
        boolean shouldUseCamera = (flg & 0x8) != 0;
        String foregroundPackageName = in.readString();
        int currentRotation = in.readInt();
        int proposedRotation = in.readInt();
        long timeoutMillis = in.readLong();

        this.mForegroundPackageName = foregroundPackageName;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mForegroundPackageName);
        this.mCurrentRotation = currentRotation;
        com.android.internal.util.AnnotationValidations.validate(
                Surface.Rotation.class, null, mCurrentRotation);
        this.mProposedRotation = proposedRotation;
        com.android.internal.util.AnnotationValidations.validate(
                Surface.Rotation.class, null, mProposedRotation);
        this.mShouldUseCamera = shouldUseCamera;
        this.mTimeoutMillis = timeoutMillis;
        com.android.internal.util.AnnotationValidations.validate(
                DurationMillisLong.class, null, mTimeoutMillis);

        // onConstructed(); // You can define this method to get a callback
    }

    @DataClass.Generated.Member
    public static final @NonNull Parcelable.Creator<RotationResolutionRequest> CREATOR
            = new Parcelable.Creator<RotationResolutionRequest>() {
        @Override
        public RotationResolutionRequest[] newArray(int size) {
            return new RotationResolutionRequest[size];
        }

        @Override
        public RotationResolutionRequest createFromParcel(@NonNull Parcel in) {
            return new RotationResolutionRequest(in);
        }
    };

    @DataClass.Generated(
            time = 1618447759819L,
            codegenVersion = "1.0.23",
            sourceFile = "frameworks/base/core/java/android/service/rotationresolver/RotationResolutionRequest.java",
            inputSignatures = "private final @android.annotation.NonNull java.lang.String mForegroundPackageName\nprivate final @android.view.Surface.Rotation int mCurrentRotation\nprivate final @android.view.Surface.Rotation int mProposedRotation\nprivate final  boolean mShouldUseCamera\nprivate final @android.annotation.DurationMillisLong long mTimeoutMillis\nclass RotationResolutionRequest extends java.lang.Object implements [android.os.Parcelable]\n@com.android.internal.util.DataClass(genParcelable=true, genToString=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
