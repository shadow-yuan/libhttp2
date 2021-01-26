#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "src/hpack/metadata.h"
#include "src/utils/slice_buffer.h"
#include "src/http2/flow_control.h"

class http2_stream {
public:
    static constexpr uint32_t MAX_STREAM_ID = 0x7fffffff;
    enum state : uint8_t {
        IDLE,
        RESERVED_LOCAL,
        RESERVED_REMOTE,
        OPEN,
        HALF_CLOSED_LOCAL,
        HALF_CLOSED_REMOTE,
        CLOSED,
        ERROR,
    };

    http2_stream(ConnectionFlowControl *cfc, uint32_t stream_id);
    ~http2_stream() {}

    // action
    void send_push_promise();
    void recv_push_promise();
    void send_headers();
    void recv_headers(const std::vector<hpack::mdelem_data> &headers);
    void send_rst_stream();
    void recv_rst_stream(uint32_t error_code);
    void send_end_stream();
    void recv_end_stream();

    // test
    bool try_send();

    uint8_t frame_type();
    uint8_t frame_flags();
    void frame_type(uint8_t type);
    void frame_flags(uint8_t flags);

    void push_headers(const std::vector<hpack::mdelem_data> &headers);
    void push_data(slice s);
    bool is_closed();
    uint32_t stream_id() const;
    void set_weight(int32_t w);
    state get_status() const;
    void mark_unwritable();
    StreamFlowControl &flow_control();

private:
    StreamFlowControl _sfc;
    uint32_t _stream_id;
    uint64_t _connection_id;

    state _state;

    uint8_t _frame_flags;
    uint8_t _frame_type;

    bool _finish_header;  // END_HEADERS

    int32_t weight;

    uint32_t _last_error;
    std::vector<hpack::mdelem_data> _headers;
    slice_buffer _data_cache;
};
