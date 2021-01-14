#pragma once
#include "src/http2/errors.h"
#include "src/http2/frame.h"

http2_errors http2_parse(const uint8_t *data, size_t len, http2_frame *frame);
