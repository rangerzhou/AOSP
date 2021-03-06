/*
 * Copyright (C) 2013 The Android Open Source Project
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

package android.graphics;

import androidx.test.filters.SmallTest;

import junit.framework.TestCase;

public class PathTest extends TestCase {

    @SmallTest
    public void testResetPreservesFillType() throws Exception {
        Path path = new Path();

        final Path.FillType defaultFillType = path.getFillType();
        final Path.FillType fillType = Path.FillType.INVERSE_EVEN_ODD;

        // This test is only meaningful if it changes from the default.
        assertFalse(fillType.equals(defaultFillType));

        path.setFillType(fillType);
        path.reset();
        assertEquals(path.getFillType(), fillType);
    }
}
