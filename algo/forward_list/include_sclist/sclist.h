#ifndef __sclist_h
#define __sclist_h

#include <memory>

#include "sclist_base.h"
#include "scnode.h"

// single chain list
template <typename T>
struct SCList : public SCList_base {
};

// 遍历list所有结点, Function处理element
template <typename T, typename Function>
void list_for_each(SCList<T> &list, Function fn)
{
    for (SCLink x = list_head(list); x != NULL; x = x->next)
        fn(get_element<T>(x));
}

// 查找list中等于指定element值的结点
template <typename T>
SCNode<T> *list_search(SCList<T> &list, const T &element)
{
    SCLink x = list_head(list);
    while (x != NULL && get_element<T>(x) != element)
        x = x->next;
    return static_pointer_cast<T>(x); 
}

// 删除list中值为element的结点
template <typename T>
SCNode<T> *list_delete(SCList<T> &list, const T &element)
{
    SCLink y = NULL;
    SCLink x = list_head(list);
    while (x != NULL && get_element<T>(x) != element) {
        y = x;
        x = x->next;
    }

    if (x == NULL) {    // nofound
        return NULL;
    }

    if (y == NULL) {    // x is head node
        list_delete_head(list);
    } else {
        delete_next(y);
    }

    return static_pointer_cast<T>(x); 
}

// 释放list所有结点, Function操作SCNode<T> *
template <typename T, typename Deleter = std::default_delete<SCNode<T>>>
void list_clear(SCList<T> &list, Deleter del = Deleter())
{
    SCLink y = NULL;
    SCLink x = list_head(list);
    while (x != NULL) {
        y = x;
        x = x->next;
        del(static_pointer_cast<T>(y));
    }

    list_init(list);
}

#endif
