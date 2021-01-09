#pragma once

#include <stddef.h>
#include <stdint.h>
#include <atomic>
#include <string>

enum slice_type { STATIC, DYNAMIC };

class slice_refcount final {
public:
    explicit slice_refcount(slice_type type);
    ~slice_refcount() {}

    slice_refcount(const slice_refcount&) = delete;
    slice_refcount& operator= (const slice_refcount&) = delete;

    void ref();
    void unref();

private:
    std::atomic<int32_t> _refs;
    slice_type _type;
};

class slice {
public:
    slice(const void* ptr, size_t length, slice_type t = slice_type::DYNAMIC);
    slice(const char* str, slice_type t = slice_type::DYNAMIC);

    slice(const slice& oth);
    slice& operator= (const slice& oth);

    slice();
    virtual ~slice();

    slice(slice&& oth);
    slice& operator= (slice&& oth);

    size_t size() const;
    const uint8_t* data() const;
    void pop_back(size_t remove_size);
    void pop_front(size_t remove_size);

    std::string to_string() const;
    bool empty() const;

protected:
    slice_refcount* _refs;
    uint8_t* _bytes;
    size_t _length;
};

struct static_slice_refcount {
    static slice_refcount kStaticSubRefcount;

    static_slice_refcount(uint32_t idx)
        : base(kStaticSubRefcount)
        , index(idx) {}

    slice_refcount& base;
    const uint32_t index;
};

struct static_slice : public slice {
    static_slice(slice_refcount* refs, size_t len,
                    const uint8_t* buf) {
        _refs = refs;
        _bytes = const_cast<uint8_t*>(buf);
        _length = len;
    }
    ~static_slice() {}
};
