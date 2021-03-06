/*
 * Copyright 2019 The Android Open Source Project
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

package android.media.tv.tuner.frontend;

import android.annotation.SystemApi;

/**
 * ISDBS Capabilities.
 *
 * @hide
 */
@SystemApi
public class IsdbsFrontendCapabilities extends FrontendCapabilities {
    private final int mModulationCap;
    private final int mCodeRateCap;

    private IsdbsFrontendCapabilities(int modulationCap, int codeRateCap) {
        mModulationCap = modulationCap;
        mCodeRateCap = codeRateCap;
    }

    /**
     * Gets modulation capability.
     */
    @IsdbsFrontendSettings.Modulation
    public int getModulationCapability() {
        return mModulationCap;
    }
    /**
     * Gets code rate capability.
     */
    @IsdbsFrontendSettings.CodeRate
    public int getCodeRateCapability() {
        return mCodeRateCap;
    }
}
