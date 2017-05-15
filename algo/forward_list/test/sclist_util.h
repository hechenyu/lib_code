#ifndef __sclist_init_h
#define __sclist_init_h

#include <iostream>
#include "sclist.h"

template<typename T>
std::ostream& operator<<(std::ostream& s, const SCList<T>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    auto print_data = [&](const T &e) {
        s << comma << e;
        comma[0] = ',';
    };

    list_for_each(const_cast<SCList<T> *>(&v), print_data);
    return s << ']';
}

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
