#ifndef __rbtree_h
#define __rbtree_h

#include <stddef.h>
#include <assert.h>

typedef struct RBTree_node_base *RBTree_link;

namespace rbtree {

// 红黑树结点颜色
enum node_color {
    RED,
    BLACK
};

}   // namespace rbtree

// 红黑树结点, 包含指向父结点的指针,
// 以及指向左右子结点的指针,
// 以及颜色属性
// 不包含数据
struct RBTree_node_base {
    RBTree_link left;   // 指向左孩子的指针
    RBTree_link right;  // 指向右孩子的指针
    RBTree_link parent; // 指向父结点的指针
    int         color;  // 结点颜色
};

// 红黑树为满足如下性质的二叉搜索树:
// 1)每个结点或是红色的, 或是黑色的;
// 2)根结点是黑色的;
// 3)每个叶结点(NIL)是黑色的;
// 4)如果一个结点是红色的, 则它的两个子结点都是黑色的,
//   (任何路径上不存在连续的红色结点);
// 5)对每个结点, 从该结点到其所有后代叶结点的简单路径上,
//   均包含相同数目的黑色结点.
struct RBTree_base {
    RBTree_link      root;  // 指向根结点的指针
    RBTree_node_base nil;   // 哨兵结点
};

// 初始化红黑树
inline
void tree_init(RBTree_base &tree)
{
    using rbtree::RED;
    using rbtree::BLACK;

    tree.nil.parent = tree.nil.left = tree.nil.right = &tree.nil;
    tree.nil.color = BLACK;
    tree.root = &tree.nil;
}

// 判断红黑树是否为空,
inline
bool tree_is_empty(const RBTree_base &tree)
{
    return (tree.root == &tree.nil);
}

// 返回红黑色的NIL结点
inline
RBTree_link tree_nil(RBTree_base &tree)
{
    return &tree.nil;
}

// 返回以结点x为根的子树的最小元素的指针,
inline
RBTree_link tree_minimum(RBTree_base &tree, RBTree_link x)
{
    while (x->left != &tree.nil)
        x = x->left;
    return x;
}

// 返回以结点x为根的子树的最大元素的指针,
inline
RBTree_link tree_maximum(RBTree_base &tree, RBTree_link x)
{
    while (x->right != &tree.nil)
        x = x->right;
    return x;
}

/**
 * 左旋指定结点x:
 * 当在某个结点x上做左旋时, 假设它的右孩子为y而不是NIL结点;
 * 左旋以x到y的链为“支轴”进行; 
 * 它使y成为该子树新的根结点, x成为y的左孩子, y的左孩子成为x的右孩子;
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

    // 取x的右孩子为y结点, 并将y的左孩子成为x的右孩子;
    auto y = x->right;
    x->right = y->left;
    if (y->left != &tree.nil)
        y->left->parent = x;

    // 将y成为该子树新的根结点
    y->parent = x->parent;
    if (x->parent == &tree.nil)     // x为整棵树根结点
        tree.root = y;
    else if (x == x->parent->left)  // x为父结点的左孩子
        x->parent->left = y;
    else                            // x为父结点的右孩子
        x->parent->right = y;

    // 将x成为y的左孩子
    y->left = x;
    x->parent = y;
}

/**
 * 右旋指定结点y:
 * 同左旋镜像
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

    // 取y的左孩子为x结点, 并将x的右孩子成为y的左孩子;
    auto x = y->left;
    y->left = x->right;
    if (x->right != &tree.nil)
        x->right->parent = y;

    // 将x成为该子树新的根结点
    x->parent = y->parent;
    if (y->parent == &tree.nil)     // y为整棵树根结点
        tree.root = x;
    else if (x == x->parent->left)  // y为父结点的左孩子
        x->parent->left = y;
    else                            // y为父结点的右孩子
        x->parent->right = y;

    // 将y成为x的右孩子
    x->right = y;
    y->parent = x;
}

/**
 * 插入结点后, 对结点重新着色并旋转, 以保持红黑性质
 * ------------------------------------------------
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
 *            |                            |                         |
 *           [C]                          [C]                       [B]
 *        __/   \__                    __/   \__                 __/   \__
 *       /         \    ======>       /         \    ======>    /         \
 *     (A)          d y             (B)          d y         z(A)         (C)
 *    /   \                        /   \                     /   \       /   \
 *   a    (B)z                  z(A)    c                   a     b     r     d
 *       /   \                  /   \
 *      b     c                a     b                         
 *         情况2                       情况3
 *
 */
