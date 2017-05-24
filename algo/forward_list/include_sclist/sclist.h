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
        x = list_remove_if_next(x, pred, del);
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

// 选择排序list
template <typename T, typename Compare = std::less<T>>
void list_selection(SCList<T> *list, Compare comp = Compare())
{
    list_selection_next(list_node<T>(list_dummy_head(list)), comp);
}

template <typename T, typename Compare = std::less<T>>
void list_sort(SCList<T> *list, Compare comp = Compare())
{
    list_selection(list, comp);
}

// 合并list1和list2, 并且将结果放到list1中
template <typename T, typename Compare = std::less<T>>
void list_merge(SCList<T> *list1, SCList<T> *list2, Compare comp = Compare())
{
    list_merge_next(list_node<T>(list_dummy_head(list1)), list_node<T>(list_dummy_head(list2)), comp);
}

#endif
