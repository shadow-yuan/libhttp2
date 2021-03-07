#include "src/http2/transport.h"
#include <assert.h>
#include <string.h>
#include "src/http2/errors.h"
#include "src/http2/frame.h"
#include "src/http2/parser.h"
#include "src/http2/connection.h"
#include "src/http2/settings.h"
#include "src/utils/log.h"

http2_transport::http2_transport(http2::TcpSendService *sender)
    : _tcp_sender(sender) {}

http2_transport::~http2_transport() {}

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
    std::unique_lock<std::mutex> lck(_mutex);
    auto conn = std::make_shared<http2_connection>(_tcp_sender, cid, client_side);
    auto result = _connections.insert({cid, conn});
    if (!result.second) {
        log_error("http2_transport::connection_enter, the same cid comes in repeatedly");
        abort();
    }
}

void http2_transport::received_data(uint64_t cid, const void *buf, size_t len) {
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
    std::unique_lock<std::mutex> lck(_mutex);
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

http2::Stream *create_stream(uint64_t cid) {
    // TODO(SHADOW):
    return nullptr;
}
