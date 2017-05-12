#ifndef __scnode_h
#define __scnode_h

#include "scnode_base.h"

// single chain list node
template <typename T>
struct SCNode : public SCNode_base {
    T element;  // 数据成员

    SCNode() {} 
    SCNode(const T &element) { this->element = element; } 
};

// 将SCLink强转成SCNode<T> *
template <typename T>
SCNode<T> *static_pointer_cast(SCLink link)
{
    return static_cast<SCNode<T> *>(link);
}

// 获取element数据成员
template <typename T>
T &get_element(SCNode<T> *node)
{
    return node->element;
}

// 获取element数据成员
template <typename T>
T &get_element(SCLink link)
{
    return get_element(static_pointer_cast<T>(link));
}

#endif
