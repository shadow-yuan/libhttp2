#include "src/http2/connection.h"
#include "src/http2/settings.h"
#include "src/http2/stream.h"
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"
#include "src/hpack/hpack.h"
#include "src/http2/flow_control.h"
#include "src/utils/log.h"
#include "src/http2/pack.h"

http2_connection::http2_connection(http2::TcpSendService *sender, uint64_t cid, bool client_side)
    : _dynamic_table(g_http2_settings_parameters[HTTP2_SETTINGS_HEADER_TABLE_SIZE].default_value) {
    _sender_service = sender;
    _connection_id = cid;
    _client_side = client_side;

    for (size_t i = 0; i < HTTP2_NUMBER_OF_SETTINGS; i++) {
        _local_settings[i] = g_http2_settings_parameters[i].default_value;
        _remote_settings[i] = g_http2_settings_parameters[i].default_value;
    }

    _local_settings[HTTP2_SETTINGS_INITIAL_WINDOW_SIZE] = INITIAL_WINDOW_SIZE;
    _local_settings[HTTP2_SETTINGS_MAX_FRAME_SIZE] = MAX_FRAME_SIZE;
    _local_settings[HTTP2_SETTINGS_MAX_HEADER_LIST_SIZE] = MAX_HEADER_LIST_SIZE;
    _local_settings[HTTP2_SETTINGS_GRPC_ALLOW_TRUE_BINARY_METADATA] = GRPC_ALLOW_TRUE_BINARY_METADATA;

    if (client_side) {
        _local_settings[HTTP2_SETTINGS_ENABLE_PUSH] = 0;
        _local_settings[HTTP2_SETTINGS_MAX_CONCURRENT_STREAMS] = 0;
        _sender_service->SendTcpData(cid, PREFACE, PREFACE_SIZE);
        _finish_handshake = true;
        _next_stream_id = 1;
    } else {
        _finish_handshake = false;
        _next_stream_id = 2;
    }
    _last_stream_id = 0;

    // TODO(SHADOW): send settings window_update
}

http2_connection::~http2_connection() {}

uint32_t http2_connection::create_stream() {
    if (_next_stream_id >= http2_stream::MAX_STREAM_ID) {
        return 0;
    }
    auto stream = std::make_shared<http2_stream>(_next_stream_id, this);
    _streams[_next_stream_id] = stream;
    _next_stream_id += 2;
    return stream->stream_id();
}

std::shared_ptr<http2_stream> http2_connection::find_stream(uint32_t stream_id) {
    auto it = _streams.find(stream_id);
    if (it == _streams.end()) {
        return nullptr;
    }
    return it->second;
}

uint64_t http2_connection::connection_id() const {
    return _connection_id;
}

bool http2_connection::need_verify_preface() {
    return !_finish_handshake;
}

void http2_connection::verify_preface_done() {
    _finish_handshake = true;
}

void http2_connection::send_goaway(uint32_t error_code, uint32_t last_stream_id) {
    if (last_stream_id == 0) {
        last_stream_id = _last_stream_id;
    }
    http2_frame_goaway frame = build_http2_frame_goaway(error_code, last_stream_id);
    slice s = pack_http2_frame_goaway(&frame);
    send_tcp_data(s);
}

void http2_connection::async_send_reply(std::shared_ptr<http2::RpcResponse> rsp) {
    // TODO(SHADOW):
}

uint32_t http2_connection::local_max_frame_size() {
    return _local_settings[HTTP2_SETTINGS_MAX_FRAME_SIZE];
}

