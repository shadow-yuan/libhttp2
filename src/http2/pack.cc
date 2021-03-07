#include "src/http2/pack.h"
#include <assert.h>
#include <string.h>
#include "src/utils/byte_order.h"

slice_buffer pack_http2_frame_data(http2_frame_data *frame, uint32_t max_frame_size) {
    size_t readed_length = 0;
    slice_buffer buffer;
    while (readed_length < frame->data.size()) {
        size_t pad_len = 0;
        size_t frame_length;
        if (frame->hdr.flags & HTTP2_FLAG_PADDED) {
            pad_len = 1;
            pad_len += frame->pad_len;
        }
        frame_length =
            (frame->data.size() + pad_len) < max_frame_size ? (frame->data.size() + pad_len) : max_frame_size;

        slice data = MakeSliceByLength(frame_length + HTTP2_FRAME_HEADER_SIZE);
        uint8_t *p = const_cast<uint8_t *>(data.data());
        http2_frame_header_pack(p, &frame->hdr);
        p += HTTP2_FRAME_HEADER_SIZE;

        if (frame->hdr.flags & HTTP2_FLAG_PADDED) {
            *p++ = frame->pad_len;
        }
        memcpy(p, frame->data.data() + readed_length, frame_length - pad_len);
        readed_length += frame_length - pad_len;

        buffer.add_slice(data);
    }
    return buffer;
}

slice pack_http2_frame_headers(http2_frame_headers *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    if (frame->hdr.flags & HTTP2_FLAG_PADDED) {
        *p++ = frame->pad_len;
    }
    if (frame->hdr.flags & HTTP2_FLAG_PRIORITY) {
        uint32_t stream_id = frame->pspec.exclusive ? frame->pspec.stream_id | ~HTTP2_STREAM_ID_MASK
                                                    : frame->pspec.stream_id & HTTP2_STREAM_ID_MASK;
        put_uint32_in_be_stream(p, stream_id);
        p += 4;
        *p++ = frame->pspec.weight;
    }

    memcpy(p, frame->header_block_fragment.data(), frame->header_block_fragment.size());

    return frame_data;
}

slice pack_http2_frame_priority(http2_frame_priority *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    assert(frame_length == 14);
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    uint32_t stream_id = frame->pspec.exclusive ? frame->pspec.stream_id | ~HTTP2_STREAM_ID_MASK
                                                : frame->pspec.stream_id & HTTP2_STREAM_ID_MASK;
    put_uint32_in_be_stream(p, stream_id);
    p += 4;
    *p++ = frame->pspec.weight;

    return frame_data;
}

slice pack_http2_frame_rst_stream(http2_frame_rst_stream *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    assert(frame_length == 13);
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;
    put_uint32_in_be_stream(p, frame->error_code);

    return frame_data;
}

slice pack_http2_frame_settings(http2_frame_settings *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    for (size_t i = 0; i < frame->settings.size(); i++) {
        put_uint16_in_be_stream(p, frame->settings.at(i).id);
        p += 2;
        put_uint32_in_be_stream(p, frame->settings.at(i).value);
        p += 4;
    }
    return frame_data;
}

slice pack_http2_frame_push_promise(http2_frame_push_promise *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    if (frame->hdr.flags & HTTP2_FLAG_PADDED) {
        *p++ = frame->pad_len;
    }

    uint32_t promised_stream_id = frame->reserved ? frame->promised_stream_id | ~HTTP2_STREAM_ID_MASK
                                                  : frame->promised_stream_id & HTTP2_STREAM_ID_MASK;
    put_uint32_in_be_stream(p, promised_stream_id);
    p += 4;

    memcpy(p, frame->header_block_fragment.data(), frame->header_block_fragment.size());
    return frame_data;
}

slice pack_http2_frame_ping(http2_frame_ping *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    assert(frame_length == 17);
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    p[0] = frame->opaque_data[7];
    p[1] = frame->opaque_data[6];
    p[2] = frame->opaque_data[5];
    p[3] = frame->opaque_data[4];
    p[4] = frame->opaque_data[3];
    p[5] = frame->opaque_data[2];
    p[6] = frame->opaque_data[1];
    p[7] = frame->opaque_data[0];

    return frame_data;
}

slice pack_http2_frame_goaway(http2_frame_goaway *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    uint32_t last_stream_id =
        frame->reserved ? frame->last_stream_id | ~HTTP2_STREAM_ID_MASK : frame->last_stream_id & HTTP2_STREAM_ID_MASK;
    put_uint32_in_be_stream(p, last_stream_id);
    p += 4;
    put_uint32_in_be_stream(p, frame->error_code);
    p += 4;

    memcpy(p, frame->debug_data.data(), frame->debug_data.size());
    return frame_data;
}

slice pack_http2_frame_window_update(http2_frame_window_update *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    uint32_t window_size_inc = frame->reserved ? frame->window_size_inc | ~HTTP2_STREAM_ID_MASK
                                               : frame->window_size_inc & HTTP2_STREAM_ID_MASK;
    put_uint32_in_be_stream(p, window_size_inc);

    return frame_data;
}

slice pack_http2_frame_continuation(http2_frame_continuation *frame) {
    size_t frame_length = HTTP2_FRAME_HEADER_SIZE + frame->hdr.length;
    slice frame_data = MakeSliceByLength(frame_length);

    uint8_t *p = const_cast<uint8_t *>(frame_data.data());
    http2_frame_header_pack(p, &frame->hdr);
    p += HTTP2_FRAME_HEADER_SIZE;

    memcpy(p, frame->header_block_fragment.data(), frame->header_block_fragment.size());

    return frame_data;
}
