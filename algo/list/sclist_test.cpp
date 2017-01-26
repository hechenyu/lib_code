#include "sclist.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    typedef SCList<string> List;
    typedef SCList_node<string> Node;

    List list;
    list_init(list);
    for (int i = 1; i < argc; i++) {
        list_insert_front(list, list_new_node(string(argv[i])));
    }

    if (list_is_empty(list)) {
        cout << "list is empty!" << endl;
    } else {
        cout << "list: [";
        list_for_each(list, [](Node *node) { cout << node->value << ", "; });
        cout << "]" << endl;
    }

    cout << "entry val for search: ";
    string val;
    cin >> val;
    auto x = list_search(list, val);
    if (x != NULL) {
        cout << "found it!" << endl;
		auto y = static_cast<Node *>(x->next);
		if (y != NULL) {
            cout << "delete next node: " << static_cast<Node *>(y)->value << endl;
			list_delete_next(x);
        	list_free_node(y);
		}
        cout << "insert new next node: ";
        cin >> val;
		auto t = list_new_node(val);
		list_insert_next(x, t);
    } else {
        cout << "not found!" << endl;
    }

    cout << "free list: ";
    while (!list_is_empty(list)) {
		auto node = list_delete_front(list);
		cout << node->value << ", ";
        list_free_node(node);
    }
	cout << endl;

    cout << "after free list" << endl;
    if (list_is_empty(list)) {
        cout << "list is empty!" << endl;
    } else {
        cout << "list is not empty!" << endl;
    }

	return 0;
}
