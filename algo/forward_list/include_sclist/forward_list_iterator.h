#ifndef __forward_list_iterator_h
#define __forward_list_iterator_h

#include "scnode.h"

template <typename T>
struct forward_list_iterator {
    SCLink link;

    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    typedef forward_list_iterator<T> this_type;

    forward_list_iterator(): link(NULL) {}

    explicit forward_list_iterator(SCLink *link): link(link) {}

    reference operator *() const
    {
        return get_element<T>(link);
    }

    pointer operator ->() const
    {
        return &get_element<T>(link);
    }

    this_type &operator ++()
    {
		link = link->next;
        return *this;
    }

    this_type operator ++(int)
    {
        this_type tmp(*this);
        link = link->next;
        return tmp;
    }

    bool operator ==(const this_type &other) const
    {
        return (link == other.link);
    }

    bool operator !=(const this_type &other) const
    {
        return !(*this == other);
    }
};

#endif
