#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "src/hpack/metadata.h"

#define HPACK_STATIC_MDELEM_COUNT 85
#define HPACK_STATIC_MDELEM_STANDARD_COUNT 61

namespace hpack {

class static_metadata {
public:
    static_metadata(const slice &key, const slice &value, uint32_t idx);
    const mdelem_data &data() const;
    uint32_t hash() const;
    uint32_t index() const;

private:
    mdelem_data _kv;
    uint32_t _index;
    uint32_t _hash;
};

extern static_metadata *g_static_mdelem_table;
}  // namespace hpack

void init_static_metadata_context(void);
void destroy_static_metadata_context(void);

inline hpack::static_metadata *get_static_mdelem_table() {
    assert(hpack::g_static_mdelem_table != nullptr);
    return hpack::g_static_mdelem_table;
}

// Return 0 means not found
uint32_t full_match_static_mdelem_index(const hpack::mdelem_data &mdel);
