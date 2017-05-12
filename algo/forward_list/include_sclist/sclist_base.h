#ifndef __sclist_base_h
#define __sclist_base_h

#include "scnode_base.h"

/**
 * 单链表: 有哑元头结点, 尾结点的next为空
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *
 */
struct SCList_base {
    SCNode_base head;  // 哑元头结点
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

// 判断链表是否为空, 
inline
bool list_is_empty(const SCList_base &list)
{
	return (list.head.next == NULL);
}

// 返回列表头部第一个结点(非哑头结点)的指针
inline
SCLink list_head(SCList_base &list)
{
    return list.head.next;
}

// 在链表头部插入结点
inline
void list_insert_head(SCList_base &list, SCLink x)
{
    insert_next(&list.head, x);
}

// 在链表头部删除结点
inline
SCLink list_delete_head(SCList_base &list)
{
    assert(!list_is_empty(list));
    return delete_next(&list.head);
}

#endif
