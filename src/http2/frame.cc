#include "src/http2/frame.h"

#pragma pack(push ,1)
struct http2_internal_frame_header{
    uint8_t size2;
    uint8_t size1;
    uint8_t size0;
    uint8_t type;
    uint8_t flags;
    uint8_t stream_id3;
    uint8_t stream_id2;
    uint8_t stream_id1;
    uint8_t stream_id0;
};
#pragma pack(pop ,1)