inline
void tree_insert_fixup(RBTree_base &tree, RBTree_link z) 
{
    using rbtree::RED;
    using rbtree::BLACK;

    assert(z->color == RED);

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {         // z为父结点的左孩子
            auto y = z->parent->parent->right;              // y为z的叔结点
            if (y->color == RED) {
                z->parent->color = BLACK;                   // 情况1
                y->color = BLACK;                           // 情况1
                z->parent->parent->color = RED;             // 情况1
                z = z->parent->parent;                      // 情况1
            } else { 
                if (z == z->parent->right) {
                    z = z->parent;                          // 情况2
                    tree_left_rotate(tree, z);              // 情况2
                }
                z->parent->color = BLACK;                   // 情况3
                z->parent->parent->color = RED;             // 情况3
                tree_right_rotate(tree, z->parent->parent); // 情况3
            }
        } else {                                            // z的父结点为右孩子
            auto y = z->parent->parent->left;               // y为z的叔结点
            if (y->color == RED) {
                z->parent->color = BLACK;                   // 情况1
                y->color = BLACK;                           // 情况1
                z->parent->parent->color = RED;             // 情况1
                z = z->parent->parent;                      // 情况1
            } else {
                if (z == z->parent->left) {
                    z = z->parent;                          // 情况2
                    tree_right_rotate(tree, z);             // 情况2
                }
                z->parent->color = BLACK;                   // 情况3
                z->parent->parent->color = RED;             // 情况3
                tree_left_rotate(tree, z->parent->parent);  // 情况3
            }
        }
    }
    tree.root->color = BLACK;
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
void tree_transplant(RBTree_base &tree, RBTree_link u, RBTree_link v)
{
	if (u->parent == &tree.nil) {       // u为树的根结点
		tree.root = v;
	} else if (u == u->parent->left) {  // u为父结点的左子树
		u->parent->left = v;
	} else {                            // u为父结点的右子树
		u->parent->right = v;
	}

	v->parent = u->parent;
}

/**
 * 在删除结点后, 恢复搜索树的红黑性质:
 * 将额外的黑色沿树上移, 直到:
 * 1.x指向红黑结点, 此时将x着为(单个)黑色,
 * 2.x指向根结点, 此时可以简单地“移除”额外的黑色,
 * 3.执行适当的旋转和重新着色;
 * ----------------------------------
 * () -> 红色结点 
 * [] -> 黑色结点
 * {} -> 双重黑色结点
 * ?? -> 不确定颜色结点
 *
 * 情况1: x的兄弟结点w是红色的
 * 
 *              |                                |
 *             [B]                              [D]
 *          __/   \__                        __/   \__
 *         /         \        =====>        /         \
 *     x{A}           (D)w               (B)           [E]
 *     /   \         /   \              /   \         /   \
 *    a     b     [C]     [E]       x{A}new w[C]     e     f   
 *                / \     / \        / \     / \
 *               c   d   e   f      a   b   c   d   
 *
 * 情况2: x的兄弟结点w是黑色的, 而且w的两个子结点都是黑色的
 *
 *              |                             |             
 *             ?B?c                     new x?B?c
 *          __/   \__                     __/   \__         
 *         /         \        =====>     /         \
 *     x{A}           [D]w            [A]           (D)
 *     /   \         /   \           /   \         /   \
 *    a     b     [C]     [E]       a     b     [C]     [E] 
 *                / \     / \                   / \     / \
 *               c   d   e   f                 c   d   e   f
 *                                                        
 * 情况3: x的兄弟节点是黑色的, w的左孩子是红色的, w的右孩子是黑色的
 *
 *              |                             |
 *             ?B?c                          ?B?c
 *          __/   \__                     __/   \__
 *         /         \        =====>     /         \
 *     x{A}           [D]w           x{A}           [C]new w 
 *     /   \         /   \           /   \         /   \
 *    a     b     (C)     [E]       a     b       c    (D)
 *                / \     / \                         /   \
 *               c   d   e   f                       d     [E]
 *                                                         / \
 *                                                        e   f
 *
 * 情况4: x的兄弟结点w是黑色的, 且w的右孩子是红色的
 *
 *              |                                |
 *             ?B?c                             ?D?c
 *          __/   \__                        __/   \__
 *         /         \        =====>        /         \
 *     x{A}           [D]w               [B]           [E]
 *     /   \         /   \              /   \          / \
 *    a     b     ?C?c'   (E)        [A]     ?C?c'    e   f
 *                / \     / \        / \     / \
 *               c   d   e   f      a   b   c   d 
 *                                                new x = tree.root
 *
 */
