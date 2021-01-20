#pragma once
#include <stdint.h>
#include <memory>
#include <map>

#include "http2/http2.h"
#include "src/http2/settings.h"
#include "src/hpack/send_record.h"
#include "src/hpack/dynamic_metadata.h"

class http2_stream;
class http2_connection {
public:
    http2_connection(uint64_t cid, bool client);
    ~http2_connection();

    uint64_t connection_id() const;
    uint32_t create_stream();
    bool is_handshake();
    void handshake_done();
    void send_goaway(uint32_t error_code, uint32_t last_stream_id = 0);
    int package_process(const uint8_t *data, uint32_t len);
    void async_send_reply(std::shared_ptr<http2::RpcResponse> rsp);

private:
    std::shared_ptr<http2_stream> find_stream(uint32_t stream_id);

    void received_data(std::shared_ptr<http2_stream> stream, http2_frame *frame);
    void received_header(std::shared_ptr<http2_stream> stream, http2_frame *frame);
    void received_priority(http2_frame *frame);
    void received_rst_stream(std::shared_ptr<http2_stream> stream, http2_frame *frame);
    void received_settings(http2_frame *frame);
    void received_push_promise(std::shared_ptr<http2_stream> stream, http2_frame *frame);
    void received_ping(http2_frame *frame);
    void received_goaway(http2_frame *frame);
    void received_window_update(http2_frame *frame);
    void received_continuation(std::shared_ptr<http2_stream> stream, http2_frame *frame);

private:
    uint64_t _cid;
    bool _client;
    bool _handshake;
    uint32_t _last_stream_id;
    uint32_t _max_stream_id;
    uint32_t _client_max_stream_id;
    uint32_t _server_max_stream_id;

    std::map<uint32_t, std::shared_ptr<http2_stream>> _streams;
    uint32_t _local_settings[HTTP2_NUMBER_OF_SETTINGS];
    uint32_t _remote_settings[HTTP2_NUMBER_OF_SETTINGS];
    hpack::dynamic_metadata_table _dynamic_table;
    hpack::mdelem_send_record _send_record;

    uint32_t _goaway_stream_id;
    uint32_t _goaway_error_code;
    bool _received_goaway;
};
