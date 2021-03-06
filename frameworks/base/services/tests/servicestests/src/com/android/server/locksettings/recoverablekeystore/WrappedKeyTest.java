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

package com.android.server.locksettings.recoverablekeystore;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import android.security.keystore.KeyGenParameterSpec;
import android.security.keystore.KeyProperties;
import android.util.Pair;

import androidx.test.filters.SmallTest;
import androidx.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.nio.charset.StandardCharsets;
import java.security.KeyStore;
import java.util.HashMap;
import java.util.Map;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.GCMParameterSpec;

@SmallTest
@RunWith(AndroidJUnit4.class)
public class WrappedKeyTest {
    private static final String ANDROID_KEY_STORE_PROVIDER = "AndroidKeyStore";
    private static final String KEY_ALGORITHM = "AES";
    private static final String CIPHER_ALGORITHM = "AES/GCM/NoPadding";
    private static final String WRAPPED_KEY_ALIAS = "WrappedKeyTestWrappingKeyAlias";
    private static final int GENERATION_ID = 1;
    private static final int GCM_TAG_LENGTH_BYTES = 16;
    private static final int BITS_PER_BYTE = 8;
    private static final int GCM_TAG_LENGTH_BITS = GCM_TAG_LENGTH_BYTES * BITS_PER_BYTE;
    private static final byte[] NULL_METADATA = null;
    private static final byte[] NON_NULL_METADATA = "keyMetadata".getBytes(StandardCharsets.UTF_8);

    @After
    public void tearDown() throws Exception {
        KeyStore keyStore = KeyStore.getInstance(ANDROID_KEY_STORE_PROVIDER);
        keyStore.load(/*param=*/ null);
        keyStore.deleteEntry(WRAPPED_KEY_ALIAS);
    }

    // TODO: Add tests for non-null metadata

    @Test
    public void fromSecretKey_createsWrappedKeyThatCanBeUnwrapped_nullMetadata() throws Exception {
        PlatformEncryptionKey wrappingKey = new PlatformEncryptionKey(
                GENERATION_ID, generateAndroidKeyStoreKey());
        SecretKey rawKey = generateKey();

        WrappedKey wrappedKey = WrappedKey.fromSecretKey(wrappingKey, rawKey, NULL_METADATA);

        Cipher cipher = Cipher.getInstance(CIPHER_ALGORITHM);
        cipher.init(
                Cipher.UNWRAP_MODE,
                wrappingKey.getKey(),
                new GCMParameterSpec(GCM_TAG_LENGTH_BITS, wrappedKey.getNonce()));
        SecretKey unwrappedKey = (SecretKey) cipher.unwrap(
                wrappedKey.getKeyMaterial(), KEY_ALGORITHM, Cipher.SECRET_KEY);
        assertEquals(rawKey, unwrappedKey);
    }

    @Test
    public void fromSecretKey_createsWrappedKeyThatCanBeUnwrapped_nonNullMetadata()
            throws Exception {
        PlatformEncryptionKey wrappingKey = new PlatformEncryptionKey(
                GENERATION_ID, generateAndroidKeyStoreKey());
        SecretKey rawKey = generateKey();

        WrappedKey wrappedKey = WrappedKey.fromSecretKey(wrappingKey, rawKey, NON_NULL_METADATA);

        Cipher cipher = Cipher.getInstance(CIPHER_ALGORITHM);
        cipher.init(
                Cipher.UNWRAP_MODE,
                wrappingKey.getKey(),
                new GCMParameterSpec(GCM_TAG_LENGTH_BITS, wrappedKey.getNonce()));
        SecretKey unwrappedKey = (SecretKey) cipher.unwrap(
                wrappedKey.getKeyMaterial(), KEY_ALGORITHM, Cipher.SECRET_KEY);
        assertEquals(rawKey, unwrappedKey);
    }

    @Test
    public void fromSecretKey_returnsAKeyWithTheGenerationIdOfTheWrappingKey() throws Exception {
        PlatformEncryptionKey wrappingKey = new PlatformEncryptionKey(
                GENERATION_ID, generateAndroidKeyStoreKey());
        SecretKey rawKey = generateKey();

        WrappedKey wrappedKey = WrappedKey.fromSecretKey(wrappingKey, rawKey, NULL_METADATA);

        assertEquals(GENERATION_ID, wrappedKey.getPlatformKeyGenerationId());
    }