int http2_connection::package_process(const uint8_t *package, uint32_t package_length) {
    if (package_length < HTTP2_FRAME_HEADER_SIZE) {
        log_error("process http2 package, but length(%u) < HTTP2_FRAME_HEADER_SIZE(9)", package_length);
        abort();
        return;
    }

    http2_frame_hdr hdr;
    http2_frame_header_unpack(&hdr, package);
    if (package_length < hdr.length + HTTP2_FRAME_HEADER_SIZE) {
        log_error("process http2 package, but the payload is incomplete. package length(%u) < need(%u)", package_length,
                  hdr.length + HTTP2_FRAME_HEADER_SIZE);
        abort();
        return;
    }

    uint32_t max_frame_size = local_max_frame_size();
    if (hdr.length > max_frame_size) {
        log_error("process http2 package, but length(%u) exceeds the maximum frame size limit(%u)", package_length,
                  max_frame_size);
        send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return -1;
    }

    http2_frame frame;
    int ret = parse_http2_package(&frame, package + HTTP2_FRAME_HEADER_SIZE, &hdr);
    if (ret != HTTP2_NO_ERROR) {
        send_goaway(ret);
        return ret;
    }

    // record last stream id
    if (hdr.stream_id > _last_stream_id) {
        _last_stream_id = hdr.stream_id;
    }

    std::shared_ptr<http2_stream> stream;
    if (hdr.stream_id > 0) {
        stream = find_stream(hdr.stream_id);
    }

    switch (hdr.type) {
    case HTTP2_FRAME_DATA:
        received_data(stream, reinterpret_cast<http2_frame_data *>(&frame.data));
        break;
    case HTTP2_FRAME_HEADERS:  // open stream
        received_header(stream, reinterpret_cast<http2_frame_headers *>(&frame.headers));
        break;
    case HTTP2_FRAME_PRIORITY:
        received_priority(stream, reinterpret_cast<http2_frame_priority *>(&frame.priority));
        break;
    case HTTP2_FRAME_RST_STREAM:  // close stream
        received_rst_stream(stream, reinterpret_cast<http2_frame_rst_stream *>(&frame.rst_stream));
        break;
    case HTTP2_FRAME_SETTINGS:  // update settings
        received_settings(reinterpret_cast<http2_frame_settings *>(&frame.settings));
        break;
    case HTTP2_FRAME_PUSH_PROMISE:
        received_push_promise(stream, reinterpret_cast<http2_frame_push_promise *>(&frame.promise));
        break;
    case HTTP2_FRAME_PING:  //
        received_ping(reinterpret_cast<http2_frame_ping *>(&frame.ping));
        break;
    case HTTP2_FRAME_GOAWAY:
        received_goaway(reinterpret_cast<http2_frame_goaway *>(&frame.goaway));
        break;
    case HTTP2_FRAME_WINDOW_UPDATE:
        received_window_update(stream, reinterpret_cast<http2_frame_window_update *>(&frame.window_update));
        break;
    case HTTP2_FRAME_CONTINUATION:
        received_continuation(stream, reinterpret_cast<http2_frame_continuation *>(&frame.continuation));
        break;
    default:
        ret = HTTP2_PROTOCOL_ERROR;
        break;
    }

    if (stream) {  // record type & flags
        stream->frame_type(hdr.type);
        stream->frame_flags(hdr.flags);

        if (stream->is_closed()) {
            _streams.erase(stream->stream_id());
        }
    }
    return ret;
}

void http2_connection::received_data(std::shared_ptr<http2_stream> &stream, http2_frame_data *frame) {
    if (frame->pad_len >= frame->hdr.length) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    if (frame->data.empty()) return;
    if (stream) {
        stream->push_data(frame->data);
    }
    // TODO(SHADOW): flow-control counter
}

void http2_connection::received_header(std::shared_ptr<http2_stream> &stream, http2_frame_headers *frame) {
    if (frame->hdr.stream_id == 0) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    if (frame->pad_len >= frame->hdr.length) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }
    if (!stream) {
        stream = std::make_shared<http2_stream>(_connection_id, frame->hdr.stream_id);
        _streams[frame->hdr.stream_id] = stream;
    }

    slice headers = frame->header_block_fragment;
    std::vector<hpack::mdelem_data> decoded_headers;
    int err = hpack::decode_headers(headers.data(), headers.size(), &_dynamic_table, &decoded_headers);
    if (err != HTTP2_NO_ERROR) {
        send_goaway(err);
        return;
    }

    stream->recv_headers(decoded_headers);
}

void http2_connection::received_priority(std::shared_ptr<http2_stream> &stream, http2_frame_priority *frame) {
    if (frame->hdr.length != 5) {
        send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return;
    }
    if (frame->hdr.stream_id == 0) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    if (stream) {
        stream->set_weight(frame->pspec.weight);
    }
}

void http2_connection::received_rst_stream(std::shared_ptr<http2_stream> &stream, http2_frame_rst_stream *frame) {
    if (frame->hdr.length != 4) {
        send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return;
    }

    if (stream) {
        stream->recv_rst_stream(frame->error_code);
    }
}

