#pragma once

#include "src/utils/slice.h"

namespace hpack {

typedef struct {
    slice key;
    slice value;
} mdelem_data;

}  // namespace hpack

#define MDELEM_SIZE(mdel) ((mdel).key.size() + (mdel).value.size())

static inline bool operator==(const hpack::mdelem_data &md1, const hpack::mdelem_data &md2) {
    return (md1.key == md2.key) && (md1.value == md2.value);
}
