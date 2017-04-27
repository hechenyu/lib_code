#ifndef __shared_ptr_h
#define __shared_ptr_h

#include <iostream>
#include <utility>
#include <cstddef>
#include "sp_counted_impl.h"
#include "bad_weak_ptr.h"

template <typename T>
class shared_ptr;

template <typename T>
class weak_ptr;

template <typename T>
class enable_shared_from_this;

template <typename T>
inline void sp_enable_shared_from_this(const shared_ptr<T> *sp, const enable_shared_from_this<T> *pe)
{
    if (pe != nullptr) {
        pe->internal_accept_owner(sp);
    }
}

// SFINAE:substitution-failure-is-not-an-error
// 默认匹配函数
inline void sp_enable_shared_from_this(...)
{
}

template <typename T>
class shared_ptr {
public:
    typedef T element_type;

private:
    sp_counted_base *pi_ = nullptr;
    element_type *px_ = nullptr;

    typedef shared_ptr<T> this_type;

    template<typename> friend class shared_ptr;
    template<typename> friend class weak_ptr;

public:
    // 默认构造函数, (不持有任何指针, 共享引用计数为0)
    shared_ptr() {}

    // 通过指针p构造, 持有指针p, 共享引用计数为1
    template <typename U>
    explicit shared_ptr(U *p): px_(p)
    {
        try 
        {
            pi_ = new sp_counted_impl_p<U>(p);
        }
        catch (...) 
        {
            delete p;
            throw;
        }
        sp_enable_shared_from_this(this, p);
    }

    // 通过指针p和deleter构造, 持有指针p和deleter, 共享引用计数为1,
    // 当共享引用计数降到0时, 通过deleter释放指针p
    template <typename U, typename D>
    shared_ptr(U *p, D del): px_(p)
    {
        try 
        {
            pi_ = new sp_counted_impl_pd<U *, D>(p, del);
        }
        catch (...)
        {
            del(p);    // delete p
            throw;
        }
        sp_enable_shared_from_this(this, p);
    }

    // 析构函数, 释放共享引用
    ~shared_ptr()
    {
        if (pi_ != nullptr) pi_->release();
    }

    // 复制构造函数, 如果x非空, 增加共享引用,
    // 否则创建一个空对象, 类似于默认构造函数
    shared_ptr(const shared_ptr &x): pi_(x.pi_), px_(x.px_)
    {
        if (pi_ != nullptr) pi_->add_ref_copy();
    }

    template <typename U>
    shared_ptr(const shared_ptr<U> &x): pi_(x.pi_), px_(x.px_)
    {
        if (pi_ != nullptr) pi_->add_ref_copy();
    }

    // 复制构造函数, 如果x非空, 增加共享引用,
    // 否则创建一个空对象, 类似于默认构造函数
    template <typename U>
    explicit shared_ptr(const weak_ptr<U> &x): pi_(x.pi_), px_(x.px_)
    {
        if (pi_ == nullptr || !pi_->add_ref_lock()) {
            throw bad_weak_ptr();
        }
    }

    // 赋值运算符, 释放*this共享引用, 增加对x的共享引用
    shared_ptr &operator =(const shared_ptr &x)
    {
        /**
        if (pi_ != x.pi_) {
            if (x.pi_ != nullptr) x.pi_->add_ref_copy();
            if (pi_ != nullptr) pi_->release();
            pi_ = x.pi_;
        }
        */
        this_type(x).swap(*this);
        return *this;
    }

    template <typename U>
    shared_ptr &operator =(const shared_ptr<U> &x)
    {
        this_type(x).swap(*this);
        return *this;
    }

    // 交给两个shared_ptr
    void swap(shared_ptr &x)
    {
        using std::swap;
        swap(this->pi_, x.pi_);
        swap(this->px_, x.px_);
    }

    // 重置当前智能指针对象, 使得当前对象为空, 即默认构造的对象
    void reset()
    {
        /**
        if (pi_) {
            pi_->release();
            pi_ = nullptr;
        }
        */
        this_type().swap(*this);
    }

    // 使用指针p重置当前智能指针对象, 使得当前对象拥有指针p, 
    // 并且将共享引用计数置为1
    template <typename U>
    void reset(U *p)
    {
        this_type(p).swap(*this);
    }

