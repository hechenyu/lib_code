#include "stl_list.h"
#include <cassert>
#include <iterator>
#include <iostream>

typedef stl::list<int> list_type;

template <typename T>
void push_back(stl::list<T> &list, std::initializer_list<T> il, const std::string &list_name="list")
{
    std::cout << "push back " << list_name << ": ";
    for (auto &val : il) {
        std::cout << val << ", ";
        list.push_back(val);
    }
    std::cout << std::endl;
}

template <typename T>
void push_front(stl::list<T> &list, std::initializer_list<T> il, const std::string &list_name="list")
{
    std::cout << "push front " << list_name << ": ";
    for (auto &val : il) {
        std::cout << val << ", ";
        list.push_front(val);
    }
    std::cout << std::endl;
}

template <typename T>
void print(stl::list<T> &list, const std::string &beg="", const std::string &end="")
{
    std::cout << beg;
    for (auto &val: list) {
        std::cout << val << ", ";
    }
    std::cout << end;
}

template <typename T>
void print_list(stl::list<T> &list, const std::string &list_name="list")
{
    if (list.empty()) {
        std::cout << list_name << " is empty!";
    } else {
        print(list, list_name+": [", "]");
    }
    std::cout << std::endl;
}

void test_construct()
{
    std::cout << "-------------------------------" << std::endl;
    std::cout << __func__ << std::endl;

    list_type list1;
    list_type list2{1, 2, 3, 4, 5};
    int array[] = {5, 6, 7, 8, 9};
    list_type list3(std::begin(array), std::end(array));
    assert(list1.empty());
    assert(!list2.empty());
    assert(!list3.empty());

    print_list(list1, "list1");
    print_list(list2, "list2");
    print_list(list3, "list3");
}

int main()
{
    test_construct();

    return 0;
}
