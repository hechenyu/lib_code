
template <typename T>
class list_iterator {
private:
    typedef Dlist_link link_type;
	typedef Dlist_node<T> node_type;
	typedef list_iterator<T> this_type;

    // 成员变量
	link_type link_;    

public:
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef ptrdiff_t difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

	list_iterator(): link_(nullptr) {}

	explicit list_iterator(link_type *link): link_(link) {}

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
	typedef Dlist_link link_type;
	typedef Dlist_node<T> node_type;
	typedef Dlist<T> list_type;

    // 成员变量
	list_type list_;

public:
	typedef	T value_type;
	typedef Alloc allocator_type;
	typedef T value_type;
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
        for (auto iter = first; iter != last; ++iter) {
            auto new_node = list_new_node(*iter);
            list_insert_back(list_, new_node);
        }
    }

    // copy constructor
	list(const list &x): list(x.begin(), x.end()) {}

    // destructor
	~list()
    {
        auto link = list_.nil.next;
        auto nil = &list_.nil;
        while (link != nil) {
            auto node = static_cast<Dlist_node<T> *>(link);
            link = link->next;    // 先获取下一个节点, 再释放当前节点
            list_free_node(node);
        }
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
	bool empty() const { return list_is_empty(&lst_); }

    // 统计list中元素个数
	size_type size() const
	{
        int count = 0;
        auto count_node = [&count](node_type *node) { ++count; };
        list_for_each(list_, count_node);
	}
};
