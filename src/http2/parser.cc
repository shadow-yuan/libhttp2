#include "parser.h"
#include "frame_data.h"


struct http2_internal_frame_header{
#pragma pack(push ,1)
    uint8_t size2;
    uint8_t size1;
    uint8_t size0;
    uint8_t type;
    uint8_t flags;
    uint8_t stream_id3;
    uint8_t stream_id2;
    uint8_t stream_id1;
    uint8_t stream_id0;
#pragma pack(pop ,1)
    uint32_t get_payload_size();
    uint32_t get_stream_id();
};

uint32_t http2_internal_frame_header::get_payload_size(){
    uint32_t result = 0;
    result |= size2 << 16 | size1 << 8 | size0;
    return result;
}

uint32_t http2_internal_frame_header::get_stream_id(){
    uint32_t result = 0;
    result |= stream_id3 << 24 | stream_id2 << 16 | stream_id1 << 8 | stream_id0;
    return result;
}
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
http2_errors http2_parse(const uint8_t* data,size_t len,http2_frame* frame){
    if (frame == nullptr)
        return HTTP2_NO_ERROR;
    if (len < sizeof(http2_internal_frame_header)/*9*/)
        return HTTP2_FRAME_SIZE_ERROR;
    size_t offset = 0;
    http2_internal_frame_header* head = (http2_internal_frame_header*)data;
    frame->head.frame_type = head->type;
    frame->head.frame_flag = head->flags;
    frame->head.payload_length = head->get_payload_size();
    frame->head.stream_id = head->get_stream_id();
    offset += sizeof(http2_internal_frame_header);
    switch (head->type)
    {
    case HTTP2_FRAME_DATA:{
/*
    +---------------+
    |Pad Length? (8)|
    +---------------+-----------------------------------------------+
    |                            Data (*)                         ...
    +---------------------------------------------------------------+
    |                           Padding (*)                       ...
    +---------------------------------------------------------------+
*/
        frame->data.pad_len = 0;
        frame->data.data_len = 0;
        if(frame->head.frame_flag == HTTP2_FLAG_PADDED){
            frame->data.pad_len = *(uint8_t*)(data + offset);
            if(frame->data.pad_len >= frame->head.payload_length){
                return HTTP2_PROTOCOL_ERROR;
            }
            offset += sizeof(uint8_t);
        }
        frame->data.data_len = frame->head.payload_length - frame->data.pad_len;
        frame->data.data = data + offset;
        if(frame->data.pad_len > 0){
            frame->data.pad_data = data + offset + frame->data.data_len;
        }
    }
    break;
    case HTTP2_FRAME_HEADERS:{

    }
    break;
    case HTTP2_FRAME_PRIORITY:
    break;
    case HTTP2_FRAME_RST_STREAM:
    break;
    case HTTP2_FRAME_SETTINGS:
    break;
    case HTTP2_FRAME_PUSH_PROMISE:
    break;
    case HTTP2_FRAME_PING:
    break;
    case HTTP2_FRAME_GOAWAY:
    break;
    case HTTP2_FRAME_WINDOW_UPDATE:
    break;
    case HTTP2_FRAME_CONTINUATION:
    break;
    default:
        return HTTP2_PROTOCOL_ERROR;
    }

    return HTTP2_NO_ERROR;
}