    // 同上, 但指定deleter
    template <typename U, typename D>
    void reset(U *p, D del)
    {
        this_type(p, del).swap(*this);
    }

    // 获取当前对象管理的指针
    element_type *get() const
    {
        return px_;
    }

    // 解引用当前对象管理的指针
    element_type &operator *() const { return *get(); }

    // 解引用当前对象管理的指针, 获取成员变量
    element_type *operator ->() const { return get(); }

    // 返回共享引用计数
    long int use_count() const
    {
        return pi_ != nullptr ? pi_->use_count() : 0;
    }

    // 测试共享引用计数是否为1
    bool unique() const
    {
        return use_count() == 1;
    }

    // 判断当前对象是否为空
    explicit operator bool() const
    {
        return get() != nullptr;
    }

    // 获取deleter指针
    void *get_deleter() const
    {
        return (this->pi_ != nullptr ? this->pi_->get_deleter() : 0);
    }

    template <typename U>
    bool owner_before(const shared_ptr<U> &x) const
    {
        return this->pi_ < x.pi_;
    }

    template <typename U>
    bool owner_before(const weak_ptr<U> &x) const
    {
        return this->pi_ < x.pi_;
    }
};

// 比较两个shared_ptr
template <typename T>
bool operator ==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T>
bool operator <(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs)
{
    return lhs.get() < rhs.get();
}

template <typename T>
bool operator <=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs)
{
    return (lhs < rhs || lhs == rhs);
}

template <typename T>
bool operator !=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator >(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs)
{
    return !(lhs <= rhs);
}

template <typename T>
bool operator >=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs)
{
    return !(lhs < rhs);
}

// 比较shared_ptr和nullptr
template <typename T>
bool operator ==(const shared_ptr<T> &lhs, std::nullptr_t)
{
    return lhs.get() == nullptr;
}

template <typename T>
bool operator ==(std::nullptr_t, const shared_ptr<T> &rhs)
{
    return nullptr == rhs.get();
}

template <typename T>
bool operator !=(const shared_ptr<T> &lhs, std::nullptr_t)
{
    return !(lhs == nullptr);
}

template <typename T>
bool operator !=(std::nullptr_t, const shared_ptr<T> &rhs)
{
    return !(nullptr == rhs);
}

template <typename T>
bool operator <(const shared_ptr<T> &lhs, std::nullptr_t)
{
    return lhs.get() < nullptr;
}

template <typename T>
bool operator <(std::nullptr_t, const shared_ptr<T> &rhs)
{
    return nullptr < rhs.get();
}

template <typename T>
bool operator <=(const shared_ptr<T> &lhs, std::nullptr_t)
{
    return !(lhs.get() > nullptr);
}

template <typename T>
bool operator <=(std::nullptr_t, const shared_ptr<T> &rhs)
{
    return !(nullptr > rhs.get());
}

template <typename T>
bool operator >(const shared_ptr<T> &lhs, std::nullptr_t)
{
    return (nullptr < lhs);
}

template <typename T>
bool operator >(std::nullptr_t, const shared_ptr<T> &rhs)
{
    return (rhs < nullptr);
}

template <typename T>
bool operator >=(const shared_ptr<T> &lhs, std::nullptr_t)
{
    return !(lhs < nullptr);
}

template <typename T>
bool operator >=(std::nullptr_t, const shared_ptr<T> &rhs)
{
    return !(nullptr < rhs);
}

// 重载输出运算符
template <class charT, class traits, class T>
std::basic_ostream<charT, traits> &operator <<(
        std::basic_ostream<charT, traits> &os, const shared_ptr<T> &x)
{
    os << x.get();
    return os;
}

// 实现make_shared
template <typename T, typename ...Args>
shared_ptr<T> make_shared(Args &&...args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

// 交换指针
template <typename T>
void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs)
{
    lhs.swap(rhs);
}

// 获取deleter
template <typename D, typename T>
D *get_deleter(const shared_ptr<T> &sp)
{
    return static_cast<D *>(sp.get_deleter());
}

#include "weak_ptr.h"
#include "enable_shared_from_this.h"

#endif
