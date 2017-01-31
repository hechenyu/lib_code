#ifndef __stl_stack_h
#define __stl_stack_h

#include "stack.h"
#include <stddef.h>
#include <assert.h>

namespace stl {

template <typename T>
class stack {
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
        return stack_is_full(stack_);
    }

    void extend()
    {
        auto new_length = stack_max_size(stack_) * EXTAND_FACTOR;
        auto old_array = stack_extend(stack_, new_array(new_length), new_length);
        free_array(old_array);
    }

private:
    mutable Stack<T> stack_;

public:
    typedef T value_type;
    typedef size_t size_type;

    // construct an empty stack
    stack()
    {
        stack_init(stack_, new_array(DEFAULT_SIZE), DEFAULT_SIZE);  
    }

    // destroy stack
    ~stack()
    {
        free_array(stack_data(stack_));
    }

    // number of elements
    size_type size() const 
    {
        return stack_size(stack_);
    }

    // is stack empty?
    bool empty() const 
    {
        return stack_is_empty(stack_);
    }

    // push element into the stack
    void push(const T& elem) 
    {
        if (full()) {
            extend();
        }

        stack_push(stack_, elem);
    }

    // pop element out of the stack
    void pop() 
    {
        assert(!empty());

        stack_pop(stack_);
    }

    // return value of next element
    T& top() 
    {
        assert(!empty());

        return stack_peek(stack_);
    }
};

}   // namespace stl

#endif /* __stl_stack_h */
