#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "src/hpack/metadata.h"
#include "src/utils/slice_buffer.h"

class http2_stream {
public:
    enum status {
        IDLE,
        RESERVED_LOCAL,
        RESERVED_REMOTE,
        OPEN,
        HALF_CLOSED_LOCAL,
        HALF_CLOSED_REMOTE,
        CLOSED,
        ERROR,
    };

    explicit http2_stream(uint32_t stream_id);
    ~http2_stream() {}

    // action
    void send_push_promise();
    void recv_push_promise();
    void send_headers();
    void recv_headers();
    void send_rst_stream();
    void recv_rst_stream();
    void send_end_stream();
    void recv_end_stream();

    uint8_t frame_type();
    uint8_t frame_flags();
    void frame_type(uint8_t type);
    void frame_flags(uint8_t flags);

    void set_connection_id(uint64_t cid);
    void set_window_size(uint32_t size);

    void push_headers(const std::vector<hpack::mdelem_data> &headers);
    void push_data(slice s);

private:
    status _cur_status;
    uint32_t _stream_id;

    uint64_t _cid;
    int32_t _window_size;

    uint8_t _frame_flags;
    uint8_t _frame_type;

    std::string _path;            // ":path"
    std::string _method;          // ":method"
    std::string _server_address;  // ":authority"
    std::string _scheme;          // ":scheme"
    std::string _status;          // ":status"

    uint32_t _last_error;
    std::vector<hpack::mdelem_data> _headers;
    slice_buffer _data_cache;
};
