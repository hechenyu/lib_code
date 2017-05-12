#ifndef __forward_list_h
#define __forward_list_h

#include <cstddef>
#include <initializer_list>

#include "sclist.h"
#include "forward_list_iterator.h"

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
        list_init(*this);
    }

    explicit forward_list(std::initializer_list<value_type> il)
    {
        list_init(*this);
        auto x = list_dumb_head(*this);
        for (auto &e : il) {
            insert_next(x, new SCNode<T>(e));
            x = x->next;
        }
    }

    bool empty() const
    {
        return list_is_empty(*this);
    }

    void push_front(const value_type &val)
    {
        list_insert_head(*this, new SCNode<T>(val));
    }

};

#endif
