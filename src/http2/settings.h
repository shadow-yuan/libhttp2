/*
 * Copyright 2017 gRPC authors.
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
#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum {

    /**
     * Allows the sender to inform the
     *  remote endpoint of the maximum size of the header compression
     *  table used to decode header blocks, in octets.  The encoder can
     *  select any size equal to or less than this value by using
     *  signaling specific to the header compression format inside a
     *  header block. The initial value is 4,096 octets.
     */
    HTTP2_SETTINGS_HEADER_TABLE_SIZE = 0, /* wire id 1 */

    /**
     * This setting can be used to disable
     *  server push.  An endpoint MUST NOT send a
     *  PUSH_PROMISE frame if it receives this parameter set to a value of
     *  0.  An endpoint that has both set this parameter to 0 and had it
     *  acknowledged MUST treat the receipt of a PUSH_PROMISE frame as a
     *  connection error of type PROTOCOL_ERROR.
     */
    HTTP2_SETTINGS_ENABLE_PUSH = 1, /* wire id 2 */

    /**
     *  Indicates the maximum number
     *   of concurrent streams that the sender will allow.  This limit is
     *   directional: it applies to the number of streams that the sender
     *   permits the receiver to create.  Initially, there is no limit to
     *   this value.  It is recommended that this value be no smaller than
     *   100, so as to not unnecessarily limit parallelism.
     */
    HTTP2_SETTINGS_MAX_CONCURRENT_STREAMS = 2, /* wire id 3 */

    /**
     * Indicates the sender’s initial
     *  window size (in octets) for stream-level flow control.  The
     *  initial value is 2^16-1 (65,535) octets.
     */
    HTTP2_SETTINGS_INITIAL_WINDOW_SIZE = 3, /* wire id 4 */

    /**
     * Indicates the size of the largest
     *  frame payload that the sender is willing to receive, in octets.
     */
    HTTP2_SETTINGS_MAX_FRAME_SIZE = 4, /* wire id 5 */

    /**
     *  This advisory setting informs a
     *   peer of the maximum size of header list that the sender is
     *   prepared to accept, in octets.  The value is based on the
     *   uncompressed size of header fields, including the length of the
     *   name and value in octets plus an overhead of 32 octets for each
     *   header field.
     */
    HTTP2_SETTINGS_MAX_HEADER_LIST_SIZE = 5, /* wire id 6 */

    HTTP2_SETTINGS_GRPC_ALLOW_TRUE_BINARY_METADATA = 6, /* wire id 65027 */
} http2_setting_id;

#define HTTP2_NUMBER_OF_SETTINGS 7

extern const uint16_t g_setting_id_to_wire_id[];

bool wire_id_to_setting_id(uint32_t wire_id, http2_setting_id *out);

typedef enum { HTTP2_CLAMP_INVALID_VALUE, HTTP2_DISCONNECT_ON_INVALID_VALUE } http2_invalid_value_behavior;

typedef struct {
    const char *name;
    uint32_t default_value;
    uint32_t min_value;
    uint32_t max_value;
    http2_invalid_value_behavior invalid_value_behavior;
    uint32_t error_value;
} http2_setting_parameters;

extern const http2_setting_parameters g_http2_settings_parameters[HTTP2_NUMBER_OF_SETTINGS];
