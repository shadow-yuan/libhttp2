#pragma once
#include <stddef.h>

enum http2_stream_status {
    HTTP2_STREAM_IDLE,
    HTTP2_STREAM_RESERVED_LOCAL,
    HTTP2_STREAM_RESERVED_REMOTE,
    HTTP2_STREAM_OPEN,
    HTTP2_STREAN_HALF_LOCAL,
    HTTP2_STREAM_HALF_REMOTE,
    HTTP2_STREAM_CLOSED,
};

enum http2_stream_event {
    HTTP2_STREAM_EVENT_HEADERS_R,
    HTTP2_STREAM_EVENT_HEADERS_S,
    HTTP2_STREAM_EVENT_PP_R,  // PUSH_PROMISE
    HTTP2_STREAM_EVENT_PP_S,  // PUSH_PROMISE
    HTTP2_STREAM_EVENT_ES_R,  // END_STREAM
    HTTP2_STREAM_EVENT_ES_S,
    HTTP2_STREAM_EVENT_RST_R,  // RST_STREAM
    HTTP2_STREAM_EVENT_RST_S,  // RST_STREAM
};

class http2_stream_status_fsm {
    struct fsm_table {
        http2_stream_event event;
        http2_stream_status cur_status;
        http2_stream_status next_status;
        // TODO action.
    };

public:
    http2_stream_status_fsm();

    bool handle_status(http2_stream_event event);
    http2_stream_status get_curr_status() const {
        return _cur_status;
    }

private:
    http2_stream_status _cur_status;
    static const fsm_table _fsm_table[];
    static const size_t _fsm_table_size;
};
