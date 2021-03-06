/*
 * Copyright (C) 2011 The Android Open Source Project
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

package com.android.settings.deviceinfo;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ProgressBar;

import androidx.preference.Preference;
import androidx.preference.PreferenceViewHolder;

import com.android.settings.R;
import com.android.settings.deviceinfo.storage.StorageUtils;

public class StorageItemPreference extends Preference {
    public int userHandle;

    private static final int UNINITIALIZED = -1;

    private ProgressBar mProgressBar;
    private static final int PROGRESS_MAX = 100;
    private int mProgressPercent = UNINITIALIZED;
    private long mStorageSize;

    public StorageItemPreference(Context context) {
        this(context, null);
    }

    public StorageItemPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
        setLayoutResource(R.layout.storage_item);
    }

    public void setStorageSize(long size, long total) {
        mStorageSize = size;
        setSummary(StorageUtils.getStorageSizeLabel(getContext(), size));

        if (total == 0) {
            mProgressPercent = 0;
        } else {
            mProgressPercent = (int)(size * PROGRESS_MAX / total);
        }
        updateProgressBar();
    }

    public long getStorageSize() {
        return mStorageSize;
    }

    protected void updateProgressBar() {
        if (mProgressBar == null || mProgressPercent == UNINITIALIZED)
            return;

        mProgressBar.setMax(PROGRESS_MAX);
        mProgressBar.setProgress(mProgressPercent);
    }

    @Override
    public void onBindViewHolder(PreferenceViewHolder view) {
        mProgressBar = (ProgressBar) view.findViewById(android.R.id.progress);
        updateProgressBar();
        super.onBindViewHolder(view);
    }
}
