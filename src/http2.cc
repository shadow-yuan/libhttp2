#include "http2/http2.h"
#include "src/http2/transport.h"
#include "src/utils/log.h"

class http2_transport;
namespace http2 {
class TransportImpl : public Transport {
public:
    explicit TransportImpl(TcpSendService *sender);
    ~TransportImpl();

    void SetDataNotificationService(DataService *service) override;

    // Send response message asynchronously.
    void AsyncSendResponse(std::shared_ptr<Response> rsp) override;

    // Call this function to get the maximum header size of the http2 package.
    size_t GetHttp2PackageMaxHeader() override;

    /*
     * Return -1 means an error occurred, return 0 means still need to provide
     * data, other values greater than 0 means the length of a complete http2
     * packet. When calling the ReceivedData function, at least one complete
     * http2 package must be provided.
     */
    int CheckHttp2PackageLength(uint64_t cid, const void *data, size_t len) override;

    // Call this function to notify that the connection has been established.
    void ConnectionEstablished(uint64_t cid, bool client = false) override;

    /*
     * Need to provide one or more complete http2 data package. To get the
     * complete http2 package, please check CheckHttp2PackageLength function.
     */
    void ReceivedHttp2Data(uint64_t cid, const void *buf, size_t len) override;

    // Call this function to notify a connection to be disconnected.
    void Disconnect(uint64_t cid) override;

private:
    std::shared_ptr<http2_transport> _impl;
};

TransportImpl::TransportImpl(TcpSendService *sender)
    : _impl(std::make_shared<http2_transport>(sender)) {}

TransportImpl::~TransportImpl() {}

void TransportImpl::SetDataNotificationService(DataService *service) {
    _impl->set_data_notification_service(service);
}

// Send response message asynchronously.
void TransportImpl::AsyncSendResponse(std::shared_ptr<Response> rsp) {
    _impl->async_send_response(rsp);
}

// Call this function to get the maximum header size of the http2 package.
size_t TransportImpl::GetHttp2PackageMaxHeader() {
    return _impl->get_max_header_size();
}

/*
 * Return -1 means an error occurred, return 0 means still need to provide
 * data, other values greater than 0 means the length of a complete http2
 * packet. When calling the ReceivedData function, at least one complete
 * http2 package must be provided.
 */
int TransportImpl::CheckHttp2PackageLength(uint64_t cid, const void *data, size_t len) {
    return _impl->check_package_length(cid, data, len);
}

// Call this function to notify that the connection has been established.
void TransportImpl::ConnectionEstablished(uint64_t cid, bool client) {
    _impl->connection_enter(cid, client);
}

/*
 * Need to provide one or more complete http2 data package. To get the
 * complete http2 package, please check CheckHttp2PackageLength function.
 */
void TransportImpl::ReceivedHttp2Data(uint64_t cid, const void *buf, size_t len) {
    _impl->received_data(cid, buf, len);
}

// Call this function to notify a connection to be disconnected.
void TransportImpl::Disconnect(uint64_t cid) {
    _impl->connection_leave(cid);
}

Transport *CreateTransport(TcpSendService *sender) {
    auto transport = new TransportImpl(sender);
    return transport;
}

void DestroyTransport(Transport *transport) {
    delete transport;
}

void SetLogOutputEnable(bool enable) {
    global_enable_log_output(enable);
}
}  // namespace http2
