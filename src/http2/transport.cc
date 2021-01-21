#include "src/http2/transport.h"
#include <string.h>
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"
#include "src/http2/connection.h"
#include "src/http2/settings.h"

http2_transport::http2_transport(http2::TcpSendService *sender)
    : _tcp_sender(sender)
    , _call_service(nullptr) {}

http2_transport::~http2_transport() {}

void http2_transport::set_rpc_call_service(http2::RpcCallService *service) {
    _call_service = service;
}

void http2_transport::async_send_reply(std::shared_ptr<http2::RpcResponse> rsp) {
    // TODO(SHADOW)
}

size_t http2_transport::get_max_header_size() {
    return HTTP2_FRAME_HEADER_SIZE;
}

int http2_transport::check_package_length(uint64_t cid, const void *data, size_t len) {
    if (len < HTTP2_FRAME_HEADER_SIZE) return 0;

    auto conn = find_connection(cid);
    if (!conn) return -1;

    if (conn->need_verify_preface() && memcmp(data, http2_connection::PREFACE, 9) == 0) {
        return http2_connection::PREFACE_SIZE;
    }

    http2_frame_hdr hdr;
    http2_frame_header_unpack(&hdr, static_cast<const uint8_t *>(data));
    if (hdr.length > 0 && hdr.length > conn->local_max_frame_size()) {
        conn->send_goaway(HTTP2_FRAME_SIZE_ERROR);
        return -1;
    }
    return hdr.length + HTTP2_FRAME_HEADER_SIZE;
}

void http2_transport::connection_enter(uint64_t cid, bool client_side) {
    _connections[cid] = std::make_shared<http2_connection>(_tcp_sender, cid, client_side);
}

void http2_transport::received_data(uint16_t cid, const void *buf, size_t len) {
    auto conn = find_connection(cid);
    if (!conn) return;

    const uint8_t *package = reinterpret_cast<const uint8_t *>(buf);
    size_t package_length = len;

    if (conn->need_verify_preface()) {
        if (package_length != http2_connection::PREFACE_SIZE ||
            memcmp(package, http2_connection::PREFACE, http2_connection::PREFACE_SIZE) != 0) {
            conn->send_goaway(HTTP2_PROTOCOL_ERROR);
            return;
        }
        conn->verify_preface_done();
        package_length -= http2_connection::PREFACE_SIZE;
        package += http2_connection::PREFACE_SIZE;
    }

    if (package_length > 0) {
        conn->package_process(package, package_length);
    }
}

void http2_transport::connection_leave(uint64_t cid) {
    _connections.erase(cid);
}

std::shared_ptr<http2_connection> http2_transport::find_connection(uint64_t cid) {
    std::unique_lock<std::mutex> lck(_mutex);
    auto it = _connections.find(cid);
    if (it == _connections.end()) {
        return nullptr;
    }
    return it->second;
}
