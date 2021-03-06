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

package android.security;

import android.annotation.NonNull;
import android.annotation.Nullable;

import java.security.KeyPair;
import java.security.cert.Certificate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * The {@code AttestedKeyPair} class contains a {@code KeyPair} instance of
 * keys generated by Keystore and owned by KeyChain, as well as an attestation
 * record for the key.
 *
 * <p>Such keys can be obtained by calling
 * {@link android.app.admin.DevicePolicyManager#generateKeyPair}.
 */

public final class AttestedKeyPair {
    private final KeyPair mKeyPair;
    private final List<Certificate> mAttestationRecord;

    /**
     * Public constructor for creating a new instance (useful for testing).
     *
     * @param keyPair the key pair associated with the attestation record.
     * @param attestationRecord attestation record for the provided key pair.
     */
    public AttestedKeyPair(
            @Nullable KeyPair keyPair, @NonNull List<Certificate> attestationRecord) {
        mKeyPair = keyPair;
        mAttestationRecord = attestationRecord;
    }

    /**
     * @hide used by platform.
     */
    public AttestedKeyPair(@Nullable KeyPair keyPair, @Nullable Certificate[] attestationRecord) {
        mKeyPair = keyPair;
        if (attestationRecord == null) {
            mAttestationRecord = new ArrayList();
        } else {
            mAttestationRecord = Arrays.asList(attestationRecord);
        }
    }

    /**
     * Returns the generated key pair associated with the attestation record
     * in this instance.
     */
    public @Nullable KeyPair getKeyPair() {
        return mKeyPair;
    }

    /**
     * Returns the attestation record for the key pair in this instance.
     *
     * The attestation record is a chain of certificates. The leaf certificate links to the public
     * key of this key pair and other properties of the key or the device. If the key is in secure
     * hardware, and if the secure hardware supports attestation, the leaf certificate will be
     * signed by a chain of certificates rooted at a trustworthy CA key. Otherwise the chain will be
     * rooted at an untrusted certificate.
     *
     * The attestation record could be for properties of the key, or include device identifiers.
     *
     * See {@link android.security.keystore.KeyGenParameterSpec.Builder#setAttestationChallenge}
     * and  <a href="https://developer.android.com/training/articles/security-key-attestation.html">
     * Key Attestation</a> for the format of the attestation record inside the certificate.
     */
    public @NonNull List<Certificate> getAttestationRecord() {
        return Collections.unmodifiableList(mAttestationRecord);
    }
}
