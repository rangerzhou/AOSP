/*
 * Copyright (C) 2017 The Android Open Source Project
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

package com.android.settings.notification.app;

import static android.app.NotificationManager.IMPORTANCE_LOW;
import static android.app.NotificationManager.IMPORTANCE_MIN;

import android.app.NotificationChannel;
import android.content.Context;

import com.android.settings.core.PreferenceControllerMixin;
import com.android.settings.notification.NotificationBackend;
import com.android.settingslib.RestrictedSwitchPreference;

import androidx.preference.Preference;

public class MinImportancePreferenceController extends NotificationPreferenceController
        implements PreferenceControllerMixin, Preference.OnPreferenceChangeListener  {

    private static final String KEY_IMPORTANCE = "min_importance";
    private NotificationSettings.DependentFieldListener mDependentFieldListener;

    public MinImportancePreferenceController(Context context,
            NotificationSettings.DependentFieldListener dependentFieldListener,
            NotificationBackend backend) {
        super(context, backend);
        mDependentFieldListener = dependentFieldListener;
    }

    @Override
    public String getPreferenceKey() {
        return KEY_IMPORTANCE;
    }

    @Override
    public boolean isAvailable() {
        if (!super.isAvailable()) {
            return false;
        }
        if (mChannel == null) {
            return false;
        }
        if (isDefaultChannel()) {
            return false;
        }
        return mChannel.getImportance() <= IMPORTANCE_LOW;
    }

    @Override
    boolean isIncludedInFilter() {
        return mPreferenceFilter.contains(NotificationChannel.EDIT_IMPORTANCE);
    }

    @Override
    public void updateState(Preference preference) {
        if (mAppRow != null && mChannel != null) {
            preference.setEnabled(mAdmin == null && !mChannel.isImportanceLockedByOEM());

            RestrictedSwitchPreference pref = (RestrictedSwitchPreference) preference;
            pref.setChecked(mChannel.getImportance() == IMPORTANCE_MIN);
        }
    }

    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) {
        if (mChannel != null) {
            final boolean checked = (boolean) newValue;

            mChannel.setImportance(checked ? IMPORTANCE_MIN : IMPORTANCE_LOW);
            mChannel.lockFields(NotificationChannel.USER_LOCKED_IMPORTANCE);
            saveChannel();
            mDependentFieldListener.onFieldValueChanged();
        }
        return true;
    }
}
