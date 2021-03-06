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
 * limitations under the License.
 */

package android.util;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;

import androidx.test.filters.SmallTest;
import androidx.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
@SmallTest
public class LongArrayTest {

    @Test
    public void testLongArray() {
        LongArray a = new LongArray();
        a.add(1);
        a.add(2);
        a.add(3);
        verify(new long[]{1, 2, 3}, a);

        LongArray b = LongArray.fromArray(new long[]{4, 5, 6, 7, 8}, 3);
        a.addAll(b);
        verify(new long[]{1, 2, 3, 4, 5, 6}, a);

        a.resize(2);
        verify(new long[]{1, 2}, a);

        a.resize(8);
        verify(new long[]{1, 2, 0, 0, 0, 0, 0, 0}, a);

        a.set(5, 10);
        verify(new long[]{1, 2, 0, 0, 0, 10, 0, 0}, a);

        a.add(5, 20);
        assertEquals(20, a.get(5));
        assertEquals(5, a.indexOf(20));
        verify(new long[]{1, 2, 0, 0, 0, 20, 10, 0, 0}, a);

        assertEquals(-1, a.indexOf(99));

        a.resize(15);
        a.set(14, 30);
        verify(new long[]{1, 2, 0, 0, 0, 20, 10, 0, 0, 0, 0, 0, 0, 0, 30}, a);

        long[] backingArray = new long[]{1, 2, 3, 4};
        a = LongArray.wrap(backingArray);
        a.set(0, 10);
        assertEquals(10, backingArray[0]);
        backingArray[1] = 20;
        backingArray[2] = 30;
        verify(backingArray, a);
        assertEquals(2, a.indexOf(30));

        a.resize(2);
        assertEquals(0, backingArray[2]);
        assertEquals(0, backingArray[3]);

        a.add(50);
        verify(new long[]{10, 20, 50}, a);
    }

    public void verify(long[] expected, LongArray longArrays) {
        assertEquals(expected.length, longArrays.size());
        assertArrayEquals(expected, longArrays.toArray());
    }
}
