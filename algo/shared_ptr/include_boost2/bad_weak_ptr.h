#ifndef __bad_weak_ptr_h
#define __bad_weak_ptr_h

#include <exception>

class bad_weak_ptr: public std::exception {
public:
    virtual const char *what() const noexcept { return "bad_weak_ptr"; }
};

#endif

