#include "service.h"
#include "frame_data.h"

http2_frame* http2_parse(const int8_t* data,size_t len){
    if (len < 9)
        return nullptr;
    http2_frame *frame = nullptr;
    int32_t frame_len;
    int8_t type , flag_data;
    bool reserved;
    int32_t stream_identfier;

/*
    +-----------------------------------------------+
    |                 Length (24)                   |
    +---------------+---------------+---------------+
    |   Type (8)    |   Flags (8)   |
    +-+-------------+---------------+-------------------------------+
    |R|                 Stream Identifier (31)                      |
    +=+=============================================================+
    |                   Frame Payload (0...)                      ...
    +---------------------------------------------------------------+
*/
    size_t offset = 0;
    frame_len = *((int32_t*)data + offset) & (1<<25 - 1);
    offset += 3;
    type = *((int8_t*)data + offset) & 0xff;
    offset += 1;
    flag_data = *((int8_t*)data + offset) & 0xff;
    offset += 1;
    reserved = *((int8_t*)data + offset) & 0x01;
    stream_identfier = *(int32_t*)data & 0xefffffff;
    offset += 4;

    const int8_t* pay_load = data + offset;

    http2_frame_flags flag;
    if (http2_frame::convert_flag(flag_data,flag)){
        if (type == HTTP2_FRAME_DATA){
            frame = new http2_frame_data(flag);
            if (!frame->parse_data(pay_load,frame_len)){
                 // parse failed
                delete frame;
                frame = nullptr;
            }
        }
    }

    return frame;
}
