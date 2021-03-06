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

package com.android.settingslib.deviceinfo;

import android.app.usage.StorageStatsManager;
import android.os.storage.VolumeInfo;

import java.io.IOException;
import java.util.List;

/**
 * StorageVolumeProvider provides access to the storage volumes on a device for free space
 * calculations.
 */
public interface StorageVolumeProvider {
    /**
     * Returns the number of bytes of total storage on the primary storage.
     */
    long getPrimaryStorageSize();

    /**
     * Returns a list of VolumeInfos for the device.
     */
    List<VolumeInfo> getVolumes();

    /**
     * Returns the emulated volume for a given private volume.
     */
    VolumeInfo findEmulatedForPrivate(VolumeInfo privateVolume);

    /**
     * Returns the total bytes for a given storage volume.
     *
     * @pre The volume is a private volume and is readable.
     */
    long getTotalBytes(StorageStatsManager stats, VolumeInfo volume) throws IOException;

    /**
     * Returns the free bytes for a given storage volume.
     *
     * @pre The volume is a private volume and is readable.
     */
    long getFreeBytes(StorageStatsManager stats, VolumeInfo volume) throws IOException;
}
