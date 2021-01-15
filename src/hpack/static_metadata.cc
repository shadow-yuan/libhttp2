#include "src/hpack/static_metadata.h"
#include <chrono>
#include <map>
#include "src/utils/useful.h"
#include "src/utils/murmur_hash.h"

#define METADATA_KV_HASH(k_hash, v_hash) (ROTL((k_hash), 2) ^ (v_hash))

inline slice make_static_slice(const char *buf) {
    if (!buf) return slice();
    return slice(buf, slice::STATIC);
}

static uint32_t g_seed = 0;

template <typename T>
static uint32_t get_slice_hash(const T &s) {
    return murmur_hash3(s.data(), s.size(), g_seed);
}

namespace hpack {
static_metadata::static_metadata(const slice &key, const slice &value, uint32_t idx)
    : _kv({key, value})
    , _index(idx) {

    if (!g_seed) {
        auto d = std::chrono::system_clock::now().time_since_epoch();
        auto n = std::chrono::duration_cast<std::chrono::nanoseconds>(d);
        uint32_t seconds = 1 * 1000 * 1000000;
        g_seed = n.count() % seconds;
    }
    uint32_t k_hash = get_slice_hash(key);
    uint32_t v_hash = get_slice_hash(value);
    _hash = METADATA_KV_HASH(k_hash, v_hash);
}

const mdelem_data &static_metadata::data() const {
    return _kv;
}

uint32_t static_metadata::hash() const {
    return _hash;
}

uint32_t static_metadata::index() const {
    return _index;
}

struct static_metadata_context {

    static_metadata static_mdelem_table[HPACK_STATIC_MDELEM_COUNT + 1] = {
        static_metadata(make_static_slice(nullptr), make_static_slice(nullptr), 0),
        static_metadata(make_static_slice(":authority"), make_static_slice(nullptr), 1),
        static_metadata(make_static_slice(":method"), make_static_slice("GET"), 2),
        static_metadata(make_static_slice(":method"), make_static_slice("POST"), 3),
        static_metadata(make_static_slice(":path"), make_static_slice("/"), 4),
        static_metadata(make_static_slice(":path"), make_static_slice("/index.html"), 5),
        static_metadata(make_static_slice(":scheme"), make_static_slice("http"), 6),
        static_metadata(make_static_slice(":scheme"), make_static_slice("https"), 7),
        static_metadata(make_static_slice(":status"), make_static_slice("200"), 8),
        static_metadata(make_static_slice(":status"), make_static_slice("204"), 9),
        static_metadata(make_static_slice(":status"), make_static_slice("206"), 10),
        static_metadata(make_static_slice(":status"), make_static_slice("304"), 11),
        static_metadata(make_static_slice(":status"), make_static_slice("400"), 12),
        static_metadata(make_static_slice(":status"), make_static_slice("404"), 13),
        static_metadata(make_static_slice(":status"), make_static_slice("500"), 14),
        static_metadata(make_static_slice("accept-charset"), make_static_slice(nullptr), 15),
        static_metadata(make_static_slice("accept-encoding"), make_static_slice("gzip, deflate"), 16),
        static_metadata(make_static_slice("accept-language"), make_static_slice(nullptr), 17),
        static_metadata(make_static_slice("accept-ranges"), make_static_slice(nullptr), 18),
        static_metadata(make_static_slice("accept"), make_static_slice(nullptr), 19),
        static_metadata(make_static_slice("access-control-allow-origin"), make_static_slice(nullptr), 20),
        static_metadata(make_static_slice("age"), make_static_slice(nullptr), 21),
        static_metadata(make_static_slice("allow"), make_static_slice(nullptr), 22),
        static_metadata(make_static_slice("authorization"), make_static_slice(nullptr), 23),
        static_metadata(make_static_slice("cache-control"), make_static_slice(nullptr), 24),
        static_metadata(make_static_slice("content-disposition"), make_static_slice(nullptr), 25),
        static_metadata(make_static_slice("content-encoding"), make_static_slice(nullptr), 26),
        static_metadata(make_static_slice("content-language"), make_static_slice(nullptr), 27),
        static_metadata(make_static_slice("content-length"), make_static_slice(nullptr), 28),
        static_metadata(make_static_slice("content-location"), make_static_slice(nullptr), 29),
        static_metadata(make_static_slice("content-range"), make_static_slice(nullptr), 30),
        static_metadata(make_static_slice("content-type"), make_static_slice(nullptr), 31),
        static_metadata(make_static_slice("cookie"), make_static_slice(nullptr), 32),
        static_metadata(make_static_slice("date"), make_static_slice(nullptr), 33),
        static_metadata(make_static_slice("etag"), make_static_slice(nullptr), 34),
        static_metadata(make_static_slice("expect"), make_static_slice(nullptr), 35),
        static_metadata(make_static_slice("expires"), make_static_slice(nullptr), 36),
        static_metadata(make_static_slice("from"), make_static_slice(nullptr), 37),
        static_metadata(make_static_slice("host"), make_static_slice(nullptr), 38),
        static_metadata(make_static_slice("if-match"), make_static_slice(nullptr), 39),
        static_metadata(make_static_slice("if-modified-since"), make_static_slice(nullptr), 40),
        static_metadata(make_static_slice("if-none-match"), make_static_slice(nullptr), 41),
        static_metadata(make_static_slice("if-range"), make_static_slice(nullptr), 42),
        static_metadata(make_static_slice("if-unmodified-since"), make_static_slice(nullptr), 43),
        static_metadata(make_static_slice("last-modified"), make_static_slice(nullptr), 44),
        static_metadata(make_static_slice("link"), make_static_slice(nullptr), 45),
        static_metadata(make_static_slice("location"), make_static_slice(nullptr), 46),
        static_metadata(make_static_slice("max-forwards"), make_static_slice(nullptr), 47),
        static_metadata(make_static_slice("proxy-authenticate"), make_static_slice(nullptr), 48),
        static_metadata(make_static_slice("proxy-authorization"), make_static_slice(nullptr), 49),
        static_metadata(make_static_slice("range"), make_static_slice(nullptr), 50),
        static_metadata(make_static_slice("referer"), make_static_slice(nullptr), 51),
        static_metadata(make_static_slice("refresh"), make_static_slice(nullptr), 52),
        static_metadata(make_static_slice("retry-after"), make_static_slice(nullptr), 53),
        static_metadata(make_static_slice("server"), make_static_slice(nullptr), 54),
        static_metadata(make_static_slice("set-cookie"), make_static_slice(nullptr), 55),
        static_metadata(make_static_slice("strict-transport-security"), make_static_slice(nullptr), 56),
        static_metadata(make_static_slice("transfer-encoding"), make_static_slice(nullptr), 57),
        static_metadata(make_static_slice("user-agent"), make_static_slice(nullptr), 58),
        static_metadata(make_static_slice("vary"), make_static_slice(nullptr), 59),
        static_metadata(make_static_slice("via"), make_static_slice(nullptr), 60),
        static_metadata(make_static_slice("www-authenticate"), make_static_slice(nullptr), 61),

        //
        // The following data (62-85) are from gRPC
        //
        static_metadata(make_static_slice("grpc-status"), make_static_slice("0"), 62),
        static_metadata(make_static_slice("grpc-status"), make_static_slice("1"), 63),
        static_metadata(make_static_slice("grpc-status"), make_static_slice("2"), 64),
        static_metadata(make_static_slice("grpc-encoding"), make_static_slice("identity"), 65),
        static_metadata(make_static_slice("grpc-encoding"), make_static_slice("gzip"), 66),
        static_metadata(make_static_slice("grpc-encoding"), make_static_slice("deflate"), 67),
        static_metadata(make_static_slice("te"), make_static_slice("trailers"), 68),
        static_metadata(make_static_slice("content-type"), make_static_slice("application/grpc"), 69),
        static_metadata(make_static_slice(":scheme"), make_static_slice("grpc"), 70),
        static_metadata(make_static_slice(":method"), make_static_slice("PUT"), 71),
        static_metadata(make_static_slice("accept-encoding"), make_static_slice(nullptr), 72),
        static_metadata(make_static_slice("content-encoding"), make_static_slice("identity"), 73),
        static_metadata(make_static_slice("content-encoding"), make_static_slice("gzip"), 74),
        static_metadata(make_static_slice("lb-cost-bin"), make_static_slice(nullptr), 75),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("identity"), 76),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("deflate"), 77),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("identity,deflate"), 78),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("gzip"), 79),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("identity,gzip"), 80),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("deflate,gzip"), 81),
        static_metadata(make_static_slice("grpc-accept-encoding"), make_static_slice("identity,deflate,gzip"), 82),
        static_metadata(make_static_slice("accept-encoding"), make_static_slice("identity"), 83),
        static_metadata(make_static_slice("accept-encoding"), make_static_slice("gzip"), 84),
        static_metadata(make_static_slice("accept-encoding"), make_static_slice("identity,gzip"), 85),
    };
    std::multimap<uint32_t, uint32_t> hash_table;
};  // struct static_metadata_context

