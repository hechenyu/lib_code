#ifndef __stl_list_h
#define __stl_list_h

#include <stddef.h>
#include <iterator>
#include "dlist.h"

namespace stl {

template <typename T>
class list;

template <typename T>
class list_iterator {
private:
    typedef DList_link link_type;
	typedef DList_node<T> node_type;
	typedef list_iterator<T> this_type;

    // 成员变量
	link_type link_;    

    friend class list<T>;

public:
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

	list_iterator(): link_(nullptr) {}

	explicit list_iterator(link_type link): link_(link) {}

	reference operator *() const 
	{
		return static_cast<node_type *>(link_)->value;
	}

	pointer operator ->() const 
	{
		return &static_cast<node_type *>(link_)->value;
	}

	this_type &operator ++()	// prefix increment
	{
        link_ = link_->next;
		return *this;
	}

	this_type operator ++(int)	// postfix increment
	{
		this_type temp(*this);
        link_ = link_->next;
		return temp;
	}

	this_type &operator --()	// prefix decrement
	{
        link_ = link_->prev;
		return *this;
	}

	this_type operator --(int)	// postfix decrement
	{
		this_type temp(*this);
        link_ = link_->prev;
		return temp;
	}

	bool operator ==(const this_type &other) const
	{
		return (this->link_ == other.link_);
	}

	bool operator !=(const this_type &other) const
	{
		return !(*this == other);
	}
};

template <typename T>
class list {
	typedef DList_link link_type;
	typedef DList_node<T> node_type;
	typedef DList<T> list_type;

    // 成员变量
	list_type list_;

public:
	typedef	T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef list_iterator<T> iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

    // default constructor
    list() { list_init(list_); }

    // 用[first, last)区间元素构造list
	template <typename InputIterator>
	list(InputIterator first, InputIterator last): list()
    {
        assign(first, last);
    }

    // 用ininializer_list构造list
	list(std::initializer_list<value_type> il): list(il.begin(), il.end()) {}

    // copy constructor
	list(const list &x): list(x.begin(), x.end()) {}

    // destructor
	~list()
    {
        destroy();
    }

    // 赋值
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
        for (auto iter = first; iter != last; ++iter) {
            auto new_node = list_new_node(*iter);
            list_insert_back(list_, new_node);
        }
	}

    // 重载=运算符, 
	list &operator =(const list &x)
	{
		if (this == &x)
			return *this;

		assign(x.begin(), x.end());
		return *this;
	}

    // 重载=运算符, 
	list &operator =(std::initializer_list<value_type> il)
	{
		assign(il.begin(), il.end());
		return *this;
	}

    // 头迭代器
	iterator begin()
	{
		return iterator(list_.nil.next);
	}

    // 逾尾迭代器
    iterator end()
    {
        return iterator(&list_.nil);
    }

    // 判断list是否为空
	bool empty() const { return list_is_empty(list_); }

    // 统计list中元素个数
	size_type size() const
	{
        int count = 0;
        auto count_node = [&count](node_type *node) { ++count; };
        list_for_each(list_, count_node);
        return count;
	}

    // 获取list头节点元素值, 如果list为空, 结果为未定义
	reference front()
	{
        auto node = static_cast<node_type *>(list_.nil.next);
		return node->value;
	}

    // 获取list尾节点元素值, 如果list为空, 结果为未定义
	reference back()
	{
        auto node = static_cast<node_type *>(list_.nil.prev);
        return node->value;
	}

    // 在list头插入元素
	void push_front(const value_type &val)
	{
        auto new_node = list_new_node(val);
        list_insert_front(list_, new_node);
	}

    // 在list尾插入元素
	void push_back(const value_type &val)
	{
        auto new_node = list_new_node(val);
        list_insert_back(list_, new_node);
	}

    // 删除list头元素
	void pop_front()
	{
        if (list_is_empty(list_))
            return;

        auto node = list_delete_front(list_);
        list_free_node(node);
	}

    // 删除list尾节点
	void pop_back()
	{
        if (list_is_empty(list_))
            return;

        auto node = list_delete_back(list_);
        list_free_node(node);
	}

    // 在position前插入值为val的元素, 返回指向第一个被插入元素的迭代器
	iterator insert(iterator position, const value_type &val)
	{
        auto new_node = list_new_node(val);
        list_insert(position.link_, new_node);

		return iterator(new_node);
	}

    // 在position前插入[first, last)个元素, 返回指向第一个被插入元素的迭代器
	template <typename InputIterator>
	iterator insert(iterator position, 
            InputIterator first, InputIterator last)
	{
		auto keep = &list_.nil;
		for (auto iter = first; iter != last; ++iter) {
			auto node = list_new_node(*iter);
			if (iter == first) {
				keep = node;
			}
			list_insert(position.link_, node);
		}
		return iterator(keep);
	}

    // 删除position指向的元素节点, 返回被删除节点的下一个节点位置
	iterator erase(iterator position)
	{
        auto node = static_cast<node_type *>(position.link_);
		auto keep = node->next;
		list_delete(node);
        list_free_node(node);
		return iterator(keep);
	}

    // 删除[first, last)个元素, 返回指向最后一个被删除元素的下一个位置
	iterator erase(iterator first, iterator last)
	{
        auto iter = first;
        while (iter != last) {
            auto node = static_cast<node_type *>(iter.link_);
            ++iter;
            list_delete(node);
            list_free_node(node);
        }
		return last;
	}

    // 清除list中的所有元素
	void clear()
	{
        destroy();
	}

    // 交换两个list的元素
	void swap(list &x)
	{
        list_swap(this->list_, x.list_);
	}

private:
    // 销毁list中所有节点, 使list变成一个空list
    void destroy()
    {
        while (!list_is_empty(list_)) {
            auto node = list_delete_front(list_);
            list_free_node(node);
        }
    }
};

}   // namespace stl

#endif
