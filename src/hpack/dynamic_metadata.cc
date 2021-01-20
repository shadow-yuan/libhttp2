#include "src/hpack/dynamic_metadata.h"

namespace hpack {

dynamic_metadata_table::dynamic_metadata_table(uint32_t default_max_size)
    : _max_table_size_limit(default_max_size)
    , _max_table_size(default_max_size)
    , _current_table_size(0) {}

dynamic_metadata_table::~dynamic_metadata_table() {}

bool dynamic_metadata_table::get_mdelem_data(size_t index, mdelem_data *mdel) {
    auto n = _dynamic_table.size();
    if (index >= n) {
        return false;
    }

    *mdel = _dynamic_table[index];
    return true;
}

void dynamic_metadata_table::push_mdelem_data(const mdelem_data &md) {
    _dynamic_table.push_front(md);
    _current_table_size += MDELEM_SIZE(md);
    _current_table_size += 32;
    adjust_dynamic_table_size();
}

// when recv SETTINGS FRAME
// SETTINGS_HEADER_TABLE_SIZE
void dynamic_metadata_table::update_max_table_size_limit(uint32_t limit) {
    _max_table_size_limit = limit;
}

// when recv header frame (RFC 7540)
// 6.3.  Dynamic Table Size Update
void dynamic_metadata_table::update_max_table_size(uint32_t size) {
    _max_table_size = size;
    adjust_dynamic_table_size();
}

size_t dynamic_metadata_table::entry_count() {
    return _dynamic_table.size();
}

uint32_t dynamic_metadata_table::max_table_size_limit() {
    return _max_table_size;
}
uint32_t dynamic_metadata_table::max_table_size() {
    return _max_table_size;
}

int32_t dynamic_metadata_table::get_mdelem_data_index(const mdelem_data &mdel) {
    size_t count = _dynamic_table.size();
    for (size_t i = 0; i < count; i++) {
        if (mdel.key == _dynamic_table[i].key && mdel.value == _dynamic_table[i].value) {
            return static_cast<int32_t>(i);
        }
    }
    return -1;
}

void dynamic_metadata_table::adjust_dynamic_table_size() {
    while (_current_table_size > _max_table_size && !_dynamic_table.empty()) {
        auto entry = _dynamic_table.back();
        auto element_size = MDELEM_SIZE(entry);
        _current_table_size -= element_size + 32;
        _dynamic_table.pop_back();
    }
}

void dynamic_metadata_table::roll_back(uint32_t count) {
    uint32_t n = _dynamic_table.size();
    if (count <= n) {
        while (count > 0) {
            const mdelem_data &mdel = _dynamic_table.front();
            auto element_size = MDELEM_SIZE(mdel);
            _current_table_size -= element_size + 32;
            _dynamic_table.pop_front();
            count--;
        }
    }
}
}  // namespace hpack
