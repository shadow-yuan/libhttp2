#include "src/http2/stream_status.h"

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

const http2_stream_status_fsm::fsm_table http2_stream_status_fsm::_fsm_table[] = {
    {HTTP2_STREAM_EVENT_HEADERS_R, HTTP2_STREAM_IDLE, HTTP2_STREAM_OPEN},
    {HTTP2_STREAM_EVENT_HEADERS_S, HTTP2_STREAM_IDLE, HTTP2_STREAM_OPEN},
    {HTTP2_STREAM_EVENT_HEADERS_R, HTTP2_STREAM_RESERVED_REMOTE, HTTP2_STREAN_HALF_LOCAL},
    {HTTP2_STREAM_EVENT_HEADERS_S, HTTP2_STREAM_RESERVED_LOCAL, HTTP2_STREAM_HALF_REMOTE},
    {HTTP2_STREAM_EVENT_PP_R, HTTP2_STREAM_IDLE, HTTP2_STREAM_RESERVED_REMOTE},
    {HTTP2_STREAM_EVENT_PP_S, HTTP2_STREAM_IDLE, HTTP2_STREAM_RESERVED_LOCAL},
    {HTTP2_STREAM_EVENT_ES_R, HTTP2_STREAM_OPEN, HTTP2_STREAM_HALF_REMOTE},
    {HTTP2_STREAM_EVENT_ES_S, HTTP2_STREAM_OPEN, HTTP2_STREAN_HALF_LOCAL},
    {HTTP2_STREAM_EVENT_ES_R, HTTP2_STREAN_HALF_LOCAL, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_ES_S, HTTP2_STREAM_HALF_REMOTE, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_R, HTTP2_STREAM_OPEN, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_S, HTTP2_STREAM_OPEN, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_R, HTTP2_STREAM_RESERVED_REMOTE, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_S, HTTP2_STREAM_RESERVED_LOCAL, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_R, HTTP2_STREAM_RESERVED_LOCAL, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_S, HTTP2_STREAM_RESERVED_REMOTE, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_R, HTTP2_STREAN_HALF_LOCAL, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_S, HTTP2_STREAM_HALF_REMOTE, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_R, HTTP2_STREAM_HALF_REMOTE, HTTP2_STREAM_CLOSED},
    {HTTP2_STREAM_EVENT_RST_S, HTTP2_STREAN_HALF_LOCAL, HTTP2_STREAM_CLOSED},
};

const size_t http2_stream_status_fsm::_fsm_table_size =
    sizeof(http2_stream_status_fsm::_fsm_table) / sizeof(http2_stream_status_fsm::fsm_table);

http2_stream_status_fsm::http2_stream_status_fsm() {
    _cur_status = HTTP2_STREAM_IDLE;
}

bool http2_stream_status_fsm::handle_status(http2_stream_event event) {
    for (size_t i = 0; i < _fsm_table_size; i++) {
        if (event == _fsm_table[i].event && _cur_status == _fsm_table->cur_status) {
            _cur_status = _fsm_table[i].next_status;
            return true;
        }
    }

    return false;
}
