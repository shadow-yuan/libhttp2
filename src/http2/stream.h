#pragma once
#include <stdint.h>

enum http2_stream_type {
    HTTP2_STREAM_IDLE,
    HTTP2_STREAM_RESERVED_LOCAL,
    HTTP2_STREAM_RESERVED_REMOTE,
    HTTP2_STREAM_OPEN,
    HTTP2_STREAN_HALF_LOCAL,
    HTTP2_STREAM_HALF_REMOTE,
    HTTP2_STREAM_CLOSED,
};

class http2_stream {
public:
    http2_stream(uint32_t sid);
    ~http2_stream();

    bool is_control_stream() const {
        return _sid == 0;
    }
    uint32_t get_sid() const {
        return _sid;
    }
    void close();

private:
    uint32_t _sid;
};
