#include <string>
#include <iostream>
#include "rbtree.h"

using namespace std;

int main(int argc, char *argv[])
{
    typedef RBTree<string> RBTree;
    typedef RBTree_node<string> Node;

    RBTree tree;
    tree_init(tree);
    for (int i = 1; i < argc; i++) {
        tree_insert(tree, tree_new_node(string(argv[i])));
    }

    if (tree_is_empty(tree)) {
        cout << "tree is empty!" << endl;
    } else {
    }

    cout << "entry val for search: ";
    string val;
    cin >> val;
    auto x = tree_search(tree, val);
    if (x != &tree.nil) {
        cout << "found it!" << endl;
    } else {
        cout << "not found!" << endl;
    }

    return 0;
}
