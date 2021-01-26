#pragma once
#include <stdint.h>
#include "src/http2/frame.h"
#include "src/utils/slice_buffer.h"

slice_buffer pack_http2_frame_data(http2_frame_data *frame, uint32_t max_frame_size);
slice pack_http2_frame_headers(http2_frame_headers *frame);
slice pack_http2_frame_priority(http2_frame_priority *frame);
slice pack_http2_frame_rst_stream(http2_frame_rst_stream *frame);
slice pack_http2_frame_settings(http2_frame_settings *frame);
slice pack_http2_frame_push_promise(http2_frame_push_promise *frame);
slice pack_http2_frame_ping(http2_frame_ping *frame);
slice pack_http2_frame_goaway(http2_frame_goaway *frame);
slice pack_http2_frame_window_update(http2_frame_window_update *frame);
slice pack_http2_frame_continuation(http2_frame_continuation *frame);
