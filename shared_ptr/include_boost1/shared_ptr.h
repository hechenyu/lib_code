#ifndef __shared_ptr_h
#define __shared_ptr_h

#include <iostream>
#include <utility>
#include <cstddef>
#include "sp_counted_impl.h"

template <typename T>
class shared_ptr {
public:
    typedef T element_type;

private:
    sp_counted_base *pi_ = nullptr;

    typedef shared_ptr<T> this_type;

public:
    // 默认构造函数, (不持有任何指针, 引用计数为0)
    shared_ptr() {}

    // 通过指针p构造, 持有指针p, 引用计数为1
    explicit shared_ptr(T *p)
    {
        try 
        {
            pi_ = new sp_counted_impl_p<T>(p);
        }
        catch (...) 
        {
            delete p;
            throw;
        }
    }

    // 通过指针p和deleter构造, 持有指针p和deleter, 引用计数为1,
    // 当引用计数降到0时, 通过deleter释放指针p
    template <typename D>
    explicit shared_ptr(T *p, D del)
    {
        try 
        {
            pi_ = new sp_counted_impl_pd<T, D>(p, del);
        }
        catch (...)
        {
            del(p);    // delete p
            throw;
        }
    }

    // 析构函数, 减少引用计数
    ~shared_ptr()
    {
        if (pi_ != nullptr) pi_->decr_ref_count();
    }

    // 复制构造函数, 如果x非空, 增加引用计数,
    // 否则创建一个空对象, 类似于默认构造函数
    shared_ptr(const shared_ptr &x)
        : pi_(x.pi_)
    {
        if (pi_ != nullptr) pi_->incr_ref_count();
    }

    // 赋值运算符, 减少当前引用计数, 增加x的引用计数
    shared_ptr &operator =(const shared_ptr &x)
    {
        /**
        if (this != &x) {
            pi_->decr_ref_count();
            pi_ = x.pi_;
            pi_->incr_ref_count();
        }
        */
        this_type(x).swap(*this);
        return *this;
    }

    // 交给两个shared_ptr
    void swap(shared_ptr &x)
    {
        using std::swap;
        swap(this->pi_, x.pi_);
    }

    // 重置当前智能指针对象, 使得当前对象为空, 即默认构造的对象
    void reset()
    {
        /**
        pi_->decr_ref_count();
        pi_ = nullptr;
        */
        this_type().swap(*this);
    }

    // 使用指针p重置当前智能指针对象, 使得当前对象拥有指针p, 并且引用计数为1,
    void reset(T *p)
    {
        this_type(p).swap(*this);
    }

    // 同上, 但指定deleter
    template <typename D>
    void reset(T *p, D del)
    {
        this_type(p, del).swap(*this);
    }

    // 获取当前对象管理的指针
    element_type *get() const
    {
        if (pi_ != nullptr) {
            return static_cast<element_type *>(pi_->get_pointer());
        } else {
            return nullptr;
        }
    }

    // 解引用当前对象管理的指针
    element_type &operator *() const { return *get(); }

    // 解引用当前对象管理的指针, 获取成员变量
    element_type *operator ->() const { return get(); }

    // 返回引用计数
    long int use_count() const
    {
        return pi_ != nullptr ? pi_->use_count() : 0;
    }

    // 测试引用计数是否为1
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

#endif
