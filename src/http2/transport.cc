#include "src/http2/transport.h"
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"

http2_transport::http2_transport() {}
http2_transport::~http2_transport() {}

bool http2_transport::ConnectionClosed(uint64_t cid) {
    return destroy_connection(cid);
}

bool http2_transport::ConnectionComming(uint64_t cid) {
    return create_connection(cid);
}

void http2_transport::ReceivedHttp2Data(uint64_t cid, const uint8_t *buff, size_t buff_size) {
    http2_frame frame;
    http2_errors error = http2_parse(buff, buff_size, &frame);
    if (error == HTTP2_NO_ERROR) {
    }
}

bool http2_transport::is_connection_exist(uint64_t cid) const {
    for (auto conn : _connections) {
        if (conn != nullptr && conn->get_cid() == cid) {
            return true;
        }
    }
    return false;
}

bool http2_transport::create_connection(uint64_t cid) {
    if (is_connection_exist(cid)) {
        return false;
    }

    std::shared_ptr<http2_connection> conn = std::make_shared<http2_connection>(cid);
    _connections.push_back(conn);
    return true;
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
