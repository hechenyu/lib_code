// -*- C++ -*-
// HeXu's
// 2013 Nov

#ifndef __bstree_h
#define __bstree_h

#include <stddef.h>
#include <assert.h>

typedef struct BSTree_node_base *BSTree_link;

// 二叉搜索树结点, 包含指向父结点的指针,
// 以及指向左右子结点的指针,
// 不包含数据
struct BSTree_node_base {
	BSTree_link parent;
	BSTree_link left;
	BSTree_link right;
} BSTree_node_base;

// 二叉搜索树
struct BSTree_base {
	BSTree_link root;
};

// 初始化二叉搜索树
inline
void tree_init(BSTree_base &tree)
{
	tree.root = NULL;
}

// 判断二叉搜索树是否为空,
inline
bool tree_is_empty(const BSTree_base &tree)
{
	return (tree.root == NULL);
}

// 返回以结点x为根的子树的最小元素的指针,
inline
BSTree_link tree_minimum(BSTree_link x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}

// 返回以结点x为根的子树的最大元素的指针,
inline
BSTree_link tree_maximum(BSTree_link x)
{
	while (x->right != NULL)
		x = x->right;
	return x;
}

// 返回以结点x的后继结点
inline
BSTree_link tree_successor(BSTree_link x)
{
	if (x->right != NULL)
		return tree_minimum(x->right);

	auto y = x->parent;
	while (y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}	
	return y;
}

// 返回以结点x的前驱结点
inline
BSTree_link tree_predecessor(BSTree_link x)
{
	if (x->left != NULL)
		return tree_maximum(x->left);

	auto y = x->parent;
	while (y != NULL && x == y->left) {
		x = y;
		y = y->parent;
	}	
	return y;
}

/**
 * 用另一棵子树替换一棵子树并成为其父结点的孩子结点:
 * 用一个以v为根的子树来替换一棵以u为根的子树时,
 * 结点u的父结点就变为v的父结点, 并且最后v成为u的父结点的相应孩子.
 *
 *         q           
 *         |         |
 *         B u       E v
 *        / \       / \
 *       A   C     D   F
 *
 *              ||
 *              \/
 *         q           
 *         |         |  
 *         E v       B u
 *        / \       / \
 *       D   F     A   C
 *
 */
inline
void tree_transplant(BSTree_base &tree, BSTree_link u, BSTree_link v)
{
	if (u->parent == NULL) {            // u为树的根结点
		tree.root = v;
	} else if (u == u->parent->left) {  // u为父结点的左子树
		u->parent->left = v;
	} else {                            // u为父结点的右子树
		u->parent->right = v;
	}

    if (v != NULL)
        v->parent = u->parent;
}

/**
 * 从一棵二叉搜索树中删除一个结点z, 整个策略分为三种基本情况:
 * 1)如果z没有孩子结点, 那么只是简单的将它删除, 并修改它的父结点, 
 *   用NIL作为孩子来替换z;
 * 2)如果z只有一个孩子, 那么将这个孩子提升到树中z的位置上, 
 *   并修改z的父结点, 用z的孩子还替换z;
 * 3)如果z有两个孩子, 那么找z的后继y(一定在z的右子树中),
 *   并让y占据树中z的位置; z的原来右子树部分成为y的新的右子树,
 *   并且z的左子树成为y的新的左子树.
 *
 * a): 情况1和情况2的一部分(z只有一个右孩子)
 *        q             q
 *        |             |
 *        A z  =====>   B r
 *       / \           / \
 *     NIL  B r
 *         / \
 *
 * b): 情况2的另一部分(z只有一个左孩子)
 *        q             q
 *        |             |
 *        B z  =====>   A l
 *       / \           / \
 *    l A  NIL
 *     / \
 *
 * c): 情况3的一部分(z的后继y正好为z的右孩子)
 *           q                       q
 *           |                       |
 *           B z                     C y
 *        __/ \__     =====>      __/ \__
 *       /       \               /       \
 *    l A         C y         l A         D x
 *    /   \     /   \         /   \     /   \
 *            NIL    D x
 *                  / \
 *
 * d): 情况3的另一部分(z的后继y不是z的右孩子)
 *         q                       q                             q
 *         |                       |                             |
 *         B z                     B z       C y                 C y
 *     __/   \__    ======>    __/         /   \   =====>    __/   \__
 *    /         \             /          NIL    E r         /         \
 * l A           E r       l A                /   \      l A           E r
 * /   \       /   \       /   \           x D           /   \       /   \
 *          y C                             / \                   x D
 *          /   \                                                  / \
 *        NIL  x D                   
 *              / \
 *
 */
