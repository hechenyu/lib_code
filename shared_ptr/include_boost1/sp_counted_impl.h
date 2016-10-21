#ifndef __sp_counted_impl_h
#define __sp_counted_impl_h

#include "sp_counted_base.h"

// shared pointer counted implement: pointer
template <typename T>
class sp_counted_impl_p: public sp_counted_base {
private:
    T *p_;  // pointer

    sp_counted_impl_p(const sp_counted_impl_p &) = delete;
    sp_counted_impl_p &operator =(const sp_counted_impl_p &) = delete;

public:
    explicit sp_counted_impl_p(T *p): p_(p) {}

    virtual void dispose() noexcept { delete p_; }

    virtual void *get_pointer() { return p_; }

    virtual void *get_deleter() { return nullptr; }
};

// shared pointer counted implement: pointer+deleter
template <typename T, typename D>
class sp_counted_impl_pd: public sp_counted_base {
private:
    T *p_;      // pointer
    D del_;     // deleter

    sp_counted_impl_pd(const sp_counted_impl_pd &) = delete;
    sp_counted_impl_pd &operator =(const sp_counted_impl_pd &) = delete;

public:
    sp_counted_impl_pd(T *p, const D &d): p_(p), del_(d) {}

    virtual void dispose() noexcept { del_(p_); }

    virtual void *get_pointer() { return p_; }

    virtual void *get_deleter() { return &del_; }
};

#endif
