#pragma once
#include <stddef.h>
#include <stdint.h>

#include "src/http2/errors.h"
#include "src/http2/frame.h"

http2_errors http2_parse(const uint8_t *data, size_t len, http2_frame *frame);
size_t http2_get_frame_head_length();
size_t http2_get_frame_length(const uint8_t *data, size_t len);
