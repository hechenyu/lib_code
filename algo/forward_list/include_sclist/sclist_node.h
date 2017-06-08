#ifndef __sclist_node_h
#define __sclist_node_h

#include <functional>
#include "sclist_node_base.h"

// single chain list node
template <typename T>
struct SCList_node : public SCList_node_base {
    T data;  // 数据成员

    SCList_node() {} 
    SCList_node(const T &data) { this->data = data; } 
};

// 将SCList_link强转成SCList_node<T> *
template <typename T>
SCList_node<T> *list_node(SCList_link x)
{
    return static_cast<SCList_node<T> *>(x);
}

template <typename T>
SCList_node<T> *list_next(SCList_node<T> *x)
{
    return list_node<T>(x->next);
}

// 获取element数据成员
template <typename T>
T *list_data(SCList_node<T> *x)
{
    return &(x->data);
}

// 遍历list所有结点, Function处理data
template <typename T, typename Function>
void list_for_each(SCList_node<T> *x, Function fn)
{
    for ( ; x != NULL; x = list_next(x)) {
        fn(*list_data(x));
    }
}

// 查找list中data等于指定值的结点
template <typename T>
SCList_node<T> *list_search(SCList_node<T> *x, const T &val)
{
    while (x != NULL && *list_data(x) != val) {
        x = list_next(x);
    }
    return x;
}

template <typename T, typename Predicate>
SCList_node<T> *list_search_if(SCList_node<T> *x, Predicate pred)
{
    while (x != NULL && !pred(*list_data(x))) {
        x = list_next(x);
    }
    return x;
}

// 删除x结点之后第一个值为val的结点, 
// 并返回被删除结点的前一个结点的指针,
// 如果没有满足条件的结点, 返回空指针
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
SCList_node<T> *list_remove_next(SCList_node<T> *x, const T &val, Deleter del = Deleter())
{
    assert(x != NULL);

    SCList_node<T> *y = x;
    x = list_next(x);
    while (x != NULL && *list_data(x) != val) {
        y = x;
        x = list_next(x);
    }

    if (x == NULL) {    // nofound
        return NULL;
    }

    del(list_node<T>(list_delete_next(y)));

    return y;
}

template <typename T, typename Predicate, typename Deleter = std::default_delete<SCList_node<T>>>
SCList_node<T> *list_remove_if_next(SCList_node<T> *x, Predicate pred, Deleter del = Deleter())
{
    assert(x != NULL);

    SCList_node<T> *y = x;
    x = list_next(x);
    while (x != NULL && !pred(*list_data(x))) {
        y = x;
        x = list_next(x);
    }

    if (x == NULL) {    // nofound
        return NULL;
    }

    del(list_node<T>(list_delete_next(y)));

    return y;
}

// 查找x结点之后值最大的结点, 
// 并把该结点从链表中摘除, 并返回该结点的指针,
template <typename T, typename Compare = std::less<T>>
SCList_node<T> *list_delete_max_next(SCList_node<T> *x, Compare comp = Compare())
{
    assert(x != NULL && list_next(x) != NULL);

    SCList_node<T> *max = x;
    x = list_next(x);

    while (list_next(x) != NULL) {
        // max->next->data < x->next->data
        if (comp(*list_data(list_next(max)), *list_data(list_next(x)))) {
            max = x;
        }
        x = list_next(x);
    }

    return list_node<T>(list_delete_next(max));
}

// 对x结点后的链表进行选择排序
//
// [] -> [113] -> [515] -> [101] ->
//  ^-x    ^-max    ^-t
//
// [627] -> [758] -> [838] ->
//   ^-out
//          ||
//          \/
//
// [] -> [113] -> [101] ->
//  ^-x
//
// [515] -> [627] -> [758] -> [838] ->
//   ^-out
//
template <typename T, typename Compare = std::less<T>>
SCList_node<T> *list_selection_next(SCList_node<T> *x, Compare comp = Compare())
{
    SCList_link out = NULL;
    while (x->next != NULL) {
        auto t = list_delete_max_next(x, comp); // t为x后最大元素结点
        t->next = out;                          // 将t插入out的前头
        out = t;                                // out挪到链表头
    }
    x->next = out;

    return x;
}

// 查找x结点和y结点之后值小的结点, 
// 并把该结点从链表中摘除, 并返回该结点的指针,
template <typename T, typename Compare = std::less<T>>
SCList_node<T> *list_delete_min_next(SCList_node<T> *x, SCList_node<T> *y, Compare comp = Compare())
{
    assert(x != NULL && list_next(x) != NULL);
    assert(y != NULL && list_next(y) != NULL);

    if (comp(*list_data(list_next(y)), *list_data(list_next(x)))) {     // y->next->data < x->next->data
        return list_node<T>(list_delete_next(y));
    } 

    return list_node<T>(list_delete_next(x));
}

// 合并x结点和y结点之后的链表, 根据Compare指定的偏序关系
template <typename T, typename Compare = std::less<T>>
SCList_node<T> *list_merge_next(SCList_node<T> *x, SCList_node<T> *y, Compare comp = Compare())
{
    SCList_node_base head = {NULL};   // dummy head node
    SCList_link out = &head;

    while (x->next != NULL && y->next != NULL) {
        auto t = list_delete_min_next(x, y, comp);  // t为x和y后最小元素结点
        out = list_insert_next(out, t);             // 将t插入out的后头, out挪到链表尾
    }

    if (x->next != NULL) {  // y->next == NULL
        assert(out->next == NULL);
        out->next = x->next;
        out = list_tail(out);
    }

    if (y->next != NULL) {  // x->next == NULL
        assert(out->next == NULL);
        out->next = y->next;
    }

    y->next = NULL;
    x->next = head.next;

    return x;
}

// 去除链表中从x结点开始的重复元素, 根据Compare指定的等价关系
template <typename T, typename Compare = std::equal_to<T>, typename Deleter = std::default_delete<SCList_node<T>>>
void list_unique(SCList_node<T> *x, Compare comp = Compare(), Deleter del = Deleter())
{
    if (x == NULL)
        return;

    while (x->next != NULL) {
        if (comp(*list_data(x), *list_data(list_next(x)))) {    // x->data == x->next->data
            del(list_node<T>(list_delete_next(x)));
        } else {
            x = list_next(x);
        }
    }
}

#endif
