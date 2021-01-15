#pragma once
#include <stddef.h>
#include <stdint.h>
#include <memory>

namespace http2 {
class InitService {
public:
    virtual ~InitService() {}
    virtual void init() = 0;
    virtual void shutdown() = 0;
};

/* Call this interface to send tcp data */
class TcpSendService {
public:
    virtual ~TcpSendService() {}

    //
    // cid:  cid refers to the connection id, managed by the external network module
    // buf:  buf refers to the data pointer to be sent
    // size: size refers to the length of the data to be sent
    virtual bool SendTcpData(uint64_t cid, const void *buf, size_t size);
};

/*
 * Rpc request
 * Example:
 * Path: rpc service, such as '/helloworld.Greeter/SayHello'
 * Method: http method, such as POST or GET
 * Remote: Remote service address, such as 'localhost:50051'
 * Payload: the byte stream after protobuf message serialization
 */
class RpcRequest {
public:
    virtual ~RpcRequest() {}
    virtual const uint8_t *Path() = 0;
    virtual const uint8_t *Method() = 0;
    virtual const uint8_t *Remote() = 0;
    virtual const uint8_t *Payload() = 0;
    virtual size_t PayloadLength() = 0;
};

class RpcResponse {
public:
    virtual ~RpcResponse() {}
    virtual void SetStatus(int status = 200) = 0;
    virtual void AttachMsg(const void *buff, size_t len) = 0;
};

class RpcCallService {
public:
    virtual ~RpcCallService() {}

    /*
     * If you want an asynchronous response, please set async to true, and
     * call the AsyncReply function of the Transport class at the right time.
     */
    virtual int OnCall(std::shared_ptr<RpcRequest> request, std::shared_ptr<RpcResponse> response, bool &async) = 0;
};

class Transport {
public:
    virtual ~Transport() {}

    virtual void SetRpcCallService(RpcCallService *service) = 0;

    // Send response message asynchronously.
    virtual void AsyncReply(std::shared_ptr<RpcResponse> rsp) = 0;

    // Call this function to get the maximum header size of the http2 package.
    virtual size_t GetHttp2PackageMaxHeader() = 0;

    /*
     * Return -1 means an error occurred, return 0 means still need to provide
     * data, other values greater than 0 means the length of a complete http2
     * packet. When calling the ReceivedData function, at least one complete
     * http2 package must be provided.
     */
    virtual int CheckHttp2PackageLength(uint64_t cid, const void *data, size_t len) = 0;

    // Call this function to notify that the connection has been established.
    virtual void ConnectionEstablished(uint64_t cid, bool client = false) = 0;

    /*
     * Need to provide one or more complete http2 data package. To get the
     * complete http2 package, please check CheckHttp2PackageLength function.
     */
    virtual void ReceivedHttp2Data(uint16_t cid, const void *buf, size_t len) = 0;

    // Call this function to notify a connection to be disconnected.
    virtual void Disconnect(uint64_t cid) = 0;
};

Transport *CreateTransport(TcpSendService *sender);
void DestroyTransport(Transport *transport);

}  // namespace http2
