#include "src/http2/parser.h"
#include <assert.h>
#include "src/http2/settings.h"
#include "src/utils/byte_order.h"

static int on_frame_data(frame_parser *);
static int on_frame_headers(frame_parser *);
static int on_frame_priority(frame_parser *);
static int on_frame_rst_stream(frame_parser *);
static int on_frame_settings(frame_parser *);
static int on_frame_push_promise(frame_parser *);
static int on_frame_ping(frame_parser *);
static int on_frame_goaway(frame_parser *);
static int on_frame_window_update(frame_parser *);
static int on_frame_continuation(frame_parser *);

static int on_frame_data(frame_parser *parser) {
    /*
        +---------------+
        |Pad Length? (8)|
        +---------------+-----------------------------------------------+
        |                            Data (*)                         ...
        +---------------------------------------------------------------+
        |                           Padding (*)                       ...
        +---------------------------------------------------------------+
    */

    const uint8_t *data = nullptr;
    int data_size = 0;

    uint8_t pad_length = 0;
    if (parser->frame->hdr.flags & HTTP2_FLAG_PADDED) {
        pad_length = parser->input[0];
        data = parser->input + 1;
        data_size = parser->input_size - pad_length - 1;  // 1 bytes pad length
    } else {
        data = parser->input;
        data_size = parser->frame->hdr.length;
    }

    parser->frame->data.data = MakeStaticSlice(data, data_size);
    parser->frame->data.pad_len = pad_length;

    if (pad_length >= parser->input_size) {
        parser->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }

    return HTTP2_NO_ERROR;
}

static int on_frame_headers(frame_parser *p) {
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

    if (p->frame->hdr.stream_id == 0) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }

    const uint8_t *payload = nullptr;
    size_t payload_length = 0;
    uint8_t pad_length = 0;

    if (p->frame->hdr.flags & HTTP2_FLAG_PADDED) {
        pad_length = p->input[0];
        payload = p->input + 1;
        payload_length = p->input_size - pad_length - 1;
    } else {
        pad_length = 0;
        payload = p->input;
        payload_length = p->frame->hdr.length;
    }

    p->frame->headers.pad_len = pad_length;
    if (pad_length >= p->input_size) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }

    int32_t dep_stream_id = 0;
    uint8_t exclusive = 0;
    int32_t weight = 0;

    if (p->frame->hdr.flags & HTTP2_FLAG_PRIORITY) {
        dep_stream_id = get_uint32_from_be_stream(payload) & HTTP2_STREAM_ID_MASK;
        exclusive = (payload[0] & 0x80) != 0;
        weight = payload[4] + 1;  // 1-256

        payload += 4 + 1;  // weight + stream id
        payload_length -= 4 + 1;
    }
    p->frame->headers.pspec.stream_id = dep_stream_id;
    p->frame->headers.pspec.weight = weight;
    p->frame->headers.pspec.exclusive = exclusive;
    p->frame->headers.header_block_fragment = MakeStaticSlice(payload, payload_length);

    return HTTP2_NO_ERROR;
}

static int on_frame_rst_stream(frame_parser *p) {
    /*
        +---------------------------------------------------------------+
        |                        Error Code (32)                        |
        +---------------------------------------------------------------+
     */

    if (p->input_size != 4) {
        p->error_code = HTTP2_FRAME_SIZE_ERROR;
        return HTTP2_FRAME_SIZE_ERROR;
    }
    p->frame->rst_stream.error_code = get_uint32_from_be_stream(p->input);
    return HTTP2_NO_ERROR;
}

static int on_frame_settings(frame_parser *p) {
    /*
        +-------------------------------+
        |       Identifier (16)         |
        +-------------------------------+-------------------------------+
        |                        Value (32)                             |
        +---------------------------------------------------------------+
     */

    p->frame->settings.settings.clear();

    if (p->frame->hdr.flags & HTTP2_FLAG_ACK) {
        if (p->input_size != 0) {
            p->error_code = HTTP2_FRAME_SIZE_ERROR;
            return HTTP2_FRAME_SIZE_ERROR;
        }
        return HTTP2_NO_ERROR;
    }

    if (p->input_size % 6) {
        p->error_code = HTTP2_FRAME_SIZE_ERROR;
        return HTTP2_FRAME_SIZE_ERROR;
    }

    if (p->frame->hdr.stream_id) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }

    // uint16_t id + uint32_t value = 6 bytes
    size_t niv = p->input_size / 6;

    const uint8_t *payload = p->input;
    for (size_t i = 0; i < niv; i++) {
        http2_settings_entry entry;
        entry.id = get_uint16_from_be_stream(payload);
        entry.value = get_uint32_from_be_stream(payload + 2);
        payload += 6;
    }

    return HTTP2_NO_ERROR;
}

static int on_frame_ping(frame_parser *p) {
    /*
        +---------------------------------------------------------------+
        |                                                               |
        |                      Opaque Data (64)                         |
        |                                                               |
        +---------------------------------------------------------------+
     */
    if (p->input_size != 8) {
        p->error_code = HTTP2_FRAME_SIZE_ERROR;
    } else if (p->frame->hdr.stream_id) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
    } else {
        memcpy(p->frame->ping.opaque_data, p->input, 8);
    }
    return p->error_code;
}

