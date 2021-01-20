#pragma once
#include <stddef.h>
#include <stdint.h>

#include "src/http2/errors.h"
#include "src/http2/frame.h"

typedef struct {
    // input params
    const uint8_t *input;
    size_t input_size;
    bool first_frame;  // stream first frame
    int prev_type;
    int prev_flags;

    // output result
    http2_frame *frame;
    uint32_t error_code;
} frame_parser;

int http2_package_parse(frame_parser *parser);

int connection_preface_length();
bool verify_connection_preface(const void *buf, size_t len);
int check_http2_package_length(const void *data, size_t len);
