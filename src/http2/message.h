#pragma once
#include <stddef.h>
#include <stdint.h>
#include <map>
#include <memory>
#include <string>

#include "http2/http2.h"
#include "src/utils/slice.h"
#include "src/http2/stream.h"

class http2_message : public http2::Message {
    friend class http2_connection;
    friend class http2_stream;

public:
    http2_message(/* args */)
        : _connection_id(0) {}

    ~http2_message() = default;

    const uint8_t *Data() override {
        return _buff.data();
    }

    size_t DataLength() override {
        return _buff.size();
    }

    const std::multimap<std::string, std::string> &Metadata() override {
        return _metadata;
    }

    uint64_t ConnectionId() override {
        return _connection_id;
    }

    uint32_t StreamId() {
        return _stream->stream_id();
    }

private:
    uint64_t _connection_id;
    slice _buff;
    std::multimap<std::string, std::string> _metadata;
    std::shared_ptr<http2_stream> _stream;
};
