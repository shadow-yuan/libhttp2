#include "src/http2/parser.h"
#include "src/utils/byte_convert.h"

#pragma pack(push, 1)
struct http2_internal_frame_header {
    uint8_t size2;
    uint8_t size1;
    uint8_t size0;
    uint8_t type;
    uint8_t flags;
    uint8_t stream_id3;
    uint8_t stream_id2;
    uint8_t stream_id1;
    uint8_t stream_id0;

    uint32_t get_payload_size();
    uint32_t get_stream_id();
};
#pragma pack(pop)

uint32_t http2_internal_frame_header::get_payload_size() {
    uint32_t result = 0;
    result = (uint32_t)size2 << 16 | (uint32_t)size1 << 8 | size0;
    return result;
}

uint32_t http2_internal_frame_header::get_stream_id() {
    uint32_t result = 0;
    result = (uint32_t)stream_id3 << 24 | (uint32_t)stream_id2 << 16 | (uint32_t)stream_id1 << 8 | stream_id0;
    return result;
}

http2_errors parse_data(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
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
    if (frame->head.flag == HTTP2_FLAG_PADDED) {
        frame->data.pad_len = *(data + offset);
        if (frame->data.pad_len >= frame->head.payload_length) {
            return HTTP2_PROTOCOL_ERROR;
        }
    }
    size_t data_len = 0;
    if (frame->data.pad_len == 0) {
        data_len = frame->head.payload_length;
    } else {
        offset += sizeof(uint8_t);
        data_len = frame->head.payload_length - frame->data.pad_len - 1;
    }
    frame->data.data = slice(void *(data + offset), data_len, slice::STATIC);

    return HTTP2_NO_ERROR;
}

http2_errors parse_headers(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +---------------+
        |Pad Length? (8)|
        +-+-------------+-----------------------------------------------+
        |E|                 Stream Dependency? (31)                     |
        +-+-------------+-----------------------------------------------+
        |  Weight? (8)  |
        +-+-------------+-----------------------------------------------+
        |                   Header Block Fragment (*)                 ...
        +---------------------------------------------------------------+
        |                           Padding (*)                       ...
        +---------------------------------------------------------------+
    */
    frame->headers.pad_len = 0;
    size_t block_len = frame->head.payload_length;
    frame->headers.stream_id = 0;
    frame->headers.weight = 0;
    switch (frame->head.flag) {
    case HTTP2_FLAG_PADDED: {
        frame->headers.pad_len = *reinterpret_cast<const uint8_t *>(data + offset);
        if (frame->headers.pad_len >= frame->head.payload_length) {
            return HTTP2_PROTOCOL_ERROR;
        }
        offset += sizeof(uint8_t);
        block_len -= sizeof(uint8_t) + frame->headers.pad_len;
    } break;
    case HTTP2_FLAG_PRIORITY: {
        frame->headers.stream_id = get_uint32_from_byte(data + offset);
        offset += sizeof(uint32_t);
        block_len -= sizeof(uint32_t);
        frame->headers.weight = *(data + offset);
        offset += sizeof(uint8_t);
        block_len -= sizeof(uint8_t);
        if (frame->headers.stream_id == 0) {
            return HTTP2_PROTOCOL_ERROR;
        }
    } break;
    }
    frame->headers.header_block_fragment = slice(void *(data + offset), block_len, slice::STATIC);

    return HTTP2_NO_ERROR;
}

http2_errors parse_priority(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +-+-------------------------------------------------------------+
        |E|                  Stream Dependency (31)                     |
        +-+-------------+-----------------------------------------------+
        |   Weight (8)  |
        +-+-------------+
    */
    if (frame->head.payload_length != (sizeof(uint32_t) + sizeof(uint8_t)) /*6*/) {
        return HTTP2_FRAME_SIZE_ERROR;
    }
    frame->priority.stream_id = get_uint32_from_byte(data + offset);
    if (frame->priority.stream_id == 0) {
        return HTTP2_PROTOCOL_ERROR;
    }
    offset += sizeof(uint32_t);
    frame->priority.weight = *(data + offset);

    return HTTP2_NO_ERROR;
}

http2_errors parse_rst_stream(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +---------------------------------------------------------------+
        |                        Error Code (32)                        |
        +---------------------------------------------------------------+
    */
    if (frame->head.payload_length != sizeof(uint32_t)) {
        return HTTP2_FRAME_SIZE_ERROR;
    }
    frame->rst_stream.error_code = get_uint32_from_byte(data + offset);

    return HTTP2_NO_ERROR;
}

http2_errors parse_settings(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +-------------------------------+
        |       Identifier (16)         |
        +-------------------------------+-------------------------------+
        |                        Value (32)                             |
        +---------------------------------------------------------------+
    */
    if (frame->head.payload_length % 6) {
        return HTTP2_FRAME_SIZE_ERROR;
    }
    frame->settings.count = frame->head.payload_length / 6;
    frame->settings.settings = (http2_settings_entry *)new uint8_t[frame->head.payload_length];
    for (size_t i = 0; i < frame->settings.count; i++) {
        frame->settings.settings[i].id = get_uint16_from_byte(data + offset + i * 6);
        frame->settings.settings[i].value = get_uint32_from_byte(data + offset + i * 6 + 2);
    }

    return HTTP2_NO_ERROR;
}

