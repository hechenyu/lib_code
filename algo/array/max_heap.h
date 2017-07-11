#ifndef __max_heap_h
#define __max_heap_h

#include <assert.h>
#include <utility>

/**
 * (二叉)堆是一个数组, 被看做为一个近似的完全二叉树,
 * 树上的每一个结点对应数组中的一个元素.
 * 除了最底层外, 该树是完全充满的, 而且是从左向右填充.
 * 表示堆的数组A包含两个属性: A.length(通常)给出数组元素的个数,
 * A.heap-size表示有多少个堆元素存储在该数组中.
 * 注意: 虽然A[1..A.length]可能都存有数据, 
 * 但只有A[1..A.heap-size]中存放的是堆的有效元素,
 * 这里, 0 <(=) A.heap-size <(=) A.length.
 * 树的根结点是A[1], 这样给定一个结点的下标i,
 * 我们很容易计算得到它的父结点、左孩子和右孩子的下标:
 * PARENT(i): i/2下取整
 * LEFT(i): 2*i
 * RIGHT(i): 2*i+1
 *
 * 最大堆堆的性质: 除了根以外的所有结点i都满足
 * A[PARENT(i)] >(=) A[i]
 *
 *                16(1)
 *               /   \
 *             /       \
 *           /           \
 *         14(2)          10(3)
 *        /  \           /  \
 *      /      \       /      \
 *     8(4)     7(5)  9(6)    3(7)
 *   /   \     /  \
 *  2(8) 4(9) 1(10) 
 *
 *  | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|  index
 *  |16|14|10| 8| 7| 9| 3| 2| 4| 1|  array
 */
template <typename T>
struct MAXHeap {
    int heap_size;  // 堆中元素个数, 等价于A.heap-size
    int length;     // 数组元素个数, 等价于A.length
    T  *array;
};

// 给定结点的下标i, 计算父结点的下标
inline
int heap_parent(int i) { return i/2; }

// 给定结点的下标i, 计算左子结点的下标
inline
int heap_left(int i) { return i*2; }

// 给定结点的下标i, 计算右子结点的下标
inline
int heap_right(int i) { return i*2+1; }

// 维护最大堆性质, 输入时下标i,
// 在调用heap_fix_down时, 
// 我们假定根结点为left(i)和right(i)的二叉树都是最大堆,
// 这时array[i]有可能小于其孩子, 这样就违背了最大堆的性质.
// 通过让array[i]的值在最大堆中"逐级下降",
// 从而使得以下标i为根结点的子树重新遵循最大堆的性质.
template <typename T>
void heap_fix_down(MAXHeap<T> &heap, int i)
{
    using std::swap;

    auto l = heap_left(i);
    auto r = heap_right(i);

    // 找到i,left(i),right(i)中最大元素位置
    auto largest = i;
    if (l <= heap.heap_size && heap.array[largest] < heap.array[l])
        largest = l;
    if (r <= heap.heap_size && heap.array[largest] < heap.array[r])
        largest = r;

    // 如果最大元素位置不是i, 那么交换元素, 并逐级下降
    if (largest != i) {
        swap(heap.array[i], heap.array[largest]);
        heap_fix_down(heap, largest);
    }
}

// 构建最大堆: 数组元素为array[1..length], 堆元素为array[1..heap_size]
template <typename T>
void heap_build(MAXHeap<T> &heap, T *array, int length, int heap_size)
{
    assert(heap_size <= length);
    heap.array = array;
    heap.length = length;
    heap.heap_size = heap_size;

    for (int i = heap.heap_size/2; i >= 1; i--) {
        heap_fix_down(heap, i);
    }
}

// 初始化堆
template <typename T>
void heap_init(MAXHeap<T> &heap, T *array, int length)
{
    heap_build(heap, array, length, 0);
}

// 扩展堆
template <typename T>
T *heap_extend(MAXHeap<T> &heap, T *array, int length)
{
    assert(heap.length <= length);

    auto old_array = heap.array;
    for (int i = 1; i <= heap.heap_size; i++) {
        array[i] = heap.array[i];
    }
    heap.array = array;
    heap.length = length;

    return old_array;
}

// 返回当前堆中元素个数
template <typename T>
int heap_size(MAXHeap<T> &heap)
{
    return heap.heap_size;
}

// 返回堆中最大存放元素个数
template <typename T>
int heap_max_size(MAXHeap<T> &heap)
{
	return heap.length;
}

// 查找最大元素
template <typename T>
T &heap_maximum(MAXHeap<T> &heap)
{
    return heap.array[1];
}

// 判断最大堆是否为空
template <typename T>
bool heap_is_empty(MAXHeap<T> &heap)
{
    return heap.heap_size == 0;
}

// 判断最大堆是否为满
template <typename T>
bool heap_is_full(MAXHeap<T> &heap)
{
    return heap.heap_size == heap.length;
}

// 从最大堆中弹出最大元素, 并维护最大堆性质
template <typename T>
T heap_extract_max(MAXHeap<T> &heap)
{
    assert(!heap_is_empty(heap) && "underflow");

    auto max = heap.array[1];
    heap.array[1] = heap.array[heap.heap_size];
    heap.heap_size -= 1;
    heap_fix_down(heap, 1);
    return max;
}

// 维护最大堆性质, 输入时下标i,
// 在调用heap_fix_up时, 
// 我们假定array[i]的值比以前的值大,
// 这时array[i]有可能大于其PARENT, 这样就违背了最大堆的性质.
// 通过让array[i]的值在最大堆中"逐级上升",
// 从而使得整个树重新遵循最大堆的性质.
template <typename T>
void heap_fix_up(MAXHeap<T> &heap, int i)
{
    assert(i <= heap.heap_size);

    using std::swap;

    while (i > 1 && heap.array[heap_parent(i)] < heap.array[i]) {
        swap(heap.array[i], heap.array[heap_parent(i)]);
        i = heap_parent(i);
    }
}

// 增加下标i对应元素的值
template <typename T>
void heap_increase_key(MAXHeap<T> &heap, int i, const T &key)
{
    assert(i <= heap.heap_size);
    assert(heap.array[i] < key);

    heap.array[i] = key;
    heap_fix_up(heap, i);
}

// 向最大堆中插入一个新元素
template <typename T>
void heap_insert(MAXHeap<T> &heap, const T &key)
{
    assert(!heap_is_full(heap) && "overflow");

    heap.heap_size += 1;
    heap.array[heap.heap_size] = key;
    heap_fix_up(heap, heap.heap_size);
}

#endif

