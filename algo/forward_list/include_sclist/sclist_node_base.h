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
    assert(x != NULL);

    if (x->next == NULL) return NULL;   // x is tail of list

	SCList_link t = x->next;
	x->next = t->next;
    return t;
}

/**
 * reverse singly linked list after x
 * [head] -> [N1] -> [N2] -> [N3] -> [N4] -> [NIL]
 *    ^-x      ^-t
 *                ||  list_insert_next(x, t->next)
 *                \/
 *
 * [head] -> [N2] -> [N1] -> [N3] -> [N4] -> [NIL]
 *    ^-x             ^-t
 *                ||  list_insert_next(x, t->next)
 *                \/
 *
 * [head] -> [N3] -> [N2] -> [N1] -> [N4] -> [NIL]
 *    ^-x                     ^-t
 *                ||  list_insert_next(x, t->next)
 *                \/
 *
 * [head] -> [N4] -> [N3] -> [N2] -> [N1] -> [NIL]
 *    ^-x                              ^-t
 */
inline
void list_reverse_next(SCList_link x)
{
    assert(x != NULL);

    if (x->next == NULL) return;    // x is tail of list

    SCList_link t = x->next;
    while (t->next != NULL) {
        list_insert_next(x, list_delete_next(t));
    }
}

#endif
