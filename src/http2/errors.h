#pragma once

/**
 *  Error codes are 32-bit fields that are used in RST_STREAM and GOAWAY
 *  frames to convey the reasons for the stream or connection error.
 */
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

