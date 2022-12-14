#ifndef TPC__COMMON_H
#define TPC__COMMON_H

#include <string>
#include <string.h>

inline void memZero(void* p, size_t n) {
    memset(p, 0, n);
}

class noncopyable {
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:
        noncopyable(const noncopyable&) = delete;
        const noncopyable& operator=(const noncopyable&) = delete;
};

struct copyable {};

// For passing C-style string argument to a function 
class StringArg : copyable {
    public:
        StringArg(const char* str) : str_(str) {}

        StringArg(const std::string& str) : str_(str.c_str()) {}

        const char* c_str() const { return str_; }

    private:
        const char* str_;
};

#endif