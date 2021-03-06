#include "dclist.h"
#include <cassert>
#include <iostream>
#include <string>
#include <initializer_list>

#define NAME(list) #list

using namespace dclist;

template <typename T>
void insert_inorder(DCList<T> &list, std::initializer_list<T> il, const std::string &list_name="list")
{
    std::cout << "insert inorder " << list_name << ": ";
    for (auto &val : il) {
        std::cout << val << ", ";
        list_insert_back(list, new_node(val));
    }
    std::cout << std::endl;
}

template <typename T>
void insert_reverse(DCList<T> &list, std::initializer_list<T> il, const std::string &list_name="list")
{
    std::cout << "insert reverse " << list_name << ": ";
    for (auto &val : il) {
        std::cout << val << ", ";
        list_insert_front(list, new_node(val));
    }
    std::cout << std::endl;
}

template <typename T>
void delete_inorder(DCList<T> &list, const std::string &list_name="list")
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
void delete_reverse(DCList<T> &list, const std::string &list_name="list")
{
    std::cout << "free reverse " << list_name << ": ";
    while (!list_is_empty(list)) {
        auto node = list_link_cast<T>(list_delete_back(list));
        std::cout << node->value << ", ";
        free_node(node);
    }
    std::cout << std::endl;
}

template <typename T>
void print(DCList<T> &list, const std::string &beg="", const std::string &end="")
{
    std::cout << beg;
    list_for_each(list, [](DCList_link x) { std::cout << list_link_cast<T>(x)->value << ", "; });
    std::cout << end;
}

template <typename T>
void print_list(DCList<T> &list, const std::string &list_name="list")
{
    if (list_is_empty(list)) {
        std::cout << list_name << " is empty!";
    } else {
        print(list, list_name+": [", "]");
    }
    std::cout << std::endl;
}

template <typename T>
bool test_replace(DCList<T> &list, T val, T new_val, const std::string &list_name="list")
{
    auto x = list_search(list, val);
    if (x == &list.nil) {
        std::cout << "not found " << val << " in " << list_name << "!" << std::endl;
        return false;
    }

    std::cout << "found " << val << " in " 
        << list_name << "!" << std::endl;
    std::cout << "replace " << val << " with " << new_val << std::endl;
    auto t = new_node(new_val);
    list_insert(x, t);
    list_delete(x);
    free_node(x);
    print(list, "after replace, "+list_name+": [", "]");
    std::cout << std::endl;
    return true;
}

int main(int argc, char *argv[])
{
    typedef DCList<int> List;
    typedef DCList_node<int> Node;

    List list1, list2;
    list_init(list1);
    assert(list_is_empty(list1));
    list_init(list2);
    assert(list_is_empty(list2));

    std::cout << "---------------------------" << std::endl;
    std::cout << "after init" << std::endl;
    print_list(list1, NAME(list1));
    print_list(list2, NAME(list2));

    std::cout << "---------------------------" << std::endl;
    std::cout << "test insert" << std::endl;
    insert_inorder(list1, {1, 3, 5, 7, 9});
    assert(!list_is_empty(list1));
    insert_reverse(list2, {0, 2, 4, 6, 8});
    assert(!list_is_empty(list2));

    std::cout << "---------------------------" << std::endl;
    std::cout << "after insert" << std::endl;
    print_list(list1, NAME(list1));
    print_list(list2, NAME(list2));

    std::cout << "---------------------------" << std::endl;
    std::cout << "test replace" << std::endl;
    int val = 3;
    int new_val = 19;
    bool is_found;
    is_found = test_replace(list1, val, new_val, NAME(list1));
    assert(is_found);
    is_found = test_replace(list2, val, new_val, NAME(list2));
    assert(!is_found);

    std::cout << "---------------------------" << std::endl;
    std::cout << "after replace" << std::endl;
    print_list(list1, NAME(list1));
    print_list(list2, NAME(list2));

    for (int i = 1; i <= 2; i++) {
        std::cout << "---------------------------" << std::endl;
        std::cout << "test swap" << std::endl;
        list_swap(list1, list2);

        std::cout << "---------------------------" << std::endl;
        std::cout << "after swap" << std::endl;
        print_list(list1, NAME(list1));
        print_list(list2, NAME(list2));
    }

    std::cout << "---------------------------" << std::endl;
    std::cout << "test delete" << std::endl;
    delete_inorder(list1);
    assert(list_is_empty(list1));
    delete_reverse(list2);
    assert(list_is_empty(list2));

    std::cout << "---------------------------" << std::endl;
    std::cout << "after delete" << std::endl;
    print_list(list1, NAME(list1));
    print_list(list2, NAME(list2));

    return 0;
}
