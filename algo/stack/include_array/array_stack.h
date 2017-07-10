#ifndef	__array_stack_h
#define	__array_stack_h

#include <assert.h>

// 数组实现的栈
// index: [0][1][2]...[length-1]
// array: [x][x][x]...[   x    ]
//               ^top
template <typename T>
struct Stack {
	int top;	// 栈顶下标
	int length;	// 栈大小
	T  *array;	// 栈实际空间
};

// 初始化栈
template <typename T>
void stack_init(Stack<T> &stack, T *array, int length, int num_elem = 0)
{
    assert(length > 0 && num_elem <= length);
    stack.top = num_elem-1;
    stack.length = length;
    stack.array = array;
}

// 获取存放数据的数组
template <typename T>
T *stack_data(Stack<T> &stack)
{
    return stack.array;
}

// 返回当前栈中元素个数
template <typename T>
int stack_size(const Stack<T> &stack)
{
    return stack.top+1;
}

// 返回栈中最大存放元素个数
template <typename T>
int stack_max_size(const Stack<T> &stack)
{
	return stack.length;
}

// 判断栈是否为空
template <typename T>
bool stack_is_empty(const Stack<T> &stack)
{
    return stack.top == -1;
}

// 判断栈是否已满
template <typename T>
bool stack_is_full(const Stack<T> &stack)
{
	return stack.top == stack.length-1;
}

// 入栈
template <typename T>
void stack_push(Stack<T> &stack, const T &x)
{
    assert(!stack_is_full(stack) && "overflow");

	stack.top += 1;
	stack.array[stack.top] = x;
}

// 查看栈顶元素
template <typename T>
T &stack_peek(Stack<T> &stack)
{
    assert(!stack_is_empty(stack) && "stack empty");
    return stack.array[stack.top];
}

// 出栈
template <typename T>
T stack_pop(Stack<T> &stack)
{
    assert(!stack_is_empty(stack) && "underflow");
	stack.top -= 1;
	return stack.array[stack.top+1];
}

template <typename T>
void stack_swap(Stack<T> &stack1, Stack<T> &stack2)
{
    Stack<T> tmp = stack1;
    stack1 = stack2;
    stack2 = tmp;
}

#endif	// __stack_h
