#ifndef __stl_queue_h
#define __stl_queue_h

#include "queue.h"
#include <stddef.h>
#include <assert.h>

namespace stl {

template <typename T>
class queue {
protected:
    enum { DEFAULT_SIZE = 10, EXTAND_FACTOR = 2 };

    T *new_array(int length)
    {
        return new T[length];
    }

    void free_array(T *array)
    {
        delete [] array;
    }

    bool full()
    {
        return queue_is_full(queue_);
    }

    void extend()
    {
        auto new_length = queue_max_size(queue_) * EXTAND_FACTOR;
        auto old_array = queue_extend(queue_, new_array(new_length+1), new_length+1);
        free_array(old_array);
    }

private:
    mutable Queue<T> queue_;

public:
    typedef T value_type;
    typedef size_t size_type;

    // construct an empty queue
    queue()
    {
        queue_init(queue_, new_array(DEFAULT_SIZE+1), DEFAULT_SIZE+1);
    }

    // destroy queue
    ~queue()
    {
        free_array(queue_data(queue_));
    }

    // number of elements
    size_type size() const
    {
        return queue_size(queue_);
    }

    // is queue empty?
    bool empty() const 
    {
        return queue_is_empty(queue_);
    }

    // insert element into the queue
    void push(const T& elem) 
    {
        if (full()) {
            extend();
        }

        queue_put(queue_, elem);
    }

    // remove next element from the queue
    void pop()
    {
        assert(!empty());

        queue_get(queue_);
    }

    // return value of next element
    T& front()
    {
        assert(!empty());

        return queue_head(queue_);
    }

    // return value of last element
    T& back()
    {
        assert(!empty());

        return queue_tail(queue_);
    }
};

}   // namespace stl

#endif /* __stl_queue_h */
