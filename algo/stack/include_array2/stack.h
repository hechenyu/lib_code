#ifndef __stack_h
#define __stack_h

#include "stack_view.h"
#include <stddef.h>
#include <assert.h>

// 栈结构: LIFO, 后进先出
template <typename T, typename C = void>    // typename C 是为了适配std::stack接口
class stack: public Stack_view<T> {
protected:
    enum { DEFAULT_SIZE = 64, EXTAND_FACTOR = 2 };

    typedef Stack_view<T> base;

    void extend()
    {
        auto size = this->size();
        auto length = size * EXTAND_FACTOR;
        T *array = new T[length];
        T *data = this->data();
        for (int i = 0; i < size; i++) {    // copy
            array[i] = data[i];
        }
        this->assign(array, length, size);
        delete [] data;
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
        this->assign(array, length, size);
    }

    // 构造一个空的stack对象
    stack(int n = DEFAULT_SIZE): base(new T[n], n)
    {
    }

    // 复制stack
    stack(const stack &x)
    {
        auto size = x.size();
        auto length = size * EXTAND_FACTOR;
        T *array = new T[length];
        T *data = x.data();
        for (int i = 0; i < size; i++) {
            array[i] = data[i];
        }
        this->assign(array, length, size);
    }

    // 销毁stack对象
    ~stack()
    {
        delete [] this->data();
    }

    // 往stack中push一个元素
    void push(const T& elem) 
    {
        if (this->full()) {
            extend();
        }

        base::push(elem);
    }
};

#endif /* __stl_stack_h */
