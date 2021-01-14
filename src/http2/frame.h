#pragma once
#include <stdint.h>
#include "src/utils/slice.h"

enum http2_frame_type {
    /**
     * DATA frames convey arbitrary, variable-length sequences of
     *  octets associated with a stream.  One or more DATA frames are used,
     *  for instance, to carry HTTP request or response payloads.
     */
    HTTP2_FRAME_DATA = 0x0,
    /**
     * The HEADERS frame is used to open a stream,
     *  and additionally carries a header block fragment.  HEADERS frames can
     *  be sent on a stream in the "idle", "reserved (local)", "open", or
     *  "half-closed (remote)" state.
     */
    HTTP2_FRAME_HEADERS = 0x1,
    /**
     * The PRIORITY frame specifies the sender-advised priority
     *  of a stream.  It can be sent in any stream state,
     *  including idle or closed streams.
     */
    HTTP2_FRAME_PRIORITY = 0x2,
    /**
     * The RST_STREAM frame allows for immediate termination of a
     *  stream.  RST_STREAM is sent to request cancellation of a stream or to
     *  indicate that an error condition has occurred.
     */
    HTTP2_FRAME_RST_STREAM = 0x3,
    /**
     * The SETTINGS frame conveys configuration parameters that
     *  affect how endpoints communicate, such as preferences and constraints
     *  on peer behavior.  The SETTINGS frame is also used to acknowledge the
     *  receipt of those parameters.  Individually, a SETTINGS parameter can
     *  also be referred to as a "setting".
     */
    HTTP2_FRAME_SETTINGS = 0x4,
    /**
     * The PUSH_PROMISE frame is used to notify the peer endpoint
     *  in advance of streams the sender intends to initiate.  The
     *  PUSH_PROMISE frame includes the unsigned 31-bit identifier of the
     *  stream the endpoint plans to create along with a set of headers that
     *  provide additional context for the stream.
     */
    HTTP2_FRAME_PUSH_PROMISE = 0x5,
    /**
     * The PING frame is a mechanism for measuring a minimal
     *  round-trip time from the sender, as well as determining whether an
     *  idle connection is still functional.  PING frames can be sent from
     *  any endpoint.
     */
    HTTP2_FRAME_PING = 0x6,
    /**
     * The GOAWAY frame is used to initiate shutdown of a
     *  connection or to signal serious error conditions.  GOAWAY allows an
     *  endpoint to gracefully stop accepting new streams while still
     *  finishing processing of previously established streams.  This enables
     *  administrative actions, like server maintenance.
     */
    HTTP2_FRAME_GOAWAY = 0x7,
    /**
     *  The WINDOW_UPDATE frame is used to implement flow control;
     */
    HTTP2_FRAME_WINDOW_UPDATE = 0x8,
    /**
     * The CONTINUATION frame is used to continue a sequence of
     *  header block fragments . Any number of CONTINUATION
     *  frames can be sent, as long as the preceding frame is on the same
     *  stream and is a HEADERS, PUSH_PROMISE, or CONTINUATION frame without
     *  the END_HEADERS flag set.
     */
    HTTP2_FRAME_CONTINUATION = 0x9,
};

enum http2_frame_flags {
    /**
     * When set, bit 0 indicates that this frame is the
     *  last that the endpoint will send for the identified stream.
     */
    HTTP2_FLAG_END_STREAM = 0x1,
    /**
     * When set, bit 2 indicates that this frame
     *  contains an entire header block and is not followed
     *  by any CONTINUATION frames.
     */
    HTTP2_FLAG_END_HEADERS = 0x4,
    /**
     * When set, bit 3 indicates that the Pad Length field
     *  and any padding that it describes are present.
     */
    HTTP2_FLAG_PADDED = 0x8,
    /**
     *  When set, bit 5 indicates that the Exclusive Flag
     *   (E), Stream Dependency, and Weight fields are present;
     */
    HTTP2_FLAG_PRIORITY = 0x20,

    /**
     * no flag.
     */
    HTTP2_FLAG_NONE = 0x0,
};

struct http2_frame_head {
    uint32_t payload_length;
    uint8_t type;
    uint8_t flag;
    uint32_t stream_id;
};

struct http2_frame_data {
    http2_frame_head head;
    uint8_t pad_len;
    slice data;
};

struct http2_frame_headers {
    http2_frame_head head;
    uint8_t pad_len;
    uint32_t stream_id;
    uint8_t weight;
    slice header_block_fragment;
};

struct http2_frame_priority {
    http2_frame_head head;
    uint32_t stream_id;
    uint8_t weight;
};

struct http2_frame_rst_stream {
    http2_frame_head head;
    uint32_t error_code;
};

struct http2_settings_entry {
    uint16_t id;
    uint32_t value;
};

struct http2_frame_settings {
    http2_frame_head head;
    size_t count;
    http2_settings_entry *settings;
};

struct http2_frame_push_promise {
    http2_frame_head head;
    uint8_t pad_len;
    uint32_t promised_stream_id;
    slice header_block_fragment;
};

struct http2_frame_ping {
    http2_frame_head head;
    uint64_t data;
};

struct http2_frame_goaway {
    http2_frame_head head;
    uint32_t last_stream_id;
    uint32_t error_code;
    slice data;
};

struct http2_frame_window_update {
    http2_frame_head head;
    uint32_t size;
};

struct http2_frame_continuation {
    http2_frame_head head;
    slice header_block_fragment;
};

struct http2_frame {
    union {
        http2_frame_head head;
        http2_frame_data data;
        http2_frame_headers headers;
        http2_frame_priority priority;
        http2_frame_rst_stream rst_stream;
        http2_frame_settings settings;
        http2_frame_push_promise promise;
        http2_frame_ping ping;
        http2_frame_goaway goaway;
        http2_frame_window_update window_update;
        http2_frame_continuation continuation;
    };
};

void http2_free_frame(http2_frame *frame);

uint8_t head_bit(uint8_t v);
uint8_t head_bit(uint16_t v);
uint8_t head_bit(uint32_t v);
void rm_head_bit(uint32_t &v);
