#pragma once
#include <stdint.h>
#include <memory>
#include <vector>
#include "src/http2/stream.h"

class http2_connection {
public:
    http2_connection(uint64_t cid);
    ~http2_connection();

    uint64_t get_cid() const {
        return _cid;
    }

private:
    uint64_t _cid;
    std::vector<std::shared_ptr<http2_stream>> _streams;
    uint32_t _client_max_id;
    uint32_t _server_max_id;
};
