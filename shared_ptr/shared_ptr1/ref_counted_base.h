#ifndef __ref_counted_base_h
#define __ref_counted_base_h

// reference counted base
class Ref_counted_base {
private:
    std::atomic<int> ref_count_;

    Ref_counted_base(const Ref_counted_base &) = delete;
    Ref_counted_base &operator =(const Ref_counted_base &) = delete;

public:
    Ref_counted_base(): ref_count_(1) {}

    virtual ~Ref_counted_base() noexcept {}

    // dispose() is called when ref_count_ drops to zero, to release
    // the resources managed by *this.
    virtual void dispose() = 0; // nothrow

    // destroy() is called when ref_count_ drops to zero, to delete this.
    virtual void destroy() noexcept
    {
        delete this;
    }

    // increase ref_count_
    void incr_ref_count()
    {
        ++ref_count_;
    }

    // decrease ref_count_
    void decr_ref_count() noexcept
    {
        if(--ref_count_ == 0) {
            dispose();
            destroy();
        }
    }

public:
    long ref_count() const noexcept
    {
        return ref_count_;
    }
};

#endif
