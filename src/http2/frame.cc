#include "src/http2/frame.h"

uint8_t head_bit(uint8_t v) {
    return v & 0x80;
}
uint8_t head_bit(uint16_t v) {
    return v & 0x8000;
};
uint8_t head_bit(uint32_t v) {
    return v & 0x80000000;
};
void rm_head_bit(uint32_t &v) {
    v = v & ~0x80000000;
};
