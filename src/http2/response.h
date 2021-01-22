#pragma once
#include <map>
#include <memory>
#include <string>

#include "http2/http2.h"
#include "src/utils/slice_buffer.h"
#include "src/http2/stream.h"

class http2_response : public http2::Response {
    friend class http2_connection;
    friend class http2_stream;

public:
    http2_response()
        : _connection_id(0)
        , _status(200) {}

    ~http2_response() = default;

    void SetStatus(int status) override {
        _status = status;
    }

    void AppendData(const void *buff, size_t len) override {
        if (len > 0) {
            _buff.add_slice(slice(buff, len));
        }
    }

    void AddMetadata(const std::string &key, const std::string &value) override {
        _metadata.insert({key, value});
    }

    uint64_t ConnectionId() override {
        return _connection_id;
    }

    uint32_t StreamId() {
        return _stream->stream_id();
    }

private:
    uint64_t _connection_id;
    int _status;
    slice_buffer _buff;
    std::multimap<std::string, std::string> _metadata;
    std::shared_ptr<http2_stream> _stream;
};
