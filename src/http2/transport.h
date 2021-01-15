#pragma once
#include <stddef.h>
#include <stdint.h>
#include <memory>
#include <vector>
#include "include/http2/http2.h"
#include "src/http2/connection.h"

class RpcCallService;
class RpcResponse;
class http2_transport {
public:
    http2_transport(http2::TcpSendService *sender);
    ~http2_transport();

    void set_rpc_call_service(http2::RpcCallService *service);
    void async_send_reply(std::shared_ptr<http2::RpcResponse> rsp);
    size_t get_max_header_size();
    int check_package_length(uint64_t cid, const void *data, size_t len);
    void connection_enter(uint64_t cid, bool client = false);
    void received_data(uint16_t cid, const void *buf, size_t len);
    void connection_leave(uint64_t cid);

    /*
        bool ConnectionComming(uint64_t cid);
        bool ConnectionClosed(uint64_t cid);

        void ReceivedHttp2Data(uint64_t cid, const uint8_t *buff, size_t buff_size);
    */
private:
    bool is_connection_exist(uint64_t cid, std::shared_ptr<http2_connection> *conn = nullptr);
    std::shared_ptr<http2_connection> create_connection(uint64_t cid, bool client);
    bool destroy_connection(uint64_t cid);

private:
    std::vector<std::shared_ptr<http2_connection>> _connections;
    http2::RpcCallService *_service = nullptr;
    http2::TcpSendService *_sender = nullptr;
};
