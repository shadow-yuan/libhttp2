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

/*
 * WARNING: Auto-generated code.
 *
 * To make changes to this file, change
 * tools/codegen/core/gen_static_metadata.py, and then re-run it.
 *
 * See metadata.h for an explanation of the interface here, and metadata.cc for
 * an explanation of what's going on.
 */

#pragma once
#include "src/utils/slice.h"
namespace hpack {

typedef struct {
  const slice key;
  const slice value;
} metadata_item;

class static_metadata {
public:
    static_metadata(const slice& key, const slice& value, uintptr_t idx);

    const metadata_item& data() const;
    uint32_t hash() const;
    uintptr_t index() const;

private:
    metadata_item _kv;
    uint32_t _hash;
    uintptr_t _index;
};
}  // namespace hpack
