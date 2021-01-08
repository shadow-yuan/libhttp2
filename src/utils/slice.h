#pragma once

#include <stddef.h>
#include <stdint.h>
#include <atomic>
#include <string>

class static_slice final {
public:
    static_slice(const uint8_t* buf, size_t len);
    ~static_slice();

    std::string to_string() const;
    bool empty() const;
    size_t size() const;
    const uint8_t* data() const;

    bool operator == (const static_slice& oth);
    bool operator != (const static_slice& oth);

    bool operator == (const std::string& str);
    bool operator != (const std::string& str);

private:
    const uint8_t* _ptr;
    size_t _len;
};

// ---------------------------------
class slice_refcount;
class slice final
{
public:
    slice(const void* ptr, size_t length);
    slice(const char* str);

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
