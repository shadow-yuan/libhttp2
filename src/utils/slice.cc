#include "src/utils/slice.h"
#include <assert.h>

static_slice::static_slice(const uint8_t* buf, size_t len)
    : _ptr(buf)
    , _len(len) {
}

static_slice::~static_slice()
{
}

std::string static_slice::to_string() const {
    if (_len == 0) return std::string();
    return std::string(reinterpret_cast<const char*>(_ptr), _len);
}

bool static_slice::empty() const {
    return _len == 0;
}

size_t static_slice::size() const {
    return _len;
}

const uint8_t* static_slice::data() const {
    return _ptr;
}

bool static_slice::operator == (const static_slice& oth) {
    std::string s1 = to_string();
    std::string s2 = oth.to_string();
    return s1 == s2;
}

bool static_slice::operator != (const static_slice& oth) {
    return !(this->operator== (oth));
}

bool static_slice::operator == (const std::string& str) {
    std::string s = to_string();
    return s == str;
}

bool static_slice::operator != (const std::string& str) {
    return !(this->operator== (str));
}

// ---------------------------------
class slice_refcount final {
public:
    slice_refcount();
    ~slice_refcount() {}

    slice_refcount(const slice_refcount&) = delete;
    slice_refcount& operator= (const slice_refcount&) = delete;

    void ref();
    void unref();

private:
    std::atomic<int32_t> _refs;
};

slice_refcount::slice_refcount() {
    _refs.store(1, std::memory_order_relaxed);
}

void slice_refcount::ref() {
    _refs.fetch_add(1, std::memory_order_relaxed);
}

void slice_refcount::unref() {
    int32_t n = _refs.fetch_sub(1, std::memory_order_acq_rel);
    if (n == 1) {
        delete this;
    }
}

slice::slice(const void* ptr, size_t length) {
    if (length == 0) {  // empty object
        _refs = nullptr;
        _bytes = nullptr;
        _length = 0;
        return;
    }

    assert(ptr);

    /*  Memory layout used by the slice created here:

        +-----------+----------------------------------------------------------+
        | refcount  | bytes                                                    |
        +-----------+----------------------------------------------------------+

        refcount is a slice_refcount
        bytes is an array of bytes of the requested length
    */

    _refs = (slice_refcount*)new uint8_t[(sizeof(slice_refcount) + length)];
    new (_refs) slice_refcount();
    _length = length;
    _bytes = reinterpret_cast<uint8_t*>(_refs + 1);
    if (ptr) {
        memcpy(_bytes, ptr, length);
    }
}

slice::slice(const char* str)
    : slice(static_cast<const void*>(str), strlen(str)) {
}

slice::slice()
    : slice(nullptr, 0) {}

slice::~slice() {
    if (_refs) {
        _refs->unref();
    }
}

slice::slice(const slice& oth) {
    if(oth._refs != nullptr) {
        oth._refs->ref();
    }
    _refs = oth._refs;
    _bytes = oth._bytes;
    _length = oth._length;
}

slice& slice::operator= (const slice& oth) {
    if (this != &oth) {
        if (_refs) {
            _refs->unref();
        }
        if (oth._refs) {
            oth._refs->ref();
        }
        _refs = oth._refs;
        _bytes = oth._bytes;
        _length = oth._length;
    }
    return *this;
}

slice::slice(slice&& oth) {
    if (oth._refs) {
        oth._refs->ref();
    }
    _refs = std::move(oth._refs);
    _bytes = std::move(oth._bytes);
    _length = std::move(oth._length);
}

slice& slice::operator= (slice&& oth) {
    if (this != &oth) {
        if (oth._refs) {
            oth._refs->ref();
        }
        if (_refs) {
            _refs->unref();
        }
        _refs = std::move(oth._refs);
        _bytes = std::move(oth._bytes);
        _length = std::move(oth._length);
    }
    return *this;
}

size_t slice::size() const {
    return _length;
}

const uint8_t* slice::data() const {
    return _bytes;
}

void slice::pop_back(size_t remove_size) {
    if (remove_size == 0) return;
    if (remove_size > size()) {
        remove_size = size();
    }
    if (_refs) {
        _length -= remove_size;
    }
}

void slice::pop_front(size_t remove_size) {
    if (remove_size == 0) return;
    if (remove_size > size()) {
        remove_size = size();
    }
    if (_refs) {
        _length -= remove_size;
        _bytes += remove_size;
    }
}

std::string slice::to_string() const {
    if (_length == 0) return std::string();
    return std::string(reinterpret_cast<const char*>(_bytes), _length);
}

bool slice::empty() const {
    return (_length == 0);
}
