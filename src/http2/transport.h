#pragma once
#include <stddef.h>
#include <stdint.h>
#include <memory>
#include <vector>
#include "src/http2/connection.h"

class http2_transport {
public:
    http2_transport();
    ~http2_transport();

    bool ConnectionComming(uint64_t cid);
    bool ConnectionClosed(uint64_t cid);

    void ReceivedHttp2Data(uint64_t cid, const uint8_t *buff, size_t buff_size);

private:
    bool is_connection_exist(uint64_t cid) const;
    bool create_connection(uint64_t cid);
    bool destroy_connection(uint64_t cid);

private:
    std::vector<std::shared_ptr<http2_connection>> _connections;
};
