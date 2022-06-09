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
package com.android.launcher3;

import static android.content.Intent.EXTRA_COMPONENT_NAME;
import static android.content.Intent.EXTRA_USER;

import android.annotation.TargetApi;
import android.content.ComponentName;
import android.content.Intent;
import android.graphics.RectF;
import android.os.Build;
import android.os.Bundle;
import android.os.Message;
import android.os.RemoteException;
import android.os.UserHandle;
import android.util.Log;
import android.view.SurfaceControl;

import androidx.annotation.Nullable;

/**
 * Class to encapsulate the handshake protocol between Launcher and gestureNav.
 */
public class GestureNavContract {

    private static final String TAG = "GestureNavContract";

    public static final String EXTRA_GESTURE_CONTRACT = "gesture_nav_contract_v1";
    public static final String EXTRA_ICON_POSITION = "gesture_nav_contract_icon_position";
    public static final String EXTRA_ICON_SURFACE = "gesture_nav_contract_surface_control";
    public static final String EXTRA_REMOTE_CALLBACK = "android.intent.extra.REMOTE_CALLBACK";

    public final ComponentName componentName;
    public final UserHandle user;

    private final Message mCallback;

    public GestureNavContract(ComponentName componentName, UserHandle user, Message callback) {
        this.componentName = componentName;
        this.user = user;
        this.mCallback = callback;
    }

    /**
     * Sends the position information to the receiver
     */
    @TargetApi(Build.VERSION_CODES.R)
    public void sendEndPosition(RectF position, @Nullable SurfaceControl surfaceControl) {
        Bundle result = new Bundle();
        result.putParcelable(EXTRA_ICON_POSITION, position);
        result.putParcelable(EXTRA_ICON_SURFACE, surfaceControl);

        Message callback = Message.obtain();
        callback.copyFrom(mCallback);
        callback.setData(result);

        try {
            callback.replyTo.send(callback);
        } catch (RemoteException e) {
            Log.e(TAG, "Error sending icon position", e);
        }
    }

    /**
     * Clears and returns the GestureNavContract if it was present in the intent.
     */
    public static GestureNavContract fromIntent(Intent intent) {
        if (!Utilities.ATLEAST_R) {
            return null;
        }
        Bundle extras = intent.getBundleExtra(EXTRA_GESTURE_CONTRACT);
        if (extras == null) {
            return null;
        }
        intent.removeExtra(EXTRA_GESTURE_CONTRACT);

        ComponentName componentName = extras.getParcelable(EXTRA_COMPONENT_NAME);
        UserHandle userHandle = extras.getParcelable(EXTRA_USER);
        Message callback = extras.getParcelable(EXTRA_REMOTE_CALLBACK);

        if (componentName != null && userHandle != null && callback != null
                && callback.replyTo != null) {
            return new GestureNavContract(componentName, userHandle, callback);
        }
        return null;
    }
}
