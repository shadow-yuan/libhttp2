#pragma once
#include <stdint.h>
#include <functional>
#include "src/http2/frame.h"
#include "src/http2/errors.h"
#include "src/http2/stream_status.h"
/*
class http2_stream_status_listener {
public:
    virtual void http2_stream_status_changed(http2_stream_status old_status, http2_stream_status new_status) const = 0;
};
*/
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
    /*
    void set_stauts_listener(http2_stream_status_listener *listener) {
        _listener = listener;
    }*/
    http2_errors frame_arrived(http2_frame *frame);
    void close();

private:
    struct internal_stream_frame_func {
        http2_frame_type type;
        std::function<http2_errors(http2_frame *frame)> func;
    };
    static const internal_stream_frame_func frame_funcs[];

    http2_errors frame_data(http2_frame *frame);
    http2_errors frame_header(http2_frame *frame);
    http2_errors frame_priority(http2_frame *frame);
    http2_errors frame_rst_stream(http2_frame *frame);
    http2_errors frame_push_promise(http2_frame *frame);
    http2_errors frame_ping(http2_frame *frame);
    http2_errors frame_continuation(http2_frame *frame);

private:
    uint32_t _sid;
    uint32_t _flow_max;
    http2_connection *_conn;
    http2_stream_status_fsm _stream_status;
    // http2_stream_status_listener *_listener = nullptr;
};
