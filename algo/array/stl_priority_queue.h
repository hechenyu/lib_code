#ifndef __stl_priority_queue_h
#define __stl_priority_queue_h

#include "max_heap.h"

namespace stl {

// 优先级队列不管理内存
template <typename T>
class priority_queue {
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

	// 队列是否已满
	bool full() const
	{
		return heap_is_full(heap_);
	}

    void extend()
    {
        auto new_length = heap_max_size(heap_) * EXTAND_FACTOR;
        auto old_array = heap_extend(heap_, new_array(new_length+1), new_length);
        free_array(old_array);
    }

private:
	mutable MAXHeap<T> heap_;	// 最大堆

public:
	// 创建优先级队列
	// buffer为缓存, size为缓存大小
	// buffer[0]废弃不用, heap_size最大值要比size小1
	priority_queue()
	{
        heap_init(heap_, new_array(DEFAULT_SIZE+1), DEFAULT_SIZE);
	}

	// 队列是否为空
	bool empty() const
	{
		return heap_is_empty(heap_);
	}

	// 返回队列中元素个数
	int size() const
	{
		return heap_size(heap_);
	}

	// 返回最大值元素
	const T &top() const
	{
		return heap_maximum(heap_);
	}

	// 弹出最大值元素
	void pop()
	{
        assert(!empty() && "underflow");
		heap_extract_max(heap_);
	}

	// 往队列里插入一个元素
	void push(const T &val)
	{
		if (full()) {
            extend();
		}

		heap_insert(heap_, val);
	}
};

}   // namespace stl

#endif
