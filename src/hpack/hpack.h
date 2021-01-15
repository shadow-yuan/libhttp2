#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

#include "src/hpack/static_metadata.h"

namespace hpack {
class headers {
public:
    explicit headers(std::function<void(mdelem_data *)> notifier);
    ~headers();

    // parse FRAME - HEADER payload
    // return http2_errors
    int decode_headers(const uint8_t *buf, const uint8_t *buf_end);

private:
    std::function<void(mdelem_data *)> _notifier;

    int _dynamic_table_size;
    int _max_dynamic_table_size;
    int _max_table_size;

    std::vector<mdelem_data> _dynamic_table;
};
}  // namespace hpack
