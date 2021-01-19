#pragma once
#include <stdint.h>

// Used to replace a series of functions such as htonl.
// T: just for u/int16/32/64
template <typename T>
T change_byte_order(T value) {
    uint8_t buf[sizeof(T)] = {0};
    uint8_t *ptr = reinterpret_cast<uint8_t *>(&value);
    for (size_t i = 0; i < sizeof(T); i++) {
        buf[i] = ptr[sizeof(T) - i - 1];
    }
    return *reinterpret_cast<T *>(buf);
}

uint16_t get_uint16_from_be_stream(const uint8_t *p);
uint32_t get_uint24_from_be_stream(const uint8_t *p);
uint32_t get_uint32_from_be_stream(const uint8_t *p);

void put_uint16_in_be_stream(uint8_t *buf, uint16_t n);
void put_uint32_in_be_stream(uint8_t *buf, uint32_t n);
