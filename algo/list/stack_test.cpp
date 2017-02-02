#include "sclist.h"
#include <string>
#include <iostream>

using namespace std;
using namespace sclist;

int main(int argc, char *argv[])
{
    SCList<string> list;
    list_init(list);

    // push front
    for (int i = 1; i < argc; i++) {
        list_insert_front(list, new_node(string(argv[i])));
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
