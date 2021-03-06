/*
 * Copyright (C) 2020 The Android Open Source Project
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

package android.view;

import static android.view.MotionEvent.FLAG_IS_ACCESSIBILITY_EVENT;
import static android.view.MotionEvent.FLAG_WINDOW_IS_OBSCURED;
import static android.view.MotionEvent.FLAG_WINDOW_IS_PARTIALLY_OBSCURED;

import static java.lang.annotation.RetentionPolicy.SOURCE;

import android.annotation.IntDef;
import android.annotation.Nullable;
import android.annotation.SuppressLint;
import android.os.Parcel;
import android.os.Parcelable;

import com.android.internal.util.DataClass;

import java.lang.annotation.Retention;

/**
 * MotionEvent that has been verified by the system.
 * The data contained in this class is always a subset of a {@link MotionEvent}. Use this class to
 * check which data has been confirmed by the system to be authentic.
 *
 * Most applications do not need to use this class.
 *
 * {@see android.hardware.input.InputManager#verifyInputEvent}
 */
@DataClass(genHiddenConstructor = true, genEqualsHashCode = true)
public final class VerifiedMotionEvent extends VerifiedInputEvent implements Parcelable {
    private static final String TAG = "VerifiedMotionEvent";

    /**
     * The raw X coordinate of the primary pointer.
     * @see MotionEvent#getRawX()
     */
    private float mRawX;

    /**
     * The raw Y coordinate of the primary pointer.
     * @see MotionEvent#getRawY()
     */
    private float mRawY;

    /** @hide */
    @Retention(SOURCE)
    @IntDef({MotionEvent.ACTION_DOWN, MotionEvent.ACTION_POINTER_DOWN, MotionEvent.ACTION_CANCEL,
            MotionEvent.ACTION_POINTER_UP, MotionEvent.ACTION_UP})
    public @interface MotionEventAction {};

    /**
     * The masked action being performed, without pointer index information.
     *
     * @see MotionEvent#getActionMasked()
     */
    @MotionEventAction
    private int mActionMasked;

    /**
     * The time that the gesture started, in nanoseconds.
     * Uses the same time base as {@link android.os.SystemClock#uptimeMillis()}
     *
     * @see MotionEvent#getDownTime()
     */
    @SuppressLint({"MethodNameUnits"})
    private long mDownTimeNanos;

    /**
     * Returns the flags for this motion event.
     *
     * @see MotionEvent#getFlags()
     * @see MotionEvent#FLAG_IS_ACCESSIBILITY_EVENT
     * @see MotionEvent#FLAG_WINDOW_IS_OBSCURED
     * @see MotionEvent#FLAG_WINDOW_IS_PARTIALLY_OBSCURED
     * @hide
     */
    private int mFlags;

    /**
     * The state of any meta / modifier keys that were in effect when the event was generated.
     *
     * @see MotionEvent#getMetaState()
     */
    private int mMetaState;

    /**
     *  The state of all buttons that are pressed such as a mouse or stylus button.
     *
     * @see MotionEvent#getButtonState()
     */
    private int mButtonState;

    /**
     * Get a specific flag of this motion event, if possible. Return null if the flag value could
     * not be checked.
     *
     * @param flag the flag of interest
     * @return Boolean(true) if the motion event has the requested flag
     *         Boolean(false) if the motion event does not have the requested flag
     *         null if the flag value could not be checked
     *
     * @see MotionEvent#FLAG_WINDOW_IS_OBSCURED
     * @see MotionEvent#FLAG_WINDOW_IS_PARTIALLY_OBSCURED
     */
    public @Nullable Boolean getFlag(int flag) {
        switch(flag) {
            // InputDispatcher only verifies a subset of the MotionEvent flags.
            // These values must be kept in sync with Input.cpp
            case FLAG_IS_ACCESSIBILITY_EVENT:
            case FLAG_WINDOW_IS_OBSCURED:
            case FLAG_WINDOW_IS_PARTIALLY_OBSCURED:
                return (mFlags & flag) != 0;
        }
        return null;
    }

