#include "src/hpack/encode.h"
#include <time.h>
#include "src/utils/useful.h"
#include "src/hpack/static_metadata.h"

namespace hpack {

// Http1.1 DATE FORMAT
// Date: Tue, 03 Jul 2012 04:40:59 GMT
std::string build_date_string() {
    char buf[64] = {0};
    time_t now = time(nullptr);
    struct tm *gmt = gmtime(&now);
    strftime(buf, sizeof(buf), "%a, %d %h %G %T GMT", gmt);  // strlen(buf) = 29
    return std::string(buf);
}

void encode_uint16_impl(std::string &buf, int I, uint8_t mask) {
    if (I < mask) {
        buf.append(1, char(I));
        return;
    }

    I -= mask;
    buf.append(1, char(mask));
    while (I >= 128) {
        buf.append(1, char((I & 0x7f) | 0x80));
        I = I >> 7;
    }
    buf.append(1, char(I));
}

std::string encode_uint16(int I, uint8_t mask) {
    std::string buf;
    encode_uint16_impl(buf, I, mask);
    return buf;
}

void encodeH2caseHeader(std::string &buf, const std::string &key) {
    std::string buf = encode_uint16(key.length(), INT_MASK(7));
    for (auto keyIt : key) {
        if (isalpha(keyIt)) {
            buf.append(1, tolower(keyIt));
        } else if (keyIt == char('_')) {
            buf.append(1, '-');
        } else {
            buf.append(1, keyIt);
        }
    }
}

void encode_headers_impl(const std::map<std::string, std::string> &headers, std::string &buf) {

    bool has_date = false;
    for (auto it = headers.begin(); it != headers.end(); ++it) {
        const std::string &key = it->first;
        const std::string &value = it->second;

        if (!has_date && key == "date") {
            auto date = build_date_string();
            // 0f12 Date header not indexed
            // 1d = date length: 29
            buf.append("\x0f\x12\x1d", 3);
            buf.append(date);
            has_date = true;
            continue;
        }

        uint32_t index = full_match_mdelem_data_index(key, value);
        if (index > 0) {
            // already in static table
            uint8_t b = static_cast<uint8_t>(0x80 | (index & 0xff));
            buf.append(1, b);
            continue;
        }
        // RFC 7541 6.2.1
        /*
              0   1   2   3   4   5   6   7
            +---+---+---+---+---+---+---+---+
            | 0 | 1 |           0           |
            +---+---+-----------------------+
            | H |     Name Length (7+)      |
            +---+---------------------------+
            |  Name String (Length octets)  |
            +---+---------------------------+
            | H |     Value Length (7+)     |
            +---+---------------------------+
            | Value String (Length octets)  |
            +-------------------------------+
         */

        buf.append(1, 0x40);

        encode_uint16_impl(buf, key.size(), INT_MASK(7));
        buf.append(key);

        encode_uint16_impl(buf, value.size(), INT_MASK(7));
        buf.append(value);
    }
}

std::string encode_headers(const std::map<std::string, std::string> &headers) {
    std::string buf;
    encode_headers_impl(headers, buf);
    return buf;
}

std::string encode_headers(int status, const std::map<std::string, std::string> &headers) {
    std::string buf;
    if (status == 200) {
        buf.append(1, char(0x88));
    } else if (status == 204) {
        buf.append(1, char(0x89));
    } else if (status == 206) {
        buf.append(1, char(0x8A));
    } else if (status == 304) {
        buf.append(1, char(0x8B));
    } else if (status == 400) {
        buf.append(1, char(0x8C));
    } else if (status == 404) {
        buf.append(1, char(0x8D));
    } else if (status == 500) {
        buf.append(1, char(0x8E));
    } else {
        buf.append(1, char(0x08));

        const std::string status_str = std::to_string(status);
        encode_uint16_impl(buf, status_str.length(), INT_MASK(4));
        buf.append(status_str);
    }

    encode_headers_impl(headers, buf);
    return buf;
}

}  // namespace hpack
