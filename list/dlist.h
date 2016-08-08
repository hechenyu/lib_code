#ifndef __dlist_h
#define __dlist_h

// 双向循环链表结点, 不包含数据
typedef struct Dlist_node_base *Dlist_link;

struct Dlist_node_base {
	Dlist_link next;
	Dlist_link prev;
};

// 带哨兵结点的双向循环链表
struct Dlist_base {
	Dlist_node_base nil;	// 哨兵结点
};

/**
 * 初始化链表
 *         ____
 *        |    |
 *        V    |
 *   .--[nil]--'
 *   |    A    
 *   |____|     
 */
inline 
void list_init(Dlist_base &list)
{
	// 初始化nil结点
	list.nil.prev = list.nil.next = &list.nil;
}

// 判断list是否为空, 
inline
bool list_empty(const Dlist_base &list)
{
	return (list.nil.next == &list.nil);
}

/**
 * 在链表的x结点前插入t结点
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *                                ^-x
 *                  ___        
 *                 |   |------>
 *            <----|___|       
 *                   ^-t       
 * =========================================
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *             A                 A ^-x
 *             |    ___          |
 *             |   |   |---------'
 *             '---|___|       
 *                   ^-t       
 * =========================================
 *            ___                ___
 *           |   |--.     .---->|   |------>
 *    <------|___|  |     |  .--|___|
 *             A    |     |  |    ^-x
 *             |    V__   |  |
 *             |   |   |--'  |
 *             '---|___|<----'
 *                   ^-t
 */
void list_insert(Dlist_link x, Dlist_link t)
{
	t->prev = x->prev;
	t->next = x;
	x->prev->next = t;
	x->prev = t;
}

/**
 * 从链表上删除x结点
 *            ___           ___           ___ 
 *           |   |-------->|   |-------->|   |------>
 *    <------|___|<--------|___|<--------|___|
 *                           ^-x       
 * ==================================================
 *                     ____________________
 *                    |                    |
 *            ___     |     ___           _V_ 
 *           |   |----'    |   |-------->|   |------>
 *    <------|___|<--------|___|    .----|___|
 *             A             ^-x    |   
 *             |____________________|                    
 */
void list_remove(Dlist_link x)
{
	x->prev->next = x->next;
	x->next->prev = x->prev;
}

template <typename T>
struct Dlist_node : public Dlist_node_base {
    T value;
};

template <typename T>
struct Dlist : public Dlist_base {
};

template <typename T>
Dlist_node<T> *list_new_node(const T &val)
{
    auto x = new Dlist_node<T>;
    x->value = val;
    return x;
}

template <typename T>
void list_free_node(Dlist_node<T> *x)
{
    delete x;
}

// 在链表头插入结点
template <typename T>
void list_insert_front(Dlist<T> &list, Dlist_node<T> *x)
{
    list_insert(list.nil.next, x);
}

// 在链表尾插入结点
template <typename T>
void list_insert_back(Dlist<T> &list, Dlist_node<T> *x)
{
    list_insert(&list.nil, x);
}

// 在链表头删除结点
template <typename T>
Dlist_node<T> *list_remove_front(Dlist<T> &list)
{
    auto x = list.nil.next;
    list_remove(x);
    return static_cast<Dlist_node<T> *>(x);
}

// 在链表尾删除结点
template <typename T>
Dlist_node<T> *list_remove_back(Dlist<T> &list)
{
    auto x = list.nil.prev;
    list_remove(x);
    return static_cast<Dlist_node<T> *>(x);
}

template <typename T, typename Function>
void list_for_each(Dlist<T> &list, Function fn)
{
    for (Dlist_link x = list.nil.next; x != &list.nil; x = x->next)
        fn(static_cast<Dlist_node<T> *>(x));
}

template <typename T>
Dlist_node<T> *list_search(Dlist<T> &list, const T &val)
{
    Dlist_link x = list.nil.next; 
    while (x != &list.nil && static_cast<Dlist_node<T> *>(x)->value != val)
        x = x->next;
    return static_cast<Dlist_node<T> *>(x); 
}

#endif
