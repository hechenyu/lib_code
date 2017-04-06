#ifndef __sp_counted_base_h
#define __sp_counted_base_h

#include <atomic>

// shared pointer counted base
class sp_counted_base {
private:
    std::atomic<long> use_count_;   // #shared: 共享引用计数
    std::atomic<long> weak_count_;  // #weak + (#shared != 0): 弱引用计数+1/0(共享引用计数是否非0)

    sp_counted_base(const sp_counted_base &) = delete;
    sp_counted_base &operator =(const sp_counted_base &) = delete;

public:
    sp_counted_base(): use_count_(1), weak_count_(1) {}

    virtual ~sp_counted_base() {}

    // 当共享引用计数(use_count_)递减至0, 释放*this所管理的资源对象
    virtual void dispose() = 0;

    // 当共享引用计数+弱引用计数之和(weak_count_)递减至0, 释放*this本身
    virtual void destroy() 
    {
        delete this;
    }

    // 增加共享引用, 共享引用计数(use_count_)+1
    void add_ref_copy()
    {
        ++use_count_; 
    }

    // 测试共享引用计数(use_count_), 
    // 如果共享引用计数非0, 将共享引用计数(use_count_)+1, 返回true
    // 否则直接返回false
    bool add_ref_lock() // true on sucess
    {
        /**
         * 原子的操作
         * long r = use_count_;
         * if (r != 0) ++use_count_;
         * return r;
         */
        long r = use_count_;
        while (true) {
            if (r == 0)
                return false;
            if (use_count_.compare_exchange_weak(r, r+1)) {
                return true;
            }
        }
    }

    // 释放共享引用, 将共享引用计数(use_count_)-1
    // 如果共享引用计数(use_count_)减至0,
    // 释放*this所管理的资源对象,
    // 当共享引用计数+弱引用计数之和(weak_count_)递减至0, 释放*this本身
    void release() 
    {
        if(--use_count_ == 0) {
            dispose();
            weak_release();
        }
    }

    // 增加弱引用, weak_count_+1
    void weak_add_ref()
    {
        ++weak_count_;
    }

    // 当释放弱引用, 或者共享引用计数减至0时, weak_count_-1
    // 当共享引用计数+弱引用计数之和(weak_count_)递减至0, 释放*this本身
    // PS: weak_count_递减至0(代表没用任何共享引用和弱引用)
    void weak_release()
    {
        if (--weak_count_ == 0) {
            destroy();
        }
    }

    // 获取*this管理的资源对象的指针
    virtual void *get_pointer() = 0;

    // 获取指向deleter的指针
    virtual void *get_deleter() = 0;

    // 获取当前共享引用计数
    long use_count() const
    {
        return use_count_;
    }
};

#endif