inline
void tree_delete_fixup(RBTree_base &tree, RBTree_link x)
{
    using rbtree::RED;
    using rbtree::BLACK;

    while (x != tree.root && x->color == BLACK) {
        if (x == x->parent->left) {                 // x为父结点的左孩子
            auto w = x->parent->right;              // w为x的兄弟结点
            if (w->color == RED) {
                w->color = BLACK;                   // 情况1
                x->parent->color = RED;             // 情况1
                tree_left_rotate(tree, x->parent);  // 情况1
                w = x->parent->right;               // 情况1
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                     // 情况2
                x = x->parent;                      // 情况2
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;         // 情况3
                    w->color = RED;                 // 情况3
                    tree_right_rotate(tree, w);     // 情况3
                    w = x->parent->right;           // 情况3
                }
                w->color = x->parent->color;        // 情况4
                x->parent->color = BLACK;           // 情况4
                w->right->color = BLACK;            // 情况4
                tree_left_rotate(tree, x->parent);  // 情况4
                x = tree.root;                      // 情况4
            }
        } else {                                    // x为父结点的右孩子
            auto w = x->parent->left;               // w为x的兄弟结点
            if (w->color == RED) {
                w->color = BLACK;                   // 情况1
                x->parent->color = RED;             // 情况1
                tree_right_rotate(tree, x->parent); // 情况1
                w = x->parent->left;                // 情况1
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                     // 情况2
                x = x->parent;                      // 情况2
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;        // 情况3
                    w->color = RED;                 // 情况3
                    tree_left_rotate(tree, w);      // 情况3
                    w = x->parent->left;            // 情况3
                }
                w->color = x->parent->color;        // 情况4
                x->parent->color = BLACK;           // 情况4
                w->left->color = BLACK;             // 情况4
                tree_right_rotate(tree, x->parent); // 情况4
                x = tree.root;                      // 情况4
            }
        }
    }
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
 * PS: 结点x可能引起红黑性质的破坏.
 */
