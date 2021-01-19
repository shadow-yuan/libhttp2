
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "src/utils/slice.h"

class slice_buffer final {
public:
    slice_buffer();
    ~slice_buffer();

    slice merge() const;
    size_t slice_count() const;
    size_t get_buffer_length() const;

    void add_slice(slice &&s);
    void add_slice(const slice &s);

    slice get_header(size_t len);
    bool move_header(size_t len);

    void clear_buffer();
    bool empty() const;

    // have assert if empty
    const slice &front() const;
    const slice &back() const;

    void pop_front();
    void pop_back();

    // after transfer, this class is reset
    // output will be replace
    void transfer(slice_buffer *output);

private:
    size_t copy_to_buffer(void *buff, size_t len);

    std::vector<slice> _vs;
    size_t _length;
};
