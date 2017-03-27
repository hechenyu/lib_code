#ifndef __sp_counted_base_h
#define __sp_counted_base_h

#include <atomic>

// shared pointer counted base
class sp_counted_base {
private:
    std::atomic<long> use_count_;   // #shared: 共享引用计数

    sp_counted_base(const sp_counted_base &) = delete;
    sp_counted_base &operator =(const sp_counted_base &) = delete;

public:
    sp_counted_base(): use_count_(1) {}

    virtual ~sp_counted_base() {}

    // 当共享引用计数(use_count_)递减至0, 释放*this所管理的资源对象
    virtual void dispose() = 0;

    // 当共享引用计数(use_count_)递减至0, 释放*this本身
    virtual void destroy()
    {
        delete this;
    }

    // 增加共享引用, 共享引用计数(use_count_)+1
    void add_ref_copy()
    {
        ++use_count_;
    }

    // 释放共享引用, 将共享引用计数(use_count_)-1
    // 如果共享引用计数(use_count_)减至0,
    // 释放*this所管理的资源对象, 并释放*this本身
    void release() 
    {
        if(--use_count_ == 0) {
            dispose();
            destroy();
        }
    }

    // 获取持有对象的指针
    virtual void *get_pointer() = 0;

    // 获取指向deleter的指针
    virtual void *get_deleter() = 0;

    // 获取当前引用计数
    long use_count() const
    {
        return use_count_;
    }
};

#endif
