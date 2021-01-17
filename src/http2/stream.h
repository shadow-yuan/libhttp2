#pragma once
#include <stdint.h>
#include "src/http2/frame.h"

enum http2_stream_status {
    HTTP2_STREAM_IDLE,
    HTTP2_STREAM_RESERVED_LOCAL,
    HTTP2_STREAM_RESERVED_REMOTE,
    HTTP2_STREAM_OPEN,
    HTTP2_STREAN_HALF_LOCAL,
    HTTP2_STREAM_HALF_REMOTE,
    HTTP2_STREAM_CLOSED,
};

class http2_stream_status_listener {
public:
    virtual void http2_stream_status_changed(http2_stream_status old_status, http2_stream_status new_status) const = 0;
}

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
    void set_stauts_listener(http2_stream_status_listener *listener) {
        _listener = listener;
    }
    http2_stream_status get_stream_status() const {
        return _stream_status;
    }
    bool frame_arrived(http2_frame *frame);
    void close();

private:
    bool frame_data(http2_frame *frame);
    bool frame_header(http2_frame *frame);
    bool frame_priority(http2_frame *frame);
    bool frame_rst_stream(http2_frame *frame);
    bool frame_setting(http2_frame *frame);
    bool frame_push_promise(http2_frame *frame);
    bool frame_ping(http2_frame *frame);
    bool frame_goaway(http2_frame *frame);
    bool frame_window_update(http2_frame *frame);
    bool frame_continuation(http2_frame *frame);

private:
    uint32_t _sid;
    uint32_t _flow_max;
    http2_stream_status _stream_status;
    http2_connection *_conn;
    http2_stream_status_listener *_listener = nullptr;
};
