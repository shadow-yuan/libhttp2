#pragma once
#include <stdint.h>

uint16_t get_uint16_from_big_endian(const uint8_t *v);
uint32_t get_uint24_from_big_endian(const uint8_t *v);
uint32_t get_uint32_from_big_endian(const uint8_t *v);
uint64_t get_uint64_from_big_endian(const uint8_t *v);

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
