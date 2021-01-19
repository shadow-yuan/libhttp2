#include "src/http2/stream.h"
#include "src/http2/errors.h"

const http2_stream::internal_stream_frame_func http2_stream::frame_funcs[] = {
    {HTTP2_FRAME_DATA, frame_data},
    {HTTP2_FRAME_HEADERS, frame_header},
    {HTTP2_FRAME_PRIORITY, frame_priority},
    {HTTP2_FRAME_RST_STREAM, frame_rst_stream},
    {HTTP2_FRAME_PUSH_PROMISE, frame_push_promise},
    {HTTP2_FRAME_PING, frame_ping},
    {HTTP2_FRAME_CONTINUATION, frame_continuation},
};

http2_stream::http2_stream(uint32_t sid, http2_connection *conn) {
    _sid = sid;
    _conn = conn;
    _flow_max = 0xffff;
}

http2_errors http2_stream::frame_arrived(http2_frame *frame) {
    if (frame == nullptr || frame->head.stream_id != _sid) {
        return HTTP2_NO_ERROR;
    }

    for (size_t i = 0; i < sizeof(frame_funcs) / sizeof(internal_stream_frame_func); i++) {
        if (frame_funcs[i].type == frame->head.type) {
            return frame_funcs[i].func(frame);
        }
    }
    return HTTP2_PROTOCOL_ERROR;
}

http2_errors http2_stream::frame_data(http2_frame *frame) {
    if (is_control_stream()) {
        return HTTP2_PROTOCOL_ERROR;
    }
    if (frame->head.flag & HTTP2_FLAG_END_STREAM) {
        _stream_status.handle_status(HTTP2_STREAM_EVENT_ES_R);
    }
    return HTTP2_NO_ERROR;
}

http2_errors http2_stream::frame_header(http2_frame *frame) {
    if (frame->head.flag & HTTP2_FLAG_END_HEADERS) {
    }
    if (frame->head.flag & HTTP2_FLAG_END_STREAM) {
        _stream_status.handle_status(HTTP2_STREAM_EVENT_ES_R);
    }

    if (_stream_status.handle_status(HTTP2_STREAM_EVENT_HEADERS_R)) {
    }
    return HTTP2_NO_ERROR;
}

http2_errors http2_stream::frame_priority(http2_frame *frame) {
    return HTTP2_NO_ERROR;
}

http2_errors http2_stream::frame_rst_stream(http2_frame *frame) {
    if (is_control_stream()) {
        return HTTP2_PROTOCOL_ERROR;
    }
    if (!_stream_status.handle_status(HTTP2_STREAM_EVENT_RST_R)) {
        return HTTP2_PROTOCOL_ERROR;
    }
    return HTTP2_NO_ERROR;
}

http2_errors http2_stream::frame_push_promise(http2_frame *frame) {
    _stream_status.handle_status(HTTP2_STREAM_EVENT_PP_R);
    return HTTP2_NO_ERROR;
}

http2_errors http2_stream::frame_ping(http2_frame *frame) {
    return HTTP2_NO_ERROR;
}

http2_errors http2_stream::frame_continuation(http2_frame *frame) {
    return HTTP2_NO_ERROR;
}
