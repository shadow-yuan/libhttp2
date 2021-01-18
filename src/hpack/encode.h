#include <stdint.h>

#include "src/hpack/metadata.h"
#include "src/utils/slice.h"

namespace hpack {

slice encode_uint16(int I, uint8_t mask);

// 6.1 Indexed Header Field Representation
slice encode_index(uint32_t index);

// 6.3.  Dynamic Table Size Update
slice encode_update_max_size(uint32_t max_size);

// 6.2.1 Literal Header Field with Incremental Indexing
slice encode_with_incremental_indexing(const mdelem_data &mdel);

// 6.2.2 Literal Header Field without Indexing
slice encode_without_indexing(const mdelem_data &mdel);

// 6.2.3 Literal Header Field Never Indexed
slice encode_never_indexed(const mdelem_data &mdel);

}  // namespace hpack
