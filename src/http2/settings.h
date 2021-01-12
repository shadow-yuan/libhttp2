#pragma once

enum http2_settings_type{
    /**
     * Allows the sender to inform the
     *  remote endpoint of the maximum size of the header compression
     *  table used to decode header blocks, in octets.  The encoder can
     *  select any size equal to or less than this value by using
     *  signaling specific to the header compression format inside a
     *  header block. The initial value is 4,096 octets.
    */
    HTTP2_SETTINGS_HEADER_TABLE_SIZE = 0x1,
    /**
     * This setting can be used to disable
     *  server push.  An endpoint MUST NOT send a
     *  PUSH_PROMISE frame if it receives this parameter set to a value of
     *  0.  An endpoint that has both set this parameter to 0 and had it
     *  acknowledged MUST treat the receipt of a PUSH_PROMISE frame as a
     *  connection error of type PROTOCOL_ERROR.
    */
    HTTP2_SETTINGS_ENABLE_PUSH = 0x2,
    /**
     *  Indicates the maximum number
     *   of concurrent streams that the sender will allow.  This limit is
     *   directional: it applies to the number of streams that the sender
     *   permits the receiver to create.  Initially, there is no limit to
     *   this value.  It is recommended that this value be no smaller than
     *   100, so as to not unnecessarily limit parallelism.
    */
    HTTP2_SETTINGS_MAX_CONCURRENT_STREAMS = 0x3,
    /**
     * Indicates the sender’s initial
     *  window size (in octets) for stream-level flow control.  The
     *  initial value is 2^16-1 (65,535) octets.
    */
    HTTP2_SETTINGS_INITIAL_WINDOW_SIZE = 0x4,
    /**
     * Indicates the size of the largest
     *  frame payload that the sender is willing to receive, in octets.
    */
    HTTP2_SETTINGS_MAX_FRAME_SIZE = 0x5,
    /**
     *  This advisory setting informs a
     *   peer of the maximum size of header list that the sender is
     *   prepared to accept, in octets.  The value is based on the
     *   uncompressed size of header fields, including the length of the
     *   name and value in octets plus an overhead of 32 octets for each
     *   header field.
    */
    HTTP2_SETTINGS_MAX_HEADER_LIST_SIZE = 0x6,
};
