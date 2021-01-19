#include "src/hpack/hpack.h"
#include <assert.h>
#include "src/hpack/static_metadata.h"
#include "src/hpack/decode.h"
#include "src/http2/errors.h"
#include "src/utils/useful.h"
#include "src/hpack/encode.h"

/*
inline bool is_valid_header(const std::string &k, const std::string &v) {
    return k != std::string("connection") && (k != std::string("te") || v == std::string("trailers"));
}

bool string_starts_with(const std::string &str, char c) {
    if (str.empty()) return false;
    return (str[0] == c);
}
*/

// -------------------------------------------
namespace hpack {

int decode_headers(const uint8_t *buf, uint32_t buf_len, dynamic_table_service *dynamic_table,
                   std::vector<mdelem_data> *decoded_headers) {
    static_metadata *hpack_static_headers = get_static_mdelem_table();
    const uint8_t *buf_end = buf + buf_len;
    while (buf < buf_end) {
        uint16_t int_value = 0;
        if (*buf & 0x80) {
            /*  6.1 Indexed Header Field Representation

                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 1 |        Index (7+)         |
                +---+---------------------------+
             */
            buf = decode_uint16(buf, buf_end, int_value, INT_MASK(7));

            if (!buf || int_value == 0) {
                return HTTP2_COMPRESSION_ERROR;
            }

            mdelem_data mdel;
            // Table 1: Static Table Entries (max entries 61)
            if (int_value > HPACK_STATIC_MDELEM_STANDARD_COUNT) {
                int_value -= HPACK_STATIC_MDELEM_STANDARD_COUNT + 1;
                if (!dynamic_table->get_mdelem_data(int_value, &mdel)) {
                    return HTTP2_COMPRESSION_ERROR;
                }

            } else {
                const auto sm = hpack_static_headers[int_value];
                mdel = sm.data();
            }

            decoded_headers->push_back(mdel);

        } else {
            bool add_to_dynamic_table = false;
            if (*buf & 0x40) {
                // 6.2.1 Literal Header Field with Incremental Indexing
                /*
                      0   1   2   3   4   5   6   7
                    +---+---+---+---+---+---+---+---+
                    | 0 | 1 |      Index (6+)       |
                    +---+---+-----------------------+
                    | H |     Value Length (7+)     |
                    +---+---------------------------+
                    | Value String (Length octets)  |
                    +-------------------------------+
                 */
                buf = decode_uint16(buf, buf_end, int_value, INT_MASK(6));
                if (!buf) {
                    return HTTP2_COMPRESSION_ERROR;
                }
                add_to_dynamic_table = true;
            } else if (*buf & 0x20) {
                // 6.3.  Dynamic Table Size Update
                /*
                    Figure: Maximum Dynamic Table Size Change

                      0   1   2   3   4   5   6   7
                    +---+---+---+---+---+---+---+---+
                    | 0 | 0 | 1 |   Max size (5+)   |
                    +---+---------------------------+
                 */
                buf = decode_uint16(buf, buf_end, int_value, INT_MASK(5));

                // The new maximum size MUST be lower than or equal to the limit
                // determined by the protocol using HPACK.
                if (!buf || int_value > dynamic_table->max_table_size_limit()) {
                    return HTTP2_COMPRESSION_ERROR;
                }
                dynamic_table->update_max_table_size(int_value);
                continue;

            } else {
                // 6.2.2 Literal Header Field without Indexing
                // 6.2.3 Literal Header Field Never Indexed
                /*
                      0   1   2   3   4   5   6   7
                    +---+---+---+---+---+---+---+---+
                    | 0 | 0 | 0 | 1 |  Index (4+)   |
                    +---+---+-----------------------+
                    | H |     Value Length (7+)     |
                    +---+---------------------------+
                    | Value String (Length octets)  |
                    +-------------------------------+
                 */
                buf = decode_uint16(buf, buf_end, int_value, INT_MASK(4));
                if (!buf) {
                    return HTTP2_COMPRESSION_ERROR;
                }
            }

            mdelem_data mdel;

            if (int_value > HPACK_STATIC_MDELEM_STANDARD_COUNT) {
                if (add_to_dynamic_table) {
                    // 6.2.1 Literal Header Field with Incremental Indexing
                    // Indexed Name
                    int_value -= HPACK_STATIC_MDELEM_STANDARD_COUNT + 1;
                    if (!dynamic_table->get_mdelem_data(int_value, &mdel)) {
                        return HTTP2_COMPRESSION_ERROR;
                    }
                } else {
                    return HTTP2_COMPRESSION_ERROR;
                }
            } else if (int_value != 0) {
                const auto sm = hpack_static_headers[int_value];
                mdel.key = sm.data().key;
            } else {
                std::string key;
                buf = parse_string_key(key, buf, buf_end);
                if (!buf) {
                    return HTTP2_PROTOCOL_ERROR;
                }
                mdel.key.assign(key);
            }

            std::string value;
            buf = parse_string(value, buf, buf_end);
            if (!buf) {
                return HTTP2_COMPRESSION_ERROR;
            }

            mdel.value.assign(value);

            decoded_headers->push_back(mdel);

            if (add_to_dynamic_table) {
                dynamic_table->push_mdelem_data(mdel);
            }
        }
    }

    return HTTP2_NO_ERROR;
}

slice_buffer encode_headers(const std::vector<mdelem_data> &headers, dynamic_table_service *dynamic_table) {
    slice_buffer header_block_fragment;
    for (size_t i = 0; i < headers.size(); i++) {
        const mdelem_data &mdel = headers[i];

        slice s;
        // step 1. find static metadata table
        uint32_t static_index = full_match_static_mdelem_index(mdel);
        if (static_index > 0) {
            s = encode_index(static_index);
            header_block_fragment.add_slice(s);
            continue;
        }

        // step 2. find dynamic metadata table
        uint32_t dynamic_index = dynamic_table->get_mdelem_data_index(mdel);
        if (dynamic_index >= 0) {
            dynamic_index += HPACK_STATIC_MDELEM_STANDARD_COUNT + 1;
            s = encode_index(dynamic_index);
            header_block_fragment.add_slice(s);
            continue;
        }

        // step 3. <6.2.1 Literal Header Field with Incremental Indexing>
        s = encode_with_incremental_indexing(mdel);
        header_block_fragment.add_slice(s);
    }
    return header_block_fragment;
}

}  // namespace hpack
