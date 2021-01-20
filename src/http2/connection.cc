#include "src/http2/connection.h"
#include "src/http2/settings.h"
#include "src/http2/stream.h"
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"
#include "src/hpack/hpack.h"

constexpr uint32_t MAX_STREAM_ID = (1 << 31) - 1;

http2_connection::http2_connection(uint64_t cid, bool client) {
    _cid = cid;
    _client = client;
    _handshake = client;

    // create control stream.
    std::shared_ptr<http2_stream> stream = std::make_shared<http2_stream>(0, this);
    _streams.insert(std::make_pair(0, stream));
}

uint32_t http2_connection::create_stream() {
    std::shared_ptr<http2_stream> stream;
    if (_client) {
        if (_client_max_stream_id + 2 >= MAX_STREAM_ID) {
            return 0;
        }
        stream = std::make_shared<http2_stream>(_client_max_stream_id, this);
        _client_max_stream_id += 2;
    } else {
        if (_server_max_stream_id + 2 >= MAX_STREAM_ID) {
            return 0;
        }
        stream = std::make_shared<http2_stream>(_server_max_stream_id, this);
        _server_max_stream_id += 2;
    }
    _streams.insert(std::make_pair(stream->stream_id(), stream));
    return stream->stream_id();
}

std::shared_ptr<http2_stream> http2_connection::find_stream(uint32_t sid) {
    auto it = _streams.find(sid);
    if (it != _streams.end()) {
        return it->second;
    }
    return nullptr;
}

http2_connection::~http2_connection() {}

bool http2_connection::is_handshake() {
    return _handshake;
}

void http2_connection::handshake_done() {
    _handshake = true;
}

int http2_connection::package_process(const uint8_t *package, uint32_t package_length) {
    if (package_length < HTTP2_FRAME_HEADER_SIZE) {
        send_goaway(HTTP2_INTERNAL_ERROR);
        return;
    }

    http2_frame_header hdr;
    http2_frame_header_unpack(&hdr, package);
    if (package_length - HTTP2_FRAME_HEADER_SIZE < hdr.length) {
        send_goaway(HTTP2_INTERNAL_ERROR);
        return;
    }

    std::shared_ptr<http2_stream> stream;
    if (hdr.stream_id > 0) {
        stream = find_stream(hdr.stream_id);
    }

    http2_frame frame;
    frame.hdr = hdr;

    frame_parser parser;
    parser.frame = &frame;
    parser.error_code = HTTP2_NO_ERROR;
    parser.input = package + HTTP2_FRAME_HEADER_SIZE;
    parser.input_size = hdr.length;
    parser.first_frame = !stream;

    if (stream) {
        parser.prev_type = stream->frame_type();
        parser.prev_flags = stream->frame_flags();
    }

    int r = http2_package_parse(&parser);
    if (parser.error_code != HTTP2_NO_ERROR) {
        send_goaway(parser.error_code);
        return r;
    }

    switch (frame.hdr.type) {
    case HTTP2_FRAME_DATA:
        received_data(stream, &frame);
        break;
    case HTTP2_FRAME_HEADERS:  // open stream
        received_header(stream, &frame);
        break;
    case HTTP2_FRAME_PRIORITY:
        received_priority(stream, &frame);
        break;
    case HTTP2_FRAME_RST_STREAM:  // close stream
        received_rst_stream(&frame);
        break;
    case HTTP2_FRAME_SETTINGS:  // update settings
        received_settings(&frame);
        break;
    case HTTP2_FRAME_PUSH_PROMISE:
        received_push_promise(&frame);
        break;
    case HTTP2_FRAME_PING:  //
        received_ping(&frame);
        break;
    case HTTP2_FRAME_GOAWAY:
        received_goaway(&frame);
        break;
    case HTTP2_FRAME_WINDOW_UPDATE:
        received_window_update(&frame);
        break;
    case HTTP2_FRAME_CONTINUATION:
        received_continuation();
        break;
    default:
        r = HTTP2_PROTOCOL_ERROR;
        break;
    }

    if (stream) {
        stream->frame_type(frame.hdr.type);
        stream->frame_flags(frame.hdr.flags);
    }

    return r;
}

void http2_connection::received_header(std::shared_ptr<http2_stream> stream, http2_frame *frame) {

    if (!stream) {
        std::shared_ptr<http2_stream> str = std::make_shared<http2_stream>(_cid, frame->hdr.stream_id);
        _streams.insert({frame->hdr.stream_id, str});
        stream = str;
    }

    std::vector<hpack::mdelem_data> decoded_headers;
    int err = hpack::decode_headers(frame->headers.header_block_fragment.data(),
                                    frame->headers.header_block_fragment.size(), &_dynamic_table, &decoded_headers);

    if (err != HTTP2_NO_ERROR) {
        send_goaway(err, _max_stream_id);
        return;
    }

    // stream->received_headers(frame);
}

std::shared_ptr<http2_stream> http2_connection::find_stream(uint32_t stream_id) {
    auto it = _streams.find(stream_id);
    if (it == _streams.end()) {
        return nullptr;
    }
    return it->second;
}

void http2_connection::async_send_reply(std::shared_ptr<http2::RpcResponse> rsp) {
    // TODO(SHADOW):
}

void http2_connection::received_settings(http2_frame *frame) {
    if (frame->hdr.flags & HTTP2_FLAG_ACK) {
        return;
    }

    for (size_t i = 0; i < frame->settings.settings.size(); i++) {
        auto settings = frame->settings.settings[i];
        http2_setting_id sid;
        if (wire_id_to_setting_id(settings.id, &sid)) {
            _remote_settings[sid] = settings.value;
        }
    }

    http2_frame_settings ack = build_http2_frame_settings_ack();
    // send settings ack
}

void http2_connection::received_ping(http2_frame *frame) {
    if (frame->hdr.flags & HTTP2_FLAG_ACK) {
        return;
    }

    http2_frame_ping ack = build_http2_frame_ping(frame->ping.opaque_data, true);
    // send ping ack
}

void http2_connection::received_goaway(http2_frame *frame) {
    _goaway_stream_id = frame->goaway.last_stream_id;
    _goaway_error_code = frame->goaway.error_code;
    _received_goaway = true;
}

void http2_connection::received_window_update(http2_frame *frame) {
    // if (!stream) {
    //}
}

void http2_connection::received_data(std::shared_ptr<http2_stream> stream, http2_frame *frame) {
    if (stream) stream->push_data(frame->data.data);
}

void http2_connection::received_priority(http2_frame *frame) {
    // do nothing
}

void http2_connection::received_rst_stream(std::shared_ptr<http2_stream> stream, http2_frame *frame) {
    if (!stream) {
        return;
    }
    stream->recv_rst_stream();
    if (stream->is_closed()) {
        _streams.erase(stream->stream_id());
    }
}

void http2_connection::received_push_promise(std::shared_ptr<http2_stream> stream, http2_frame *frame) {
    //
}

void http2_connection::received_continuation(std::shared_ptr<http2_stream> stream, http2_frame *frame) {
    //
}
