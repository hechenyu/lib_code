#ifndef __stack_h
#define __stack_h

#include "adapter_stack.h"
#include <stddef.h>
#include <assert.h>
#include <deque>

// 栈结构: LIFO, 后进先出
template <typename T, typename Container = std::deque<T>> 
class stack {
private:
    Stack<Container> self;
    Container cont_;

protected:
    enum { DEFAULT_SIZE = 64, EXTAND_FACTOR = 2 };

    bool full()
    {
        return stack_is_full(self);
    }

    void extend()
    {
        auto length = stack_max_size(self) * EXTAND_FACTOR;
        auto size = stack_size(self);
        cont_.resize(length);
        stack_init(self, cont_, length, size);
    }

public:
    typedef T value_type;
    typedef size_t size_type;
    typedef Container container_type;
    typedef T &reference;
    typedef const T &const_reference;

    explicit stack(const Container &cont): cont_(cont)
    {
        auto size = cont_.size();
        auto length = cont_.size();
        stack_init(self, cont_, length, size);
    }

    // 构造一个空的stack对象
    stack()
    {
        cont_.resize(DEFAULT_SIZE);
        stack_init(self, cont_, DEFAULT_SIZE);
    }

    // 复制stack
    stack(const stack &x): cont_(x.cont_)
    {
        auto size = x.size();
        auto length = cont_.size();
        stack_init(self, cont_, length, size);
    }

    // 销毁stack对象
    ~stack()
    {
    }

    // 返回stack中元素个数
    size_type size() const 
    {
        return stack_size(self);
    }

    // 返回stack是否为空
    bool empty() const 
    {
        return stack_is_empty(self);
    }

    // 往stack中push一个元素
    void push(const T& elem) 
    {
        if (full()) {
            extend();
        }

        stack_push(self, elem);
    }

    // 从stack中pop一个元素
    void pop() 
    {
        assert(!empty());

        stack_pop(self);
    }

    // 返回stack顶部元素的引用
    T& top() 
    {
        assert(!empty());

        return stack_peek(self);
    }

    // 交换两个stack的所有元素
    void swap(stack &x)
    {
        stack_swap(self, x.self);
    }
};

#endif /* __stl_stack_h */
