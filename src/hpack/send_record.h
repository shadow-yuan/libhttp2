#pragma once
#include <stdint.h>
#include <vector>
#include "src/hpack/metadata.h"

namespace hpack {
class mdelem_send_record : public send_record_service {
public:
    mdelem_send_record(/* args */);
    ~mdelem_send_record();
    bool push_record(const mdelem_data &md) override;
    void roll_back(uint32_t count) override;
    bool check_record_exists(const mdelem_data &md) override;
    uint32_t record_count();

private:
    std::vector<uint32_t> _record;
};

}  // namespace hpack
