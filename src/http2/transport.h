#pragma once
#include <stddef.h>
#include <stdint.h>
#include <map>
#include <memory>
#include <mutex>
#include <utility>

#include "http2/http2.h"

class http2_connection;
class http2_transport {
public:
    explicit http2_transport(http2::TcpSendService *sender);
    ~http2_transport();

    void set_rpc_call_service(http2::RpcCallService *service);
    void async_send_reply(std::shared_ptr<http2::RpcResponse> rsp);
    size_t get_max_header_size();
    int check_package_length(uint64_t cid, const void *data, size_t len);
    void connection_enter(uint64_t cid, bool client_side);
    void received_data(uint16_t cid, const void *buf, size_t len);
    void connection_leave(uint64_t cid);

private:
    std::shared_ptr<http2_connection> find_connection(uint64_t cid);

    http2::TcpSendService *_tcp_sender;
    http2::RpcCallService *_call_service;
    std::map<uint64_t, std::shared_ptr<http2_connection>> _connections;
    std::mutex _mutex;
};
