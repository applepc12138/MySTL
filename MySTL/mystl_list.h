#pragma once
#ifndef STL_LIST
#define STL_LIST

#include "mystl_allocator.h"
#include "mystl_iterator.h"

namespace mystl {

	template <typename T>
	struct list_node{
		list_node<T>* pre;
		list_node<T>* next;
		T data;
		
	};

	template <typename T>
	struct list_iterator {
		 template <typename U, typename Alloc> friend class list;
	private:
		typedef list_iterator<T> self;
		typedef list_node<T> list_node;
		typedef list_node* link_type;

	public:
		typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef typename iterator<bidirectional_iterator_tag, T>::pointer pointer;
		typedef typename iterator<bidirectional_iterator_tag, T>::reference reference;
		typedef typename iterator<bidirectional_iterator_tag, typename std::remove_const<T>::type>::value_type value_type;
		typedef typename iterator<bidirectional_iterator_tag, T>::difference_type difference_type;

		list_iterator() {}
		list_iterator(link_type node) : nodeptr(node) {}
		list_iterator(const list_iterator& iter) : nodeptr(iter.nodeptr) {}

		T& operator*() {
			return nodeptr->data;
		}
		T* operator->() {
			return &(operator*());
		}
		self& operator++() {
			nodeptr = nodeptr->next;
			return *this;
		}
		self operator++(int) {
			auto tmp = *this;
			nodeptr = nodeptr->next;
			return tmp;
		}
		self& operator--() {
			nodeptr = nodeptr->pre;
			return *this;
		}
		self operator--(int) {
			auto tmp = *this;
			nodeptr = nodeptr->pre;
			return tmp;
		}
		bool operator==(const list_iterator& iter) const { return nodeptr == iter.nodeptr; }
		bool operator!=(const list_iterator& iter) const { return nodeptr != iter.nodeptr; }

	private:
		link_type nodeptr;
	};


	template<typename T,typename Alloc>
	bool operator== (const  list<T, Alloc>&x, const list<T, Alloc>&y);
	template<typename T,typename Alloc>
	bool operator< (const  list<T, Alloc>&x, const list<T, Alloc>&y);
	template <typename T, typename Alloc = simple_alloc<list_node<T>, alloc>>
	class list {
		friend bool operator==<T, Alloc> (const list<T, Alloc>& x, const list<T, Alloc>& y);
		friend bool operator< <T, Alloc> (const list<T, Alloc>& x, const list<T, Alloc>& y);
	private:
		typedef Alloc data_allocator;
		typedef list_node<T>* link_type;

	public:
		typedef size_t size_type;
		typedef list_iterator<T> iterator;
		typedef list_iterator<const T> const_iterator;
		typedef typename iterator::difference_type difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;

	private:
		link_type node;//指向尾后节点

	public:
		list() { empty_initialize(); }
		list(const list& l);
		explicit list(size_type n, const value_type& x = value_type());
		template <typename InputIterator>
		list(InputIterator first, InputIterator last);
		~list();

		reference operator=(const list& x);

	public:
		iterator begin() { return node->next; }
		const_iterator begin()const { return (list_node<const T>*)node->next; }//const_iterator中的成员变量类型是list_node<const T>*类型
		iterator end() { return node; }
		const_iterator end()const { return (list_node<const T>*)node; }//const_iterator中的成员变量类型是list_node<const T>*类型
		
		reference front(){ return node->next->data; }
		const_reference front()const { return node->next->data; }
		reference back(){ return node->pre->data; }
		const_reference back()const { return node->pre->data; }
		//reference operator[](size_type i);
		//const_reference operator[](size_type i)const;
			
		void push_front(const value_type& v);
		void push_back(const value_type& v);
		void pop_back() { erase(--(end())); }
		void pop_front() { erase(begin()); }
	
	public:
		iterator insert(iterator position, const value_type& v);
		void insert(iterator position, size_type n, const value_type& v);
		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		void remove(const value_type& v);
		iterator erase(iterator  position);
		iterator erase(iterator  first, iterator last);
		void merge(list& l);
		void splice(iterator position, list& l);
		void splice(iterator posititon, iterator first, iterator last);
		void reverse();
		void sort();
		void unique();


	private:
		//将[first, last)区间放置到position之前
		void transfer(iterator position, iterator first, iterator last);
		//分配一个节点空间
		link_type get_node() {
			return data_allocator::allocate();
		}
		//释放节点空间
		void put_node(link_type p) {
			data_allocator::deallocate(p);
		}
		//分配节点空间并构造节点元素
		link_type create_node(const value_type& x) {
			link_type node = get_node();
			construct(&node->data, x);
			return node;
		}
		//析构节点元素并释放节点空间
		void destory_node(link_type p) {
			destroy(&p->data);
			put_node(p);
		}
		//初始化一个空链表
		void empty_initialize() {
			node = get_node();
			node->next = node;
			node->pre = node;
		}
	public:
		size_type size()const
		{
			size_type n = 0;
			distance(begin(), end(), n);
			return n;
		}
		bool empty()const 
		{
			return node->next == node;
		}
		void clear();

	};

