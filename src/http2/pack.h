#pragma once
#include "src/utils/slice_buffer.h"
#include "src/http2/frame.h"

slice_buffer pack_frame_data(http2_frame *frame, size_t max_data_len);
slice_buffer pack_frame_header(http2_frame *frame);
slice_buffer pack_frame_priority(http2_frame *frame);
slice_buffer pack_frame_rst_stream(http2_frame *frame);
slice_buffer pack_frame_settings(http2_frame *frame);
slice_buffer pack_frame_push_promise(http2_frame *frame);
slice_buffer pack_frame_ping(http2_frame *frame);
slice_buffer pack_frame_goaway(http2_frame *frame);
slice_buffer pack_frame_window_update(http2_frame *frame);
slice_buffer pack_frame_continuation(http2_frame *frame);
