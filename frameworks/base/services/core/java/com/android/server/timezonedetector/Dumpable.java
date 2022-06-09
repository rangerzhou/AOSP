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
package com.android.server.timezonedetector;

import android.annotation.NonNull;
import android.annotation.Nullable;
import android.util.IndentingPrintWriter;

/** An interface for components that can write their internal state to dumpsys logs. */
public interface Dumpable {

    /** Dump internal state. */
    void dump(@NonNull IndentingPrintWriter pw, @Nullable String[] args);

    /**
     * An interface that can be used expose when one component allows another to be registered so
     * that it is dumped at the same time.
     */
    interface Container {

        /**
         * Registers the supplied {@link Dumpable}. When the implementation is dumped
         * {@link Dumpable#dump(IndentingPrintWriter, String[])} should be called on the
         * {@code dumpable}.
         */
        void addDumpable(@NonNull Dumpable dumpable);
    }
}
