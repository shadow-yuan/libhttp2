#include "src/http2/connection.h"

http2_connection::http2_connection(uint64_t cid) {
    _cid = cid;
    _client_max_id = 1;
    _server_max_id = 2;
}

uint32_t http2_connection::create_stream(bool client) {
    std::shared_ptr<http2_stream> stream;
    if (client) {
        if (_client_max_id + 2 >= 1 << 31) {
            return 0;
        }
        stream = std::make_shared<http2_stream>(_client_max_id);
        _client_max_id += 2;
    } else {
        if (_server_max_id + 2 > 1 << 31) {
            return 0;
        }
        stream = std::make_shared<http2_stream>(_server_max_id);
        _server_max_id += 2;
    }
    _streams.push_back(stream);
    return stream->get_sid();
}
