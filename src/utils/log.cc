#include "src/utils/log.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include "src/utils/atomic.h"

typedef struct {
    const char *file;
    int line;
    log_level level;
    char *message;
} internal_log_info;

typedef void (*log_output_func)(internal_log_info *);
void format_log_output_impl(internal_log_info *info);

AtomicIntptr global_log_func((intptr_t)format_log_output_impl);
char g_level_string[] = {'D', 'I', 'E'};
bool global_enable_log = true;

void format_log_output_impl(internal_log_info *info) {
    auto display_file = strstr(info->file, "src");
    if (!display_file) {
        display_file = info->file;
    }

    char time_buffer[64] = {0};
    time_t timer = time(NULL);

#ifdef _WIN32
    struct tm stm;
    if (localtime_s(&stm, &timer)) {
        strcpy(time_buffer, "error:localtime");
    }
#else
    struct tm stm;
    if (!localtime_r(&timer, &stm)) {
        strcpy(time_buffer, "error:localtime");
    }
#endif
    // "%F %T" 2020-05-10 01:43:06
    else if (0 == strftime(time_buffer, sizeof(time_buffer), "%F %T", &stm)) {
        strcpy(time_buffer, "error:strftime");
    }

    auto d = std::chrono::system_clock::now().time_since_epoch();
    auto m = std::chrono::duration_cast<std::chrono::milliseconds>(d);
    int millisec = m.count() % 1000;
    fprintf(stderr, "[%s.%03u %c] %s (%s:%d)\n", time_buffer,
            millisec,  // millisecond
            g_level_string[static_cast<int>(info->level)], info->message, display_file, info->line);

    fflush(stderr);
}

void format_log_output(const char *file, int line, log_level level, const char *format, ...) {
    if (!global_enable_log) return;
#ifndef NDEBUG

    char *message = NULL;
    va_list args;
    va_start(args, format);

#ifdef _WIN32
    int ret = _vscprintf(format, args);
    va_end(args);
    if (ret < 0) {
        return;
    }

    size_t buff_len = (size_t)ret + 1;
    message = (char *)malloc(buff_len);
    va_start(args, format);
    ret = vsnprintf_s(message, buff_len, _TRUNCATE, format, args);
    va_end(args);
#else
    if (vasprintf(&message, format, args) == -1) {  // stdio.h
        va_end(args);
        return;
    }
#endif
    internal_log_info info;
    info.file = file;
    info.line = line;
    info.level = level;
    info.message = message;
    ((log_output_func)global_log_func.Load())(&info);
    free(message);
#endif
}
