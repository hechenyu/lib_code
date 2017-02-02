#include <string>
#include <vector>
#include <iostream>
#include "rbtree.h"

using namespace std;
using namespace rbtree;

template <typename T>
void print_node_info(RBTree<T> &tree, RBTree_node<T> *node) 
{
    cout << "node(" << (void *) node << "): value[" << node->value << "]"
        << ", color[" << ((node->color == BLACK) ? "black" : "red") << "]";

    cout << ", ";
    cout << "left[";
    if (node->left == tree_nil(tree))
        cout << "NIL";
    else
        cout << tree_link_cast<T>(node->left)->value;
    cout << "]";

    cout << ", ";
    cout << "right[";
    if (node->right == tree_nil(tree))
        cout << "NIL";
    else
        cout << tree_link_cast<T>(node->right)->value;
    cout << "]";

    cout << ", ";
    cout << "parent[";
    if (node->parent == tree_nil(tree))
        cout << "NIL";
    else
        cout << tree_link_cast<T>(node->parent)->value;
    cout << "]";

    cout << endl;
}

template <typename T>
void print_tree_inorder(RBTree<T> &tree) 
{
    auto print_func = [](RBTree_base &tree, RBTree_link x) {
        print_node_info(*static_cast<RBTree<T> *>(&tree), tree_link_cast<T>(x));
    };

    cout << "============================================================================\n";
    cout << "tree: \n";
    if (tree.root != tree_nil(tree)) {
        cout << "root ";
        print_func(tree, tree.root);
    }
    tree_inorder_walk(tree, print_func);
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
    if (x != tree_nil(tree)) {
        cout << "found it!" << endl;
        tree_delete(tree, x);
        cout << "after delete " << val << " from tree\n";
        print_tree_inorder(tree);
        x = tree_search(tree, val);
        assert(x == tree_nil(tree));
    } else {
        cout << "not found!" << endl;
    }

    return 0;
}