inline
void tree_delete(RBTree_base &tree, RBTree_link z)
{
    using rbtree::RED;
    using rbtree::BLACK;

    auto y = z;
    auto y_original_color = y->color;
    RBTree_link x = NULL;
    if (z->left == &tree.nil) {
        x = z->right;
        tree_transplant(tree, z, z->right);
    } else if (z->right == &tree.nil) {
        x = z->left;
        tree_transplant(tree, z, z->left);
    } else {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {   // x有可能是NIL
            x->parent = y;
        } else {
            tree_transplant(tree, y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
        tree_transplant(tree, z, y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        tree_delete_fixup(tree, x);
}

/**
 * 中序遍历树: 先处理左子树, 然后处理当前结点, 然后处理右子树
 */
template <typename Func>
void tree_inorder_walk(RBTree_base &tree, RBTree_link x, Func func)
{
    if (x != &tree.nil) {
        tree_inorder_walk(tree, x->left, func);
        func(tree, x);
        tree_inorder_walk(tree, x->right, func);
    }
}

template <typename Func>
void tree_inorder_walk(RBTree_base &tree, Func func)
{
    tree_inorder_walk(tree, tree.root, func);
}

template <typename T>
struct RBTree_node : public RBTree_node_base {
    T value;
};

template <typename T>
struct RBTree : public RBTree_base {
};

namespace rbtree {

template <typename T>
RBTree_node<T> *new_node(const T &val)
{
    auto x = new RBTree_node<T>;
    x->value = val;
    return x;
}

template <typename T>
void free_node(RBTree_node<T> *x)
{
    delete x;
}

}   // namespace rbtree

// 将RBTree_link强转成子类指针
template <typename T>
RBTree_node<T> *tree_link_cast(RBTree_link x)
{
    return static_cast<RBTree_node<T> *>(x);
}

/**
 * 向红黑树里插入一个结点z(假设z的value属性已被事先赋值):
 * 插入结点z的位置搜索方式同二叉搜索树,
 * 插入结点z后, z的颜色被设置为红色, 
 * 所以有可能破环性质4, 需要调用tree_insert_fixup调整树结构
 */
template <typename T>
void tree_insert(RBTree<T> &tree, RBTree_node<T> *z) 
{
    using rbtree::RED;
    using rbtree::BLACK;

    auto y = &tree.nil;                                         // y为要插入位置的父结点
    auto x = tree.root;                                         // x遍历树
    while (x != &tree.nil) {
        y = x;
#ifndef NDEBUG
        auto debug = tree_link_cast<T>(x);
        (void) debug;
#endif
        if (z->value < tree_link_cast<T>(x)->value)
            x = x->left;
        else
            x = x->right;
    }

#ifndef NDEBUG
    auto debug = tree_link_cast<T>(y);
    (void) debug;
#endif

    z->parent = y;
    if (y == &tree.nil)                                         // 树为空
        tree.root = z;
    else if (z->value < tree_link_cast<T>(y)->value)// z插入到左子树
        y->left = z;
    else                                                        // z插入到右子树
        y->right =z;
    z->left = z->right = &tree.nil;                             // z的左右子结点均为NIL
    z->color = RED; 
    tree_insert_fixup(tree, z);                                 // 调整树
}

/**
 * 从红黑树中从x为根结点的子树向下查找等于特定值的结点
 * 如果未找到, 返回tree.nil
 * 迭代实现
 */
template <typename T>
RBTree_link tree_iterative_search(RBTree<T> &tree, RBTree_link x, const T &v)
{
	while (x != &tree.nil && v != tree_link_cast<T>(x)->value) {
#ifndef NDEBUG
        auto debug = tree_link_cast<T>(x);
        (void) debug;
#endif
        if (v < tree_link_cast<T>(x)->value) {
            x = x->left;
        } else {
            x = x->right;
        }
	}
	return x;
}

template <typename T>
RBTree_link tree_iterative_search(RBTree<T> &tree, const T &v)
{
    return tree_iterative_search(tree, tree.root, v);
}

/**
 * 从红黑树中从x为根结点的子树向下查找等于特定值的结点
 * 如果未找到, 返回tree.nil
 * 递归实现
 */
template <typename T>
RBTree_link tree_search(RBTree<T> &tree, RBTree_link x, const T &v)
{
#ifndef NDEBUG
    auto debug = tree_link_cast<T>(x);
    (void) debug;
#endif

    if (x == &tree.nil || v == tree_link_cast<T>(x)->value) 
        return x;

    if (v < tree_link_cast<T>(x)->value)
        return tree_search(tree, x->left, v);
    else
        return tree_search(tree, x->right, v);
}

template <typename T>
RBTree_link tree_search(RBTree<T> &tree, const T &v)
{
    return tree_search(tree, tree.root, v);
}

#endif