    // The codegen tool doesn't fully support subclasses, since it works on a per-file basis.
    // To modify this file:
    // 1. run codegen on this file
    // 2. edit the constructor signature
    // 3. add the "super" call for constructor that receives a Parcel
    // 4. add the "super" call to the writeToParcel method
    // 5. Update "equals" and "hashcode" methods to include VerifiedInputEvent fields



    // Code below generated by codegen v1.0.20.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/view/VerifiedMotionEvent.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    /**
     * Creates a new VerifiedMotionEvent.
     *
     * @param rawX
     *   The raw X coordinate of the primary pointer.
     * @param rawY
     *   The raw Y coordinate of the primary pointer.
     * @param actionMasked
     *   The masked action being performed, without pointer index information.
     * @param downTimeNanos
     *   The time that the gesture started, in nanoseconds.
     *   Uses the same time base as {@link android.os.SystemClock#uptimeMillis()}
     * @param flags
     *   Returns the flags for this motion event.
     * @param metaState
     *   The state of any meta / modifier keys that were in effect when the event was generated.
     * @param buttonState
     *    The state of all buttons that are pressed such as a mouse or stylus button.
     * @hide
     */
    @DataClass.Generated.Member
    public VerifiedMotionEvent(
            int deviceId, long eventTimeNanos, int source, int displayId,
            float rawX,
            float rawY,
            @MotionEventAction int actionMasked,
            @SuppressLint({ "MethodNameUnits" }) long downTimeNanos,
            int flags,
            int metaState,
            int buttonState) {
        super(VERIFIED_MOTION, deviceId, eventTimeNanos, source, displayId);
        this.mRawX = rawX;
        this.mRawY = rawY;
        this.mActionMasked = actionMasked;
        com.android.internal.util.AnnotationValidations.validate(
                MotionEventAction.class, null, mActionMasked);
        this.mDownTimeNanos = downTimeNanos;
        this.mFlags = flags;
        this.mMetaState = metaState;
        this.mButtonState = buttonState;

        // onConstructed(); // You can define this method to get a callback
    }

    /**
     * The raw X coordinate of the primary pointer.
     *
     * @see MotionEvent#getRawX()
     */
    @DataClass.Generated.Member
    public float getRawX() {
        return mRawX;
    }

    /**
     * The raw Y coordinate of the primary pointer.
     *
     * @see MotionEvent#getRawY()
     */
    @DataClass.Generated.Member
    public float getRawY() {
        return mRawY;
    }

    /**
     * The masked action being performed, without pointer index information.
     *
     * @see MotionEvent#getActionMasked()
     */
    @DataClass.Generated.Member
    public @MotionEventAction int getActionMasked() {
        return mActionMasked;
    }

    /**
     * The time that the gesture started, in nanoseconds.
     * Uses the same time base as {@link android.os.SystemClock#uptimeMillis()}
     *
     * @see MotionEvent#getDownTime()
     */
    @DataClass.Generated.Member
    public @SuppressLint({ "MethodNameUnits" }) long getDownTimeNanos() {
        return mDownTimeNanos;
    }

    /**
     * Returns the flags for this motion event.
     *
     * @see MotionEvent#getFlags()
     * @hide
     */
    @DataClass.Generated.Member
    public int getFlags() {
        return mFlags;
    }

    /**
     * The state of any meta / modifier keys that were in effect when the event was generated.
     *
     * @see MotionEvent#getMetaState()
     */
    @DataClass.Generated.Member
    public int getMetaState() {
        return mMetaState;
    }

    /**
     *  The state of all buttons that are pressed such as a mouse or stylus button.
     *
     * @see MotionEvent#getButtonState()
     */
    @DataClass.Generated.Member
    public int getButtonState() {
        return mButtonState;
    }

    @Override
    @DataClass.Generated.Member
    public boolean equals(@Nullable Object o) {
        // You can override field equality logic by defining either of the methods like:
        // boolean fieldNameEquals(VerifiedMotionEvent other) { ... }
        // boolean fieldNameEquals(FieldType otherValue) { ... }

        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        @SuppressWarnings("unchecked")
        VerifiedMotionEvent that = (VerifiedMotionEvent) o;
        //noinspection PointlessBooleanExpression
        return true
                && super.equals(that)
                && mRawX == that.mRawX
                && mRawY == that.mRawY
                && mActionMasked == that.mActionMasked
                && mDownTimeNanos == that.mDownTimeNanos
                && mFlags == that.mFlags
                && mMetaState == that.mMetaState
                && mButtonState == that.mButtonState;
    }

    @Override
    @DataClass.Generated.Member
    public int hashCode() {
        // You can override field hashCode logic by defining methods like:
        // int fieldNameHashCode() { ... }

        int _hash = 1;
        _hash = 31 * _hash + super.hashCode();
        _hash = 31 * _hash + Float.hashCode(mRawX);
        _hash = 31 * _hash + Float.hashCode(mRawY);
        _hash = 31 * _hash + mActionMasked;
        _hash = 31 * _hash + Long.hashCode(mDownTimeNanos);
        _hash = 31 * _hash + mFlags;
        _hash = 31 * _hash + mMetaState;
        _hash = 31 * _hash + mButtonState;
        return _hash;
    }

    @Override
    @DataClass.Generated.Member
    public void writeToParcel(@android.annotation.NonNull Parcel dest, int flags) {
        // You can override field parcelling by defining methods like:
        // void parcelFieldName(Parcel dest, int flags) { ... }
        super.writeToParcel(dest, flags);

        dest.writeFloat(mRawX);
        dest.writeFloat(mRawY);
        dest.writeInt(mActionMasked);
        dest.writeLong(mDownTimeNanos);
        dest.writeInt(mFlags);
        dest.writeInt(mMetaState);
        dest.writeInt(mButtonState);
    }

    @Override
    @DataClass.Generated.Member
    public int describeContents() { return 0; }

    /** @hide */
    @SuppressWarnings({"unchecked", "RedundantCast"})
    @DataClass.Generated.Member
    /* package-private */ VerifiedMotionEvent(@android.annotation.NonNull Parcel in) {
        // You can override field unparcelling by defining methods like:
        // static FieldType unparcelFieldName(Parcel in) { ... }
        super(in, VERIFIED_MOTION);

        float rawX = in.readFloat();
        float rawY = in.readFloat();
        int actionMasked = in.readInt();
        long downTimeNanos = in.readLong();
        int flags = in.readInt();
        int metaState = in.readInt();
        int buttonState = in.readInt();

        this.mRawX = rawX;
        this.mRawY = rawY;
        this.mActionMasked = actionMasked;
        com.android.internal.util.AnnotationValidations.validate(
                MotionEventAction.class, null, mActionMasked);
        this.mDownTimeNanos = downTimeNanos;
        this.mFlags = flags;
        this.mMetaState = metaState;
        this.mButtonState = buttonState;

        // onConstructed(); // You can define this method to get a callback
    }

    @DataClass.Generated.Member
    public static final @android.annotation.NonNull Parcelable.Creator<VerifiedMotionEvent> CREATOR
            = new Parcelable.Creator<VerifiedMotionEvent>() {
        @Override
        public VerifiedMotionEvent[] newArray(int size) {
            return new VerifiedMotionEvent[size];
        }

        @Override
        public VerifiedMotionEvent createFromParcel(@android.annotation.NonNull Parcel in) {
            return new VerifiedMotionEvent(in);
        }
    };

    @DataClass.Generated(
            time = 1604509199368L,
            codegenVersion = "1.0.20",
            sourceFile = "frameworks/base/core/java/android/view/VerifiedMotionEvent.java",
            inputSignatures = "private static final  java.lang.String TAG\nprivate  float mRawX\nprivate  float mRawY\nprivate @android.view.VerifiedMotionEvent.MotionEventAction int mActionMasked\nprivate @android.annotation.SuppressLint long mDownTimeNanos\nprivate  int mFlags\nprivate  int mMetaState\nprivate  int mButtonState\npublic @android.annotation.Nullable java.lang.Boolean getFlag(int)\nclass VerifiedMotionEvent extends android.view.VerifiedInputEvent implements [android.os.Parcelable]\n@com.android.internal.util.DataClass(genHiddenConstructor=true, genEqualsHashCode=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
