#ifndef __sclist_base_h
#define __sclist_base_h

#include "sclist_node_base.h"

/**
 * 单链表: 有哑元头结点, 尾结点的next为空
 *
 * [head] -> [N1] -> [N2] -> ... -> NIL
 *
 */
struct SCList_base {
    SCList_node_base head;  // 哑元头结点
};

/**
 * 初始化链表
 *
 * [head] -> NIL
 *
 */
inline
void list_init(SCList_base *list)
{
    list->head.next = NULL;
}

// 判断链表是否为空, 
inline
bool list_is_empty(const SCList_base *list)
{
	return (list->head.next == NULL);
}

// 返回链表哑元头结点的指针
inline
SCList_link list_dummy_head(SCList_base *list)
{
    return &(list->head);
}

// 返回链表头部第一个结点(非哑元头结点)的指针
inline
SCList_link list_head(SCList_base *list)
{
    return list->head.next;
}

// 在链表头部插入结点
inline
void list_insert_head(SCList_base *list, SCList_link x)
{
    list_insert_next(list_dummy_head(list), x);
}

// 在链表头部删除结点
inline
SCList_link list_delete_head(SCList_base *list)
{
    assert(!list_is_empty(list));
    return list_delete_next(list_dummy_head(list));
}

// 返回链表中元素个数
inline
int list_size(SCList_base *list)
{
    int n = 0;
    auto x = list_head(list);
    while (x != NULL) {
        x = x->next;
        n++;
    }
    return n;
}

// 将链表结点逆序排列
inline
void list_reverse(SCList_base *list)
{
    list_reverse_next(list_dummy_head(list));
}

// 将整个链表的结点插入到x结点后面
inline
void list_transfer_next(SCList_link x, SCList_base *list)
{
    list_transfer_next(x, list_dummy_head(list), NULL);
}

#endif
