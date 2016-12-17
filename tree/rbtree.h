#ifndef __rbtree_h
#define __rbtree_h

#include <stddef.h>

typedef struct RBTree_node_base *RBTree_link;

// 红黑树结点颜色
enum {
    RED,
    BLACK
};

// 红黑树结点, 包含指向父结点的指针,
// 以及指向左右子结点的指针,
// 以及颜色属性
// 不包含数据
struct RBTree_node_base {
    RBTree_link left;   // 指向左子树的指针
    RBTree_link rigth;  // 指向右子树的指针
    RBTree_link parent; // 指向父结点的指针
    int         color;  // 结点颜色
};

// 红黑树为满足如下性质的二叉搜索树:
// 每个结点或是红色的, 或是黑色的;
// 根结点是黑色的;
// 每个叶结点(NIL)是黑色的;
// 如果一个结点是红色的, 则它的两个子结点都是黑色的,
// (任何路径上不存在连续的红色结点);
// 对每个结点, 从该结点到其所有后代叶结点的简单路径上,
// 均包含相同数目的黑色结点.
struct RBTree_base {
    RBTree_link      root;  // 指向根结点的指针
    RBTree_node_base nil;   // 哨兵结点
};

// 初始化红黑树
inline
void tree_init(RBTree_node_base &tree)
{
    tree.nil.parent = tree.nil.left = tree.nil.right = &tree.nil;
    tree.nil.color = BLACK;
    tree.root = &tree.nil;
}

// 判断rbtree是否为空, 
inline
bool tree_is_empty(const RBTree_node_base &tree)
{
    return (tree.root == &tree.nil);
}

// 返回以结点x为根的子树的最小元素的指针,
inline
RBTree_link tree_minimum(RBTree_node_base &tree, RBTree_link x)
{
    while (x->left != &tree.nil)
        x = x->left;
    return x;
}

// 返回以结点x为根的子树的最大元素的指针,
inline
RBTree_link tree_maximum(RBTree_node_base &tree, RBTree_link x)
{
    while (x->right != &tree.nil)
        x = x->right;
    return x;
}

/**
 * 左旋指定结点x,
 * 前置条件: x的右子树不为空, 且根结点的父结点为nil结点
 * 
 *       |              |         
 *       y              x
 *      / \   <=====   / \
 *     x   r          a   y
 *    / \                / \
 *   a   b              b   r      
 */
inline
void tree_left_rotate(RBTree_base &tree, RBTree_link x)
{
    assert(x->right != &tree.nil);
    assert(tree.root->parent == &tree.nil);

    // 将x结点的右子树的左子树, 挂接成为x结点的右子树
    auto y = x->right;
    x->right = y->left;
    if (y->left != &tree.nil)
        y->left->parent = x;

    // 将x结点的原先的右子树挂接到x的父节点下
    y->parent = x->parent;
    if (x->parent == &tree.nil)     // x结点为根结点, (这里用到了根结点的父节点为nil结点的前置条件)
        tree.root = y;
    else if (x == x->parent->left)  // x为父结点的左子树
        x->parent->left = y;
    else                            // x为父结点的右子树
        x->parent->right = y;

    // 将x结点挂接成为原先的右子树结点的左子树
    y->left = x;
    x->parent = y;
}

/**
 * 右旋指定结点y,
 * 前置条件: y的左子树不为空, 且根结点的父结点为nil结点
 * 
 *       |              |         
 *       y              x
 *      / \   =====>   / \
 *     x   r          a   y
 *    / \                / \
 *   a   b              b   r      
 */
inline
void tree_right_rotate(RBTree_base &tree, RBTree_link y)
{
    assert(y->left != &tree.nil);
    assert(tree.root->parent == &tree.nil);

    // 将y结点的左子树的右子树, 挂接成为y结点的左子树
    auto x = y->left;
    y->left = x->right;
    if (x->right != &tree.nil)
        x->right->parent = y;

    // 将y结点的原先的左子树挂接到y的父节点下
    x->parent = y->parent;
    if (y->parent == &tree.nil)     // y结点为根结点, (这里用到了根结点的父节点为nil结点的前置条件)
        tree.root = x;
    else if (x == x->parent->left)  // y为父结点的左子树
        x->parent->left = y;
    else                            // y为父结点的右子树
        x->parent->right = y;

    // 将y结点挂接成为原先的左子树结点的右子树
    x->right = y;
    y->parent = x;
}

/**
 * 对结点重新着色并旋转, 以保持红黑性质
 * ------------------------------------
 * () -> 红色结点 
 * [] -> 黑色结点
 *
 * 情况1: z的叔结点y是红色的
 * a)
 *                |                             |           
 *               [C]                    新结点z(C)
 *            __/   \__                     __/   \__        
 *           /         \      ======>      /         \
 *         (A)         (D)y              [A]         [D]
 *        /   \       /   \             /   \       /   \
 *       a    (B)z   d     e           a    (B)    d     e  
 *           /   \                         /   \
 *          b     c                       b     c
 * b)
 *                 |                             |           
 *                [C]                    新结点z(C)
 *             __/   \__                     __/   \__        
 *            /         \     ======>       /         \
 *          (B)         (D)y              [B]         [D]
 *         /   \       /   \             /   \       /   \
 *      z(A)    c     d     e          (A)    c     d     e
 *      /   \                         /   \
 *     a     b                       a     b
 *
 * 情况2: z的叔结点y是黑色的且z是一个右孩子
 * 情况3: z的叔结点y是黑色的且z是一个左孩子
 *
 *                |                               |                           |
 *               [C]                             [C]                         [B]
 *            __/   \__                       __/   \__                   __/   \__
 *           /         \      ======>        /         \     ======>     /         \
 *         (A)          d y                (B)          d y           z(A)         (C)
 *        /   \                           /   \                       /   \       /   \
 *       a    (B)z                     z(A)    c                     a     b     r     d
 *           /   \                     /   \
 *          b     c                   a     b                          
 *             情况2                          情况3
 *
 */
inline
void tree_insert_fixup(RBTree_base &tree, RBTree_link z) 
{
    while (z->parent->color == RED) {
    }
}


template <typename T>
struct RBTree_node : public RBTree_node_base {
    T value;
};

template <typename T>
struct RBTree : public RBTree_base {
};

// 向红黑树里插入一个结点z(假设z的value属性已被事先赋值)
template <typename T>
void tree_insert(RBTree<T> &tree, RBTree_node<T> *z) 
{
    auto y = &tree.nil;     // y为要插入位置的父结点
    auto x = tree.root;     // x遍历树
    while (x != &tree.nil) {
        y = x;
        if (z.value < static_cast<RBTree_node<T> *>(x).value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == &tree.nil)     // 树为空
        tree.root = z;
    else if (z.value < static_cast<RBTree_node<T> *>(y).value)  // z插入到左子树
        y->left = z;
    else                    // z插入到右子树
        y->right =z;
    z->left = z->right = &tree.nil; // z的左右子树指向nil
    z.color = RED; 
    tree_insert_fixup(tree, z); // 调整树
}

#endif
