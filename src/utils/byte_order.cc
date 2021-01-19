#include "src/utils/byte_order.h"
#include <string.h>

uint16_t get_uint16_from_be_stream(const uint8_t *p) {
    uint8_t buf[4] = {0};
    buf[0] = p[1];
    buf[1] = p[0];
    return *reinterpret_cast<uint16_t *>(buf);
}

uint32_t get_uint24_from_be_stream(const uint8_t *p) {
    uint8_t buf[4] = {0};
    buf[0] = p[2];
    buf[1] = p[1];
    buf[2] = p[0];
    return *reinterpret_cast<uint32_t *>(buf);
}

uint32_t get_uint32_from_be_stream(const uint8_t *p) {
    uint8_t buf[4] = {0};
    buf[0] = p[3];
    buf[1] = p[2];
    buf[2] = p[1];
    buf[3] = p[0];
    return *reinterpret_cast<uint32_t *>(buf);
}

void put_uint16_in_be_stream(uint8_t *buf, uint16_t n) {
    uint16_t x = change_byte_order(n);
    memcpy(buf, &x, sizeof(uint16_t));
}

void put_uint32_in_be_stream(uint8_t *buf, uint32_t n) {
    uint32_t x = change_byte_order(n);
    memcpy(buf, &x, sizeof(uint32_t));
}
