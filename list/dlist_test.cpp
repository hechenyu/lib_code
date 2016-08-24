#include <string>
#include <iostream>
#include "dlist.h"

using namespace std;

int main(int argc, char *argv[])
{
    typedef Dlist<string> List;
    typedef Dlist_node<string> Node;

    List list;
    list_init(list);
    for (int i = 1; i < argc; i++) {
        if (i % 2) 
            list_insert_front(list, list_new_node(string(argv[i])));
        else
            list_insert_back(list, list_new_node(string(argv[i])));
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
    if (x != &list.nil) {
        cout << "found it!" << endl;
		auto t = list_new_node(std::string("fake"));
		list_insert(x, t);
		list_remove(x);
    } else {
        cout << "not found!" << endl;
    }

    cout << "free list: ";
	int i = 0;
    while (!list_is_empty(list)) {
		Node *node = nullptr;
		if (i++ % 2) {
			node = list_remove_front(list);
		} else {
			node = list_remove_back(list);
		}
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
