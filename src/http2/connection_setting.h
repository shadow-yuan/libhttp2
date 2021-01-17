#pragma once
#include "src/http2/errors.h"
#include "src/http2/frame.h"

class connection_setting {
public:
    connection_setting();
    ~connection_setting();

    http2_errors excute_frame(http2_frame *frame);

private:
    http2_errors header_table_size(uint32_t value);
    http2_errors enable_push(uint32_t value);
    http2_errors max_concurrent_streams(uint32_t value);
    http2_errors initial_window_size(uint32_t value);
    http2_errors max_frame_size(uint32_t value);
    http2_errors max_header_list_size(uint32_t value);

private:
    uint32_t _header_table_size;
    bool _enable_pp;
    uint32_t _max_concurrent_streams;
    uint32_t _initial_window_size;
    uint32_t _max_frame_size;
    uint32_t _max_header_list_size;
};
