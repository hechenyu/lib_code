#ifndef __stl_queue_h
#define __stl_queue_h

#include "dclist.h"
#include <stddef.h>
#include <assert.h>

namespace stl {

template <typename T>
class queue {
protected:
    typedef DCList<T> list_type;
    typedef DCList_link link_type;
	typedef DCList_node<T> node_type;

private:
    list_type list_;
    int size_ = 0;

public:
    typedef T value_type;
    typedef size_t size_type;

    // construct an empty queue
    queue()
    {
        list_init(list_);
    }

    // destroy queue
    ~queue()
    {
        using dclist::free_node;
        list_destroy(list_, [](link_type x) { free_node(list_link_cast<T>(x)); });
    }

    // number of elements
    size_type size() const
    {
        return size_;
    }

    // is queue empty?
    bool empty() const 
    {
        return list_is_empty(list_);
    }

    // insert element into the queue
    void push(const T& elem) 
    {
        using dclist::new_node;
        list_insert_back(list_, new_node(elem));
        size_++;
    }

    // remove next element from the queue
    void pop()
    {
        assert(!empty());

        using dclist::free_node;
        free_node(list_link_cast<T>(list_delete_front(list_)));
        size_--;
    }

    // return value of next element
    T& front()
    {
        assert(!empty());

        return list_link_cast<T>(list_head(list_))->value;
    }

    // return value of last element
    T& back()
    {
        assert(!empty());

        return list_link_cast<T>(list_tail(list_))->value;
    }
};

}   // namespace stl

#endif /* __stl_queue_h */
