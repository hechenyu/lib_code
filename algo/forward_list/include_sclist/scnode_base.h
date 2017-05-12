#ifndef __scnode_base_h
#define __scnode_base_h

#include <stddef.h>
#include <assert.h>

// Single Chain Node
// 单链结点
typedef struct SCNode_base *SCLink;

/**
 * 单向链表节点基类
 *    ___     
 *   |   |------>
 *   |___| next  
 * 
 */
struct SCNode_base {
    SCLink next;
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
void insert_next(SCLink x, SCLink t)
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
SCLink delete_next(SCLink x)
{
    assert(x != NULL);

    if (x->next == NULL) return NULL;

	SCLink t = x->next;
	x->next = t->next;
    return t;
}

#endif