static static_metadata_context *g_static_metadata_ctx = nullptr;
static_metadata *g_static_mdelem_table = nullptr;
}  // namespace hpack

void init_static_metadata_context(void) {
    if (!hpack::g_static_metadata_ctx) {
        hpack::g_static_metadata_ctx = new hpack::static_metadata_context();
        hpack::g_static_mdelem_table = hpack::g_static_metadata_ctx->static_mdelem_table;

        for (size_t i = 1; i <= HPACK_STATIC_MDELEM_COUNT; i++) {
            auto hash = hpack::g_static_mdelem_table[i].hash();
            auto index = hpack::g_static_mdelem_table[i].index();
            hpack::g_static_metadata_ctx->hash_table.insert({hash, index});
        }
    }
}

void destroy_static_metadata_context(void) {
    if (hpack::g_static_metadata_ctx) {
        delete hpack::g_static_metadata_ctx;
        hpack::g_static_metadata_ctx = nullptr;
        hpack::g_static_mdelem_table = nullptr;
    }
}

uint32_t full_match_mdelem_data_index(const std::string &key, const std::string &value) {
    uint32_t hash = get_slice_hash(key);
    auto pr = hpack::g_static_metadata_ctx->hash_table.equal_range(hash);
    if (pr.first == hpack::g_static_metadata_ctx->hash_table.end()) {
        return 0;
    }

    for (auto it = pr.first; it != pr.second; ++it) {
        uint32_t index = it->second;
        const auto &mdel = hpack::g_static_mdelem_table[index].data();
        if (mdel.key.compare(key) && mdel.value.compare(value)) {
            return index;
        }
    }
    return 0;
}