	template <typename T, typename Alloc /*= simple_alloc<list_node<T>, alloc>*/>
	typename list<T, Alloc>::reference mystl::list<T, Alloc>::operator=(const list& x)
	{
		if (this != &x) {
			iterator first1 = begin();
			iterator last1 = end();
			const_iterator first2 = x.begin();
			const_iterator last2 = x.end();
			while (first1 != last1 && first2 != last2) 
				*first1++ = *first2++;//学习了! mark 一下
			if (first2 == last2)
				erase(first1, last1);
			else
				insert(last1, first2, last2);
			
		}
		return *this;
	}

	template<typename T, typename Alloc>
	inline list<T, Alloc>::list(const list & l)
	{
		empty_initialize();
		insert(end(), l.begin(), l.end());
	}
	template<typename T, typename Alloc>
	inline list<T, Alloc>::list(size_type n, const value_type & x)
	{
		empty_initialize();
		insert(end(), n, x);
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	inline list<T, Alloc>::list(InputIterator first, InputIterator last)
	{
		empty_initialize();
		insert(end(), first, last);
	}
	template<typename T, typename Alloc>
	inline list<T, Alloc>::~list()
	{
		clear();
		put_node(node);
		std::cout << "析构函数执行" << endl;
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::push_front(const value_type & v)
	{
		insert(begin(), v);
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::push_back(const value_type & v)
	{
		insert(end(), v);
	}
	template<typename T, typename Alloc>
	inline typename list<T, Alloc>::iterator list<T, Alloc>::insert(iterator position, const value_type & v)
	{
		link_type tmp = create_node(v);
		tmp->next = position.nodeptr;
		tmp->pre = position.nodeptr->pre;
		position.nodeptr->pre->next = tmp;
		position.nodeptr->pre = tmp;
		return tmp;//隐式类型转换
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::insert(iterator position, size_type n, const value_type & v)
	{
		while(n--) 
			insert(position, v);
	}
	template<typename T, typename Alloc>
	template<typename InputIterator>
	inline void list<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
	{
		while (first != last) {
			insert(position, *first);
			++first;
		}
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::remove(const value_type & v)
	{
		auto first = begin(), last = end();
		while (first != last) {
			if (*first == v)
				first = erase(first);
			else
				++first;
		}
	}
	template<typename T, typename Alloc>
	inline typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator position)
	{
		link_type next = position.nodeptr->next;
		next->pre = position.nodeptr->pre;
		position.nodeptr->pre->next = next;
		destory_node(position.nodeptr);
		return iterator(next);//返回删除后下一个迭代器
	}
	template<typename T, typename Alloc>
	inline typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator first, iterator last)
	{
		while (first != last) 
			first = erase(first);
		return first;
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::merge(list & l)//合并两个递增链表
	{
		link_type p = node->next;
		link_type q = l.node->next;
		link_type cur = node;
		while (p != node && q != l.node) {
			if (p->data > q->data) {
				cur->next = q;
				q = q->next;
			}
			else {
				cur->next = p;
				p = p->next;
			}
			cur = cur->next;
		}
		cur->next = node;
		if (q)
			transfer(end(), iterator(q), l.end());
		else
			transfer(end(), iterator(p), end());
		l.node->next = l.node->pre = l.node;
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::splice(iterator position, list & l)
	{
		if(!l.empty())
			transfer(position, l.begin(), l.end());
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::splice(iterator posititon, iterator first, iterator last)
	{
		transfer(posititon, first, last);
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::reverse()
	{
		if ( node == node->next || node == node->next->next )//零或一个元素
			return;
		auto cur = begin();
		++cur;//注意!!!这里必须++cur
		while (cur != end()) {
			auto tmp = cur;
			++cur;
			transfer(begin(), tmp, cur);
		}
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::sort()
	{

	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::unique()
	{

	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::transfer(iterator position, iterator first, iterator last)
	{
		if (position != last) {//?
			link_type lastpre = last.nodeptr->pre;
			first.nodeptr->pre->next = last.nodeptr;
			last.nodeptr->pre = first.nodeptr->pre;

			lastpre->next = position.nodeptr;
			first.nodeptr->pre = position.nodeptr->pre;
			position.nodeptr->pre = lastpre;
			first.nodeptr->pre->next = first.nodeptr;
		}
	}
	template<typename T, typename Alloc>
	inline void list<T, Alloc>::clear()
	{
		link_type p = node->next;
		while (p != node) {
			link_type q = p;
			p = p->next;
			destory_node(q);
		}
		node->next = node;
		node->pre = node;
	}

	//?
	template<typename T, typename Alloc>
	bool operator== (const list<T, Alloc>& x, const list<T, Alloc>& y) {
		auto first1 = x.begin();
		auto first2 = y.begin();
		auto last1 = x.end();
		auto last2 = y.end();
		while (first1 != last1 && first2 != last2) {
			if (*first1 == *first2) {
				++first1;
				++first2;
			}
			else
				return false;
		}
		return first1 == last1 && first2 == last2;
	}

	template<typename T, typename Alloc>
	bool operator< (const list<T, Alloc>& x, const list<T, Alloc>& y) {
		auto first1 = x.begin();
		auto first2 = y.begin();
		auto last1 = x.end();
		auto last2 = y.end();
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				++first1;
				++first2;
			}
			else
				return false;
		}
		if (first1 == last1)
			return true;
		return false;
	}
}
#endif // !STL_LIST