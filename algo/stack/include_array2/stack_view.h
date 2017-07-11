#ifndef	__stack_view_h
#define	__stack_view_h

#include <assert.h>

// 数组实现的栈
// index: [0][1][2]...[length-1]
// array: [x][x][x]...[   x    ]
//               ^top
template <typename T>
class Stack_view {
private:
	int stack_top = -1;	    // 栈顶下标
	int stack_capacity = 0;	// 栈容量
	T  *stack_data = 0;     // 栈实际空间
    
public:
    // 默认构造
    Stack_view()
    {
    }

    // 初始化栈
    Stack_view(T *array, int length, int num_elem = 0)
    {
        assign(array, length, num_elem);
    }

    // 赋值
    void assign(T *array, int length, int num_elem = 0)
    {
        assert(length > 0 && num_elem <= length);
        stack_top = num_elem-1;
        stack_capacity = length;
        stack_data = array;
    }

    // 获取存放数据的数组
    T *data() const
    {
        return stack_data;
    }

    // 返回当前栈中元素个数
    int size() const
    {
        return stack_top+1;
    }

    // 返回栈中最大存放元素个数
    int capacity() const
    {
        return stack_capacity;
    }

    // 判断栈是否为空
    bool empty() const
    {
        return stack_top == -1;
    }

    // 判断栈是否已满
    bool full() const
    {
        return stack_top == stack_capacity-1;
    }

    // 入栈
    void push(const T &x)
    {
        assert(!full() && "overflow");

        stack_top += 1;
        stack_data[stack_top] = x;
    }

    // 查看栈顶元素
    T &top() const
    {
        assert(!empty() && "stack empty");

        return stack_data[stack_top];
    }

    // 出栈
    T pop()
    {
        assert(!empty() && "underflow");

        stack_top -= 1;
        return stack_data[stack_top+1];
    }

    // 交换
    void swap(Stack_view &x)
    {
        Stack_view tmp = *this;
        *this = x;
        x = tmp;
    }
};

#endif	// __stack_h
