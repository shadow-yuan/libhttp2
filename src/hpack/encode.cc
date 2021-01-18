#include "src/hpack/encode.h"
#include <time.h>
#include "src/utils/useful.h"

namespace hpack {

size_t encode_uint16_impl(uint8_t *buf, int I, uint8_t mask) {
    if (I < mask) {
        *buf = static_cast<uint8_t>(I);
        return 1;
    }

    uint8_t *tmp = buf;

    I -= mask;
    *buf++ = mask;

    while (I >= 128) {
        *buf++ = static_cast<uint8_t>((I & 0x7f) | 0x80);
        I = I >> 7;
    }
    *buf++ = static_cast<uint8_t>(I);
    return buf - tmp;
}

slice encode_uint16(int I, uint8_t mask) {
    uint8_t buf[128] = {0};
    size_t n = encode_uint16_impl(buf, I, mask);
    return slice(buf, n);
}

slice encode_mdelem_data(const mdelem_data &mdel, uint8_t key) {
    uint8_t buf[1024] = {0};
    buf[0] = key;

    size_t n = encode_uint16_impl(&buf[1], mdel.key.size(), INT_MASK(7));
    memcpy(&buf[n + 1], mdel.key.data(), mdel.key.size());

    uint8_t *temp = buf + 1 + n + mdel.key.size();
    n = encode_uint16_impl(temp, mdel.value.size(), INT_MASK(7));
    memcpy(&temp[n], mdel.value.data(), mdel.value.size());
    temp += n + mdel.value.size();

    n = temp - buf;
    return slice(buf, n);
}

// 6.1 Indexed Header Field Representation
slice encode_index(uint32_t index) {
    /*
          0   1   2   3   4   5   6   7
        +---+---+---+---+---+---+---+---+
        | 1 |        Index (7+)         |
        +---+---------------------------+
     */
    uint8_t buf[128] = {0};
    size_t n = encode_uint16_impl(buf, static_cast<int>(index), INT_MASK(7));
    buf[0] |= 0x80;
    return slice(buf, n);
}

// 6.3.  Dynamic Table Size Update
slice encode_update_max_size(uint32_t max_size) {
    /*
          0   1   2   3   4   5   6   7
        +---+---+---+---+---+---+---+---+
        | 0 | 0 | 1 |   Max size (5+)   |
        +---+---------------------------+
     */
    uint8_t buf[128] = {0};
    size_t n = encode_uint16_impl(buf, max_size, INT_MASK(5));
    buf[0] |= 0x20;
    return slice(buf, n);
}

// 6.2.1 Literal Header Field with Incremental Indexing
slice encode_with_incremental_indexing(const mdelem_data &mdel) {
    /*
          0   1   2   3   4   5   6   7
        +---+---+---+---+---+---+---+---+
        | 0 | 1 |           0           |
        +---+---+-----------------------+
        | H |     Name Length (7+)      |
        +---+---------------------------+
        |  Name String (Length octets)  |
        +---+---------------------------+
        | H |     Value Length (7+)     |
        +---+---------------------------+
        | Value String (Length octets)  |
        +-------------------------------+
     */

    return encode_mdelem_data(mdel, 0x40);
}

// 6.2.2 Literal Header Field without Indexing
slice encode_without_indexing(const mdelem_data &mdel) {
    /*
          0   1   2   3   4   5   6   7
        +---+---+---+---+---+---+---+---+
        | 0 | 0 | 0 | 0 |       0       |
        +---+---+-----------------------+
        | H |     Name Length (7+)      |
        +---+---------------------------+
        |  Name String (Length octets)  |
        +---+---------------------------+
        | H |     Value Length (7+)     |
        +---+---------------------------+
        | Value String (Length octets)  |
        +-------------------------------+
     */

    return encode_mdelem_data(mdel, 0x0);
}

// 6.2.3 Literal Header Field Never Indexed
slice encode_never_indexed(const mdelem_data &mdel) {
    /*
          0   1   2   3   4   5   6   7
        +---+---+---+---+---+---+---+---+
        | 0 | 0 | 0 | 1 |       0       |
        +---+---+-----------------------+
        | H |     Name Length (7+)      |
        +---+---------------------------+
        |  Name String (Length octets)  |
        +---+---------------------------+
        | H |     Value Length (7+)     |
        +---+---------------------------+
        | Value String (Length octets)  |
        +-------------------------------+
     */

    return encode_mdelem_data(mdel, 0x10);
}
}  // namespace hpack
