/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the
 * License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
package com.android.settings.enterprise;

import android.content.Context;
import android.net.ConnectivityManager;

import com.android.settings.core.PreferenceControllerMixin;
import com.android.settingslib.core.AbstractPreferenceController;

public class GlobalHttpProxyPreferenceController extends AbstractPreferenceController implements
        PreferenceControllerMixin {

    private static final String KEY_GLOBAL_HTTP_PROXY = "global_http_proxy";
    private final ConnectivityManager mCm;

    public GlobalHttpProxyPreferenceController(Context context) {
        super(context);
        mCm = context.getSystemService(ConnectivityManager.class);
    }

    @Override
    public boolean isAvailable() {
        return mCm.getGlobalProxy() != null;
    }

    @Override
    public String getPreferenceKey() {
        return KEY_GLOBAL_HTTP_PROXY;
    }
}
