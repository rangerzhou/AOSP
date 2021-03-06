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

package android.content;

import android.database.Cursor;
import android.net.Uri;

/**
 * A placeholder content provider for tests.  This provider runs in a different process from the test.
 */
public class FakeProviderRemote extends ContentProvider {

    @Override
    public boolean onCreate() {
        return true;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs,
            String sortOrder) {
        return null;
    }

    @Override
    public String getType(Uri uri) {
        if (uri.getPath() != null && uri.getPath().contains("error")) {
            throw new IllegalArgumentException("Expected exception");
        }
        return "fake/remote";
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        return null;
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        return 0;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        return 0;
    }

    @Override
    public Uri canonicalize(Uri uri) {
        if (uri.getPath() != null && uri.getPath().contains("error")) {
            throw new IllegalArgumentException("Expected exception");
        }
        return new Uri.Builder().scheme(uri.getScheme()).authority(uri.getAuthority())
                .appendPath("canonical").build();
    }

    @Override
    public Uri uncanonicalize(Uri uri) {
        if (uri.getPath() != null && uri.getPath().contains("error")) {
            throw new IllegalArgumentException("Expected exception");
        }
        return new Uri.Builder().scheme(uri.getScheme()).authority(uri.getAuthority())
                .appendPath("uncanonical").build();
    }
}
