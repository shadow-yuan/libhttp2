#pragma once
#include <stdint.h>
#include <memory>
#include <map>
#include "src/http2/errors.h"
#include "src/http2/stream.h"
#include "src/http2/connection_setting.h"

class http2_connection {
public:
    http2_connection(uint64_t cid);
    ~http2_connection();

    uint64_t get_cid() const {
        return _cid;
    }

    uint32_t create_stream(bool client);
    http2_errors frame_arrived(http2_frame *frame);

private:
    std::shared_ptr<http2_stream> get_stream(uint32_t sid);
    http2_errors execute_setting(http2_frame *frame);
    http2_errors execute_goaway(http2_frame *frame);

private:
    uint64_t _cid;
    connection_setting _settings;
    std::map<uint32_t, std::shared_ptr<http2_stream>> _streams;
    uint32_t _client_max_id;
    uint32_t _server_max_id;
};
