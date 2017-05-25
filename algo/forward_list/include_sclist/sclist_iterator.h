#ifndef __sclist_iterator_h
#define __sclist_iterator_h

#include "sclist.h"

template <typename T>
struct SCList_iterator {
    SCList_node<T> *node;

    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    typedef SCList_iterator<T> this_type;

    SCList_iterator(): node(NULL) {}

    explicit SCList_iterator(SCList_link link): node(list_node<T>(link)) {}

    reference operator *() const
    {
        return *list_data(node);
    }

    pointer operator ->() const
    {
        return list_data(node);
    }

    this_type &operator ++()
    {
        node = list_next(node);
        return *this;
    }

    this_type operator ++(int)
    {
        this_type tmp(*this);
        node = list_next(node);
        return tmp;
    }

    bool operator ==(const this_type &other) const
    {
        return (node == other.node);
    }

    bool operator !=(const this_type &other) const
    {
        return !(*this == other);
    }

    SCList_link get_node()
    {
        return node;
    }
};

template <typename T>
SCList_iterator<T> list_before_begin(SCList<T> *list)
{
    assert(list != NULL);
    return SCList_iterator<T>(list_dummy_head(list));
}

template <typename T>
SCList_iterator<T> list_begin(SCList<T> *list)
{
    assert(list != NULL);
    return SCList_iterator<T>(list_head(list));
}

template <typename T>
SCList_iterator<T> list_end(SCList<T> *list)
{
    assert(list != NULL);
    return SCList_iterator<T>(NULL);
}

#endif
