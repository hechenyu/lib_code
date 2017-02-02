#include "sclist.h"
#include <cassert>
#include <iostream>
#include <string>
#include <initializer_list>

#define NAME(list) #list

using namespace sclist;

template <typename T>
void insert_reverse(SCList<T> &list, std::initializer_list<T> il, const std::string &list_name="list")
{
    std::cout << "insert reverse " << list_name << ": ";
    for (auto &val : il) {
        std::cout << val << ", ";
        list_insert_front(list, new_node(val));
    }
    std::cout << std::endl;
}

template <typename T>
void delete_inorder(SCList<T> &list, const std::string &list_name="list")
{
    std::cout << "free inorder " << list_name << ": ";
    while (!list_is_empty(list)) {
        auto node = list_link_cast<T>(list_delete_front(list));
        std::cout << node->value << ", ";
        free_node(node);
    }
    std::cout << std::endl;
}

template <typename T>
void print(SCList<T> &list, const std::string &beg="", const std::string &end="")
{
    std::cout << beg;
    list_for_each(list, [](SCList_link x) { std::cout << list_link_cast<T>(x)->value << ", "; });
    std::cout << end;
}

template <typename T>
void print_list(SCList<T> &list, const std::string &list_name="list")
{
    if (list_is_empty(list)) {
        std::cout << list_name << " is empty!";
    } else {
        print(list, list_name+": [", "]");
    }
    std::cout << std::endl;
}

template <typename T>
bool test_replace(SCList<T> &list, T val, T new_val, const std::string &list_name="list")
{
    auto x = list_search(list, val);
    if (x == NULL) {
        std::cout << "not found " << val << " in " << list_name << "!" << std::endl;
        return false;
    }

    std::cout << "found " << val << " in " 
        << list_name << "!" << std::endl;
    std::cout << "replace " << val << " with " << new_val << std::endl;
    x->value = new_val;
    print(list, "after replace, "+list_name+": [", "]");
    std::cout << std::endl;
    return true;
}

template <typename T>
bool test_remove(SCList<T> &list, T val, const std::string &list_name="list")
{
    auto x = list_delete(list, val);
    if (x == NULL) {
        std::cout << "not found " << val << " in " << list_name << "!" << std::endl;
        return false;
    }

    std::cout << "found " << val << " in " 
        << list_name << "!" << std::endl;
    std::cout << "remove " << val << " from " << list_name << std::endl;
    free_node(x);
    print(list, "after remove, "+list_name+": [", "]");
    std::cout << std::endl;
    return true;
}

int main(int argc, char *argv[])
{
    typedef SCList<int> List;
    typedef SCList_node<int> Node;

    List list;
    list_init(list);
    assert(list_is_empty(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "after init" << std::endl;
    print_list(list, NAME(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "test insert" << std::endl;
    insert_reverse(list, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    assert(!list_is_empty(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "after insert" << std::endl;
    print_list(list, NAME(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "test replace" << std::endl;
    int val = 3;
    int new_val = 19;
    bool is_found;
    is_found = test_replace(list, val, new_val, NAME(list));
    assert(is_found);
    is_found = test_replace(list, val, new_val, NAME(list));
    assert(!is_found);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "after replace" << std::endl;
    print_list(list, NAME(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "test remove" << std::endl;
    {
    int val = 19;
    bool is_found;
    is_found = test_remove(list, val, NAME(list));
    assert(is_found);
    is_found = test_remove(list, val, NAME(list));
    assert(!is_found);
    }

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "after remove" << std::endl;
    print_list(list, NAME(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "test delete" << std::endl;
    delete_inorder(list);
    assert(list_is_empty(list));

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "after delete" << std::endl;
    print_list(list, NAME(list));

    return 0;
}
