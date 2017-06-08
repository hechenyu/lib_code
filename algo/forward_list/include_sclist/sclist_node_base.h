#ifndef __sclist_node_base_h
#define __sclist_node_base_h

#include <stddef.h>
#include <assert.h>

// Single Chain List Node
// 单向链表结点
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
 * 在链表的x结点后插入t结点
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
SCList_link list_insert_next(SCList_link x, SCList_link t)
{
    assert(x != NULL && t != NULL);

	t->next = x->next;
	x->next = t;
    return t;
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
SCList_link list_delete_next(SCList_link x)
{
    assert(x != NULL && x->next != NULL);

	SCList_link t = x->next;
	x->next = t->next;
    return t;
}

/**
 * 将y结点后的结点移动到x结点后(x, y可以在同一个链表或不同链表上)
 * [head] -> [N1] -> [N2] -> [N3] -> ... -> [Nk-1] -> [Nk] -> [Nk+1] -> ... -> [NIL]
 *                    ^-x                      ^-y      ^-t
 *                               ||
 *                               \/
 *
 * [head] -> [N1] -> [N2] -> [Nk] -> [N3] -> ... -> [Nk-1] -> [Nk+1] -> ... -> [NIL]
 *                    ^-x      ^-t                     ^-y
 */
inline
SCList_link list_transfer_next(SCList_link x, SCList_link y)
{
    assert(x != NULL && y != NULL);

    auto t = list_delete_next(y);   // 从y结点后移除一个结点t
    return list_insert_next(x, t);         // 将t结点插入到x结点后
}


/**
 * 将y结点之后和z结点之前的结点插入到x结点后, 调用者必须保证(y, z)为有效区间
 * [head] -> [N1] -> [N2] -> [N3] -> ... -> [NIL]
 *                    ^-x
 *
 * [head] -> [M1] -> [M2] -> [M3] -> ... -> [Mk-1] -> [Mk] -> [Mk+1] -> ... -> [NIL]
 *                    ^-y     ^^              ^^        ^-z
 *                                     ||
 *                                     \/
 *
 * [head] -> [N1] -> [N2] -> [M3] -> ... -> [Mk-1] -> [N3] -> ... -> [NIL]
 *                    ^-x     ^^              ^^
 *
 * [head] -> [M1] -> [M2] -> [Mk] -> [Mk+1] -> ... -> [NIL]
 *                    ^-y     ^-z
 */
inline
SCList_link list_transfer_next(SCList_link x, SCList_link y, SCList_link z)
{
    assert(x != NULL && y != NULL);

    while (y->next != z) {
        x = list_transfer_next(x, y);
    }
    return x;
}

/**
 * 将链表上x结点后面的所有结点反序排列
 *
 * [head] -> [N1] -> [N2] -> [N3] -> [N4] -> [NIL]
 *    ^-x      ^-y
 *                ||  list_transfer_next(x, y)
 *                \/
 *
 * [head] -> [N2] -> [N1] -> [N3] -> [N4] -> [NIL]
 *    ^-x             ^-y
 *                ||  list_transfer_next(x, y)
 *                \/
 *
 * [head] -> [N3] -> [N2] -> [N1] -> [N4] -> [NIL]
 *    ^-x                     ^-y
 *                ||  list_transfer_next(x, y)
 *                \/
 *
 * [head] -> [N4] -> [N3] -> [N2] -> [N1] -> [NIL]
 *    ^-x                              ^-y
 */
inline
void list_reverse_next(SCList_link x)
{
    assert(x != NULL && x->next != NULL);

    SCList_link y = x->next;
    while (y->next != NULL) {
        list_transfer_next(x, y);
    }
}

// 从链表的x结点开始, 找到链表的尾结点
inline
SCList_link list_tail(SCList_link x)
{
    assert(x != NULL);

    while (x->next != NULL) {
        x = x->next;
    }

    return x;
}

#endif
