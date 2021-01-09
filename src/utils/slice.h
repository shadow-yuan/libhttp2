#pragma once

#include <stddef.h>
#include <stdint.h>
#include <atomic>
#include <string>

enum slice_type { STATIC, DYNAMIC };

class slice_refcount;
class slice final
{
public:
    slice(const void* ptr, size_t length, slice_type t = slice_type::DYNAMIC);
    slice(const char* str, slice_type t = slice_type::DYNAMIC);

    slice(const slice& oth);
    slice& operator= (const slice& oth);

    slice();
    ~slice();

    slice(slice&& oth);
    slice& operator= (slice&& oth);

    size_t size() const;
    const uint8_t* data() const;
    void pop_back(size_t remove_size);
    void pop_front(size_t remove_size);

    std::string to_string() const;
    bool empty() const;

private:
    slice_refcount* _refs;
    uint8_t* _bytes;
    size_t _length;
};
