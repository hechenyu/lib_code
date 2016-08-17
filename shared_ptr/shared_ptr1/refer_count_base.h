#ifndef __refer_count_base_h
#define __refer_count_base_h

class Refer_count_base {
private:
	std::atomic<long> ref_count_;

    Refer_count_base(const Refer_count_base &) = delete;
    Refer_count_base &operator =(const Refer_count_base &) = delete;

public:
    Refer_count_base(): ref_count_(1) {}

    virtual ~Refer_count_base() noexcept {}

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
    virtual void *get_deleter() = 0;

	virtual void *get_pointer() = 0;

    long use_count() const noexcept
    {
        return ref_count_;
    }
};

#endif
