#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "src/utils/slice.h"

#define HPACK_STATIC_MDELEM_COUNT 85
#define HPACK_STATIC_MDELEM_STANDARD_COUNT 61

namespace hpack {

typedef struct {
    slice key;
    slice value;
} mdelem_data;

class static_metadata {
public:
    static_metadata(const slice &key, const slice &value, uintptr_t idx);
    const mdelem_data &data() const;
    uint32_t hash() const;
    uintptr_t index() const;

private:
    mdelem_data _kv;
    uintptr_t _index;
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

#define MDELEM_SIZE(mdel) ((mdel).key.size() + (mdel).value.size())
