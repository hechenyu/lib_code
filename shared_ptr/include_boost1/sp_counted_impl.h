#ifndef __sp_counted_impl_h
#define __sp_counted_impl_h

#include "sp_counted_base.h"

// shared pointer counted implement: pointer
template <typename T>
class Sp_counted_impl_p: public Sp_counted_base {
private:
    T *p_;  // pointer

    Sp_counted_impl_p(const Sp_counted_impl_p &) = delete;
    Sp_counted_impl_p &operator =(const Sp_counted_impl_p &) = delete;

public:
    explicit Sp_counted_impl_p(T *p): p_(p) {}

    virtual void dispose() noexcept { delete p_; }

    virtual void *get_pointer() { return p_; }

    virtual void *get_deleter() { return nullptr; }
};

// shared pointer counted implement: pointer+deleter
template <typename T, typename D>
class Sp_counted_impl_pd: public Sp_counted_base {
private:
    T *p_;      // pointer
    D del_;     // deleter

    Sp_counted_impl_pd(const Sp_counted_impl_pd &) = delete;
    Sp_counted_impl_pd &operator =(const Sp_counted_impl_pd &) = delete;

public:
    Sp_counted_impl_pd(T *p, const D &d): p_(p), del_(d) {}

    virtual void dispose() noexcept { del_(p_); }

    virtual void *get_pointer() { return p_; }

    virtual void *get_deleter() { return &del_; }
};

#endif
