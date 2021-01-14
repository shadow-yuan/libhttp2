#include "src/http2/connection.h"

http2_connection::http2_connection(uint64_t cid) {
    _cid = cid;
    _client_max_id = 1;
    _server_max_id = 2;
}
