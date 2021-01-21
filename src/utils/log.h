#pragma once

#include <stdlib.h>

enum class log_level {
    DEBUG,
    INFO,
    ERROR,
};

void global_enable_log_output(bool enable);
void format_log_output(const char *file, int line, log_level level, const char *format, ...);

#define log_debug(FMT, ...) format_log_output(__FILE__, __LINE__, log_level::DEBUG, FMT, ##__VA_ARGS__)
#define log_info(FMT, ...) format_log_output(__FILE__, __LINE__, log_level::INFO, FMT, ##__VA_ARGS__)
#define log_error(FMT, ...) format_log_output(__FILE__, __LINE__, log_level::ERROR, FMT, ##__VA_ARGS__)
