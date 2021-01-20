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

/*
 * Endpoint need to maintain a mdelem_data table to record whether it has been
 * sent to the peer, if it is the first time, it needs to be encoded with the
 *  0x40 flag (encode_with_incremental_indexing), and update the dynamic table.
 *
 * Note: If sending the encoded headers fails, the record needs to be rolled back.
 */

struct encode_parameter {
    dynamic_table_service *dynamic_table;
    uint32_t number_of_dynamic_table_changes;
    send_record_service *send_record;
    uint32_t number_of_send_record_changes;
};

slice_buffer encode_headers(const std::vector<mdelem_data> &headers, struct encode_parameter *param);

}  // namespace hpack