void http2_connection::received_settings(http2_frame_settings *frame) {
    if (frame->hdr.flags & HTTP2_FLAG_ACK) {
        if (frame->hdr.length != 0) {
            send_goaway(HTTP2_FRAME_SIZE_ERROR);
            return;
        }
        return;
    }

    if (frame->hdr.length % 6) {
        send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return;
    }
    if (frame->hdr.stream_id) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    for (size_t i = 0; i < frame->settings.size(); i++) {
        auto settings = frame->settings[i];
        http2_setting_id sid;
        if (!wire_id_to_setting_id(settings.id, &sid)) {
            // skip
            continue;
        }
        _remote_settings[sid] = settings.value;
    }

    http2_frame_settings ack = build_http2_frame_settings_ack();
    slice s = pack_http2_frame_settings(&ack);
    send_tcp_data(s);
}

void http2_connection::received_push_promise(std::shared_ptr<http2_stream> &stream, http2_frame_push_promise *frame) {
    if (frame->pad_len >= frame->hdr.length) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }
    if (frame->promised_stream_id == 0) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    if (!_local_settings[HTTP2_SETTINGS_ENABLE_PUSH]) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    auto promise_stream = find_stream(frame->promised_stream_id);
    if (!promise_stream) {
        promise_stream = std::make_shared<http2_stream>(frame->promised_stream_id);
    } else if (promise_stream->get_status() != http2_stream::IDLE) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    if (!(frame->hdr.flags & HTTP2_FLAG_END_HEADERS)) {
        _next_frame_limit = true;
        _next_frame_stream_id = frame->promised_stream_id;
    }

    promise_stream->recv_push_promise();

    std::vector<hpack::mdelem_data> decoded_headers;
    slice headers = frame->header_block_fragment;
    int ret = hpack::decode_headers(headers.data(), headers.size(), &_dynamic_table, &decoded_headers);
    if (ret != HTTP2_NO_ERROR) {
        send_goaway(ret);
        return;
    }
    if (!decoded_headers.empty()) {
        promise_stream->push_headers(decoded_headers);
    }
}

void http2_connection::received_ping(http2_frame_ping *frame) {
    if (frame->hdr.flags & HTTP2_FLAG_ACK) {
        return;
    }
    if (frame->hdr.length != 8) {
        send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return;
    }
    if (frame->hdr.stream_id) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    http2_frame_ping ack = build_http2_frame_ping(frame->opaque_data, true);
    slice s = pack_http2_frame_ping(&ack);
    send_tcp_data(s);
}

void http2_connection::received_goaway(http2_frame_goaway *frame) {
    if (frame->hdr.stream_id) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }
    _goaway_stream_id = frame->last_stream_id;
    _received_goaway = true;
    // _goaway_stream_id之前的包全部要停止
}

void http2_connection::received_window_update(std::shared_ptr<http2_stream> &stream, http2_frame_window_update *frame) {
    if (frame->hdr.length != 4) {
        send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return;
    }
    if (frame->window_size_inc < 1 || frame->window_size_inc > 2147483647) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }

    // TODO(SHADOW): flow-control
    if (!stream) {  // for connection
        _remote_window_size = frame->window_size_inc;
    } else {  // for stream
        stream->set_window_size(frame->window_size_inc);
    }
}

void http2_connection::received_continuation(std::shared_ptr<http2_stream> &stream, http2_frame_continuation *frame) {
    if (!_next_frame_limit) {
        send_goaway(HTTP2_PROTOCOL_ERROR);
        return;
    }
    slice headers = frame->header_block_fragment;
    std::vector<hpack::mdelem_data> decoded_headers;
    int ret = hpack::decode_headers(headers.data(), headers.size(), &_dynamic_table, &decoded_headers);
    if (ret != HTTP2_NO_ERROR) {
        send_goaway(ret);
        return;
    }
    if (stream) {
        stream->push_headers(decoded_headers);
    }
}

void http2_connection::send_tcp_data(slice_buffer &sb) {
    while (!sb.empty()) {
        const slice &s = sb.front();
        _sender_service->SendTcpData(_connection_id, s.data(), s.size());
        sb.pop_front();
    }
}

void http2_connection::send_tcp_data(slice s) {
    _sender_service->SendTcpData(_connection_id, s.data(), s.size());
}
