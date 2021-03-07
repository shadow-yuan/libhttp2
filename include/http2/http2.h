#pragma once
#include <stdint.h>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace http2 {
class InitService {
public:
    virtual ~InitService() {}
    virtual void init() = 0;
    virtual void shutdown() = 0;
};

/* Implemented externally, libhttp2 internal call this interface to send tcp data */
class SendService {
public:
    virtual ~SendService() {}

    //
    // cid:  cid refers to the connection id, managed by the external network module
    // buf:  buf refers to the data pointer to be sent
    // size: size refers to the length of the data to be sent
    virtual bool SendRawData(uint64_t cid, const uint8_t *buf, uint32_t size);
};

class Stream {
public:
    virtual ~Stream() {}
    virtual uint64_t ConnectionId() = 0;
    virtual uint32_t StreamId() = 0;

    virtual int32_t Weight() = 0;  // Priority
    virtual bool Exclusive() = 0;  // Priority
    virtual int32_t Flags() = 0;
    virtual uint32_t ErrorCode() = 0;

    virtual bool GetDataBlock(uint8_t **ptr, uint32_t *size) = 0;
    virtual std::multimap<std::string, std::string> GetHeaders() = 0;
};

class StreamHandler {
public:
    virtual ~StreamHandler() {}
    virtual void OnHeaders(Stream *stream) = 0;
    virtual void OnMessage(Stream *stream) = 0;  // FRAME_DATA
};

class Request {
public:
    virtual ~Request() {}
    virtual void SetConnectionId(uint64_t cid) = 0;
    virtual void SetStreamId(uint32_t sid) = 0;
    virtual void AddMetadata(const std::string &key, const std::string &value);
    virtual void AppendData(const uint8_t *data, uint32_t size);
    virtual void Finish();  // finish stream (flag: END_OF_STREAM)
};

class Response {
public:
    virtual ~Response() {}
    virtual void SetConnectionId(uint64_t cid) = 0;
    virtual void SetStreamId(uint32_t sid) = 0;
    virtual void AppendData(const uint8_t *data, uint32_t size);
    virtual void AddInitlizeMetadata(const std::string &key, const std::string &value);
    virtual void AddTrailingMetadata(const std::string &key, const std::string &value);
    virtual void Finish();  // finish stream (flag: END_OF_STREAM)
};

class Transport {
public:
    virtual ~Transport() {}

    virtual void SetStreamHandler(StreamHandler *handler) = 0;
    virtual void SetSendService(SendService *sender) = 0;

    // Local Stream
    virtual Stream *CreateStream(uint64_t connection_id) = 0;

    virtual bool AsyncRequest(Request *req);
    virtual bool AsyncResponse(Response *rsp);

    /*
     * Return -1 means an error occurred, return 0 means still need to provide
     * data, other values greater than 0 means the length of a complete http2
     * packet. When calling the ReceivedData function, at least one complete
     * http2 package must be provided.
     */
    virtual int CheckHttp2PackageLength(uint64_t cid, const void *data, uint32_t len) = 0;

    // Call this function to notify that the connection has been established.
    virtual void ConnectionEstablished(uint64_t cid, bool client = false) = 0;

    /*
     * Need to provide one or more complete http2 data package. To get the
     * complete http2 package, please check CheckHttp2PackageLength function.
     */
    virtual void ReceivedHttp2Data(uint64_t cid, const void *buf, uint32_t len) = 0;

    // Call this function to notify a connection to be disconnected.
    virtual void Disconnect(uint64_t cid) = 0;
};

Transport *CreateTransport();
void DestroyTransport(Transport *transport);

enum LobLevel { kDebug = 0, kInfo = 1, kWarn = 2, kError = 3 };
void SetLogPrintFunction(void (*print_func)(const char *file, int line, int level, const char *message));
void SetLogOutputEnable(bool enable);
}  // namespace http2
