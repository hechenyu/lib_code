#include <string>
#include <vector>
#include <iostream>
#include "bstree.h"

using namespace std;
using namespace bstree;

template <typename T>
void print_node_info(BSTree_node<T> *node) 
{
    cout << "node(" << (void *) node << "): value[" << node->value << "]";

    cout << ", ";
    cout << "left[";
    if (node->left)
        cout << tree_link_cast<T>(node->left)->value;
    else
        cout << "NIL";
    cout << "]";

    cout << ", ";
    cout << "right[";
    if (node->right)
        cout << tree_link_cast<T>(node->right)->value;
    else
        cout << "NIL";
    cout << "]";

    cout << ", ";
    cout << "parent[";
    if (node->parent)
        cout << tree_link_cast<T>(node->parent)->value;
    else
        cout << "NIL";
    cout << "]";

    cout << endl;
}

template <typename T>
void print_tree_inorder(BSTree<T> &tree) 
{
    auto print_func = [](BSTree_link x) { print_node_info(tree_link_cast<T>(x)); };
    cout << "============================================================================\n";
    cout << "tree: \n";
    if (tree.root) {
        cout << "root ";
        print_func(tree.root);
    }
    tree_inorder_walk(tree, print_func);
    cout << "============================================================================\n";
}

int main(int argc, char *argv[])
{
    typedef BSTree<string> BSTree;
    typedef BSTree_node<string> Node;

#ifndef NDEBUG
    vector<Node *> node_list;
#endif

    BSTree tree;
    tree_init(tree);
    for (int i = 1; i < argc; i++) {
        Node *node = new_node(string(argv[i]));
#ifndef NDEBUG
        node_list.push_back(node);
#endif
        tree_insert(tree, node);
#ifndef NDEBUG
        cout << "============================================================================\n";
        for (auto item: node_list) {
            print_node_info(tree, item);
        }
#endif
    }

    if (tree_is_empty(tree)) {
        cout << "tree is empty!" << endl;
    } else {
        print_tree_inorder(tree);
    }

    cout << "entry val for search: ";
    string val;
    cin >> val;
    auto x = tree_search(tree, val);
    assert(x == tree_iterative_search(tree, val));
    if (x) {
        cout << "found it!" << endl;
        tree_delete(tree, x);
        cout << "after delete " << val << " from tree\n";
        print_tree_inorder(tree);
        x = tree_search(tree, val);
        assert(x == &tree.nil);
    } else {
        cout << "not found!" << endl;
    }

    return 0;
}
