/*
 * Copyright (C) 2021 The Android Open Source Project
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

package android.content.pm.overlay;

import android.annotation.NonNull;
import android.annotation.Nullable;

import com.android.internal.util.DataClass;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/** @hide */
@DataClass(genConstructor = false, genBuilder = false, genHiddenBuilder = false,
        genEqualsHashCode = true, genToString = true)
public class OverlayPaths {
    /**
     * Represents {@link android.content.pm.ApplicationInfo#resourceDirs}.
     * Only contains paths to APKs of overlays that can have their idmap resolved from their base
     * APK path. Currently all overlay APKs can have their idmap path resolved from their idmap
     * path.
     */
    @NonNull
    private final List<String> mResourceDirs = new ArrayList<>();

    /**
     * Represents {@link android.content.pm.ApplicationInfo#overlayPaths}.
     * Contains the contents of {@link #getResourceDirs()} and along with paths for overlays
     * that are not APKs.
     */
    @NonNull
    private final List<String> mOverlayPaths = new ArrayList<>();

    public static class Builder {
        final OverlayPaths mPaths = new OverlayPaths();

        /**
         * Adds a non-APK path to the contents of {@link OverlayPaths#getOverlayPaths()}.
         */
        public Builder addNonApkPath(@NonNull String idmapPath) {
            mPaths.mOverlayPaths.add(idmapPath);
            return this;
        }

        /**
         * Adds a overlay APK path to the contents of {@link OverlayPaths#getResourceDirs()} and
         * {@link OverlayPaths#getOverlayPaths()}.
         */
        public Builder addApkPath(@NonNull String overlayPath) {
            addUniquePath(mPaths.mResourceDirs, overlayPath);
            addUniquePath(mPaths.mOverlayPaths, overlayPath);
            return this;
        }

        public Builder addAll(@Nullable OverlayPaths other) {
            if (other != null) {
                for (final String path : other.getResourceDirs()) {
                    addUniquePath(mPaths.mResourceDirs, path);
                }
                for (final String path : other.getOverlayPaths()) {
                    addUniquePath(mPaths.mOverlayPaths, path);
                }
            }
            return this;
        }

        public OverlayPaths build() {
            return mPaths;
        }

        private static void addUniquePath(@NonNull List<String> paths, @NonNull String path) {
            if (!paths.contains(path)) {
                paths.add(path);
            }
        }
    }

    /**
     * Returns whether {@link #getOverlayPaths()} and {@link #getOverlayPaths} are empty.
     */
    public boolean isEmpty() {
        return mResourceDirs.isEmpty() && mOverlayPaths.isEmpty();
    }

    private OverlayPaths() {
    }



    // Code below generated by codegen v1.0.22.
    //
    // DO NOT MODIFY!
    // CHECKSTYLE:OFF Generated code
    //
    // To regenerate run:
    // $ codegen $ANDROID_BUILD_TOP/frameworks/base/core/java/android/content/pm/overlay/OverlayPaths.java
    //
    // To exclude the generated code from IntelliJ auto-formatting enable (one-time):
    //   Settings > Editor > Code Style > Formatter Control
    //@formatter:off


    /**
     * Represents {@link android.content.pm.ApplicationInfo#resourceDirs}.
     * Only contains paths to APKs of overlays that can have their idmap resolved from their base
     * APK path. Currently all overlay APKs can have their idmap path resolved from their idmap
     * path.
     */
    @DataClass.Generated.Member
    public @NonNull List<String> getResourceDirs() {
        return mResourceDirs;
    }

    /**
     * Represents {@link android.content.pm.ApplicationInfo#overlayPaths}.
     * Contains the contents of {@link #getResourceDirs()} and along with paths for overlays
     * that are not APKs.
     */
    @DataClass.Generated.Member
    public @NonNull List<String> getOverlayPaths() {
        return mOverlayPaths;
    }

    @Override
    @DataClass.Generated.Member
    public String toString() {
        // You can override field toString logic by defining methods like:
        // String fieldNameToString() { ... }

        return "OverlayPaths { " +
                "resourceDirs = " + mResourceDirs + ", " +
                "overlayPaths = " + mOverlayPaths +
                " }";
    }

    @Override
    @DataClass.Generated.Member
    public boolean equals(@android.annotation.Nullable Object o) {
        // You can override field equality logic by defining either of the methods like:
        // boolean fieldNameEquals(OverlayPaths other) { ... }
        // boolean fieldNameEquals(FieldType otherValue) { ... }

        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        @SuppressWarnings("unchecked")
        OverlayPaths that = (OverlayPaths) o;
        //noinspection PointlessBooleanExpression
        return true
                && Objects.equals(mResourceDirs, that.mResourceDirs)
                && Objects.equals(mOverlayPaths, that.mOverlayPaths);
    }

    @Override
    @DataClass.Generated.Member
    public int hashCode() {
        // You can override field hashCode logic by defining methods like:
        // int fieldNameHashCode() { ... }

        int _hash = 1;
        _hash = 31 * _hash + Objects.hashCode(mResourceDirs);
        _hash = 31 * _hash + Objects.hashCode(mOverlayPaths);
        return _hash;
    }

    @DataClass.Generated(
            time = 1612307813586L,
            codegenVersion = "1.0.22",
            sourceFile = "frameworks/base/core/java/android/content/pm/overlay/OverlayPaths.java",
            inputSignatures = "private final @android.annotation.NonNull java.util.List<java.lang.String> mResourceDirs\nprivate final @android.annotation.NonNull java.util.List<java.lang.String> mOverlayPaths\npublic  boolean isEmpty()\nclass OverlayPaths extends java.lang.Object implements []\nfinal  android.content.pm.overlay.OverlayPaths mPaths\npublic  android.content.pm.overlay.OverlayPaths.Builder addNonApkPath(java.lang.String)\npublic  android.content.pm.overlay.OverlayPaths.Builder addApkPath(java.lang.String)\npublic  android.content.pm.overlay.OverlayPaths.Builder addAll(android.content.pm.overlay.OverlayPaths)\npublic  android.content.pm.overlay.OverlayPaths build()\nprivate static  void addUniquePath(java.util.List<java.lang.String>,java.lang.String)\nclass Builder extends java.lang.Object implements []\n@com.android.internal.util.DataClass(genConstructor=false, genBuilder=false, genHiddenBuilder=false, genEqualsHashCode=true, genToString=true)")
    @Deprecated
    private void __metadata() {}


    //@formatter:on
    // End of generated code

}
