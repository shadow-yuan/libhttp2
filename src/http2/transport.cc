#include "src/http2/transport.h"
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"

http2_transport::http2_transport(http2::TcpSendService *sender) {
    _sender = sender;
}

http2_transport::~http2_transport() {}

void http2_transport::set_rpc_call_service(http2::RpcCallService *service) {
    _service = service;
}

size_t http2_transport::get_max_header_size() {
    return http2_get_frame_head_length();
}

int http2_transport::check_package_length(uint64_t cid, const void *data, size_t len) {
    size_t frame_len = http2_get_frame_length(reinterpret_cast<const uint8_t *>(data), len);
    if (frame_len + http2_get_frame_head_length() > len) {
        return -1;
    }
    return frame_len + http2_get_frame_head_length() == len;
}

void http2_transport::connection_enter(uint64_t cid, bool client) {
    std::shared_ptr<http2_connection> conn = create_connection(cid, client);
    //    if (conn != nullptr) {
    //        conn->create_stream(client);
    //    }
}

void http2_transport::received_data(uint16_t cid, const void *buf, size_t len) {
    http2_frame frame;
    http2_errors error = http2_parse(reinterpret_cast<const uint8_t *>(buf), len, &frame);
    if (error == HTTP2_NO_ERROR) {
    }
}

void http2_transport::connection_leave(uint64_t cid) {
    destroy_connection(cid);
}

bool http2_transport::is_connection_exist(uint64_t cid) {
    return find_connection(cid) == nullptr;
}

std::shared_ptr<http2_connection> http2_transport::create_connection(uint64_t cid, bool client) {
    std::shared_ptr<http2_connection> conn = find_connection(cid);
    if (conn == nullptr) {
        conn = std::make_shared<http2_connection>(cid);
        conn->create_stream(client);
        _connections.push_back(conn);
    }
    return conn;
}

std::shared_ptr<http2_connection> http2_transport::find_connection(uint64_t cid) {
    for (auto conn : _connections) {
        if (conn != nullptr && conn->get_cid() == cid) {
            if (conn != nullptr) {
                return conn;
            }
        }
    }
    return nullptr;
}

bool http2_transport::destroy_connection(uint64_t cid) {
    if (!is_connection_exist(cid)) {
        return false;
    }

    for (auto it = _connections.begin(); it != _connections.end(); it++) {
        if ((*it)->get_cid() == cid) {
            _connections.erase(it);
            return true;
        }
    }
    return false;
}
