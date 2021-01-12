#pragma once
#include "frame.h"

class http2_frame_data : public http2_frame{
public:
    explicit http2_frame_data(http2_frame_flags flag);
    ~http2_frame_data();

    bool parse_data(const int8_t* data,size_t len) override;
private:
    size_t _pad_len = 0;
    size_t _data_len = 0;
    int8_t *_data = nullptr;
    int8_t *_padding = nullptr;
};
