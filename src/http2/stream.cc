#include "src/http2/stream.h"

/* http2 status migrational table
                                +--------+
                        send PP |        | recv PP
                       ,--------|  idle  |--------.
                      /         |        |         \
                     v          +--------+          v
              +----------+          |           +----------+
              |          |          | send H /  |          |
       ,------| reserved |          | recv H    | reserved |------.
       |      | (local)  |          |           | (remote) |      |
       |      +----------+          v           +----------+      |
       |          |             +--------+             |          |
       |          |     recv ES |        | send ES     |          |
       |   send H |     ,-------|  open  |-------.     | recv H   |
       |          |    /        |        |        \    |          |
       |          v   v         +--------+         v   v          |
       |      +----------+          |           +----------+      |
       |      |   half   |          |           |   half   |      |
       |      |  closed  |          | send R /  |  closed  |      |
       |      | (remote) |          | recv R    | (local)  |      |
       |      +----------+          |           +----------+      |
       |           |                |                 |           |
       |           | send ES /      |       recv ES / |           |
       |           | send R /       v        send R / |           |
       |           | recv R     +--------+   recv R   |           |
       | send R /  ‘----------->|        |<-----------’  send R / |
       | recv R                 | closed |               recv R   |
       ‘----------------------->|        |<----------------------’
                                +--------+
          send:   endpoint sends this frame
          recv:   endpoint receives this frame
          H:  HEADERS frame (with implied CONTINUATIONs)
          PP: PUSH_PROMISE frame (with implied CONTINUATIONs)
          ES: END_STREAM flag
          R:  RST_STREAM frame
*/
enum internal_stream_event {
    HTTP2_STREAM_EVENT_HEADERS_R = 0,
    HTTP2_STREAM_EVENT_HEADERS_S = 1,
    HTTP2_STREAM_EVENT_PP_R = 2,  // PUSH_PROMISE
    HTTP2_STREAM_EVENT_PP_S = 3,  // PUSH_PROMISE
    HTTP2_STREAM_EVENT_ES_R = 4,  // END_STREAM
    HTTP2_STREAM_EVENT_ES_S = 5,
    HTTP2_STREAM_EVENT_RST_R = 6,  // RST_STREAM
    HTTP2_STREAM_EVENT_RST_S = 7,  // RST_STREAM
};

const http2_stream::status event_status_table[8][7] = {
    {http2_stream::OPEN, http2_stream::IDLE, http2_stream::HALF_CLOSED_LOCAL, http2_stream::IDLE, http2_stream::IDLE,
     http2_stream::IDLE, http2_stream::IDLE},
    {http2_stream::OPEN, http2_stream::HALF_CLOSED_REMOTE, http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE,
     http2_stream::IDLE, http2_stream::IDLE},
    {http2_stream::RESERVED_REMOTE, http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE,
     http2_stream::IDLE, http2_stream::IDLE},
    {http2_stream::RESERVED_LOCAL, http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE,
     http2_stream::IDLE, http2_stream::IDLE},
    {http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE, http2_stream::HALF_CLOSED_REMOTE, http2_stream::CLOSED,
     http2_stream::IDLE, http2_stream::IDLE},
    {http2_stream::IDLE, http2_stream::IDLE, http2_stream::IDLE, http2_stream::HALF_CLOSED_LOCAL, http2_stream::IDLE,
     http2_stream::CLOSED, http2_stream::IDLE},
    {http2_stream::IDLE, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED,
     http2_stream::CLOSED, http2_stream::IDLE},
    {http2_stream::IDLE, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED,
     http2_stream::CLOSED, http2_stream::IDLE},
};

http2_stream::status get_next_status(internal_stream_event event, http2_stream::status cur_status) {
    return event_status_table[event][cur_status] != http2_stream::IDLE ? event_status_table[event][cur_status]
                                                                       : cur_status;
}

void http2_stream::send_pp() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_PP_S, _cur_status);
}

void http2_stream::recv_pp() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_PP_R, _cur_status);
}

void http2_stream::send_h() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_HEADERS_S, _cur_status);
}

void http2_stream::recv_h() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_HEADERS_R, _cur_status);
}

void http2_stream::send_r() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_RST_S, _cur_status);
}

void http2_stream::recv_r() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_RST_R, _cur_status);
}

void http2_stream::send_es() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_ES_S, _cur_status);
}

void http2_stream::recv_es() {
    _cur_status = get_next_status(HTTP2_STREAM_EVENT_ES_R, _cur_status);
}
