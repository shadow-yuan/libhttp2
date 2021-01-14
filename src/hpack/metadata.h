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

#pragma once
#include <stdint.h>

#include "src/utils/slice.h"

namespace hpack {

typedef struct {
    slice key;
    slice value;
} metadata_element;

class static_metadata {
public:
    static_metadata(const slice &key, const slice &value, uintptr_t idx);
    const metadata_element &data() const;
    uint32_t hash() const;
    uintptr_t index() const;

private:
    metadata_element _kv;
    uintptr_t _index;
    uint32_t _hash;
};

typedef enum {
    METADATA_STORAGE_STATIC = 1,
    METADATA_STORAGE_DYNAMIC,
} metadata_storage_type;

typedef struct {
    uintptr_t payload;
} metadata_payload;

#ifdef __cplusplus
#define MAKE_METADATA_PAYLOAD(data, storage) (metadata_payload{((uintptr_t)(data)) | ((uintptr_t)storage)})
#else
#define MAKE_METADATA_PAYLOAD(data, storage) ((metadata_payload){((uintptr_t)(data)) | ((uintptr_t)storage)})
#endif

metadata_element get_metadata_element_from_payload(metadata_payload p);
size_t get_metadata_element_size(const metadata_element &mdel);
void medata_element_payload_free(metadata_payload p);

}  // namespace hpack
