#include "common_error.h"
#include <cstdio>
#include <cstdarg>

Error::Error(const char* fmt, ...) noexcept {
    va_list args;
    va_start(args,fmt);
    vsnprintf(msg_error,BUF_LEN,fmt,args);
}

const char* Error::what() const noexcept{
    return msg_error;
}