static int on_frame_goaway(frame_parser *p) {
    /*
        +-+-------------------------------------------------------------+
        |R|                  Last-Stream-ID (31)                        |
        +-+-------------------------------------------------------------+
        |                      Error Code (32)                          |
        +---------------------------------------------------------------+
        |                  Additional Debug Data (*)                    |
        +---------------------------------------------------------------+
    */
    if (p->frame->hdr.stream_id) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
    } else {
        p->frame->goaway.reserved = (p->input[0] & 0x80) != 0;
        p->frame->goaway.last_stream_id = get_uint32_from_be_stream(p->input) & HTTP2_STREAM_ID_MASK;
        p->frame->goaway.error_code = get_uint32_from_be_stream(p->input + sizeof(uint32_t));
        p->frame->goaway.debug_data = MakeStaticSlice(p->input + 8, p->input_size - 8);
    }
    return p->error_code;
}

static int on_frame_window_update(frame_parser *p) {
    /*
        +-+-------------------------------------------------------------+
        |R|              Window Size Increment (31)                     |
        +-+-------------------------------------------------------------+
    */
    if (p->input_size != 4) {
        p->error_code = HTTP2_FRAME_SIZE_ERROR;
    } else {
        p->frame->window_update.reserved = (p->input[0] & 0x80) != 0;
        p->frame->window_update.window_size_inc = get_uint32_from_be_stream(p->input) & HTTP2_STREAM_ID_MASK;
        if (p->frame->window_update.window_size_inc < 1 || p->frame->window_update.window_size_inc > 2147483647) {
            p->error_code = HTTP2_PROTOCOL_ERROR;
        }
    }
    return p->error_code;
}

static int on_frame_continuation(frame_parser *p) {
    /*
        +---------------------------------------------------------------+
        |                   Header Block Fragment (*)                 ...
        +---------------------------------------------------------------+
        follow HEADERS, IF NOT SET END_HEADERS FLAG
    */

    if (p->first_frame || (p->prev_type != HTTP2_FRAME_HEADERS) || (p->prev_flags & HTTP2_FLAG_END_HEADERS)) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
    } else {
        p->frame->continuation.header_block_fragment = MakeStaticSlice(p->input, p->input_size);
    }
    return p->error_code;
}

static int on_frame_priority(frame_parser *p) {
    /*
        +-+-------------------------------------------------------------+
        |E|                  Stream Dependency (31)                     |
        +-+-------------+-----------------------------------------------+
        |   Weight (8)  |
        +-+-------------+
        don't have anty flags
    */
    if (p->frame->hdr.length != 5) {
        p->error_code = HTTP2_FRAME_SIZE_ERROR;
    } else if (p->frame->hdr.stream_id == 0) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
    } else {
        p->frame->priority.pspec.stream_id = get_uint32_from_be_stream(p->input) & HTTP2_STREAM_ID_MASK;
        p->frame->priority.pspec.exclusive = (p->input[0] & 0x80) != 0;
        p->frame->priority.pspec.weight = p->input[4] + 1;  // 1-256
    }
    return p->error_code;
}

static int on_frame_push_promise(frame_parser *p) {
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
    uint8_t pad_len = 0;
    const uint8_t *payload = nullptr;
    uint32_t payload_size = 0;
    if (p->frame->hdr.flags & HTTP2_FLAG_PADDED) {
        pad_len = p->input[0];
        payload = p->input + 1;
        payload_size = p->input_size - pad_len - 1;

    } else {
        payload = p->input;
        payload_size = p->input_size;
    }

    if (pad_len >= p->input_size) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }

    uint32_t stream_id = get_uint32_from_be_stream(payload) & HTTP2_STREAM_ID_MASK;
    if (stream_id == 0) {
        p->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }

    p->frame->promise.promised_stream_id = stream_id;
    p->frame->promise.reserved = (payload[0] & 0x80) != 0;
    p->frame->promise.pad_len = pad_len;
    p->frame->promise.header_block_fragment = MakeStaticSlice(payload + 4, payload_size - 4);
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

typedef int (*parser_func)(frame_parser *);
static parser_func parser_funcs[] = {
    on_frame_data,         on_frame_headers, on_frame_priority, on_frame_rst_stream,    on_frame_settings,
    on_frame_push_promise, on_frame_ping,    on_frame_goaway,   on_frame_window_update, on_frame_continuation};

int http2_package_parse(frame_parser *parser) {
    if (parser->frame->hdr.type > HTTP2_FRAME_CONTINUATION) {
        parser->error_code = HTTP2_PROTOCOL_ERROR;
        return HTTP2_PROTOCOL_ERROR;
    }
    parser_func callback = parser_funcs[parser->frame->hdr.type];
    return callback(parser);
}

int check_http2_package_length(const void *data, size_t len) {
    if (len < HTTP2_FRAME_HEADER_SIZE) {
        return 0;
    }

    assert(data != nullptr);

    http2_frame_header hdr;
    http2_frame_header_unpack(&hdr, static_cast<const uint8_t *>(data));

    const http2_setting_parameters &max_frame_size_settings =
        g_http2_settings_parameters[HTTP2_SETTINGS_MAX_FRAME_SIZE];
    if (hdr.length < max_frame_size_settings.min_value || hdr.length > max_frame_size_settings.max_value) {
        // send GOAWAY, error_code FRAME_SIZE_ERROR
        return -1;
    }
    return static_cast<int>(hdr.length + HTTP2_FRAME_HEADER_SIZE);
}
