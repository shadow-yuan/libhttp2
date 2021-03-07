#pragma once
#include <stdint.h>
#include <vector>

#include "src/hpack/metadata.h"
#include "src/utils/slice_buffer.h"

namespace hpack {

// parse HEADER FRAME payload
// return http2_errors
int decode_headers(const uint8_t *buf, uint32_t buf_len, dynamic_table_service *dynamic_table,
                   std::vector<mdelem_data> *decoded_headers);

}  // namespace hpack
