#include "src/utils/byte_convert.h"

uint16_t get_uint16_from_byte(const uint8_t *v) {
    uint16_t r = 0;
    r = uint16_t(*v) << 8 | *(v + 1);
    return r;
}

uint32_t get_uint32_from_byte(const uint8_t *v) {
    uint32_t r = 0;
    r = uint32_t(*v) << 24 | uint32_t(*(v + 1)) << 16 | uint32_t(*(v + 2)) << 8 | *(v + 3);
    return r;
}

uint64_t get_uint64_from_byte(const uint8_t *v) {
    uint64_t r = 0;
    r = uint64_t(*v) << 56 | uint64_t(*(v + 1)) << 48 | uint64_t(*(v + 2)) << 40 | *(v + 3) << 32 |
        uint64_t(*(v + 4)) << 24 | uint64_t(*(v + 5)) << 24 | uint64_t(*(v + 6)) << 8 | *(v + 7);
    return r;
}
