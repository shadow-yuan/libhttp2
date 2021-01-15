#pragma once
#include <stdint.h>
#include "src/http2/frame.h"

enum http2_stream_type {
    HTTP2_STREAM_IDLE,
    HTTP2_STREAM_RESERVED_LOCAL,
    HTTP2_STREAM_RESERVED_REMOTE,
    HTTP2_STREAM_OPEN,
    HTTP2_STREAN_HALF_LOCAL,
    HTTP2_STREAM_HALF_REMOTE,
    HTTP2_STREAM_CLOSED,
};

class http2_connection;
class http2_stream {
public:
    http2_stream(uint32_t sid, http2_connection *conn);
    ~http2_stream();

    bool is_control_stream() const {
        return _sid == 0;
    }
    uint32_t get_sid() const {
        return _sid;
    }
    void set_flow(uint32_t flow) {
        _flow_max = flow;
    }
    bool frame_arrived(http2_frame *frame);
    void close();

private:
    uint32_t _sid;
    uint32_t _flow_max;
    http2_stream_type _stream_type;
    http2_connection *_conn;
};
