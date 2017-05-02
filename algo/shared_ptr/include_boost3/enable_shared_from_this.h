#ifndef __enable_shared_from_this_h
#define __enable_shared_from_this_h

#include "assert.h"

template <typename T>
class enable_shared_from_this {
private:
    mutable weak_ptr<T> weak_this_;

protected:
    enable_shared_from_this() noexcept {}

    // 复制构造函数: 不复制weak_this_变量
    enable_shared_from_this(const enable_shared_from_this &) noexcept {}

    // 赋值运算符: 不复制weak_this_变量
    enable_shared_from_this &operator =(const enable_shared_from_this &) noexcept
    {
        return *this;
    }

    ~enable_shared_from_this() noexcept {}

public:
    shared_ptr<T> shared_from_this()
    {
        shared_ptr<T> p(weak_this_);
        assert(p.get() == this);
        return p;
    }

    shared_ptr<const T> shared_from_this() const
    {
        shared_ptr<const T> p(weak_this_);
        assert(p.get() == this);
        return p;
    }

    // 只由构造shared_ptr时候调用
    void internal_accept_owner(const shared_ptr<T> *sp) const
    {
        if (weak_this_.expired()) {
            weak_this_ = shared_ptr<T>(*sp);
        }
    }
};

#endif
