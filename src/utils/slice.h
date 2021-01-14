#pragma once

#include <atomic>
#include <stddef.h>
#include <stdint.h>
#include <string>

class slice_refcount;
class slice {
public:
    enum type { STATIC, DYNAMIC };
    slice(const void *ptr, size_t length, slice::type t = DYNAMIC);
    slice(const char *str, slice::type t = DYNAMIC);

    slice(const slice &oth);
    slice &operator=(const slice &oth);

    slice();
    virtual ~slice();

    slice(slice &&oth);
    slice &operator=(slice &&oth);

    size_t size() const;
    const uint8_t *data() const;
    void pop_back(size_t remove_size);
    void pop_front(size_t remove_size);

    std::string to_string() const;
    bool empty() const;
    slice::type get_type() const;

protected:
    slice_refcount *_refs;
    uint8_t *_bytes;
    size_t _length;
};