inline
void tree_delete(BSTree_base &tree, BSTree_link z)
{
	if (z->left == NULL)
		tree_transplant(tree, z, z->right);     // a)
	else if (z->right == NULL)          
		tree_transplant(tree, z, z->left);      // b)
	else {
		auto y = tree_minimum(z->right);
		if (y->parent != z) {
			tree_transplant(tree, y, y->right); // d)
			y->right = z->right;                // d)
			y->right->parent = y;               // d)
		} 
		tree_transplant(tree, z, y);            // c)
		y->left = z->left;                      // c)
		y->left->parent = y;                    // c)
	}
}

/**
 * 中序遍历树: 先处理左子树, 然后处理当前结点, 然后处理右子树
 */
template <typename Func>
void tree_inorder_walk(BSTree_link x, Func func)
{
    if (x != NULL) {
        tree_inorder_walk(x->left, func);
        func(x);
        tree_inorder_walk(x->right, func);
    }
}

template <typename Func>
void tree_inorder_walk(BSTree_base &tree, Func func)
{
    tree_inorder_walk(tree.root, func);
}

template <typename T>
struct BSTree_node : public BSTree_node_base {
    T value;
};

template <typename T>
struct BSTree : public BSTree_base {
};

template <typename T>
BSTree_node<T> *tree_new_node(const T &val)
{
    auto x = new BSTree_node<T>;
    x->value = val;
    x->left = x->right = NULL;
    return x;
}

template <typename T>
void tree_free_node(BSTree_node<T> *x)
{
    delete x;
}

// 将BSTree_link强转成子类指针
template <typename T>
BSTree_node<T> *tree_link_cast(BSTree_link x)
{
    return static_cast<BSTree_node<T> *>(x);
}

/**
 * 从二叉搜索树中从x为根结点的子树向下查找等于特定值的结点
 * 如果未找到, 返回NULL
 * 迭代实现
 */
template <typename T>
BSTree_link tree_iterative_search(BSTree_link x, const T &v)
{
	while (x != NULL && v != tree_link_cast<T>(x)->value) {
        if (v < tree_link_cast<T>(x)->value) {
            x = x->left;
        } else {
            x = x->right;
        }
	}
	return x;
}

template <typename T>
BSTree_link tree_iterative_search(BSTree<T> &tree, const T &v)
{
    return tree_iterative_search(tree.root, v);
}

/**
 * 从二叉搜索树中从x为根结点的子树向下查找等于特定值的结点
 * 如果未找到, 返回NIL
 * 递归实现
 */
template <typename T>
BSTree_link tree_search(BSTree_link x, const T &v)
{
    while (x == NULL || v == tree_link_cast<T>(x)->value)
        return x;

    if (v < tree_link_cast<T>(x)->value)
        return tree_search(x->left, v);
    else
        return tree_search(x->right, v);
}

template <typename T>
BSTree_link tree_search(BSTree<T> &tree, const T &v)
{
    return tree_search(tree.root, v);
}

// 向二叉搜索树里插入一个结点z(假设z的value属性已被事先赋值), 
// 并且z->left和z->right指向NIL
template <typename T>
void tree_insert(BSTree<T> &tree, BSTree_node<T> *z) 
{
    assert(z->left == NULL && z->right == NULL);

    auto y = (BSTree_link) NULL;    // y为要插入位置的父结点
    auto x = tree.root;             // x遍历树
    while (x != NULL) {
        y = x;
        if (z->value < tree_link_cast<T>(x)->value)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        tree.root = z;              // 树为空
    else if (z->value < tree_link_cast<T>(y)->value)
        y->left = z;
    else
        y->right =z;
}

#endif
