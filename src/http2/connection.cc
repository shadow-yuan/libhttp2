#include "src/http2/connection.h"
#include "src/http2/settings.h"
#include "src/http2/stream.h"

http2_connection::http2_connection(uint64_t cid) {
    _cid = cid;
    _client_max_id = 1;
    _server_max_id = 2;

    // create control stream.
    std::shared_ptr<http2_stream> stream = std::make_shared<http2_stream>(0, this);
    _streams.insert(std::make_pair(0, stream));
}

uint32_t http2_connection::create_stream(bool client) {
    std::shared_ptr<http2_stream> stream;
    if (client) {
        if (_client_max_id + 2 >= 1 << 31) {
            return 0;
        }
        stream = std::make_shared<http2_stream>(_client_max_id, this);
        _client_max_id += 2;
    } else {
        if (_server_max_id + 2 > 1 << 31) {
            return 0;
        }
        stream = std::make_shared<http2_stream>(_server_max_id, this);
        _server_max_id += 2;
    }
    _streams.insert(std::make_pair(stream->get_sid(), stream));
    return stream->get_sid();
}

std::shared_ptr<http2_stream> http2_connection::get_stream(uint32_t sid) {
    auto it = _streams.find(sid);
    if (it != _streams.end()) {
        return it->second;
    }
    return nullptr;
}

http2_errors http2_connection::execute_setting(http2_frame *frame) {
    uint32_t stream_id = frame->head.stream_id;
    rm_head_bit(stream_id);
    if (stream_id != 0) {
        return HTTP2_PROTOCOL_ERROR;
    }
    return _settings.excute_frame(frame);
}

http2_errors http2_connection::execute_goaway(http2_frame *frame) {
    return HTTP2_NO_ERROR;
}
http2_errors http2_connection::frame_arrived(http2_frame *frame) {
    if (frame == nullptr) {
        return HTTP2_NO_ERROR;
    }

    switch (frame->head.type) {
    case HTTP2_FRAME_SETTINGS: {
        return execute_setting(frame);
    } break;
    case HTTP2_FRAME_GOAWAY: {

    } break;
    }

    uint32_t stream_id = frame->head.stream_id;
    rm_head_bit(stream_id);
    std::shared_ptr<http2_stream> stream = get_stream(stream_id);
    if (stream != nullptr) {
        return stream->frame_arrived(frame);
    }

    return HTTP2_PROTOCOL_ERROR;
}
