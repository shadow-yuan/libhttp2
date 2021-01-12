#pragma once

enum http2_frame_type{
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
    HTTP2_FRAME_WINDOW_UPDATE = 0x9,
};

enum http2_frame_flag {
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
};
