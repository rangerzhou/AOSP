/*
 * Copyright (C) 2015 The Android Open Source Project
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

package android.security.net.config;

import android.util.Pair;
import java.util.Set;

/** @hide */
public class TestConfigSource implements ConfigSource {
    private final Set<Pair<Domain, NetworkSecurityConfig>> mConfigs;
    private final NetworkSecurityConfig mDefaultConfig;
    public TestConfigSource(Set<Pair<Domain, NetworkSecurityConfig>> configs,
            NetworkSecurityConfig defaultConfig) {
        mConfigs = configs;
        mDefaultConfig = defaultConfig;
    }

    public Set<Pair<Domain, NetworkSecurityConfig>> getPerDomainConfigs() {
        return mConfigs;
    }

    public NetworkSecurityConfig getDefaultConfig() {
        return mDefaultConfig;
    }
}
