#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "src/hpack/metadata.h"
#include "src/utils/slice_buffer.h"

class http2_stream {
public:
    static constexpr uint32_t MAX_STREAM_ID = 0x7fffffff;
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

    explicit http2_stream(uint64_t connection_id, uint32_t stream_id);
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

    uint8_t frame_type();
    uint8_t frame_flags();
    void frame_type(uint8_t type);
    void frame_flags(uint8_t flags);

    void set_connection_id(uint64_t cid);
    void set_window_size(uint32_t size);

    void push_headers(const std::vector<hpack::mdelem_data> &headers);
    void push_data(slice s);
    bool is_closed();
    uint32_t stream_id() const;
    void set_weight(int32_t w);
    status get_status();

private:
    status _cur_status;
    uint32_t _stream_id;

    uint64_t _cid;
    int32_t _window_size;

    uint8_t _frame_flags;
    uint8_t _frame_type;

    bool _finish_header;  // END_HEADERS

    /* Current remote window size. This value is computed against the
       current initial window size of remote endpoint. */
    int32_t remote_window_size;
    /* Keep track of the number of bytes received without
       WINDOW_UPDATE. This could be negative after submitting negative
       value to WINDOW_UPDATE */
    int32_t recv_window_size;
    /* The number of bytes consumed by the application and now is
       subject to WINDOW_UPDATE.  This is only used when auto
       WINDOW_UPDATE is turned off. */
    int32_t consumed_size;
    /* The amount of recv_window_size cut using submitting negative
       value to WINDOW_UPDATE */
    int32_t recv_reduction;
    /* window size for local flow control. It is initially set to
       NGHTTP2_INITIAL_WINDOW_SIZE and could be increased/decreased by
       submitting WINDOW_UPDATE. See nghttp2_submit_window_update(). */
    int32_t local_window_size;
    int32_t weight;

    uint32_t _last_error;
    std::vector<hpack::mdelem_data> _headers;
    slice_buffer _data_cache;
};
