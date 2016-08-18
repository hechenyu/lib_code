#ifndef __sp_counted_base_h
#define __sp_counted_base_h

// shared pointer counted base
class Sp_counted_base: public Ref_counted_base {
public:
    Sp_counted_base() {}

    virtual ~sp_counted_base() noexcept {}

	virtual void *get_pointer() = 0;

    virtual void *get_deleter() = 0;

    long use_count() const noexcept
    {
        return this->ref_count();
    }
};

#endif
