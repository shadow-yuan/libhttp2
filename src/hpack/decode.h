#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string>

namespace hpack {

const uint8_t *decode_uint16(const uint8_t *src, const uint8_t *src_end, uint16_t &dst, uint8_t mask);
const uint8_t *decode_string(const uint8_t *src, const uint8_t *src_end, std::string &value, size_t len);
const uint8_t *parse_string(std::string &dst, const uint8_t *buf, const uint8_t *buf_end);
const uint8_t *parse_string_key(std::string &dst, const uint8_t *buf, const uint8_t *buf_end);

}  // namespace hpack
