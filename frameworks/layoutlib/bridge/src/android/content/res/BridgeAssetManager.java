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
package android.content.res;

import android.annotation.NonNull;
import android.annotation.Nullable;
import com.android.ide.common.rendering.api.AssetRepository;
import com.android.layoutlib.bridge.Bridge;

import java.io.IOException;
import java.io.InputStream;

public class BridgeAssetManager extends AssetManager {
    @Nullable private AssetRepository mAssetRepository;

    /**
     * This initializes the static field {@link AssetManager#sSystem} which is used
     * by methods who get a global asset manager using {@link AssetManager#getSystem()}.
     * <p/>
     * They will end up using our bridge asset manager.
     * <p/>
     * {@link Bridge} calls this method after setting up a new bridge.
     */
    public static AssetManager initSystem() {
        if (!(AssetManager.sSystem instanceof BridgeAssetManager)) {
            // Note that AssetManager() creates a system AssetManager and we override it
            // with our BridgeAssetManager.
            AssetManager.sSystem = new BridgeAssetManager();
        }
        return AssetManager.sSystem;
    }

    /**
     * Clears the static {@link AssetManager#sSystem} to make sure we don't leave objects
     * around that would prevent us from unloading the library.
     */
    public static void clearSystem() {
        AssetManager.sSystem = null;
    }

    public void setAssetRepository(@NonNull AssetRepository assetRepository) {
        mAssetRepository = assetRepository;
    }

    /**
     * Clears the AssetRepository reference.
     */
    public void releaseAssetRepository() {
        mAssetRepository = null;
    }

    @NonNull
    public AssetRepository getAssetRepository() {
        if (mAssetRepository == null) {
            throw new IllegalStateException("Asset repository is not set");
        }
        return mAssetRepository;
    }

    @Override
    public InputStream open(String fileName, int accessMode) throws IOException {
        return getAssetRepository().openAsset(fileName, accessMode);
    }

    @Override
    public InputStream openNonAsset(int cookie, String fileName, int accessMode)
            throws IOException {
        return getAssetRepository().openNonAsset(cookie, fileName, accessMode);
    }

    public BridgeAssetManager() {
    }
}
