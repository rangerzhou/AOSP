/*
* Copyright (C) 2016 The Android Open Source Project
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

package com.android.rs.jnikernelvariables;

import android.app.Activity;
import android.os.Bundle;
import android.graphics.BitmapFactory;
import android.graphics.Bitmap;
import android.widget.ImageView;

public class MainActivity extends Activity {
    private Bitmap mBitmapIn;
    private Bitmap mBitmapOut;

    static {
        System.loadLibrary("RS");
        System.loadLibrary("jnikernelvariables");
    }

    native void nativeRS(String cacheDir);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_layout);
        nativeRS(this.getCacheDir().toString());
    }
}
