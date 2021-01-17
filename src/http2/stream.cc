#include "src/http2/stream.h"
#include "src/http2/errors.h"

http2_stream::http2_stream(uint32_t sid, http2_connection *conn) {
    _sid = sid;
    _conn = conn;
    _flow_max = 0xffff;
}
bool http2_stream::frame_arrived(http2_frame *frame) {
    if (frame == nullptr || frame->head.stream_id != _sid) {
        return false;
    }

    switch (frame->head.type) {
    case HTTP2_FRAME_DATA: {
        return stream_data(frame);
    } break;
    case HTTP2_FRAME_RST_STREAM: {
    }
    }
    return false;
}

bool http2_stream::frame_data(http2_frame *frame) {
    if (is_control_stream()) {
        // TODO HTTP2_PROTOCOL_ERROR.
        return false;
    }
    if (frame->head.flag & HTTP2_FLAG_END_STREAM) {
        // TODO close this stream.
    }
    return true;
}

bool http2_stream::frame_header(http2_frame *frame) {
    return true;
}

bool http2_stream::frame_priority(http2_frame *frame) {
    return true;
}

bool http2_stream::frame_rst_stream(http2_frame *frame) {
    if (is_control_stream() || get_stream_status() == HTTP2_STREAM_IDLE) {
        // TODO HTTP2_PROTOCOL_ERROR;
        return false;
    }
    // TODO HTTP2_NO_ERROR;
    return true;
}

bool http2_stream::frame_setting(http2_frame *frame) {
    return true;
}

bool http2_stream::frame_push_promise(http2_frame *frame) {
    return true;
}

bool http2_stream::frame_ping(http2_frame *frame) {
    return true;
}

bool http2_stream::frame_goaway(http2_frame *frame) {
    return true;
}

bool http2_stream::frame_window_update(http2_frame *frame) {
    retruen true;
}

bool http2_stream::frame_continuation(http2_frame *frame) {
    return true;
}
