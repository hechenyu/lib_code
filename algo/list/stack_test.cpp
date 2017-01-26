#include "sclist.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    SCList<string> stack;
    list_init(stack);

    for (int i = 1; i < argc; i++) {
        auto item = list_new_node(string(argv[i]));
        list_insert_front(stack, item);
    }

    while (!list_is_empty(stack)) {
        auto item = list_link_cast<string>(list_head(stack));
        cout << item->value << " ";
        list_delete_front(stack);
        list_free_node(item);
    }
    
    cout << endl;

    return 0;
}
