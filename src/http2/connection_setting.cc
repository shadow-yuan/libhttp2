#include "src/http2/connection_setting.h"
#include "src/http2/settings.h"

connection_setting::connection_setting() {
    _header_table_size = 4096;
    _enable_pp = true;
    _max_concurrent_streams = 0;
    _initial_window_size = 1 << 16 - 1;
    _max_frame_size = 1 << 14;
    _max_header_list_size = 0;
}

connection_setting::~connection_setting() {}

// std::function<http2_errors(uint32_t)> setting_func1;
// typedef http2_errors (*setting_func)(uint32_t);
// struct internal_setting_func {
//    http2_frame_settings type;
//    std::function<http2_errors(uint32_t)> func;
//};
const connection_setting::internal_setting_func connection_setting::setting_funcs[] = {
    {HTTP2_SETTINGS_HEADER_TABLE_SIZE, &connection_setting::header_table_size},
    {HTTP2_SETTINGS_ENABLE_PUSH, &connection_setting::enable_push},
    {HTTP2_SETTINGS_MAX_CONCURRENT_STREAMS, &connection_setting::max_concurrent_streams},
    {HTTP2_SETTINGS_INITIAL_WINDOW_SIZE, &connection_setting::initial_window_size},
    {HTTP2_SETTINGS_MAX_FRAME_SIZE, &connection_setting::max_frame_size},
    {HTTP2_SETTINGS_MAX_HEADER_LIST_SIZE, &connection_setting::max_header_list_size},
};
http2_errors connection_setting::excute_frame(http2_frame *frame) {
    uint32_t stream_id = frame->head.stream_id;
    rm_head_bit(stream_id);
    if (stream_id) {
        return HTTP2_PROTOCOL_ERROR;
    }
    for (size_t i = 0; i < frame->settings.count; i++) {
        for (size_t j = 0; j < sizeof(setting_funcs) / sizeof(internal_setting_func); j++) {
            if (setting_funcs[j].type == frame->settings.settings[i].id) {
                http2_errors err = (setting_funcs[j].func)(frame->settings.settings[i].value);
                if (err != HTTP2_NO_ERROR) {
                    return err;
                }
            }
        }
    }

    return HTTP2_NO_ERROR;
}

http2_errors connection_setting::header_table_size(uint32_t value) {
    _header_table_size = value;
    return HTTP2_NO_ERROR;
}
http2_errors connection_setting::enable_push(uint32_t value) {
    _enable_pp = reinterpret_cast<bool>(!!value);
    return HTTP2_NO_ERROR;
}
http2_errors connection_setting::max_concurrent_streams(uint32_t value) {
    _max_concurrent_streams = value;
    return HTTP2_NO_ERROR;
}
http2_errors connection_setting::initial_window_size(uint32_t value) {
    if (value > 65535) {
        return HTTP2_FLOW_CONTROL_ERROR;
    }
    _initial_window_size = value;
    return HTTP2_NO_ERROR;
}
http2_errors connection_setting::max_frame_size(uint32_t value) {
    if (value < 16384 || value > 16777215) {
        return HTTP2_PROTOCOL_ERROR;
    }
    _max_frame_size = value;
    return HTTP2_NO_ERROR;
}
http2_errors connection_setting::max_header_list_size(uint32_t value) {
    _max_header_list_size = value;
    return HTTP2_NO_ERROR;
}
