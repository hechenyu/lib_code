#include "dclist.h"
#include <string>
#include <iostream>

using namespace std;
using namespace dclist;

int main(int argc, char *argv[])
{
    DCList<string> list;
    list_init(list);

    // push back
    for (int i = 1; i < argc; i++) {
        list_insert_back(list, new_node(string(argv[i])));
        cout << argv[i] << " ";
    }
    cout << endl;

    // pop front
    while (!list_is_empty(list)) {
        auto node = list_link_cast<string>(list_delete_front(list));
        cout << node->value << " ";
        free_node(node);
    }
    cout << endl;

    return 0;
}

