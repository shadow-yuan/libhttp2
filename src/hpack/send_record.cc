#include "src/hpack/send_record.h"

namespace hpack {

mdelem_send_record::mdelem_send_record(/* args */) {}

mdelem_send_record::~mdelem_send_record() {}

bool mdelem_send_record::push_record(const mdelem_data &md) {
    uint32_t hash = mdelem_data_hash(md);
    for (size_t i = 0; i < _record.size(); i++) {
        if (hash == _record[i]) {
            return false;
        }
    }
    _record.emplace_back(hash);
    return true;
}

void mdelem_send_record::roll_back(uint32_t count) {
    uint32_t n = _record.size();
    if (count <= n) {
        while (count > 0) {
            _record.pop_back();
            count--;
        }
    }
}

bool mdelem_send_record::check_record_exists(const mdelem_data &md) {
    uint32_t hash = mdelem_data_hash(md);
    for (size_t i = 0; i < _record.size(); i++) {
        if (hash == _record[i]) {
            return true;
        }
    }
    return false;
}

uint32_t mdelem_send_record::record_count() {
    return _record.size();
}
}  // namespace hpack
