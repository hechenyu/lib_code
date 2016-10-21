#ifndef __sp_counted_base_h
#define __sp_counted_base_h

#include <atomic>

// shared pointer counted base
class Sp_counted_base {
private:
    std::atomic<int> use_count_;

    Sp_counted_base(const Sp_counted_base &) = delete;
    Sp_counted_base &operator =(const Sp_counted_base &) = delete;

public:
    Sp_counted_base(): use_count_(1) {}

    virtual ~Sp_counted_base() {}

    // 当引用计数递减至0, 释放资源.
    virtual void dispose() = 0;

    // 当引用计数递减至0, 释放this.
    virtual void destroy() { delete this; }

    // 增加引用计数
    void incr_ref_count() // increase
    {
        ++use_count_;
    }

    // 减少引用计数
    void decr_ref_count() // decrease
    {
        if(--use_count_ == 0) {
            dispose();
            destroy();
        }
    }

    // 获取指向资源的指针
    virtual void *get_pointer() = 0;

    // 获取指向deleter的指针
    virtual void *get_deleter() = 0;

    // 获取当前引用计数
    long use_count() const { return use_count_; }
};

#endif
