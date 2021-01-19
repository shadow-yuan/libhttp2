#pragma once

#include <stdint.h>
#include <deque>

#include "src/hpack/metadata.h"

namespace hpack {

class dynamic_metadata_table : public dynamic_table_service {
public:
    explicit dynamic_metadata_table(uint32_t default_max_size);
    ~dynamic_metadata_table();

    bool get_mdelem_data(size_t index, mdelem_data *mdel);
    void push_mdelem_data(const mdelem_data &md);
    int32_t get_mdelem_data_index(const mdelem_data &mdel);

    // when recv SETTINGS FRAME
    // SETTINGS_HEADER_TABLE_SIZE
    void update_max_table_size_limit(uint32_t limit);

    // when recv header frame (RFC 7540)
    // 6.3.  Dynamic Table Size Update
    void update_max_table_size(uint32_t size);
    size_t entry_count();
    uint32_t max_table_size_limit();
    uint32_t max_table_size();

private:
    void adjust_dynamic_table_size();

    uint32_t _max_table_size_limit;  // set by SETTINGS_HEADER_TABLE_SIZE
    uint32_t _max_table_size;        // set by HEADER FRAME
    uint32_t _current_table_size;
    std::deque<mdelem_data> _dynamic_table;
};

}  // namespace hpack
