#ifndef __slist_h
#define __slist_h

/**
 * 有哑源头结点, 尾结点为空
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *             ^head
 */
typedef struct Slist_node_base *Slist_link;

struct Slist_node_base {
    Slist_link next;
};

struct Slist_base {
    Slist_node_base head;
};

// 初始化链表
inline
void list_init(Slist_base &list)
{
    list.head.next = nullptr;
}

// 判断list是否为空, 
inline
bool list_empty(const Slist_base &list)
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
void list_insert_next(Slist_link x, Slist_link t)
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
void list_remove_next(Slist_link x)
{
	auto t = x->next;
	x->next = t->next;
}

template <typename T>
struct Slist_node : public Slist_node_base {
    T value;
};

template <typename T>
struct Slist : public Slist_base {
};

template <typename T>
Slist_node<T> *list_new_node(const T &val)
{
    auto x = new Slist_node<T>;
    x->value = val;
    return x;
}

template <typename T>
void list_free_node(Slist_node<T> *x)
{
    delete x;
}

// 在链表头插入结点
template <typename T>
void list_insert_front(Slist<T> &list, Slist_node<T> *x)
{
    list_insert_next(&list.head, x);
}

// 在链表头删除结点
template <typename T>
Slist_node<T> *list_remove_front(Slist<T> &list)
{
    auto x = list.head.next;
    list_remove_next(&list.head);
    return static_cast<Slist_node<T> *>(x);
}

template <typename T, typename Function>
void list_for_each(Slist<T> &list, Function fn)
{
    for (Slist_link x = list.head.next; x != nullptr; x = x->next)
        fn(static_cast<Slist_node<T> *>(x));
}

template <typename T>
Slist_node<T> *list_search(Slist<T> &list, const T &val)
{
    Slist_link x = list.head.next; 
    while (x != nullptr && static_cast<Slist_node<T> *>(x)->value != val)
        x = x->next;
    return static_cast<Slist_node<T> *>(x); 
}

#endif
