/*
 * Copyright (C) 2019 The Android Open Source Project
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

package com.android.settingslib.drawer;

import android.os.Bundle;

/**
 * A controller that manages event for Primary switch.
 */
public abstract class PrimarySwitchController extends SwitchController {

    @Override
    protected final MetaData getMetaData() {
        throw new UnsupportedOperationException();
    }

    @Override
    final Bundle getBundle() {
        throw new UnsupportedOperationException();
    }
}
