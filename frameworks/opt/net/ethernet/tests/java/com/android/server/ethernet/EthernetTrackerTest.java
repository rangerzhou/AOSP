/*
 * Copyright (C) 2018 The Android Open Source Project
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

package com.android.server.ethernet;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import android.net.InetAddresses;
import android.net.IpConfiguration;
import android.net.IpConfiguration.IpAssignment;
import android.net.IpConfiguration.ProxySettings;
import android.net.LinkAddress;
import android.net.NetworkCapabilities;
import android.net.StaticIpConfiguration;

import androidx.test.filters.SmallTest;
import androidx.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.net.InetAddress;
import java.util.ArrayList;

@SmallTest
@RunWith(AndroidJUnit4.class)
public class EthernetTrackerTest {
    /**
     * Test: Creation of various valid static IP configurations
     */
    @Test
    public void createStaticIpConfiguration() {
        // Empty gives default StaticIPConfiguration object
        assertStaticConfiguration(new StaticIpConfiguration(), "");

        // Setting only the IP address properly cascades and assumes defaults
        assertStaticConfiguration(new StaticIpConfiguration.Builder()
                .setIpAddress(new LinkAddress("192.0.2.10/24")).build(), "ip=192.0.2.10/24");

        final ArrayList<InetAddress> dnsAddresses = new ArrayList<>();
        dnsAddresses.add(InetAddresses.parseNumericAddress("4.4.4.4"));
        dnsAddresses.add(InetAddresses.parseNumericAddress("8.8.8.8"));
        // Setting other fields properly cascades them
        assertStaticConfiguration(new StaticIpConfiguration.Builder()
                .setIpAddress(new LinkAddress("192.0.2.10/24"))
                .setDnsServers(dnsAddresses)
                .setGateway(InetAddresses.parseNumericAddress("192.0.2.1"))
                .setDomains("android").build(),
                "ip=192.0.2.10/24 dns=4.4.4.4,8.8.8.8 gateway=192.0.2.1 domains=android");

        // Verify order doesn't matter
        assertStaticConfiguration(new StaticIpConfiguration.Builder()
                .setIpAddress(new LinkAddress("192.0.2.10/24"))
                .setDnsServers(dnsAddresses)
                .setGateway(InetAddresses.parseNumericAddress("192.0.2.1"))
                .setDomains("android").build(),
                "domains=android ip=192.0.2.10/24 gateway=192.0.2.1 dns=4.4.4.4,8.8.8.8 ");
    }

    /**
     * Test: Attempt creation of various bad static IP configurations
     */
    @Test
    public void createStaticIpConfiguration_Bad() {
        assertStaticConfigurationFails("ip=192.0.2.1/24 gateway= blah=20.20.20.20");  // Unknown key
        assertStaticConfigurationFails("ip=192.0.2.1");  // mask is missing
        assertStaticConfigurationFails("ip=a.b.c");  // not a valid ip address
        assertStaticConfigurationFails("dns=4.4.4.4,1.2.3.A");  // not valid ip address in dns
        assertStaticConfigurationFails("=");  // Key and value is empty
        assertStaticConfigurationFails("ip=");  // Value is empty
        assertStaticConfigurationFails("ip=192.0.2.1/24 gateway=");  // Gateway is empty
    }

    private void assertStaticConfigurationFails(String config) {
        try {
            EthernetTracker.parseStaticIpConfiguration(config);
            fail("Expected to fail: " + config);
        } catch (IllegalArgumentException e) {
            // expected
        }
    }

    private void assertStaticConfiguration(StaticIpConfiguration expectedStaticIpConfig,
                String configAsString) {
        final IpConfiguration expectedIpConfiguration = new IpConfiguration();
        expectedIpConfiguration.setIpAssignment(IpAssignment.STATIC);
        expectedIpConfiguration.setProxySettings(ProxySettings.NONE);
        expectedIpConfiguration.setStaticIpConfiguration(expectedStaticIpConfig);

        assertEquals(expectedIpConfiguration,
                EthernetTracker.parseStaticIpConfiguration(configAsString));
    }

    private NetworkCapabilities.Builder makeEthernetCapabilitiesBuilder(boolean clearAll) {
        final NetworkCapabilities.Builder builder =
                clearAll ? NetworkCapabilities.Builder.withoutDefaultCapabilities()
                        : new NetworkCapabilities.Builder();
        return builder.addCapability(NetworkCapabilities.NET_CAPABILITY_NOT_ROAMING)
                .addCapability(NetworkCapabilities.NET_CAPABILITY_NOT_CONGESTED)
                .addCapability(NetworkCapabilities.NET_CAPABILITY_NOT_SUSPENDED);
    }

    /**
     * Test: Attempt to create a capabilties with various valid sets of capabilities/transports
     */
    @Test
    public void createNetworkCapabilities() {

        // Particularly common expected results
        NetworkCapabilities defaultEthernetCleared =
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(NetworkCapabilities.TRANSPORT_ETHERNET)
                        .build();

        NetworkCapabilities ethernetClearedWithCommonCaps =
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(NetworkCapabilities.TRANSPORT_ETHERNET)
                        .addCapability(12)
                        .addCapability(13)
                        .addCapability(14)
                        .addCapability(15)
                        .build();

        // Empty capabilities and transports lists with a "please clear defaults" should
        // yield an empty capabilities set with TRANPORT_ETHERNET
        assertParsedNetworkCapabilities(defaultEthernetCleared, true, "", "");

        // Empty capabilities and transports without the clear defaults flag should return the
        // default capabilities set with TRANSPORT_ETHERNET
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(false /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(NetworkCapabilities.TRANSPORT_ETHERNET)
                        .build(),
                false, "", "");

        // A list of capabilities without the clear defaults flag should return the default
        // capabilities, mixed with the desired capabilities, and TRANSPORT_ETHERNET
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(false /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(NetworkCapabilities.TRANSPORT_ETHERNET)
                        .addCapability(11)
                        .addCapability(12)
                        .build(),
                false, "11,12", "");

        // Adding a list of capabilities with a clear defaults will leave exactly those capabilities
        // with a default TRANSPORT_ETHERNET since no overrides are specified
        assertParsedNetworkCapabilities(ethernetClearedWithCommonCaps, true, "12,13,14,15", "");

        // Adding any invalid capabilities to the list will cause them to be ignored
        assertParsedNetworkCapabilities(ethernetClearedWithCommonCaps, true, "12,13,14,15,65,73", "");
        assertParsedNetworkCapabilities(ethernetClearedWithCommonCaps, true, "12,13,14,15,abcdefg", "");

        // Adding a valid override transport will remove the default TRANSPORT_ETHERNET transport
        // and apply only the override to the capabiltities object
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(0)
                        .build(),
                true, "", "0");
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(1)
                        .build(),
                true, "", "1");
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(2)
                        .build(),
                true, "", "2");
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addTransportType(3)
                        .build(),
                true, "", "3");

        // "4" is TRANSPORT_VPN, which is unsupported. Should default back to TRANPORT_ETHERNET
        assertParsedNetworkCapabilities(defaultEthernetCleared, true, "", "4");

        // "5" is TRANSPORT_WIFI_AWARE, which is currently supported due to no legacy TYPE_NONE
        // conversion. When that becomes available, this test must be updated
        assertParsedNetworkCapabilities(defaultEthernetCleared, true, "", "5");

        // "6" is TRANSPORT_LOWPAN, which is currently supported due to no legacy TYPE_NONE
        // conversion. When that becomes available, this test must be updated
        assertParsedNetworkCapabilities(defaultEthernetCleared, true, "", "6");

        // Adding an invalid override transport will leave the transport as TRANSPORT_ETHERNET
        assertParsedNetworkCapabilities(defaultEthernetCleared,true, "", "100");
        assertParsedNetworkCapabilities(defaultEthernetCleared, true, "", "abcdefg");

        // Ensure the adding of both capabilities and transports work
        assertParsedNetworkCapabilities(
                makeEthernetCapabilitiesBuilder(true /* clearAll */)
                        .setLinkUpstreamBandwidthKbps(100000)
                        .setLinkDownstreamBandwidthKbps(100000)
                        .addCapability(12)
                        .addCapability(13)
                        .addCapability(14)
                        .addCapability(15)
                        .addTransportType(3)
                        .build(),
                true, "12,13,14,15", "3");

        // Ensure order does not matter for capability list
        assertParsedNetworkCapabilities(ethernetClearedWithCommonCaps, true, "13,12,15,14", "");
    }

    private void assertParsedNetworkCapabilities(NetworkCapabilities expectedNetworkCapabilities,
            boolean clearCapabilties, String configCapabiltiies,String configTransports) {
        assertEquals(expectedNetworkCapabilities,
                EthernetTracker.createNetworkCapabilities(clearCapabilties, configCapabiltiies,
                        configTransports).build());
    }
}
