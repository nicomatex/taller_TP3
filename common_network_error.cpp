#include <cstdarg>
#include <cstdio>

#include "common_network_error.h"

NetworkError::NetworkError(const char* fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_error, BUF_LEN, fmt, args);
}

const char* NetworkError::what() const noexcept { return msg_error; }
