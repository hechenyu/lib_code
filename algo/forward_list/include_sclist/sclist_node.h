#ifndef __sclist_node_h
#define __sclist_node_h

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

// 获取element数据成员
template <typename T>
T *list_data(SCList_node<T> *x)
{
    return &(x->data);
}

// 获取element数据成员
template <typename T>
T *list_data(SCList_link x)
{
    return list_data(list_node<T>(x));
}

// 查找list中data等于指定值的结点
template <typename T>
SCList_node<T> *list_search(SCList_link x, const T &val)
{
    while (x != NULL && *list_data<T>(x) != val) {
        x = x->next;
    }
    return list_node<T>(x); 
}

template <typename T, typename Predicate>
SCList_node<T> *list_search_if(SCList_link x, Predicate pred)
{
    while (x != NULL && !pred(*list_data<T>(x))) {
        x = x->next;
    }
    return list_node<T>(x); 
}

// 删除x结点之后第一个值为val的结点, 
// 并返回被删除结点的前一个结点的指针,
// 如果没有满足条件的结点, 返回空指针
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
SCList_node<T> *list_remove_next(SCList_link x, const T &val, Deleter del = Deleter())
{
    assert(x != NULL);

    SCList_link y = x;
    x = x->next;
    while (x != NULL && *list_data<T>(x) != val) {
        y = x;
        x = x->next;
    }

    if (x == NULL) {    // nofound
        return NULL;
    }

    del(list_node<T>(list_delete_next(y)));

    return list_node<T>(y);
}

template <typename T, typename Predicate, typename Deleter = std::default_delete<SCList_node<T>>>
SCList_node<T> *list_remove_next_if(SCList_link x, Predicate pred, Deleter del = Deleter())
{
    assert(x != NULL);

    SCList_link y = x;
    x = x->next;
    while (x != NULL && !pred(*list_data<T>(x))) {
        y = x;
        x = x->next;
    }

    if (x == NULL) {    // nofound
        return NULL;
    }

    del(list_node<T>(list_delete_next(y)));

    return list_node<T>(y);
}

#endif
