#include <string>
#include <vector>
#include <iostream>
#include "bstree.h"

using namespace std;

template <typename T>
void print_node_info(const BSTree_node<T> *node) 
{
    cout << "node(" << (void *) node << "): value[" << node->value << "]";

    cout << ", ";
    cout << "left[";
    if (node->left)
        cout << static_cast<const BSTree_node<T> *>(node->left)->value;
    else
        cout << "NIL";
    cout << "]";

    cout << ", ";
    cout << "right[";
    if (node->right)
        cout << static_cast<const BSTree_node<T> *>(node->right)->value;
    else
        cout << "NIL";
    cout << "]";

    cout << ", ";
    cout << "parent[";
    if (node->parent)
        cout << static_cast<const BSTree_node<T> *>(node->parent)->value;
    else
        cout << "NIL";
    cout << "]";

    cout << endl;
}

template <typename T>
void print_node_info_aux(const BSTree_link link) 
{
    print_node_info<T>(static_cast<BSTree_node<T> *>(link));
}

template <typename T>
void print_tree_inorder(BSTree<T> &tree) 
{
    cout << "============================================================================\n";
    cout << "tree: \n";
    if (tree.root) {
        cout << "root ";
        print_node_info_aux<T>(tree.root);
    }
    tree_inorder_walk(tree, &print_node_info_aux<T>);
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
