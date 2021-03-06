/*
 * Copyright (C) 2017 The Android Open Source Project
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
 * limitations under the License
 */
package com.android.internal.colorextraction.types;

import static com.google.common.truth.Truth.assertThat;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import android.app.WallpaperColors;
import android.graphics.Color;
import android.util.Range;

import androidx.test.InstrumentationRegistry;
import androidx.test.filters.SmallTest;
import androidx.test.runner.AndroidJUnit4;

import com.android.internal.colorextraction.ColorExtractor.GradientColors;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.Arrays;

/**
 * Tests tonal palette generation.
 */
@SmallTest
@RunWith(AndroidJUnit4.class)
public class TonalTest {

    @Test
    public void extractInto_usesFallback() {
        GradientColors normal = new GradientColors();
        Tonal tonal = new Tonal(InstrumentationRegistry.getContext());
        tonal.extractInto(null, normal, new GradientColors(),
                new GradientColors());
        assertFalse("Should use fallback color if WallpaperColors is null.",
                normal.getMainColor() == Tonal.MAIN_COLOR_LIGHT);
    }

    @Test
    public void extractInto_usesFallbackWhenTooLightOrDark() {
        GradientColors normal = new GradientColors();
        Tonal tonal = new Tonal(InstrumentationRegistry.getContext());
        tonal.extractInto(new WallpaperColors(Color.valueOf(0xff000000), null, null, 0),
                normal, new GradientColors(), new GradientColors());
        assertTrue("Should use fallback color if WallpaperColors is too dark.",
                normal.getMainColor() == Tonal.MAIN_COLOR_DARK);

        tonal.extractInto(new WallpaperColors(Color.valueOf(0xffffffff), null, null,
                        WallpaperColors.HINT_SUPPORTS_DARK_TEXT),
                normal, new GradientColors(), new GradientColors());
        assertTrue("Should use fallback color if WallpaperColors is too light.",
                normal.getMainColor() == Tonal.MAIN_COLOR_LIGHT);
    }

    @Test
    public void extractInto_fromBitmap() {
        Tonal tonal = new Tonal(InstrumentationRegistry.getContext());
        GradientColors normal = new GradientColors();
        GradientColors dark = new GradientColors();
        GradientColors extraDark = new GradientColors();
        WallpaperColors wallColors = new WallpaperColors(Color.valueOf(Color.RED), null, null,
                WallpaperColors.HINT_FROM_BITMAP);

        // WHEN colors are extracted from a wallpaper with only a red primary color.
        tonal.extractInto(wallColors, normal, dark, extraDark);
        // THEN the main extracted color is red
        assertThat(normal.getMainColor()).isEqualTo(Color.RED);
    }

    @Test
    public void extractInto_supportsDarkText() {
        Tonal tonal = new Tonal(InstrumentationRegistry.getContext());
        GradientColors normal = new GradientColors();
        GradientColors dark = new GradientColors();
        GradientColors extraDark = new GradientColors();
        WallpaperColors wallColors = new WallpaperColors(Color.valueOf(Color.RED), null, null,
                WallpaperColors.HINT_SUPPORTS_DARK_TEXT);

        // WHEN colors are extracted from a wallpaper with only a red primary color.
        tonal.extractInto(wallColors, normal, dark, extraDark);
        // THEN the main extracted color is red
        assertThat(normal.getMainColor()).isEqualTo(Color.RED);
    }

    @Test
    public void colorRange_containsColor() {
        Tonal.ColorRange colorRange = new Tonal.ColorRange(new Range<>(0f, 50f),
                new Range<>(0f, 1f), new Range<>(0f, 1f));
        float[] hsl = new float[] {25, 0, 0};
        assertTrue("Range " + colorRange + " doesn't contain " + Arrays.toString(hsl),
                colorRange.containsColor(hsl[0], hsl[1], hsl[2]));
    }

    @Test
    public void colorRange_doesntContainColor() {
        Tonal.ColorRange colorRange = new Tonal.ColorRange(new Range<>(0f, 50f),
                new Range<>(0f, 0.5f), new Range<>(0f, 0.5f));
        float[] hsl = new float[] {100, 0, 0};
        assertFalse("Range " + colorRange + " shouldn't contain " + Arrays.toString(hsl),
                colorRange.containsColor(hsl[0], hsl[1], hsl[2]));
        hsl = new float[] {0, 0.6f, 0};
        assertFalse("Range " + colorRange + " shouldn't contain " + Arrays.toString(hsl),
                colorRange.containsColor(hsl[0], hsl[1], hsl[2]));
        hsl = new float[] {0, 0, 0.6f};
        assertFalse("Range " + colorRange + " shouldn't contain " + Arrays.toString(hsl),
                colorRange.containsColor(hsl[0], hsl[1], hsl[2]));
    }

    @Test
    public void configParser_dataSanity() {
        Tonal.ConfigParser config = new Tonal.ConfigParser(InstrumentationRegistry.getContext());
        // 1 to avoid regression where only first item would be parsed.
        assertTrue("Tonal palettes are empty", config.getTonalPalettes().size() > 1);
    }

    @Test
    public void tonal_rangeTest() {
        Tonal.ConfigParser config = new Tonal.ConfigParser(InstrumentationRegistry.getContext());
        for (Tonal.TonalPalette palette : config.getTonalPalettes()) {
            assertTrue("minHue should be >= to 0.", palette.minHue >= 0);
            assertTrue("maxHue should be <= to 360.", palette.maxHue <= 360);

            assertTrue("S should be >= to 0.", palette.s[0] >= 0);
            assertTrue("S should be <= to 1.", palette.s[1] <= 1);

            assertTrue("L should be >= to 0.", palette.l[0] >= 0);
            assertTrue("L should be <= to 1.", palette.l[1] <= 1);
        }
    }
}
