#ifndef __sp_counted_base_h
#define __sp_counted_base_h

// shared pointer counted base
class Sp_counted_base: public Ref_counted_base {
public:
    Sp_counted_base() {}

    virtual ~sp_counted_base() noexcept {}

    // 获取指向资源的指针
	virtual void *get_pointer() = 0;

    // 获取指向deleter的指针
    virtual void *get_deleter() = 0;

    // 获取当前引用计数
    long use_count() const noexcept { return ref_count(); }
};

#endif
