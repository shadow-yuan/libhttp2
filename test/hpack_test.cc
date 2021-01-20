#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "src/utils/testutil.h"
#include "src/hpack/hpack.h"
#include "src/hpack/dynamic_metadata.h"
#include "src/hpack/static_metadata.h"
#include "src/hpack/send_record.h"

class HpackTest {};

const char *req1 =
    "8683400a3a617574686f72697479153135302e3135382e3139322e3135303a353030353140053a706174682f2f68656c6c6f73747265616d69"
    "6e67776f726c642e4d756c7469477265657465722f736179526567756c61724d73674002746508747261696c657273400c636f6e74656e742d"
    "74797065106170706c69636174696f6e2f67727063400a757365722d6167656e742d677270632d632b2b2f312e33332e3220677270632d632f"
    "31332e302e3020286c696e75783b20636874747032294014677270632d6163636570742d656e636f64696e67156964656e746974792c646566"
    "6c6174652c677a6970400f6163636570742d656e636f64696e670d6964656e746974792c677a6970";

const char *req2 = "8683c40f342f2f68656c6c6f73747265616d696e67776f726c642e4d756c7469477265657465722f73617953747265616d5"
                   "0726f63c2c1c0bfbe";

const char *req3 = "8683c40f342f2f68656c6c6f73747265616d696e67776f726c642e4d756c7469477265657465722f73617953747265616d5"
                   "0726f63c2c1c0bfbe";

const char *req4 = "8683c40f342f2f68656c6c6f73747265616d696e67776f726c642e4d756c7469477265657465722f73617953747265616d5"
                   "0726f63c2c1c0bfbe";

const char *req5 = "8683c40f342f2f68656c6c6f73747265616d696e67776f726c642e4d756c7469477265657465722f73617953747265616d5"
                   "0726f63c2c1c0bfbe";

const char *req6 = "8683c40f342f2f68656c6c6f73747265616d696e67776f726c642e4d756c7469477265657465722f736179526567756c617"
                   "24d7367c2c1c0bfbe";

using kvobject = std::pair<uint8_t *, size_t>;

kvobject kv1;
kvobject kv2;
kvobject kv3;
kvobject kv4;
kvobject kv5;
kvobject kv6;

hpack::dynamic_metadata_table dynamic_table(4096);
hpack::mdelem_send_record send_record;

size_t parsing_bytes_stream(const std::string &str, uint8_t **output) {
    assert(str.size() % 2 == 0);
    size_t count = str.size() / 2;

    *output = new uint8_t[count];

    const char *ptr = str.data();
    for (size_t i = 0; i < count; i++) {
        uint8_t buff[8] = {0};
        int n = sscanf(ptr, "%02hhx", buff);
        (*output)[i] = buff[0];
        ptr += 2;
    }
    return count;
}
void printf_hd_list(std::vector<hpack::mdelem_data> &decoded_hd_list) {
    printf("\n");
    for (size_t i = 0; i < decoded_hd_list.size(); i++) {
        std::cout << decoded_hd_list[i].key.to_string() << "  " << decoded_hd_list[i].value.to_string() << std::endl;
    }
    printf("\n");
    decoded_hd_list.clear();
}

void printf_dynamic_table() {
    printf("\n");
    size_t n = dynamic_table.entry_count();
    for (size_t i = 0; i < n; i++) {
        hpack::mdelem_data mdel;
        dynamic_table.get_mdelem_data(i, &mdel);
        std::cout << i << ". " << mdel.key.to_string() << " " << mdel.value.to_string() << std::endl;
    }
    printf("\n");
}

