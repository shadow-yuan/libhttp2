/*
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "src/hpack/metadata.h"
#include <chrono>

#include "src/utils/murmur_hash.h"

namespace hpack {

static uint32_t g_seed = 0;

#define ROTL(x, n) (((x) << (n)) | ((x) >> (sizeof(x) * 8 - (n))))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (sizeof(x) * 8 - (n))))
#define METADATA_KV_HASH(k_hash, v_hash) (ROTL((k_hash), 2) ^ (v_hash))

static uint32_t get_slice_hash(const slice &s) {
    return murmur_hash3(s.data(), s.size(), g_seed);
}

static_metadata::static_metadata(const slice &key, const slice &value, uintptr_t idx)
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

const metadata_element &static_metadata::data() const {
    return _kv;
}

uint32_t static_metadata::hash() const {
    return _hash;
}

uintptr_t static_metadata::index() const {
    return _index;
}

}  // namespace hpack
