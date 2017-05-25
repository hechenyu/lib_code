#ifndef __forward_list_h
#define __forward_list_h

#include <cstddef>
#include <type_traits>
#include <initializer_list>

#include "sclist.h"
#include "sclist_iterator.h"

template <typename T> 
using forward_list_iterator = SCList_iterator<T>;

template <typename T>
class forward_list: private SCList<T> {
public:
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef forward_list_iterator<T> iterator;

    forward_list()
    {
        list_init(this);
    }

    forward_list(std::initializer_list<value_type> il)
    {
        list_init(this);
        auto x = list_dummy_head(this);
        for (auto &e : il) {
            x = list_insert_next(x, new SCList_node<T>(e));
        }
    }

	explicit forward_list(size_type n, const value_type &val = value_type())
    {
        list_init(this);
        auto x = list_dummy_head(this);
        for (size_type i = 0; i < n; i++) {
            x = list_insert_next(x, new SCList_node<T>(val));
        }
    }

	template <typename InputIterator, typename = typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type>
	forward_list(InputIterator first, InputIterator last)
    {
        list_init(this);
        auto x = list_dummy_head(this);
        while (first != last) {
            x = list_insert_next(x, new SCList_node<T>(*first++));
        }
    }

	forward_list(const forward_list &fwdlst)
    {
        list_init(this);
        auto x = list_dummy_head(this);
        for (auto &e : fwdlst) {
            x = list_insert_next(x, new SCList_node<T>(e));
        }
    }

    ~forward_list()
    {
        list_clear(this);
    }

    bool empty() const
    {
        return list_is_empty(this);
    }

    void push_front(const value_type &val)
    {
        list_insert_head(this, new SCList_node<T>(val));
    }

	iterator before_begin()
	{
		return iterator(list_dummy_head(this));
	}

	iterator begin()
	{
		return iterator(list_head(this)); 
	}

	iterator end()
    {
        return iterator(NULL);
    }

	void remove(const value_type &val)
	{
        list_remove(this, val);
	}

	template <typename Predicate>
	void remove_if(Predicate pred)
	{
        list_remove_if(this, pred);
	}

    void reverse()
    {
        list_reverse(this);
    }

    void sort()
    {
        list_selection(this);
    }

    template <typename Compare>
    void sort(Compare comp)
    {
        list_selection(this, comp);
    }

    void splice_after(iterator pos, forward_list &fwdlst)
    {
        list_transfer_next(pos.get_node(), &fwdlst);
    }

    void splice_after(iterator pos, forward_list &fwdlst, iterator i)
    {
        list_transfer_next(pos.get_node(), i.get_node());
    }

    void splice_after(iterator pos, forward_list &fwdlst, iterator first, iterator last)
    {
        list_transfer_next(pos.get_node(), first.get_node(), last.get_node());
    }
};

#endif
