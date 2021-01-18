#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

#include "src/hpack/dynamic_metadata.h"

namespace hpack {
class headers {
public:
    // callback is used to receive the decoded header list
    explicit headers(std::function<void(mdelem_data *)> callback);
    ~headers();

    // parse FRAME - HEADER payload
    // return http2_errors
    int decode_headers(const uint8_t *buf, const uint8_t *buf_end);

    std::string encode_headers(const std::vector<mdelem_data> &headers);

private:
    std::function<void(mdelem_data *)> _decoded_hd_list_callback;
    dynamic_metadata_table _dynamic_table;

    friend class http2_connection;
    friend class http2_stream;
};
}  // namespace hpack
