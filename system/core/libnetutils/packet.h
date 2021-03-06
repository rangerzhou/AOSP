/*
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 *
 *     http://www.apache.org/licenses/LICENSE-2.0 
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */

#ifndef _WIFI_PACKET_H_
#define _WIFI_PACKET_H_

#include <linux/if_ether.h>

int open_raw_socket(const char* ifname, uint8_t hwaddr[ETH_ALEN], int if_index);
int send_packet(int s, int if_index, struct dhcp_msg *msg, int size,
                uint32_t saddr, uint32_t daddr, uint32_t sport, uint32_t dport);
int receive_packet(int s, struct dhcp_msg *msg);

#endif
