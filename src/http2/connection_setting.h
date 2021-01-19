#pragma once
#include <functional>
#include "src/http2/errors.h"
#include "src/http2/frame.h"

class connection_setting {
public:
    connection_setting();
    ~connection_setting();

    http2_errors excute_frame(http2_frame *frame);
    bool is_enable_pp() const {
        return _enable_pp;
    }
    uint32_t get_header_table_size() const {
        return _header_table_size;
    }
    uint32_t get_max_concurrent_streams() const {
        return _max_concurrent_streams;
    }
    uint32_t get_max_frame_size() const {
        return _max_frame_size;
    }
    uint32_t get_init_window_size() const {
        return _initial_window_size;
    }
    uint32_t get_max_header_list_size() const {
        return _max_header_list_size;
    }

private:
    struct internal_setting_func {
        http2_frame_settings type;
        std::function<http2_errors(uint32_t)> func;
    };
    static const internal_setting_func setting_funcs[];

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
