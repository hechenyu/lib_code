#include "sclist.h"
#include <string>
#include <iostream>

using namespace std;

template <typename T>
SCList_node<T> *list_new_node(const T &val)
{
    auto x = new SCList_node<T>;
    x->value = val;
    return x;
}

template <typename T>
void list_free_node(SCList_node<T> *x)
{
    delete x;
}

int main(int argc, char *argv[])
{
    SCList<string> list;
    list_init(list);

    // push front
    for (int i = 1; i < argc; i++) {
        list_insert_front(list, list_new_node(string(argv[i]));
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
