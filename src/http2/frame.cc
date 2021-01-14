#include "src/http2/frame.h"

uint16_t to_ui16(const uint8_t *v) {
    uint16_t r = 0;
    r = uint16_t(*v) << 8 | *(v + 1);
    return r;
}

uint32_t to_ui32(const uint8_t *v) {
    uint32_t r = 0;
    r = uint32_t(*v) << 24 | uint32_t(*(v + 1)) << 16 | uint32_t(*(v + 2)) << 8 | *(v + 3);
    return r;
}

uint64_t to_ui64(const uint8_t *v) {
    uint64_t r = 0;
    r = uint64_t(*v) << 56 | uint64_t(*(v + 1)) << 48 | uint64_t(*(v + 2)) << 40 | *(v + 3) << 32 |
        uint64_t(*(v + 4)) << 24 | uint64_t(*(v + 5)) << 24 | uint64_t(*(v + 6)) << 8 | *(v + 7);
    return r;
}

uint8_t head_bit(uint8_t v) { return v & 0x80; }
uint8_t head_bit(uint16_t v) { return v & 0x8000; };
uint8_t head_bit(uint32_t v) { return v & 0x80000000; };
void rm_head_bit(uint32_t &v) { v = v & ~0x80000000; };
