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

package android.os;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import androidx.test.filters.SmallTest;
import androidx.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Unit tests for bundle that requires accessing hidden APS.  Tests that can be written only with
 * public APIs should go in the CTS counterpart.
 *
 * Run with: atest FrameworksCoreTests:android.os.BundleTest
 */
@SmallTest
@RunWith(AndroidJUnit4.class)
public class BundleTest {

    /**
     * Take a bundle, write it to a parcel and return the parcel.
     */
    private Parcel getParcelledBundle(Bundle bundle) {
        final Parcel p = Parcel.obtain();
        // Don't use p.writeParcelabe(), which would write the creator, which we don't need.
        bundle.writeToParcel(p, 0);
        p.setDataPosition(0);
        return p;
    }

    /**
     * Create a test bundle, parcel it and return the parcel.
     */
    private Parcel createBundleParcel(boolean withFd) throws Exception {
        final Bundle source = new Bundle();
        source.putString("string", "abc");
        source.putInt("int", 1);
        if (withFd) {
            ParcelFileDescriptor[] pipe = ParcelFileDescriptor.createPipe();
            pipe[1].close();
            source.putParcelable("fd", pipe[0]);
        }
        return getParcelledBundle(source);
    }

    /**
     * Verify a bundle generated by {@link #createBundleParcel(boolean)}.
     */
    private void checkBundle(Bundle b, boolean withFd) {
        // First, do the checks without actually unparceling the bundle.
        // (Note looking into the contents will unparcel a bundle, so we'll do it later.)
        assertTrue("mParcelledData shouldn't be null here.", b.isParcelled());

        // Make sure FLAG_HAS_FDS and FLAG_HAS_FDS_KNOWN are set/cleared properly.
        if (withFd) {
            // FLAG_HAS_FDS and FLAG_HAS_FDS_KNOWN should both be set.
            assertEquals(Bundle.FLAG_HAS_FDS | Bundle.FLAG_HAS_FDS_KNOWN,
                    b.mFlags & (Bundle.FLAG_HAS_FDS | Bundle.FLAG_HAS_FDS_KNOWN));
        } else {
            // FLAG_HAS_FDS_KNOWN should be set, bot not FLAG_HAS_FDS.
            assertEquals(Bundle.FLAG_HAS_FDS_KNOWN,
                    b.mFlags & (Bundle.FLAG_HAS_FDS | Bundle.FLAG_HAS_FDS_KNOWN));
        }

        // Then, check the contents.
        assertEquals("abc", b.getString("string"));
        assertEquals(1, b.getInt("int"));

        // Make sure FLAG_HAS_FDS and FLAG_HAS_FDS_KNOWN are set/cleared properly.
        if (withFd) {
            assertEquals(ParcelFileDescriptor.class, b.getParcelable("fd").getClass());
            assertEquals(3, b.keySet().size());
        } else {
            assertEquals(2, b.keySet().size());
        }
        assertFalse(b.isParcelled());
    }

    @Test
    public void testCreateFromParcel() throws Exception {
        boolean withFd;
        Parcel p;
        Bundle b;
        int length;

        withFd = false;

        // new Bundle with p
        p = createBundleParcel(withFd);
        checkBundle(new Bundle(p), withFd);
        p.recycle();

        // new Bundle with p and length
        p = createBundleParcel(withFd);
        length = p.readInt();
        checkBundle(new Bundle(p, length), withFd);
        p.recycle();

        // readFromParcel()
        p = createBundleParcel(withFd);
        b = new Bundle();
        b.readFromParcel(p);
        checkBundle(b, withFd);
        p.recycle();

        // Same test with FDs.
        withFd = true;

        // new Bundle with p
        p = createBundleParcel(withFd);
        checkBundle(new Bundle(p), withFd);
        p.recycle();

        // new Bundle with p and length
        p = createBundleParcel(withFd);
        length = p.readInt();
        checkBundle(new Bundle(p, length), withFd);
        p.recycle();

        // readFromParcel()
        p = createBundleParcel(withFd);
        b = new Bundle();
        b.readFromParcel(p);
        checkBundle(b, withFd);
        p.recycle();
    }

    @Test
    public void kindofEquals_bothUnparcelled_same() {
        Bundle bundle1 = new Bundle();
        bundle1.putString("StringKey", "S");
        bundle1.putInt("IntKey", 2);

        Bundle bundle2 = new Bundle();
        bundle2.putString("StringKey", "S");
        bundle2.putInt("IntKey", 2);

        assertTrue(BaseBundle.kindofEquals(bundle1, bundle2));
    }

    @Test
    public void kindofEquals_bothUnparcelled_different() {
        Bundle bundle1 = new Bundle();
        bundle1.putString("StringKey", "S");
        bundle1.putInt("IntKey", 2);

        Bundle bundle2 = new Bundle();
        bundle2.putString("StringKey", "T");
        bundle2.putLong("LongKey", 30L);

        assertFalse(BaseBundle.kindofEquals(bundle1, bundle2));
    }

    @Test
    public void kindofEquals_bothParcelled_same() {
        Bundle bundle1 = new Bundle();
        bundle1.putString("StringKey", "S");
        bundle1.putInt("IntKey", 2);
        bundle1.readFromParcel(getParcelledBundle(bundle1));

        Bundle bundle2 = new Bundle();
        bundle2.putString("StringKey", "S");
        bundle2.putInt("IntKey", 2);
        bundle2.readFromParcel(getParcelledBundle(bundle2));

        assertTrue(bundle1.isParcelled());
        assertTrue(bundle2.isParcelled());
        assertTrue(BaseBundle.kindofEquals(bundle1, bundle2));
    }

    @Test
    public void kindofEquals_bothParcelled_different() {
        Bundle bundle1 = new Bundle();
        bundle1.putString("StringKey", "S");
        bundle1.putInt("IntKey", 2);
        bundle1.readFromParcel(getParcelledBundle(bundle1));

        Bundle bundle2 = new Bundle();
        bundle2.putString("StringKey", "T");
        bundle2.putLong("LongKey", 5);
        bundle2.readFromParcel(getParcelledBundle(bundle2));

        assertTrue(bundle1.isParcelled());
        assertTrue(bundle2.isParcelled());
        assertFalse(BaseBundle.kindofEquals(bundle1, bundle2));
    }

    @Test
    public void kindofEquals_ParcelledUnparcelled_empty() {
        Bundle bundle1 = new Bundle();
        bundle1.readFromParcel(getParcelledBundle(bundle1));

        Bundle bundle2 = new Bundle();

        assertTrue(bundle1.isParcelled());
        assertFalse(bundle2.isParcelled());
        // Even though one is parcelled and the other is not, both are empty, so it should
        // return true
        assertTrue(BaseBundle.kindofEquals(bundle1, bundle2));
    }
}
