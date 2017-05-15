#ifndef __sclist_h
#define __sclist_h

#include <memory>
#include <initializer_list>

#include "sclist_base.h"
#include "sclist_node.h"

// single chain list
template <typename T>
struct SCList : public SCList_base {
};


// 遍历list所有结点, Function处理data
template <typename T, typename Function>
void list_for_each(SCList<T> *list, Function fn)
{
    list_for_each(list_node<T>(list_head(list)), fn);
}

// 查找list中data等于指定值的结点
template <typename T>
SCList_node<T> *list_search(SCList<T> *list, const T &val)
{
    return list_search(list_node<T>(list_head(list)), val);
}

template <typename T, typename Predicate>
SCList_node<T> *list_search_if(SCList<T> *list, Predicate pred)
{
    return list_search_if(list_node<T>(list_head(list)), pred);
}

// 删除list中值为val的所有的结点
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
void list_remove(SCList<T> *list, const T &val, Deleter del = Deleter())
{
    SCList_node<T> *x = list_node<T>(list_dummy_head(list));
    while (x != NULL) {
        x = list_remove_next(x, val, del);
    }
}

template <typename T, typename Predicate, typename Deleter = std::default_delete<SCList_node<T>>>
void list_remove_if(SCList<T> *list, Predicate pred, Deleter del = Deleter())
{
    SCList_node<T> *x = list_node<T>(list_dummy_head(list));
    while (x != NULL) {
        x = list_remove_next_if(x, pred, del);
    }
}

// 销毁list
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
void list_destroy(SCList<T> *list, Deleter del = Deleter())
{
    while (!list_is_empty(list)) {
        del(list_node<T>(list_delete_head(list)));
    }
}

// 清空list
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
void list_clear(SCList<T> *list, Deleter del = Deleter())
{
    list_destroy(list, del);
    list_init(list);
}

#endif
