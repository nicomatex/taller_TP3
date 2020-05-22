#ifndef __ERROR_H
#define __ERROR_H

#include <string>
#include <typeinfo>

#define BUF_LEN 256

class Error : public std::exception {
   private:
    char msg_error[BUF_LEN];

   public:
    explicit Error(const char* fmt, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~Error() noexcept {}
};

#endif