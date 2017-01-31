#ifndef	__queue_h
#define	__queue_h

#include <assert.h>

// 队列
// index: [0][1][2][3][4]...[length-1]
// array: [x][x][x][x][x]...[   x    ]
//            ^head    ^tail
template <typename T>
struct Queue {
    int head;	// 队列首下标索引
    int tail;	// 队列尾下标索引
    int length;	// 队列长度
    T * array;	// 队列实际空间
};

// 初始化队列
template <typename T>
void queue_init(Queue<T> &queue, T *array, int length)
{
    assert(length > 0);
    queue.array = array;
    queue.length = length;
    queue.head = queue.tail = 0;
}

template <typename T>
T *queue_data(Queue<T> &queue)
{
    return queue.array;
}

// 返回当前队列中元素个数
template <typename T>
int queue_size(Queue<T> &queue)
{
    return (queue.tail-queue.head+queue.length)%queue.length;
}

// 扩展队列
template <typename T>
T *queue_extend(Queue<T> &queue, T *array, int length)
{
    assert(queue.length <= length);
    auto n = queue_size(queue);
    auto old_array = queue.array;
    for (int i = 0; i < n; i++) {
        array[i] = queue.array[(queue.head+i)%queue.length];
    }
    queue.array = array;
    queue.length = length;
    queue.head = 0;
    queue.tail = n;

    return old_array;
}

// 返回队列中最大存放元素个数
template <typename T>
int queue_max_size(Queue<T> &queue)
{
    return queue.length-1;
}

// 判断队列是否为空
template <typename T>
bool queue_is_empty(Queue<T> &queue)
{
    return queue.head == queue.tail;
}

// 判断队列是否已满
template <typename T>
bool queue_is_full(Queue<T> &queue)
{
    return (queue.tail+1)%queue.length == queue.head;
}

// 返回队首元素
template <typename T>
T &queue_head(Queue<T> &queue)
{
    assert(!queue_is_empty(queue));

    return queue.array[queue.head];
}

// 返回队尾元素
template <typename T>
T &queue_tail(Queue<T> &queue)
{
    assert(!queue_is_empty(queue));

    return queue.array[(queue.tail-1+queue.length)%queue.length];
}

// 入栈
template <typename T>
void queue_put(Queue<T> &queue, const T &x)
{
    assert(!queue_is_full(queue));

    queue.array[queue.tail] = x;
    queue.tail = (queue.tail+1)%queue.length;
}

// 出队
template <typename T>
T queue_get(Queue<T> &queue)
{
    assert(!queue_is_empty(queue));

    T x = queue.array[queue.head];
    queue.head = (queue.head+1)%queue.length;
    return x;
}

#endif	// __queue_h
