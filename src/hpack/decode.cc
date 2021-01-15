#include "src/hpack/decode.h"
#include "src/hpack/huffman.h"
#include "src/utils/useful.h"

namespace hpack {
// This decodes an uint, it returns nullptr if it tries to read past end
// The value can overflow it's capacity, which should be harmless as it
// would give parsing errors on other parts
const uint8_t *decode_uint16(const uint8_t *src, const uint8_t *src_end, uint16_t &dst, uint8_t mask) {
    dst = *src & mask;
    if (dst == mask) {
        int M = 0;
        do {
            if (++src >= src_end) {
                dst = uint16_t(-1);
                return nullptr;
            }

            dst += (*src & 0x7f) << M;
            M += 7;
        } while (*src & 0x80);
    }

    return ++src;
}

const uint8_t *decode_string(const uint8_t *src, const uint8_t *src_end, std::string &value, size_t len) {
    const http2_huff_decode *entry = nullptr;
    value.reserve(len * 2);  // max compression ratio is >= 0.5
    uint8_t state = 0;

    do {
        if (entry) {
            state = entry->state;
        }
        entry = huff_decode_table[state] + (*src >> 4);

        if (entry->flags & HUFF_FAIL) {
            // A decoder decoded an invalid Huffman sequence
            return nullptr;
        }

        if (entry->flags & HUFF_SYM) {
            value.append(1, char(entry->sym));
        }

        entry = huff_decode_table[entry->state] + (*src & 0x0f);

        if (entry->flags & HUFF_FAIL) {
            // A decoder decoded an invalid Huffman sequence
            return nullptr;
        }

        if ((entry->flags & HUFF_SYM) != 0) {
            value.append(1, char(entry->sym));
        }

    } while (++src < src_end);

    if ((entry->flags & HUFF_ACCEPTED) == 0) {
        // entry->state == 28 // A invalid header name or value character was coded
        // entry->state != 28 // A decoder decoded an invalid Huffman sequence
        return nullptr;
    }

    return src_end;
}

const uint8_t *parse_string(std::string &dst, const uint8_t *buf, const uint8_t *buf_end) {
    uint16_t str_len = 0;

    bool huffman_decode = *buf & 0x80;

    buf = decode_uint16(buf, buf_end, str_len, INT_MASK(7));
    if (!buf) {
        return nullptr;
    }

    if (huffman_decode) {
        buf = decode_string(buf, buf + str_len, dst, str_len);
        if (!buf) {
            return nullptr;
        }
    } else {
        if (buf + str_len <= buf_end) {
            dst = std::string(reinterpret_cast<const char *>(buf), str_len);
            buf += str_len;
        } else {
            return nullptr;  // Reading past end
        }
    }
    return buf;
}

const uint8_t *parse_string_key(std::string &dst, const uint8_t *buf, const uint8_t *buf_end) {
    bool huffman_decode = *buf & 0x80;
    uint16_t str_len = 0;

    buf = decode_uint16(buf, buf_end, str_len, INT_MASK(7));
    if (!buf) {
        return nullptr;
    }

    if (huffman_decode) {
        buf = decode_string(buf, buf + str_len, dst, str_len);
        if (!buf) {
            return nullptr;
        }
    } else {
        if (buf + str_len <= buf_end) {
            buf_end = buf + str_len;

            while (buf < buf_end) {
                char c = char(*(buf++));
                if (isupper(c)) {
                    return nullptr;
                }
                dst += c;
            }
        } else {
            return nullptr;  // Reading past end
        }
    }
    return buf;
}
}  // namespace hpack
