#ifndef __stack_h
#define __stack_h

#include "array_stack.h"
#include <stddef.h>
#include <assert.h>

// 栈结构: LIFO, 后进先出
template <typename T, typename C = void>    // typename C 是为了适配std::stack接口
class stack {
private:
    Stack<T> self;

protected:
    enum { DEFAULT_SIZE = 64, EXTAND_FACTOR = 2 };

    T *data()
    {
        return stack_data(self);
    }

    bool full()
    {
        return stack_is_full(self);
    }

    void extend()
    {
        auto length = stack_max_size(self) * EXTAND_FACTOR;
        auto size = stack_size(self);
        T *array = new T[length];
        for (int i = 0; i < size; i++) {    // copy
            array[i] = stack_data(self)[i];
        }
        delete [] data();
        stack_init(self, array, length, size);
    }

public:
    typedef T value_type;
    typedef size_t size_type;
    typedef C container_type;
    typedef T &reference;
    typedef const T &const_reference;

    // 适配std::stack的从容器构造函数
	template <typename Container>
    explicit stack(const Container &cont)
    {
        auto size = cont.size();
        auto length = size * EXTAND_FACTOR;
        T *array = new T[length];
        int i = 0;
        for (auto &item :cont) {
            array[i++] = item;
        }
        stack_init(self, array, length, size);
    }

    // 构造一个空的stack对象
    stack(int n = DEFAULT_SIZE)
    {
        stack_init(self, new T[n], n);
    }

    // 复制stack
    stack(const stack &x)
    {
        auto size = x.size();
        auto length = size * EXTAND_FACTOR;
        T *array = new T[length];
        for (int i = 0; i < size; i++) {
            array[i] = x.data()[i];
        }
        stack_init(self, array, length, size);
    }

    // 销毁stack对象
    ~stack()
    {
        delete [] data();
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
