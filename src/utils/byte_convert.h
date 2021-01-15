#pragma once
#include <stdint.h>

uint16_t get_uint16_from_big_endian(const uint8_t *v);
uint32_t get_uint24_from_big_endian(const uint8_t *v);
uint32_t get_uint32_from_big_endian(const uint8_t *v);
uint64_t get_uint64_from_big_endian(const uint8_t *v);
