#include "src/http2/pack.h"

slice_buffer pack_frame_data(http2_frame *frame, size_t max_data_len) {
    slice_buffer buffer;
    slice head = MakeSliceByLength(HTTP2_FRAME_HEADER_SIZE);
    http2_frame_header_pack(head.data(), &frame->hdr);
    slice padding = MakeSliceByLength(frame->data.pad_len);
    slice data = MakeStaticSlice(frame->data.data(), frame->data.data.size());
    while (!data.empty()) {
        slice frame_data;
        if (!padding.empty()) {
            slice pad_len = MakeSliceByLength(1);
            pad_len.data()[0] = padding.size();
            frame_data = frame_data + pad_len;
        }

        if (data.size() + padding.size() > max_data_len) {
            frame_data = frame_data + MakeStaticSlice(data.data(), max_data_len);
            data.pop_front(max_data_len);
        } else {
            frame_data = frame_data + MakeStaticSlice(data.data(), data.size());
            data.pop_front(data.size());
        }

        if (!padding.empty()) {
            frame_data = frame_data + padding;
        }
        buffer.add_slice(frame_data);
    }
    return buffer;
}
