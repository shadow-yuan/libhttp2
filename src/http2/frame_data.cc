#include <string.h>
#include "frame_data.h"

http2_frame_data::http2_frame_data(http2_frame_flags flag) :
    http2_frame(HTTP2_FRAME_DATA,flag) {
}

http2_frame_data::~http2_frame_data(){
    if(_data != nullptr){
        delete[] _data;
        _data = nullptr;
    }
    if(_padding != nullptr){
        delete[] _padding;
        _padding = nullptr;
    }
}

bool http2_frame_data::parse_data(const int8_t* data,size_t len) {
    http2_frame::parse_data(data,len);

    /**
     *   +---------------+
     *   |Pad Length? (8)|
     *   +---------------+-----------------------------------------------+
     *   |                            Data (*)                         ...
     *   +---------------------------------------------------------------+
     *   |                           Padding (*)                       ...
     *   +---------------------------------------------------------------+
     * Pad Length:  An 8-bit field containing the length of the frame
     *  padding in units of octets.  This field is conditional (as
     *  signified by a "?" in the diagram) and is only present if the
     *  PADDED flag is set.
    */
    size_t offset = 0;
    if (get_frame_flag() == HTTP2_FLAG_PADDED){
        _pad_len = *data;
        offset += 1;
    }

    _data_len = _pad_len > 0 ? len - _pad_len - 1 : len;

    _data = new int8_t[_data_len];
    memcpy(_data,data+offset,_data_len);

    offset += _data_len;
    if(offset < len){
        _padding = new int8_t[_pad_len];
        memcpy(_padding,data+offset,_pad_len);
    }

    return true;
}
