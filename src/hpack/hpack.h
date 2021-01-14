#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

#include "src/hpack/metadata.h"

namespace hpack {
class headers {
public:
    explicit headers(std::function<void(metadata_element *)> notifier);
    ~headers();

    // parse FRAME - HEADER payload
    // return http2_errors
    int decode_headers(const uint8_t *buf, const uint8_t *buf_end);

private:
    std::function<void(metadata_element *)> _notifier;

    int _dynamic_table_size;
    int _max_dynamic_table_size;
    int _max_table_size;

    std::vector<metadata_payload> _dynamic_table;
};
}  // namespace hpack
