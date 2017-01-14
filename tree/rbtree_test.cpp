#include <string>
#include <vector>
#include <iostream>
#include "rbtree.h"

using namespace std;

template <typename T>
void print_node_info(const RBTree<T> &tree, const RBTree_node<T> *node) 
{
    cout << "node(" << (void *) node << "): value[" << node->value << "]"
        << ", color[" << ((node->color == BLACK) ? "black" : "red") << "]";

    cout << ", ";
    cout << "left[";
    if (node->left == &tree.nil)
        cout << "nil";
    else
        cout << static_cast<const RBTree_node<T> *>(node->left)->value;
    cout << "]";

    cout << ", ";
    cout << "right[";
    if (node->right == &tree.nil)
        cout << "nil";
    else
        cout << static_cast<const RBTree_node<T> *>(node->right)->value;
    cout << "]";

    cout << ", ";
    cout << "parent[";
    if (node->parent == &tree.nil)
        cout << "nil";
    else
        cout << static_cast<const RBTree_node<T> *>(node->parent)->value;
    cout << "]";

    cout << endl;
}

template <typename T>
void print_tree_inorder(RBTree<T> &tree) 
{
    cout << "============================================================================\n";
    cout << "tree: \n";
    tree_inorder_walk(tree, &print_node_info<T>);
    cout << "============================================================================\n";
}

int main(int argc, char *argv[])
{
    typedef RBTree<string> RBTree;
    typedef RBTree_node<string> Node;

#ifndef NDEBUG
    vector<Node *> node_list;
#endif

    RBTree tree;
    tree_init(tree);
    for (int i = 1; i < argc; i++) {
        Node *node = tree_new_node(string(argv[i]));
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
    if (x != &tree.nil) {
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
