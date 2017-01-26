#include "dclist.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    DCList<string> queue;
    list_init(queue);

    for (int i = 1; i < argc; i++) {
        auto item = list_new_node(string(argv[i]));
        list_insert_back(queue, item);
    }

    while (!list_is_empty(queue)) {
        auto item = list_link_cast<string>(list_head(queue));
        cout << item->value << " ";
        list_delete_front(queue);
        list_free_node(item);
    }
    
    cout << endl;

    return 0;
}

