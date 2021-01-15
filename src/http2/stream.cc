#include "src/http2/stream.h"

http2_stream::http2_stream(uint32_t sid, http2_connection *conn) {
    _sid = sid;
    _conn = conn;
    _flow_max = 0xffff;
}
bool http2_stream::frame_arrived(http2_frame *frame) {
    if (frame == nullptr || frame->head.stream_id != _sid) {
        return false;
    }

    return true;
}
