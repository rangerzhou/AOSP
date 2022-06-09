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

package android.service.voice;

import android.annotation.NonNull;
import android.annotation.Nullable;
import android.annotation.TestApi;
import android.os.CancellationSignal;
import android.os.IBinder;
import android.os.Parcel;
import android.os.Parcelable;

import com.android.internal.util.DataClass;

import java.util.Objects;
import java.util.concurrent.Executor;
import java.util.function.Consumer;

/**
 * The class is used to represent a visible activity information. The system provides this to
 * services that need to know {@link android.service.voice.VoiceInteractionSession.ActivityId}.
 */
@DataClass(
        genConstructor = false,
        genEqualsHashCode = true,
        genHiddenConstDefs = false,
        genGetters = false,
        genToString = true
)
public final class VisibleActivityInfo implements Parcelable {

    /**
     * Indicates that it is a new visible activity.
     *
     * @hide
     */
    public static final int TYPE_ACTIVITY_ADDED = 1;

    /**
     * Indicates that it has become a invisible activity.
     *
     * @hide
     */
    public static final int TYPE_ACTIVITY_REMOVED = 2;

    /**
     * The identifier of the task this activity is in.
     */
    private final int mTaskId;

    /**
     * Token for targeting this activity for assist purposes.
     */
    @NonNull
    private final IBinder mAssistToken;

    /** @hide */
    @TestApi
    public VisibleActivityInfo(
            int taskId,
            @NonNull IBinder assistToken) {
        Objects.requireNonNull(assistToken);
        mTaskId = taskId;
        mAssistToken = assistToken;
    }

    /**
     * Returns the {@link android.service.voice.VoiceInteractionSession.ActivityId} of this
     * visible activity which can be used to interact with an activity, for example through
     * {@link VoiceInteractionSession#requestDirectActions(VoiceInteractionSession.ActivityId,
     * CancellationSignal, Executor, Consumer)}.
     */
    public @NonNull VoiceInteractionSession.ActivityId getActivityId() {
        return new VoiceInteractionSession.ActivityId(mTaskId, mAssistToken);
    }



    // Code below generated by codegen v1.0.23.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/service/voice/VisibleActivityInfo.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    @Override
    @DataClass.Generated.Member
    public String toString() {
        // You can override field toString logic by defining methods like:
        // String fieldNameToString() { ... }

        return "VisibleActivityInfo { " +
                "taskId = " + mTaskId + ", " +
                "assistToken = " + mAssistToken +
        " }";
    }

    @Override
    @DataClass.Generated.Member
    public boolean equals(@Nullable Object o) {
        // You can override field equality logic by defining either of the methods like:
        // boolean fieldNameEquals(VisibleActivityInfo other) { ... }
        // boolean fieldNameEquals(FieldType otherValue) { ... }

        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        @SuppressWarnings("unchecked")
        VisibleActivityInfo that = (VisibleActivityInfo) o;
        //noinspection PointlessBooleanExpression
        return true
                && mTaskId == that.mTaskId
                && Objects.equals(mAssistToken, that.mAssistToken);
    }

    @Override
    @DataClass.Generated.Member
    public int hashCode() {
        // You can override field hashCode logic by defining methods like:
        // int fieldNameHashCode() { ... }

        int _hash = 1;
        _hash = 31 * _hash + mTaskId;
        _hash = 31 * _hash + Objects.hashCode(mAssistToken);
        return _hash;
    }

    @Override
    @DataClass.Generated.Member
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        // You can override field parcelling by defining methods like:
        // void parcelFieldName(Parcel dest, int flags) { ... }

        dest.writeInt(mTaskId);
        dest.writeStrongBinder(mAssistToken);
    }

    @Override
    @DataClass.Generated.Member
    public int describeContents() { return 0; }

    /** @hide */
    @SuppressWarnings({"unchecked", "RedundantCast"})
    @DataClass.Generated.Member
    /* package-private */ VisibleActivityInfo(@NonNull Parcel in) {
        // You can override field unparcelling by defining methods like:
        // static FieldType unparcelFieldName(Parcel in) { ... }

        int taskId = in.readInt();
        IBinder assistToken = (IBinder) in.readStrongBinder();

        this.mTaskId = taskId;
        this.mAssistToken = assistToken;
        com.android.internal.util.AnnotationValidations.validate(
                NonNull.class, null, mAssistToken);

        // onConstructed(); // You can define this method to get a callback
    }

    @DataClass.Generated.Member
    public static final @NonNull Parcelable.Creator<VisibleActivityInfo> CREATOR
            = new Parcelable.Creator<VisibleActivityInfo>() {
        @Override
        public VisibleActivityInfo[] newArray(int size) {
            return new VisibleActivityInfo[size];
        }

        @Override
        public VisibleActivityInfo createFromParcel(@NonNull Parcel in) {
            return new VisibleActivityInfo(in);
        }
    };

    @DataClass.Generated(
            time = 1632383555284L,
            codegenVersion = "1.0.23",
            sourceFile = "frameworks/base/core/java/android/service/voice/VisibleActivityInfo.java",
            inputSignatures = "public static final  int TYPE_ACTIVITY_ADDED\npublic static final  int TYPE_ACTIVITY_REMOVED\nprivate final  int mTaskId\nprivate final @android.annotation.NonNull android.os.IBinder mAssistToken\npublic @android.annotation.NonNull android.service.voice.VoiceInteractionSession.ActivityId getActivityId()\nclass VisibleActivityInfo extends java.lang.Object implements [android.os.Parcelable]\n@com.android.internal.util.DataClass(genConstructor=false, genEqualsHashCode=true, genHiddenConstDefs=false, genGetters=false, genToString=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
