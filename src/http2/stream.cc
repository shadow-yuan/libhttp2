
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

#include "src/http2/stream.h"
#include "src/http2/frame.h"

enum http2_stream_event {
    STREAM_EVENT_H_R = 0,  // HEADERS Frame recv
    STREAM_EVENT_H_S,      // HEADERS Frame send
    STREAM_EVENT_PP_R,     // PUSH_PROMISE
    STREAM_EVENT_PP_S,     // PUSH_PROMISE
    STREAM_EVENT_ES_R,     // END_STREAM Recv
    STREAM_EVENT_ES_S,     // END_STREAM Send
    STREAM_EVENT_RST_R,    // RST_STREAM
    STREAM_EVENT_RST_S,    // RST_STREAM

    _STREAM_EVENT_COUNTER
};

const http2_stream::state
    event_status_table[static_cast<int>(_STREAM_EVENT_COUNTER)][static_cast<int>(http2_stream::ERROR)] = {
        {http2_stream::OPEN, http2_stream::ERROR, http2_stream::HALF_CLOSED_LOCAL, http2_stream::ERROR,
         http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR},
        {http2_stream::OPEN, http2_stream::HALF_CLOSED_REMOTE, http2_stream::ERROR, http2_stream::ERROR,
         http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR},
        {http2_stream::RESERVED_REMOTE, http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR,
         http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR},
        {http2_stream::RESERVED_LOCAL, http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR,
         http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR},
        {http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR, http2_stream::HALF_CLOSED_REMOTE,
         http2_stream::CLOSED, http2_stream::ERROR, http2_stream::ERROR},
        {http2_stream::ERROR, http2_stream::ERROR, http2_stream::ERROR, http2_stream::HALF_CLOSED_LOCAL,
         http2_stream::ERROR, http2_stream::CLOSED, http2_stream::ERROR},
        {http2_stream::ERROR, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED,
         http2_stream::CLOSED, http2_stream::ERROR},
        {http2_stream::ERROR, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED, http2_stream::CLOSED,
         http2_stream::CLOSED, http2_stream::ERROR},
};

http2_stream::state get_next_status(http2_stream_event event, http2_stream::state status) {
    return event_status_table[event][status];
}

void http2_stream::send_push_promise() {
    _state = get_next_status(STREAM_EVENT_PP_S, _state);
}

void http2_stream::recv_push_promise() {
    _state = get_next_status(STREAM_EVENT_PP_R, _state);
}

void http2_stream::send_headers() {
    _state = get_next_status(STREAM_EVENT_H_S, _state);
}

void http2_stream::recv_headers(const std::vector<hpack::mdelem_data> &headers) {
    _state = get_next_status(STREAM_EVENT_H_R, _state);
}

void http2_stream::send_rst_stream() {
    _state = get_next_status(STREAM_EVENT_RST_S, _state);
}

void http2_stream::recv_rst_stream(uint32_t error_code) {
    _state = get_next_status(STREAM_EVENT_RST_R, _state);
}

void http2_stream::send_end_stream() {
    _state = get_next_status(STREAM_EVENT_ES_S, _state);
}

void http2_stream::recv_end_stream() {
    _state = get_next_status(STREAM_EVENT_ES_R, _state);
}

// ---------------------------------

http2_stream::http2_stream(ConnectionFlowControl *cfc, uint32_t stream_id)
    : _sfc(stream_id, cfc)
    , _stream_id(stream_id)
    , _connection_id(cfc->ConnectionId())
    , _state(IDLE) {}

uint8_t http2_stream::frame_type() {
    return _frame_type;
}

uint8_t http2_stream::frame_flags() {
    return _frame_flags;
}

void http2_stream::frame_type(uint8_t type) {
    _frame_type = type;
}

void http2_stream::frame_flags(uint8_t flags) {
    _frame_flags = flags;

    if (flags & HTTP2_FLAG_END_HEADERS) {
        _finish_header = true;
    }

    if (flags & HTTP2_FLAG_END_STREAM) {
        recv_end_stream();
    }
}

void http2_stream::push_headers(const std::vector<hpack::mdelem_data> &headers) {
    for (size_t i = 0; i < headers.size(); i++) {
        _headers.emplace_back(headers[i]);
    }
}

void http2_stream::push_data(slice s) {
    slice obj(s.data(), s.size());
    _data_cache.add_slice(obj);
}
