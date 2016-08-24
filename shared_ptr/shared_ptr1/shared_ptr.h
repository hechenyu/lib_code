
template <typename T>
class Shared_ptr {
public:
	typedef T element_type;

private:
    Sp_counted_base *pi_ = nullptr;

	/**
	 * default constructor
	 * The object is empty (owns no pointer, use count of zero).
	 */
	shared_ptr() noexcept {}

	/**
	 * construct from pointer
	 * The object owns p, setting the use count to 1.
	 */
	template <typename U>
	explicit shared_ptr(U *p)
	{
		try 
		{
			pi_ = new sp_counted_impl_p<U>(p);
		}
		catch (...) 
		{
			delete p;
			throw;
		}
	}

	/**
	 * construct from pointer + deleter
	 * the object also takes ownership of deleter del 
	 * (and uses it if at some point needs to delete p).
	 */
	template <typename U, typename D>
	explicit shared_ptr(U *p, D del)
	{
		try 
		{
			pi_ = new sp_counted_impl_pd<U, D>(p, del);
		}
		catch (...)
		{
			del(p);	// delete p
			throw;
		}
	}

	/**
	 * construct from pointer + deleter + allocator
	 * any memory needed for internal use is allocated using alloc 
	 * (of which the object keeps a copy, but does not take ownership).
	 */
	template <typename U, typename D, typename Alloc>
	shared_ptr(U *p, D del, Alloc alloc)
	{
		typedef sp_counted_impl_pda<P, D, Alloc> impl_type;
		typedef typename A::template rebind<impl_type>::other alloc_type;

		alloc_type impl_alloc(alloc);

		try
		{
			pi_ = impl_alloc.allocate(1);
			::new (static_cast<void *>(pi_)) impl_type(p, del, alloc);
		}
		catch (...)
		{
			del(p);
			if (pi_ != nullptr) {
				alloc.deallocate(static_cast<impl_type *>(pi_), 1);
			}
			throw;
		}
	}

};
