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
 *   |   |------>
 *   |___| next  
 * 
 */
struct SCList_node_base {
    SCList_link next;
};

/**
 * 有哑源头结点, 尾结点的next为空
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *  
 */
struct SCList_base {
    SCList_node_base head;
};

/**
 * 初始化链表
 *
 * [head] -> NIL
 *
 */
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

// 返回列表头部第一个结点(不包含哑结点)
inline
SCList_link list_head(SCList_base &list)
{
    return list.head.next;
}

// 在链表头插入结点
inline
void list_insert_front(SCList_base &list, SCList_link x)
{
    list_insert_next(&list.head, x);
}

// 在链表头删除结点
inline
void list_delete_front(SCList_base &list)
{
    list_delete_next(&list.head);
}

// 遍历list所有结点
template <typename Function>
void list_for_each(SCList_base &list, Function fn)
{
    for (auto x = list_head(list); x != NULL; x = x->next)
        fn(x);
}

template <typename T>
struct SCList_node : public SCList_node_base {
    T value;
};

template <typename T>
struct SCList : public SCList_base {
};

// 将SCList_link强转成子类指针
template <typename T>
SCList_node<T> *list_link_cast(SCList_link x)
{
    return static_cast<SCList_node<T> *>(x);
}

template <typename T>
SCList_node<T> *list_search(SCList<T> &list, const T &val)
{
    auto x = list_head(list);
    while (x != NULL && list_link_cast<T>(x)->value != val)
        x = x->next;
    return list_link_cast<T>(x); 
}

#endif
