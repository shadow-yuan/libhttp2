#include "src/hpack/hpack.h"
#include <assert.h>
#include "src/hpack/static_metadata.h"
#include "src/hpack/decode.h"
#include "src/http2/errors.h"

inline bool is_valid_header(const std::string &k, const std::string &v) {
    return k != std::string("connection") && (k != std::string("te") || v == std::string("trailers"));
}

bool string_starts_with(const std::string &str, char c) {
    if (str.empty())
        return false;
    return (str[0] == c);
}

// -------------------------------------------
namespace hpack {

headers::headers(std::function<void(metadata_element *)> notifier)
    : _notifier(notifier)
    , _dynamic_table_size(0)
    , _max_dynamic_table_size(0)
    , _max_table_size(4096) {  // SETTINGS_HEADER_TABLE_SIZE
}

int headers::decode_headers(const uint8_t *buf, const uint8_t *buf_end) {
    static_metadata *hpack_static_headers = get_static_metadata_table();
    while (buf < buf_end) {
        uint16_t intValue(0);
        if (*buf & 0x80) {
            /*  6.1 Indexed Header Field Representation

                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 1 |        Index (7+)         |
                +---+---------------------------+
             */
            buf = decode_uint16(buf, buf_end, intValue, INT_MASK(7));
            // std::cout << "6.1 Indexed Header Field Representation : "
            // << "index is " << intValue << std::endl;

            if (!buf || intValue == 0) {
                return HTTP2_COMPRESSION_ERROR;
            }

            metadata_element mdel;
            // Table 1: Static Table Entries (max entries 61)
            if (intValue > 61) {

                // std::cout << "dynamic table lookup index: " << intValue << ", count: " << _dynamic_table.size() <<
                // std::endl;
                intValue -= 61 + 1;
                if (intValue < int64_t(_dynamic_table.size())) {
                    auto payload = _dynamic_table[intValue];
                    mdel = get_metadata_element_from_payload(payload);
                } else {
                    return HTTP2_COMPRESSION_ERROR;
                }
            } else {
                const auto sm = hpack_static_headers[intValue - 1];
                mdel = sm.data();
            }

            _notifier(&mdel);

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
                buf = decode_uint16(buf, buf_end, intValue, INT_MASK(6));
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
                buf = decode_uint16(buf, buf_end, intValue, INT_MASK(5));
                // printf("Dynamic Table Size Update: max_table_size(%d) =>change to (%d)\n", _max_table_size,
                // int(intValue));
                if (!buf || intValue > _max_table_size) {
                    return HTTP2_COMPRESSION_ERROR;
                }

                _max_dynamic_table_size = intValue;
                while (_dynamic_table_size > _max_dynamic_table_size && !_dynamic_table.empty()) {
                    auto entry = _dynamic_table.back();
                    auto element = get_metadata_element_from_payload(entry);
                    auto element_size = get_metadata_element_size(element);
                    _dynamic_table_size -= element_size + 32;
                    _dynamic_table.pop_back();
                    medata_element_payload_free(entry);
                }

                continue;
            } else {
                // 6.2.2 Literal Header Field without Indexing
                // 6.2.3 Literal Header Field Never Indexed
                buf = decode_uint16(buf, buf_end, intValue, INT_MASK(4));
                if (!buf) {
                    return HTTP2_COMPRESSION_ERROR;
                }
            }

            std::string key;
            std::string value;

            if (intValue > 61) {
                if (add_to_dynamic_table) {
                    // 6.2.1 Literal Header Field with Incremental Indexing
                    // Indexed Name
                    intValue -= 61 + 1;
                    if (intValue < int64_t(_dynamic_table.size())) {
                        auto entry = _dynamic_table[intValue];
                        auto element = get_metadata_element_from_payload(entry);
                        key = element.key.to_string();
                    } else {
                        return HTTP2_COMPRESSION_ERROR;
                    }
                } else {
                    return HTTP2_COMPRESSION_ERROR;
                }
            } else if (intValue != 0) {
                const auto sm = hpack_static_headers[intValue - 1];
                key = sm.data().key.to_string();
            } else {
                buf = parse_string_key(key, buf, buf_end);
                if (!buf) {
                    return HTTP2_PROTOCOL_ERROR;
                }
            }

            buf = parse_string(value, buf, buf_end);
            if (!buf) {
                return HTTP2_COMPRESSION_ERROR;
            }

            // printf("got key/value: %s -> %s\n", key.c_str(), value.c_str());

            metadata_element mdel;
            mdel.key.assign(key);
            mdel.value.assign(value);
            _notifier(&mdel);

            if (add_to_dynamic_table) {
                const int size = get_metadata_element_size(mdel) + 32;
                while (size + _dynamic_table_size > _max_dynamic_table_size && !_dynamic_table.empty()) {
                    const auto entry = _dynamic_table.back();
                    auto element = get_metadata_element_from_payload(entry);
                    auto element_size = get_metadata_element_size(element);
                    _dynamic_table_size -= element_size + 32;
                    _dynamic_table.pop_back();
                    medata_element_payload_free(entry);
                }

                if (size + _dynamic_table_size <= _max_dynamic_table_size) {
                    auto element = new metadata_element;
                    element->key = mdel.key;
                    element->value = mdel.value;
                    auto payload = MAKE_METADATA_PAYLOAD(element, METADATA_STORAGE_DYNAMIC);
                    _dynamic_table.push_back(payload);
                    _dynamic_table_size += size;
                }
            }
        }
    }

    return HTTP2_NO_ERROR;
}
}  // namespace hpack
