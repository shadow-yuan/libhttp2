#pragma once
#include <stddef.h>
#include <stdint.h>
#include <map>
#include <memory>
#include <string>

namespace http2 {
class InitService {
public:
    virtual ~InitService() {}
    virtual void init() = 0;
    virtual void shutdown() = 0;
};

/* Implemented externally, libhttp2 internal call this interface to send tcp data */
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
 * Message
 * @Metadata example:
 * :path: /helloworld.Greeter/SayHello
 * :scheme: http
 * :method: POST

 * @Message: the byte stream after protobuf message serialization
 */
class Message {
public:
    virtual ~Message() {}
    virtual const uint8_t *Data() = 0;
    virtual size_t DataLength() = 0;
    virtual const std::multimap<std::string, std::string> &Metadata() = 0;
    virtual uint64_t ConnectionId() = 0;
};

class Response {
public:
    virtual ~Response() {}
    virtual void SetStatus(int status) = 0;  // http status, eg. 200 means ok
    virtual void AppendData(const void *buff, size_t len) = 0;
    virtual void AddMetadata(const std::string &key, const std::string &value) = 0;
    virtual uint64_t ConnectionId() = 0;
};

class DataService {
public:
    virtual ~DataService() {}

    /*
     * If you want an asynchronous response, please set async to true, and
     * call the AsyncSendResponse function of the Transport class at the right time.
     */
    virtual int OnMessage(std::shared_ptr<Message> msg, std::shared_ptr<Response> response, bool &async) = 0;
};

class Transport {
public:
    virtual ~Transport() {}

    virtual void SetDataNotificationService(DataService *service) = 0;

    // Send response message asynchronously.
    virtual void AsyncSendResponse(std::shared_ptr<Response> rsp) = 0;

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
void SetLogOutputEnable(bool enable);
}  // namespace http2
