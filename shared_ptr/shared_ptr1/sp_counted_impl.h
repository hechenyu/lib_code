#ifndef __sp_counted_impl_h
#define __sp_counted_impl_h

// shared pointer counted implement pointer
template <typename T>
class Sp_counted_impl_p: public Sp_counted_base {
private:
	T *p_;	// pointer

	Sp_counted_impl_p(const Sp_counted_impl_p &) = delete;
	Sp_counted_impl_p &operator =(const Sp_counted_impl_p &) = delete;

public:
	explicit Sp_counted_impl_p(T *p): p_(p) {}

	virtual void dispose() noexcept { delete p_; }

	virtual void *get_pointer() { return p_; }

	virtual void *get_deleter() { return nullptr; }
};

// shared pointer counted implement pointer deleter
template <typename T, typename D>
class Sp_counted_impl_pd: public Sp_counted_base {
private:
	T *p_;		// pointer
	D del_;	// deleter

	Sp_counted_impl_pd(const Sp_counted_impl_pd &) = delete;
	Sp_counted_impl_pd &operator =(const Sp_counted_impl_pd &) = delete;

public:
	Sp_counted_impl_pd(T *p, D &d): p_(p), del_(del) {}

	Sp_counted_impl_pd(T *p): p_(p), del_() {}

	virtual void dispose() noexcept { del_(p_); }
	
	virtual void *get_pointer() { return p_; }

	virtual void *get_deleter() { return &del_; }
};

// shared pointer counted implement pointer deleter allocator
template <typename T, typename D, typename Alloc>
class Sp_counted_impl_pda: public Sp_counted_base {
private:
	T p_;			// pointer
	D del_;		// deleter
	Alloc alloc_;	// allocator

	Sp_counted_impl_pda(const Sp_counted_impl_pda &) = delete;
	Sp_counted_impl_pda &operator =(const Sp_counted_impl_pda &) = delete;

	typedef Sp_counted_impl_pda<T, D, Alloc> this_type;

public:
	Sp_counted_impl_pda(T p, D &del, Alloc alloc): p_(p), del_(del), alloc_(alloc) {}

	Sp_counted_impl_pda(T p, Alloc alloc): p_(p), del_(), alloc_(alloc) {}

	virtual void dispose() noexcept { del_(p_); }

	virtual void destroy() noexcept
	{
		typedef typename Alloc::template rebind<this_type>::other alloc_type;
		alloc_type alloc(alloc_);
		this->~this_type();
		alloc.deallocate(this, 1);
	}
	
	virtual void *get_pointer() { return p_; }

	virtual void *get_deleter() { return &reinterpret_cast<char &>(del_); }
};

#endif