bool check_response(const std::vector<hpack::mdelem_data> &headers, const char *rsp1) {
    hpack::encode_parameter ep;
    ep.dynamic_table = &dynamic_table;
    ep.number_of_dynamic_table_changes = 0;
    ep.send_record = &send_record;
    ep.number_of_send_record_changes = 0;

    slice_buffer sb = hpack::encode_headers(headers, &ep);
    slice s = sb.merge();

    kvobject kv;
    kv.second = parsing_bytes_stream(rsp1, &kv.first);
    if (s.size() != kv.second) {
        delete[] kv.first;
        return false;
    }
    if (memcmp(kv.first, s.data(), kv.second) == 0) {
        delete[] kv.first;
        return true;
    }
    delete[] kv.first;
    return false;
}

TEST(HpackTest, Simple) {
    std::vector<hpack::mdelem_data> decoded_hd_list;
    int r;
    r = hpack::decode_headers(kv1.first, kv1.second, &dynamic_table, &decoded_hd_list);
    printf_hd_list(decoded_hd_list);
    ASSERT_EQ(r, 0);

    r = hpack::decode_headers(kv2.first, kv2.second, &dynamic_table, &decoded_hd_list);
    printf_hd_list(decoded_hd_list);
    ASSERT_EQ(r, 0);

    r = hpack::decode_headers(kv3.first, kv3.second, &dynamic_table, &decoded_hd_list);
    printf_hd_list(decoded_hd_list);
    ASSERT_EQ(r, 0);

    r = hpack::decode_headers(kv4.first, kv4.second, &dynamic_table, &decoded_hd_list);
    printf_hd_list(decoded_hd_list);
    ASSERT_EQ(r, 0);

    r = hpack::decode_headers(kv5.first, kv5.second, &dynamic_table, &decoded_hd_list);
    printf_hd_list(decoded_hd_list);
    ASSERT_EQ(r, 0);

    r = hpack::decode_headers(kv6.first, kv6.second, &dynamic_table, &decoded_hd_list);
    printf_hd_list(decoded_hd_list);
    ASSERT_EQ(r, 0);

    const char *rsp1 =
        "88400c636f6e74656e742d74797065106170706c69636174696f6e2f677270634014677270632d6163636570742d656e636f64696e6715"
        "6964656e746974792c6465666c6174652c677a6970400f6163636570742d656e636f64696e670d6964656e746974792c677a6970";
    std::vector<hpack::mdelem_data> headers;
    headers.push_back({":status", "200"});
    headers.push_back({"content-type", "application/grpc"});
    headers.push_back({"grpc-accept-encoding", "identity,deflate,gzip"});
    headers.push_back({"accept-encoding", "identity,gzip"});
    ASSERT_TRUE(check_response(headers, rsp1));
    headers.clear();

    const char *rsp2 = "400b677270632d7374617475730130";
    headers.push_back({"grpc-status", "0"});
    ASSERT_TRUE(check_response(headers, rsp2));
    headers.clear();

    const char *rsp3 = "88c1c0bf";
    headers.push_back({":status", "200"});
    headers.push_back({"content-type", "application/grpc"});
    headers.push_back({"grpc-accept-encoding", "identity,deflate,gzip"});
    headers.push_back({"accept-encoding", "identity,gzip"});
    ASSERT_TRUE(check_response(headers, rsp3));
    headers.clear();

    const char *rsp4 = "be";
    headers.push_back({"grpc-status", "0"});
    ASSERT_TRUE(check_response(headers, rsp4));
    headers.clear();
}

int main(int argc, char **argv) {
    init_static_metadata_context();
    kv1.second = parsing_bytes_stream(req1, &kv1.first);
    kv2.second = parsing_bytes_stream(req2, &kv2.first);
    kv3.second = parsing_bytes_stream(req3, &kv3.first);
    kv4.second = parsing_bytes_stream(req4, &kv4.first);
    kv5.second = parsing_bytes_stream(req5, &kv5.first);
    kv6.second = parsing_bytes_stream(req6, &kv6.first);
    int r = test::RunAllTests();
    delete[] kv1.first;
    delete[] kv2.first;
    delete[] kv3.first;
    delete[] kv4.first;
    delete[] kv5.first;
    delete[] kv6.first;
    destroy_static_metadata_context();
    return r;
}
