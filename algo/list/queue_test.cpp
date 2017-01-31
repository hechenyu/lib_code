#include "dclist.h"
#include <string>
#include <iostream>

using namespace std;

// 在堆上动态分配一个节点
template <typename T>
DCList_node<T> *list_new_node(const T &val)
{
    auto x = new DCList_node<T>;
    x->value = val;
    return x;
}

// 将一个节点释放回堆
template <typename T>
void list_free_node(DCList_node<T> *x)
{
    delete x;
}

int main(int argc, char *argv[])
{
    DCList<string> list;
    list_init(list);

    // push back
    for (int i = 1; i < argc; i++) {
        list_insert_back(list, list_new_node(string(argv[i]));
        cout << argv[i] << " ";
    }
    cout << endl;

    // pop front
    while (!list_is_empty(list)) {
        auto node = list_link_cast<string>(list_delete_front(list));
        cout << node->value << " ";
        list_free_node(node);
    }
    cout << endl;

    return 0;
}

