#ifndef __slist_h
#define __slist_h

/**
 * 有哑源头结点, 尾结点为空
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *             ^head
 */
typedef struct SList_node_base *SList_link;

struct SList_node_base {
    SList_link next;
};

struct SList_base {
    SList_node_base head;
};

// 初始化链表
inline
void list_init(SList_base &list)
{
    list.head.next = nullptr;
}

// 判断list是否为空, 
inline
bool list_is_empty(const SList_base &list)
{
	return (list.head.next == nullptr);
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
void list_insert_next(SList_link x, SList_link t)
{
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
void list_delete_next(SList_link x)
{
	auto t = x->next;
	x->next = t->next;
}

template <typename T>
struct SList_node : public SList_node_base {
    T value;
};

template <typename T>
struct SList : public SList_base {
};

template <typename T>
SList_node<T> *list_new_node(const T &val)
{
    auto x = new SList_node<T>;
    x->value = val;
    return x;
}

template <typename T>
void list_free_node(SList_node<T> *x)
{
    delete x;
}

// 在链表头插入结点
template <typename T>
void list_insert_front(SList<T> &list, SList_node<T> *x)
{
    list_insert_next(&list.head, x);
}

// 在链表头删除结点
template <typename T>
SList_node<T> *list_delete_front(SList<T> &list)
{
    auto x = list.head.next;
    list_delete_next(&list.head);
    return static_cast<SList_node<T> *>(x);
}

template <typename T, typename Function>
void list_for_each(SList<T> &list, Function fn)
{
    for (SList_link x = list.head.next; x != nullptr; x = x->next)
        fn(static_cast<SList_node<T> *>(x));
}

template <typename T>
SList_node<T> *list_search(SList<T> &list, const T &val)
{
    SList_link x = list.head.next; 
    while (x != nullptr && static_cast<SList_node<T> *>(x)->value != val)
        x = x->next;
    return static_cast<SList_node<T> *>(x); 
}

#endif
