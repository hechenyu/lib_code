#ifndef __sclist_h
#define __sclist_h

#include <stddef.h>
#include <assert.h>

// Single Chain List
// 单向循环链表节点, 不包含数据
typedef struct SCList_node_base *SCList_link;

/**
 * 单向链表节点基类
 *    ___     
 *   |   | next  
 *   |___|------>       
 *  
 */
struct SCList_node_base {
    SCList_link next;
};

/**
 * 有哑源头结点, 尾结点为空
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *             ^head
 */
struct SCList_base {
    SCList_node_base head;
};

// 初始化链表
inline
void list_init(SCList_base &list)
{
    list.head.next = NULL;
}

// 判断list是否为空, 
inline
bool list_is_empty(const SCList_base &list)
{
	return (list.head.next == NULL);
}

/**
 * 在链表的x结点后插入y结点
 *            ___                ___
 *    ------>|   |------------->|   |------>
 *           |___|              |___|
 *             ^-x
 *                     ___        
 *                    |   |------>
 *                    |___|       
 *                      ^-t       
 * =========================================
 *            ___                ___
 *    ------>|   |------------->|   |------>
 *           |___|          .-->|___|
 *             ^-x          |
 *                     ___  |      
 *                    |   |-'
 *                    |___|       
 *                      ^-t       
 * =========================================
 *            ___                ___
 *    ------>|   |--.        .->|   |------>
 *           |___|  |        |  |___|
 *             ^-x  |        |
 *                  |   ___  |      
 *                  '->|   |-'
 *                     |___|       
 *                       ^-t       
 */
inline 
void list_insert_next(SCList_link x, SCList_link t)
{
    assert(x != NULL && t != NULL);
	t->next = x->next;
	x->next = t;
}

/**
 * 从链表上删除x结点后面的结点
 *            ___           ___           ___ 
 *    ------>|   |-------->|   |-------->|   |------>
 *           |___|         |___|         |___|
 *             ^-x           ^-t
 * ==================================================
 *                     ____________________
 *                    |                    |
 *            ___     |     ___           _V_ 
 *    ------>|   |----'    |   |-------->|   |------>
 *           |___|         |___|         |___|
 *             ^-x           ^-t
 */
inline
void list_delete_next(SCList_link x)
{
    assert(x != NULL && x->next != NULL);
	auto t = x->next;
	x->next = t->next;
}

template <typename T>
struct SCList_node : public SCList_node_base {
    T value;
};

template <typename T>
struct SCList : public SCList_base {
};

template <typename T>
SCList_node<T> *list_new_node(const T &val)
{
    auto x = new SCList_node<T>;
    x->value = val;
    return x;
}

template <typename T>
void list_free_node(SCList_node<T> *x)
{
    delete x;
}

// 在链表头插入结点
template <typename T>
void list_insert_front(SCList<T> &list, SCList_node<T> *x)
{
    list_insert_next(&list.head, x);
}

// 在链表头删除结点
template <typename T>
SCList_node<T> *list_delete_front(SCList<T> &list)
{
    auto x = list.head.next;
    list_delete_next(&list.head);
    return static_cast<SCList_node<T> *>(x);
}

template <typename T, typename Function>
void list_for_each(SCList<T> &list, Function fn)
{
    for (SCList_link x = list.head.next; x != NULL; x = x->next)
        fn(static_cast<SCList_node<T> *>(x));
}

template <typename T>
SCList_node<T> *list_search(SCList<T> &list, const T &val)
{
    SCList_link x = list.head.next; 
    while (x != NULL && static_cast<SCList_node<T> *>(x)->value != val)
        x = x->next;
    return static_cast<SCList_node<T> *>(x); 
}

#endif
