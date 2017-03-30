#ifndef __weak_ptr_h
#define __weak_ptr_h

template <typename T>
class weak_ptr {
public:
    typedef T element_type;

private:
    sp_counted_base *pi_ = nullptr;

    typedef weak_ptr<T> this_type;

	template<typename> friend class shared_ptr;
	template<typename> friend class weak_ptr;

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
	weak_ptr &operator =(const weak_ptr &x)
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

    // 交换两个weak_ptr
	void swap(weak_ptr &x)
	{
        using std::swap;
        swap(this->pi_, x.pi_);
	}


    // 重置当前智能指针对象, 使得当前对象为空, 即默认构造的对象
    void reset()
    {
        /**
        if (pi_) {
            pi_->weak_release();
            pi_ = nullptr;
        }
        */
        this_type().swap(*this);
    }

    // 返回共享引用计数
    long int use_count() const
    {
        return pi_ != nullptr ? pi_->use_count() : 0;
    }

    // 检查weak_ptr是否失效,
    // 如果weak_ptr是空(默认构造的), 
    // 或者没有任何shared_ptr持有该对象的共享引用,
    // 则返回true
    bool expired() const
    {
        return use_count() == 0;
    }

    // 如果weak_ptr没有失效,
    // 返回一个weak_ptr所指向的对象的shared_ptr,
    // 否则返回一个空的shared_ptr对象
    shared_ptr<T> lock() const
    {
        if (expired())
            return shared_ptr<T>();
        else
            return shared_ptr<T>(*this);
    }

	bool owner_before(const weak_ptr &x) const
	{
		return this->pi_ < x.pi_;
	}

	bool owner_before(const shared_ptr<T> &x) const
	{
		return this->pi_ < x.pi_;
	}
};

// 交换两个weak_ptr
template <typename T>
void swap(weak_ptr<T> &x, weak_ptr<T> &y)
{
	x.swap(y);
}

#endif
