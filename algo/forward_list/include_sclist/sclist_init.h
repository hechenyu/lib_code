#ifndef __sclist_init_h
#define __sclist_init_h

#include "sclist.h"

template <typename T>
void list_init(SCList<T> *list)
{
    list_init(static_cast<SCList_base *>(list));
}

template <typename T>
void list_init(SCList<T> *list, std::initializer_list<T> il)
{
    list_init(static_cast<SCList_base *>(list));
    auto x = list_dummy_head(list);
    for (auto &e : il) {
        x = list_insert_next(x, new SCList_node<T>(e));
    }
}

template <typename T>
void list_init(SCList<T> *list, size_t n, const T &val = T())
{
    list_init(static_cast<SCList_base *>(list));
    auto x = list_dummy_head(list);
    for (size_t i = 0; i < n; i++) {
        x = list_insert_next(x, new SCList_node<T>(val));
    }
}

template <typename T, typename InputIterator, 
    typename = typename std::enable_if<!std::is_integral<InputIterator>::value>::type>
void list_init(SCList<T> *list, InputIterator first, InputIterator last)
{
    list_init(static_cast<SCList_base *>(list));
    auto x = list_dummy_head(list);
    while (first != last) {
        x = list_insert_next(x, new SCList_node<T>(*first++));
    }
}

#endif