http2_errors parse_promise(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +---------------+
        |Pad Length? (8)|
        +-+-------------+-----------------------------------------------+
        |R|                  Promised Stream ID (31)                    |
        +-+-----------------------------+-------------------------------+
        |                   Header Block Fragment (*)                 ...
        +---------------------------------------------------------------+
        |                           Padding (*)                       ...
        +---------------------------------------------------------------+
    */
    size_t block_len = frame->head.payload_length;
    if (frame->head.flag == HTTP2_FLAG_PADDED) {
        frame->promise.pad_len = *(data + offset);
        if (frame->headers.pad_len >= frame->head.payload_length) {
            return HTTP2_PROTOCOL_ERROR;
        }
        offset += sizeof(uint8_t);
        block_len -= sizeof(uint8_t) + frame->headers.pad_len;
    }
    frame->promise.promised_stream_id = get_uint32_from_byte(data + offset);
    if (frame->promise.promised_stream_id == 0) {
        return HTTP2_PROTOCOL_ERROR;
    }
    offset += sizeof(uint32_t);
    block_len -= sizeof(uint32_t);

    frame->promise.header_block_fragment = slice(void *(data + offset), block_len, slice::STATIC);

    return HTTP2_NO_ERROR;
}

http2_errors parse_ping(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +---------------------------------------------------------------+
        |                                                               |
        |                      Opaque Data (64)                         |
        |                                                               |
        +---------------------------------------------------------------+
    */
    if (frame->head.payload_length != sizeof(uint64_t)) {
        return HTTP2_FRAME_SIZE_ERROR;
    }
    frame->ping.data = get_uint64_from_byte(data + offset);

    return HTTP2_NO_ERROR;
}

http2_errors parse_goaway(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +-+-------------------------------------------------------------+
        |R|                  Last-Stream-ID (31)                        |
        +-+-------------------------------------------------------------+
        |                      Error Code (32)                          |
        +---------------------------------------------------------------+
        |                  Additional Debug Data (*)                    |
        +---------------------------------------------------------------+
    */
    frame->goaway.last_stream_id = get_uint32_from_byte(data + offset);
    offset += sizeof(uint32_t);
    if (frame->goaway.last_stream_id == 0) {
        return HTTP2_PROTOCOL_ERROR;
    }
    frame->goaway.error_code = get_uint32_from_byte(data + offset);
    offset += sizeof(uint32_t);
    size_t data_len = frame->head.payload_length - sizeof(uint32_t) * 2;
    frame->goaway.data = slice(void *(data + offset), data_len, slice::STATIC);
    return HTTP2_NO_ERROR;
}

http2_errors parse_window_update(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +-+-------------------------------------------------------------+
        |R|              Window Size Increment (31)                     |
        +-+-------------------------------------------------------------+
    */
    if (frame->head.payload_length != 4) {
        return HTTP2_FRAME_SIZE_ERROR;
    }
    frame->window_update.size = get_uint32_from_byte(data + offset);
    if (frame->window_update.size == 0) {
        return HTTP2_PROTOCOL_ERROR;
    }

    return HTTP2_NO_ERROR;
}

http2_errors parse_continuation(size_t offset, const uint8_t *data, size_t len, http2_frame *frame) {
    /*
        +---------------------------------------------------------------+
        |                   Header Block Fragment (*)                 ...
        +---------------------------------------------------------------+
    */
    frame->continuation.header_block_fragment = slice(void *(data + offset), frame->head.payload_length, slice::STATIC);

    return HTTP2_NO_ERROR;
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
http2_errors http2_parse(const uint8_t *data, size_t len, http2_frame *frame) {
    if (frame == nullptr) {
        return HTTP2_NO_ERROR;
    }
    if (len < sizeof(http2_internal_frame_header) /*9*/) {
        return HTTP2_FRAME_SIZE_ERROR;
    }
    size_t offset = 0;
    http2_internal_frame_header *head = (http2_internal_frame_header *)data;
    frame->head.type = head->type;
    frame->head.flag = head->flags;
    frame->head.payload_length = head->get_payload_size();
    frame->head.stream_id = head->get_stream_id();
    offset += sizeof(http2_internal_frame_header);
    if (len - offset != frame->head.payload_length)
        return HTTP2_FRAME_SIZE_ERROR;
    switch (head->type) {
    case HTTP2_FRAME_DATA: {
        return parse_data(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_HEADERS: {
        return parse_headers(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_PRIORITY: {
        return parse_priority(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_RST_STREAM: {
        return parse_rst_stream(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_SETTINGS: {
        return parse_settings(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_PUSH_PROMISE: {
        return parse_promise(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_PING: {
        return parse_ping(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_GOAWAY: {
        return parse_goaway(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_WINDOW_UPDATE: {
        return parse_window_update(offset, data, len, frame);
    } break;
    case HTTP2_FRAME_CONTINUATION: {
        return parse_continuation(offset, data, len, frame);
    } break;
    }

    return HTTP2_PROTOCOL_ERROR;
}
