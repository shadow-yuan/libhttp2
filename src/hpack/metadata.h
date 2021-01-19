#pragma once

#include <stddef.h>
#include <stdint.h>
#include "src/utils/slice.h"

namespace hpack {

typedef struct {
    slice key;
    slice value;
} mdelem_data;

class dynamic_table_service {
public:
    virtual ~dynamic_table_service() {}

    virtual bool get_mdelem_data(size_t index, mdelem_data *mdel) = 0;
    virtual void push_mdelem_data(const mdelem_data &md) = 0;
    virtual int32_t get_mdelem_data_index(const mdelem_data &mdel) = 0;

    // when recv SETTINGS FRAME
    // SETTINGS_HEADER_TABLE_SIZE
    virtual void update_max_table_size_limit(uint32_t limit) = 0;

    // when recv header frame (RFC 7540)
    // 6.3.  Dynamic Table Size Update
    virtual void update_max_table_size(uint32_t size) = 0;
    virtual size_t entry_count() = 0;
    virtual uint32_t max_table_size_limit() = 0;
    virtual uint32_t max_table_size() = 0;
};
}  // namespace hpack

#define MDELEM_SIZE(mdel) ((mdel).key.size() + (mdel).value.size())

static inline bool operator==(const hpack::mdelem_data &md1, const hpack::mdelem_data &md2) {
    return (md1.key == md2.key) && (md1.value == md2.value);
}
