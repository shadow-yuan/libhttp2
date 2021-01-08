
enum http2_frame{
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

enum http2_errors {
    /**
    * The associated condition is not a result of an error.
    * For example, a GOAWAY might include this code to indicate
    *  graceful shutdown of a connection.
    */
    HTTP2_NO_ERROR = 0x0,
    /**
    * The endpoint detected an unspecific protocol
    *  error.  This error is for use when a more specific error code is
    *  not available.
    */
    HTTP2_PROTOCOL_ERROR = 0x1,
    /**
    * The endpoint encountered an unexpected internal error.
    */
    HTTP2_INTERNAL_ERROR = 0x2,
    /**
    * The endpoint detected that its peer
    *  violated the flow-control protocol.
    */
    HTTP2_FLOW_CONTROL_ERROR = 0x3,
    /**
    * The endpoint sent a SETTINGS frame but did
    *  not receive a response in a timely manner.
    */
    HTTP2_SETTINGS_TIMEOUT_ERROR = 0x4,
    /**
    * The endpoint received a frame after a stream
    *  was half-closed.
    */
    HTTP2_STREAM_CLOSED_ERROR = 0x5,
    /**
    * The endpoint received a frame with an
    *  invalid size.
    */
    HTTP2_FRAME_SIZE_ERROR = 0x6,
    /**
    * The endpoint refused the stream prior to
    *  performing any application processing.
    */
    HTTP2_REFUSED_ERROR = 0x7,
    /**
    * Used by the endpoint to indicate that the stream is no
    *  longer needed.
    */
    HTTP2_CANCEL_ERROR = 0x8,
    /**
    * The endpoint is unable to maintain the
    *  header compression context for the connection.
    */
    HTTP2_COMPRESSION_ERROR = 0x9,
    /**
    * The connection established in response to a
    *  CONNECT request was reset or abnormally closed.
    */
    HTTP2_CONNECT_ERROR = 0xa,
    /**
    * The endpoint detected that its peer is
    *  exhibiting a behavior that might be generating excessive load.
    */
    HTTP2_ENHANCE_YOUR_CALM_ERROR = 0xb,
    /**
    * The underlying transport has properties
    *  that do not meet minimum security requirements.
    */
    HTTP2_INADEQUATE_SECURITY_ERROR = 0xc,
    /**
    * The endpoint requires that HTTP/1.1 be used
    *  instead of HTTP/2.
    */
    HTTP2_HTTP_1_1_REQUIRED = 0xd,
};

