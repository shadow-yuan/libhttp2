#include "frame.h"

http2_frame::http2_frame(http2_frame_type type,http2_frame_flags flag){
    _frame_type = type;
    _frame_flag = flag;
}

bool http2_frame::convert_flag(int8_t data,http2_frame_flags& flag){
    bool res = true;
    switch(data){
        case HTTP2_FLAG_END_STREAM:
        case HTTP2_FLAG_END_HEADERS:
        case HTTP2_FLAG_PADDED:
        case HTTP2_FLAG_PRIORITY:
            flag = (http2_frame_flags)data;
            break;
        default:
            res = false;
    }
    return res;
}
