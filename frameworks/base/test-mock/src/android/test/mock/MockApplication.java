/*
 * Copyright (C) 2008 The Android Open Source Project
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

package android.test.mock;

import android.app.Application;
import android.content.res.Configuration;

/**
 * A mock {@link android.app.Application} class.  All methods are non-functional and throw
 * {@link java.lang.UnsupportedOperationException}.  Override it as necessary to provide the
 * operations that you need.
 *
 * @deprecated Use a mocking framework like <a href="https://github.com/mockito/mockito">Mockito</a>.
 * New tests should be written using the
 * <a href="{@docRoot}tools/testing-support-library/index.html">Android Testing Support Library</a>.
 */
@Deprecated
public class MockApplication extends Application {

    public MockApplication() {
    }

    @Override
    public void onCreate() {
        throw new UnsupportedOperationException();
    }

    @Override
    public void onTerminate() {
        throw new UnsupportedOperationException();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        throw new UnsupportedOperationException();
    }
}
