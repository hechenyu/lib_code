#ifndef __weak_ptr_h
#define __weak_ptr_h

template <typename T>
class weak_ptr {
public:
    typedef T element_type;

private:
    sp_counted_base *pi_ = nullptr;

    typedef weak_ptr<T> this_type;

public:
    // 默认构造函数, (不持有任何指针)
    weak_ptr() {}

    // 从一个shared_ptr构造, 如果x非空, 增加弱引用,
    // 否则创建一个空对象, 类似于默认构造函数
    weak_ptr(const shared_ptr<T> &x): pi_(x.pi_)
    {
        if (pi_ != nullptr) pi_->weak_add_ref();
    }

    // 复制构造函数, 如果x非空, 增加弱引用,
    // 否则创建一个空对象, 类似于默认构造函数
    weak_ptr(const weak_ptr &x): pi_(x.pi_)
    {
        if (pi_ != nullptr) pi_->weak_add_ref();
    }

    // 析构函数, 释放弱引用
    ~weak_ptr()
    {
        if (pi_ != nullptr) pi_->weak_release();
    }

    // 赋值运算符, 释放*this弱引用, 增加对x的弱引用
    weak_ptr &operator =(const shared_ptr<T> &x)
    {
        /**
        if (pi_ != x.pi_) {
            if (x.pi_ != nullptr) x.pi_->weak_add_ref();
            if (pi_ != nullptr) pi_->weak_release();
            pi_ = x.pi_;
        }
        */
        this_type(x).swap(*this);
        return *this;
    }

};

#endif

