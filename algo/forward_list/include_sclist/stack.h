#ifndef __stack_h
#define __stack_h

#include "sclist.h"
#include <stddef.h>

// 栈结构: LIFO, 后进先出
template <typename T, typename C = void>    // typename C 是为了适配std::stack接口
class stack: private SCList<T> {
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
        list_init(this);
        for (auto &item : cont) {
            list_insert_head(this, new SCList_node<T>(item));
        }
        list_reverse(this);
    }

    // 构造一个空的stack对象
    stack()
    {
        list_init(this);
    }

    // 复制stack
    stack(const stack &x)
    {
        list_init(this);
        auto fn = [this] (const T &val) { list_insert_head(this, new SCList_node<T>(val)); };
        list_for_each(const_cast<stack *>(&x), fn);
        list_reverse(this);
    }

    // 销毁stack对象
    ~stack()
    {
        list_clear(this);
    }

    // 返回stack中元素个数
    size_type size() const 
    {
        return list_size(const_cast<stack *>(this));
    }

    // 返回stack是否为空
    bool empty() const 
    {
        return list_is_empty(const_cast<stack *>(this));
    }

    // 往stack中push一个元素
    void push(const T& elem) 
    {
        list_insert_head(this, new SCList_node<T>(elem));
    }

    // 从stack中pop一个元素
    void pop() 
    {
        delete list_node<T>(list_delete_head(this));
    }

    // 返回stack顶部元素的引用
    T& top() 
    {
        return *list_data(list_node<T>(list_head(this)));
    }

    // 交换两个stack的所有元素
    void swap(stack &x)
    {
        list_swap(this, &x);
    }
};

#endif /* __stl_stack_h */
