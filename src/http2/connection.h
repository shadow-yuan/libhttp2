#pragma once
#include <stdint.h>
#include <memory>
#include <map>

#include "http2/http2.h"
#include "src/http2/settings.h"
#include "src/hpack/send_record.h"
#include "src/hpack/dynamic_metadata.h"
#include "src/utils/slice_buffer.h"

class http2_response;
class http2_stream;
class http2_connection {
public:
    static constexpr char PREFACE[] = "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n";
    static constexpr int PREFACE_SIZE = 24;
    static constexpr int INITIAL_WINDOW_SIZE = 4 * 1024 * 1024;
    static constexpr int MAX_FRAME_SIZE = 4 * 1024 * 1024;
    static constexpr int MAX_HEADER_LIST_SIZE = 8192;
    static constexpr int GRPC_ALLOW_TRUE_BINARY_METADATA = 1;

    http2_connection(http2::TcpSendService *sender, uint64_t cid, bool client_side);
    ~http2_connection();

    uint64_t connection_id() const;
    std::shared_ptr<http2_stream> find_stream(uint32_t stream_id);

    // for server side use
    bool need_verify_preface();
    void verify_preface_done();

    void send_goaway(uint32_t error_code, uint32_t last_stream_id = 0);
    int package_process(const uint8_t *data, uint32_t len);
    void async_send_response(std::shared_ptr<http2_response> rsp);

    uint32_t local_max_frame_size();

private:
    // if fail return 0
    uint32_t create_stream();

    void received_data(std::shared_ptr<http2_stream> &stream, http2_frame_data *frame);
    void received_header(std::shared_ptr<http2_stream> &stream, http2_frame_headers *frame);
    void received_priority(std::shared_ptr<http2_stream> &stream, http2_frame_priority *frame);
    void received_rst_stream(std::shared_ptr<http2_stream> &stream, http2_frame_rst_stream *frame);
    void received_settings(http2_frame_settings *frame);
    void received_push_promise(std::shared_ptr<http2_stream> &stream, http2_frame_push_promise *frame);
    void received_ping(http2_frame_ping *frame);
    void received_goaway(http2_frame_goaway *frame);
    void received_window_update(std::shared_ptr<http2_stream> &stream, http2_frame_window_update *frame);
    void received_continuation(std::shared_ptr<http2_stream> &stream, http2_frame_continuation *frame);

    void send_tcp_data(slice_buffer &sb);
    void send_tcp_data(slice s);

private:
    hpack::dynamic_metadata_table _dynamic_table;
    http2::TcpSendService *_sender_service;
    uint64_t _connection_id;
    bool _client_side;

    uint32_t _local_settings[HTTP2_NUMBER_OF_SETTINGS];
    uint32_t _remote_settings[HTTP2_NUMBER_OF_SETTINGS];

    bool _finish_handshake;
    uint32_t _last_stream_id;
    uint32_t _next_stream_id;

    std::map<uint32_t, std::shared_ptr<http2_stream>> _streams;

    hpack::mdelem_send_record _send_record;

    uint32_t _goaway_stream_id;
    bool _received_goaway;

    int64_t _local_window_size;
    int64_t _remote_window_size;
    int64_t _init_window_size;

    bool _next_frame_limit;
    uint32_t _next_frame_stream_id;
};
