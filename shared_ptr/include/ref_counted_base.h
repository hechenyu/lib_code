#ifndef __ref_counted_base_h
#define __ref_counted_base_h

#include <atomic>

// 引用计数基类
class Ref_counted_base {    // Reference
private:
    std::atomic<int> ref_count_;

    Ref_counted_base(const Ref_counted_base &) = delete;
    Ref_counted_base &operator =(const Ref_counted_base &) = delete;

public:
    Ref_counted_base(): ref_count_(1) {}

    virtual ~Ref_counted_base() {}

    // 当引用计数递减至0, 释放资源.
    virtual void dispose() = 0;

    // 当引用计数递减至0, 释放this.
    virtual void destroy() { delete this; }

    // 增加引用计数
    void incr_ref_count() // increase
    {
        ++ref_count_;
    }

    // 减少引用计数
    void decr_ref_count() // decrease
    {
        if(--ref_count_ == 0) {
            dispose();
            destroy();
        }
    }

public:
    long ref_count() const { return ref_count_; }
};

#endif