    @Test
    public void decryptWrappedKeys_decryptsWrappedKeys_nullMetadata() throws Exception {
        String alias = "karlin";
        SecretKey platformKey = generateAndroidKeyStoreKey();
        SecretKey appKey = generateKey();
        WrappedKey wrappedKey = WrappedKey.fromSecretKey(
                new PlatformEncryptionKey(GENERATION_ID, platformKey), appKey, NULL_METADATA);
        HashMap<String, WrappedKey> keysByAlias = new HashMap<>();
        keysByAlias.put(alias, wrappedKey);

        Map<String, Pair<SecretKey, byte[]>> unwrappedKeys = WrappedKey.unwrapKeys(
                new PlatformDecryptionKey(GENERATION_ID, platformKey), keysByAlias);

        assertEquals(1, unwrappedKeys.size());
        assertTrue(unwrappedKeys.containsKey(alias));
        assertArrayEquals(appKey.getEncoded(), unwrappedKeys.get(alias).first.getEncoded());
        assertArrayEquals(null, unwrappedKeys.get(alias).second);
    }

    @Test
    public void decryptWrappedKeys_decryptsWrappedKeys_nonNullMetadata() throws Exception {
        String alias = "karlin";
        SecretKey platformKey = generateAndroidKeyStoreKey();
        SecretKey appKey = generateKey();
        WrappedKey wrappedKey = WrappedKey.fromSecretKey(
                new PlatformEncryptionKey(GENERATION_ID, platformKey), appKey, NON_NULL_METADATA);
        HashMap<String, WrappedKey> keysByAlias = new HashMap<>();
        keysByAlias.put(alias, wrappedKey);

        Map<String, Pair<SecretKey, byte[]>> unwrappedKeys = WrappedKey.unwrapKeys(
                new PlatformDecryptionKey(GENERATION_ID, platformKey), keysByAlias);

        assertEquals(1, unwrappedKeys.size());
        assertTrue(unwrappedKeys.containsKey(alias));
        assertArrayEquals(appKey.getEncoded(), unwrappedKeys.get(alias).first.getEncoded());
        assertArrayEquals(NON_NULL_METADATA, unwrappedKeys.get(alias).second);
    }

    @Test
    public void decryptWrappedKeys_doesNotDieIfSomeKeysAreUnwrappable() throws Exception {
        String alias = "karlin";
        SecretKey platformKey = generateAndroidKeyStoreKey();
        SecretKey appKey = generateKey();
        WrappedKey wrappedKey = WrappedKey.fromSecretKey(
                new PlatformEncryptionKey(GENERATION_ID, platformKey), appKey, NULL_METADATA);
        HashMap<String, WrappedKey> keysByAlias = new HashMap<>();
        keysByAlias.put(alias, wrappedKey);

        Map<String, Pair<SecretKey, byte[]>> unwrappedKeys = WrappedKey.unwrapKeys(
                new PlatformDecryptionKey(GENERATION_ID, generateAndroidKeyStoreKey()),
                keysByAlias);

        assertEquals(0, unwrappedKeys.size());
    }

    @Test
    public void decryptWrappedKeys_throwsIfPlatformKeyGenerationIdDoesNotMatch() throws Exception {
        SecretKey platformKey = generateAndroidKeyStoreKey();
        WrappedKey wrappedKey = WrappedKey.fromSecretKey(
                new PlatformEncryptionKey(GENERATION_ID, platformKey), generateKey(),
                /*metadata=*/ null);
        HashMap<String, WrappedKey> keysByAlias = new HashMap<>();
        keysByAlias.put("benji", wrappedKey);

        try {
            WrappedKey.unwrapKeys(
                    new PlatformDecryptionKey(/*generationId=*/ 2, platformKey),
                    keysByAlias);
            fail("Should have thrown.");
        } catch (BadPlatformKeyException e) {
            assertEquals(
                    "WrappedKey with alias 'benji' was wrapped with platform key 1,"
                            + " not platform key 2",
                    e.getMessage());
        }
    }

    private SecretKey generateKey() throws Exception {
        KeyGenerator keyGenerator = KeyGenerator.getInstance(KEY_ALGORITHM);
        keyGenerator.init(/*keySize=*/ 256);
        return keyGenerator.generateKey();
    }

    private SecretKey generateAndroidKeyStoreKey() throws Exception {
        KeyGenerator keyGenerator = KeyGenerator.getInstance(
                KEY_ALGORITHM,
                ANDROID_KEY_STORE_PROVIDER);
        keyGenerator.init(new KeyGenParameterSpec.Builder(
                WRAPPED_KEY_ALIAS,
                KeyProperties.PURPOSE_ENCRYPT | KeyProperties.PURPOSE_DECRYPT)
                .setBlockModes(KeyProperties.BLOCK_MODE_GCM)
                .setEncryptionPaddings(KeyProperties.ENCRYPTION_PADDING_NONE)
                .build());
        return keyGenerator.generateKey();
    }
}
