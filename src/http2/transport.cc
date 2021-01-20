#include "src/http2/transport.h"
#include <string.h>
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"
#include "src/http2/connection.h"

static const uint8_t connection_preface[24] = {0x50, 0x52, 0x49, 0x20, 0x2a, 0x20, 0x48, 0x54, 0x54, 0x50, 0x2f, 0x32,
                                               0x2e, 0x30, 0x0d, 0x0a, 0x0d, 0x0a, 0x53, 0x4d, 0x0d, 0x0a, 0x0d, 0x0a};

inline int connection_preface_length() {
    return static_cast<int>(sizeof(connection_preface));
}

bool verify_connection_preface(const void *buf, size_t len) {
    size_t preface_size = sizeof(connection_preface);
    if (len < preface_size) {
        return false;
    }
    return memcmp(buf, connection_preface, preface_size) == 0;
}

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
    auto it = _connections.find(cid);
    if (it == _connections.end()) {
        return -1;
    }

    if (!it->second->is_handshake()) {
        return connection_preface_length();
    }

    int r = check_http2_package_length(data, len);
    if (r < 0) {
        // send GOAWAY, error_code FRAME_SIZE_ERROR;
        it->second->send_goaway(HTTP2_FRAME_SIZE_ERROR);
    }
    return r;
}

void http2_transport::connection_enter(uint64_t cid, bool client) {
    if (client) {  // send preface
        _tcp_sender->SendTcpData(cid, connection_preface, sizeof(connection_preface));
    }
    _connections[cid] = std::make_shared<http2_connection>(cid, client);
}

void http2_transport::received_data(uint16_t cid, const void *buf, size_t len) {
    auto it = _connections.find(cid);
    if (it == _connections.end()) {
        return;
    }

    const uint8_t *package = reinterpret_cast<const uint8_t *>(buf);
    size_t package_length = len;

    if (!it->second->is_handshake()) {
        if (!verify_connection_preface(buf, len)) {
            it->second->send_goaway(HTTP2_PROTOCOL_ERROR);
            return;
        }
        it->second->handshake_done();
        package_length -= connection_preface_length();
        package += connection_preface_length();
    }

    if (package_length > 0) {
        it->second->package_process(package, package_length);
    }
}

void http2_transport::connection_leave(uint64_t cid) {
    _connections.erase(cid);
}

std::shared_ptr<http2_connection> http2_transport::find_connection(uint64_t cid) {
    auto it = _connections.find(cid);
    if (it == _connections.end()) {
        return nullptr;
    }
    return it->second;
}
