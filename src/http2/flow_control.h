#pragma once
#include <stddef.h>
#include <stdint.h>

class flow_control {
public:
    flow_control(/* args */);
    ~flow_control();

private:
    int64_t _local_window_size;
    int64_t _remote_window_size;
    int64_t _initial_window_size;
};
