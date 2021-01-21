#pragma once
#include <stddef.h>
#include <stdint.h>

#include "src/http2/frame.h"

int parse_http2_frame_data(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_data *output);
int parse_http2_frame_headers(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_headers *output);
int parse_http2_frame_priority(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_priority *output);
int parse_http2_frame_rst_stream(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_rst_stream *output);
int parse_http2_frame_settings(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_settings *output);
int parse_http2_frame_push_promise(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_push_promise *output);
int parse_http2_frame_ping(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_ping *output);
int parse_http2_frame_goaway(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_goaway *output);
int parse_http2_frame_window_update(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_window_update *output);
int parse_http2_frame_continuation(http2_frame_hdr *hdr, const uint8_t *input, http2_frame_continuation *output);

int parse_http2_package(http2_frame *frame, const uint8_t *input, http2_frame_hdr *hdr);
