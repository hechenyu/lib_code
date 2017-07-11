#ifndef	__array_stack_h
#define	__array_stack_h

#include <assert.h>

// 类数组容器实现的栈
// index: [0][1][2]...[length-1]
// cont : [x][x][x]...[   x    ]
//               ^top
template <typename C>
struct Stack {
	int top = -1;   	// 栈顶下标
	int length = 0; 	// 栈大小
	C *cont = 0;    	// 容器指针, 管理栈的实际空间
};

// 初始化栈
template <typename C>
void stack_init(Stack<C> &stack, C &cont, int length, int num_elem = 0)
{
    assert(length > 0 && num_elem <= length);
    stack.top = num_elem-1;
    stack.length = length;
    stack.cont = &cont;
}

// 获取存放数据的容器
template <typename C>
C *stack_data(Stack<C> &stack)
{
    return stack.cont;
}

// 返回当前栈中元素个数
template <typename C>
int stack_size(const Stack<C> &stack)
{
    return stack.top+1;
}

// 返回栈中最大存放元素个数
template <typename C>
int stack_max_size(const Stack<C> &stack)
{
	return stack.length;
}

// 判断栈是否为空
template <typename C>
bool stack_is_empty(const Stack<C> &stack)
{
    return stack.top == -1;
}

// 判断栈是否已满
template <typename C>
bool stack_is_full(const Stack<C> &stack)
{
	return stack.top == stack.length-1;
}

// 入栈
template <typename C>
void stack_push(Stack<C> &stack, typename C::const_reference x)
{
    assert(!stack_is_full(stack) && "overflow");

	stack.top += 1;
	(*stack.cont)[stack.top] = x;
}

// 查看栈顶元素
template <typename C>
typename C::reference stack_peek(Stack<C> &stack)
{
    assert(!stack_is_empty(stack) && "stack empty");
    return (*stack.cont)[stack.top];
}

// 出栈
template <typename C>
typename C::value_type stack_pop(Stack<C> &stack)
{
    assert(!stack_is_empty(stack) && "underflow");
	stack.top -= 1;
	return (*stack.cont)[stack.top+1];
}

template <typename C>
void stack_swap(Stack<C> &stack1, Stack<C> &stack2)
{
    Stack<C> tmp = stack1;
    stack1 = stack2;
    stack2 = tmp;
}

#endif	// __stack_h
