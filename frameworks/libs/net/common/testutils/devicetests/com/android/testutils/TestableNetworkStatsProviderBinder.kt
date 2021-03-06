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

package com.android.testutils

import com.android.net.module.util.ArrayTrackRecord
import kotlin.test.assertEquals
import kotlin.test.fail

private const val DEFAULT_TIMEOUT_MS = 200L

open class TestableNetworkStatsProviderBinder : NetworkStatsProviderStubCompat() {
    sealed class CallbackType {
        data class OnRequestStatsUpdate(val token: Int) : CallbackType()
        data class OnSetAlert(val quotaBytes: Long) : CallbackType()
        data class OnSetWarningAndLimit(
            val iface: String,
            val warningBytes: Long,
            val limitBytes: Long
        ) : CallbackType()
    }

    private val history = ArrayTrackRecord<CallbackType>().ReadHead()

    override fun onRequestStatsUpdate(token: Int) {
        history.add(CallbackType.OnRequestStatsUpdate(token))
    }

    override fun onSetAlert(quotaBytes: Long) {
        history.add(CallbackType.OnSetAlert(quotaBytes))
    }

    override fun onSetWarningAndLimit(iface: String, warningBytes: Long, limitBytes: Long) {
        history.add(CallbackType.OnSetWarningAndLimit(iface, warningBytes, limitBytes))
    }

    fun expectOnRequestStatsUpdate(token: Int) {
        assertEquals(CallbackType.OnRequestStatsUpdate(token), history.poll(DEFAULT_TIMEOUT_MS))
    }

    fun expectOnSetWarningAndLimit(iface: String, warningBytes: Long, limitBytes: Long) {
        assertEquals(CallbackType.OnSetWarningAndLimit(iface, warningBytes, limitBytes),
                history.poll(DEFAULT_TIMEOUT_MS))
    }

    fun expectOnSetAlert(quotaBytes: Long) {
        assertEquals(CallbackType.OnSetAlert(quotaBytes), history.poll(DEFAULT_TIMEOUT_MS))
    }

    @JvmOverloads
    fun assertNoCallback(timeout: Long = DEFAULT_TIMEOUT_MS) {
        val cb = history.poll(timeout)
        cb?.let { fail("Expected no callback but got $cb") }
    }
}
