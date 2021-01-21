#include "src/http2/frame.h"
#include "src/utils/byte_order.h"

void http2_frame_header_pack(uint8_t *buf, const http2_frame_hdr *hd) {
    put_uint32_in_be_stream(&buf[0], (uint32_t)(hd->length << 8));
    buf[3] = hd->type;
    buf[4] = hd->flags;
    put_uint32_in_be_stream(&buf[5], (uint32_t)hd->stream_id);
    // ignore hd->reserved for now
}

void http2_frame_header_unpack(http2_frame_hdr *hd, const uint8_t *buf) {
    hd->length = get_uint32_from_be_stream(&buf[0]) >> 8;
    hd->type = buf[3];
    hd->flags = buf[4];
    hd->stream_id = get_uint32_from_be_stream(&buf[5]) & HTTP2_STREAM_ID_MASK;
    hd->reserved = 0;
}

void http2_frame_header_init(http2_frame_hdr *hd, size_t length, uint8_t type, uint8_t flags, uint32_t stream_id) {
    hd->length = length;
    hd->type = type;
    hd->flags = flags;
    hd->stream_id = stream_id;
    hd->reserved = 0;
}

http2_frame_settings build_http2_frame_settings(int flags, const std::vector<http2_settings_entry> &settings) {
    http2_frame_settings frame;
    size_t length = 0;
    if (!settings.empty()) {
        length = 6 * settings.size();
    }
    http2_frame_header_init(&frame.hdr, length, HTTP2_FRAME_SETTINGS, flags, 0);
    frame.settings = settings;
    return frame;
}

http2_frame_settings build_http2_frame_settings_ack() {
    http2_frame_settings frame;
    http2_frame_header_init(&frame.hdr, 0, HTTP2_FRAME_SETTINGS, HTTP2_FLAG_ACK, 0);
    return frame;
}

http2_frame_ping build_http2_frame_ping(uint8_t payload[8], bool ack) {
    http2_frame_ping frame;
    uint8_t flags = ack ? HTTP2_FLAG_ACK : 0;
    http2_frame_header_init(&frame.hdr, 8, HTTP2_FRAME_PING, flags, 0);
    memcpy(frame.opaque_data, payload, 8);
    return frame;
}
