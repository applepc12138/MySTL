#pragma once
#ifndef STL_HASHTABLE
#define STL_HASHTABLE
#include "mystl_iterator.h"
#include "mystl_allocator.h"
#include "mystl_construct.h"
#include "mystl_vector.h"
#include "mystl_pair.h"
#include <algorithm>

namespace mystl {
	template <typename Value>
	struct hashtable_node {
		hashtable_node<Value>* next;
		Value value;
	};


	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc>
		class hashtable;//前置声明?? 只能放在外边??

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc>
	struct hashtable_iterator {
		template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
			typename EqualKey, typename Alloc>
			friend class hashtable;
	public:
		typedef forward_iterator_tag iterator_category;
		typedef Value value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef value_type* pointer;

		typedef hashtable_node<Value> node;

		typedef hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> hashtable;

		typedef hashtable_iterator<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> iterator;

	public:
		hashtable_iterator() = default;
		hashtable_iterator(node* _n, hashtable* _ht) : cur(_n), ht(_ht) {}
		hashtable_iterator(const iterator& iter) : cur(iter.cur), ht(iter.ht) {}
	public:
		reference operator*()const {//const hashtable_iterator<Value, Key>* const this
			return cur->value;
		}
		pointer operator->()const {
			return &(operator*());
		}
		iterator& operator++() {
			if (cur->next) {
				cur = cur->next;
			}
			else {
				size_type bucket = ht->bkt_num(cur->value);
				++bucket;
				while (bucket < ht->buckets.size()) {
					if (ht->buckets[bucket]) {
						cur = ht->buckets[bucket];
						return *this;
					}
					++bucket;
				}
				cur = nullptr;//置为尾后节点
			}
			return *this;
		}
		iterator operator++(int) {
			iterator tmp = *this;
			++*this;
			return tmp;
		}
		bool operator==(const iterator& iter) {
			return cur == iter.cur;
		}
		bool operator!=(const iterator& iter) {
			return !operator==(iter);
		}
	private:
		node* cur;
		hashtable* ht;
	};

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc>
		struct hashtable_const_iterator {
		template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
			typename EqualKey, typename Alloc>
			friend class hashtable;
		public:
			typedef forward_iterator_tag iterator_category;
			typedef Value value_type;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef const value_type& reference;
			typedef const value_type* pointer;

			typedef hashtable_node<Value> node;
			typedef hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> hashtable;

			typedef hashtable_const_iterator<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> iterator;

		public:
			hashtable_const_iterator() = default;
			hashtable_const_iterator(const node* _n,const hashtable* _ht) : cur(_n), ht(_ht) {}
			hashtable_const_iterator(const iterator& iter) : cur(iter.cur), ht(iter.ht) {}
		public:
			reference operator*()const {//const hashtable_iterator<Value, Key>* const this
				return cur->value;
			}
			pointer operator->()const {
				return &(operator*());
			}
			iterator& operator++() {
				if (cur->next) {
					cur = cur->next;
				}
				else {
					size_type bucket = ht->bkt_num(cur->value);
					++bucket;
					while (bucket < ht->buckets.size()) {
						if (ht->buckets[bucket]) {
							cur = ht->buckets[bucket];
							return *this;
						}
						++bucket;
					}
					cur = nullptr;//置为尾后节点
				}
				return *this;
			}
			iterator operator++(int) {
				iterator tmp = *this;
				++*this;
				return tmp;
			}
			bool operator==(const iterator& iter) {
				return cur == iter.cur;
			}
			bool operator!=(const iterator& iter) {
				return !operator==(iter);
			}
		private:
			const node* cur;
			const hashtable* ht;
	};


	// Note: assumes long is at least 32 bits.
	static const int stl_num_primes = 28;
	static const unsigned long stl_prime_list[stl_num_primes] =
	{
		53,         97,           193,         389,       769,
		1543,       3079,         6151,        12289,     24593,
		49157,      98317,        196613,      393241,    786433,
		1572869,    3145739,      6291469,     12582917,  25165843,
		50331653,   100663319,    201326611,   402653189, 805306457,
		1610612741, 3221225473ul, 4294967291ul
	};

	inline unsigned long stl_next_prime(unsigned long n)
	{
		const unsigned long* first = stl_prime_list;
		const unsigned long* last = stl_prime_list + stl_num_primes;
		const unsigned long* pos = std::lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}


	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
	typename EqualKey, typename Alloc = simple_alloc<hashtable_node<Value>, alloc>>
	class hashtable {
		friend bool operator==(const hashtable& h1, const hashtable& h2);
		template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
			typename EqualKey, typename Alloc>
		friend	struct hashtable_iterator;
		template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
			typename EqualKey, typename Alloc>
			friend	struct hashtable_const_iterator;
	public:
		typedef Alloc data_allocator;
		typedef hashtable_node<Value> node;

	public:
		typedef hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> ht;
		typedef hashtable_iterator<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> iterator;
		typedef hashtable_const_iterator<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc> const_iterator;
		typedef Value value_type;
		typedef Key key_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		typedef HashFunc hasher;
		typedef EqualKey key_equal;
	private:
		HashFunc hash;
		EqualKey equals;
		ExtractKey get_key;
		vector<node*> buckets;
		size_type num_elements;

	public:
		hashtable() = default;
		hashtable(size_type n, const HashFunc& hf, const EqualKey& eql,	const ExtractKey& ext)
			: hash(hf), equals(eql), get_key(ext), num_elements(0)
		{
			initialize_buckets(n);
		}

		hashtable(size_type n, const HashFunc& hf, const EqualKey& eql)
			: hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
		{
			initialize_buckets(n);
		}

		hashtable(const hashtable& table) : hash(table.hash), equals(table.equals), get_key(table.get_key), num_elements(0)
		{
			copy_from(table);
		}

		~hashtable() { clear(); }

	private:
		void initialize_buckets(size_type n) {
			size_type n_backets = next_size(n);
			buckets.reserve(n_backets);
			buckets.insert(buckets.end(), n_backets, (node*)0);
			num_elements = 0;
		}
		void copy_from(const hashtable& table);

		size_type next_size(size_type n)const { return stl_next_prime(n); }

		node* new_node(const value_type& v) {
			node* t = data_allocator::allocate();
			construct(&t->value, v);
			t->next = nullptr;
			return t;
		}
		void delete_node(node* n) {
			destroy(&n->value);
			data_allocator::deallocate(n);
		}
	public:

		iterator begin() {
			for (size_type n = 0; n < buckets.size(); ++n) {
				if (buckets[n])
					return iterator(buckets[n], this);
			}
			return iterator(nullptr, this);
		}
		const_iterator begin()const {
			for (size_type n = 0; n < buckets.size(); ++n) {
				if (buckets[n])
					return const_iterator(buckets[n], this);//this指针类型为const hashtable*const,const_iterator构造函数参数也必须为const hashtable*
			}
			return const_iterator(nullptr, this);
		}
		iterator end() { return iterator(nullptr, this); }
		const_iterator end()const { return const_iterator(nullptr, this); }

		size_type bucket_count()const { return buckets.size(); }
		size_type max_bucket_count()const { return stl_prime_list[stl_num_primes - 1]; }
		size_type elems_in_bucket(size_type n)const {
			size_type i = 0;
			for (auto p = buckets[n]; p != nullptr; ) {
				++i;
				p = p->next;
			}
			return i;
		}
		
		pair<iterator, bool> insert_unique(const value_type& v) {
			resize(num_elements + 1);
			return insert_unique_noresize(v);
		}
		iterator insert_equal(const value_type& v) {
			resize(num_elements + 1);
			return insert_equal_noresize(v);
		}

		template <typename InputIterator>
		void insert_unique(InputIterator first, InputIterator last) {
			insert_unique(first, last, iterator_category(first));
		}

		template <typename InputIterator>
		void insert_equal(InputIterator first, InputIterator last) {
			insert_equal(first, last, iterator_category(first));
		}

		size_type erase(const key_type& key);
		void erase(const iterator& iter);
		void erase(const const_iterator& iter);
		void erase(iterator first, iterator last);

		size_type size()const { return num_elements; }
		size_type max_size()const { return size_type(-1); }
		bool empty()const { return num_elements == 0; }

		iterator find(const key_type& key);
		const_iterator find(const key_type& key)const;
		reference find_or_insert(const value_type& key);
		size_type count(const key_type& key)const;
		pair<iterator, iterator> equal_range(const key_type& key);

		
		void clear();
	private:
		pair<iterator, bool> insert_unique_noresize(const value_type& v);
		iterator insert_equal_noresize(const value_type& v);

		template <class InputIterator>
		void insert_unique(InputIterator f, InputIterator l,
			input_iterator_tag)
		{
			for (; f != l; ++f)
				insert_unique(*f);
		}

		template <class InputIterator>
		void insert_equal(InputIterator f, InputIterator l,
			input_iterator_tag)
		{
			for (; f != l; ++f)
				insert_equal(*f);
		}

		template <class ForwardIterator>
		void insert_unique(ForwardIterator f, ForwardIterator l,
			forward_iterator_tag)
		{
			size_type n = 0;
			distance(f, l, n);
			resize(num_elements + n);
			for (; n > 0; --n, ++f)
				insert_unique_noresize(*f);
		}

		template <class ForwardIterator>
		void insert_equal(ForwardIterator f, ForwardIterator l,
			forward_iterator_tag)
		{
			size_type n = 0;
			distance(f, l, n);
			resize(num_elements + n);
			for (; n > 0; --n, ++f)
				insert_equal_noresize(*f);
		}

		void erase_bucket(size_type n, node* first, node* last);//删除第n个'桶'中[first, last)元素
		void erase_bucket(size_type n, node* last);

		void resize(size_type num_elem_hint);//判断是否需要重建表格

		size_type bkt_num_key(const key_type& key) const
		{
			return bkt_num_key(key, buckets.size());
		}

		size_type bkt_num(const value_type& obj) const
		{
			return bkt_num_key(get_key(obj));
		}

		size_type bkt_num_key(const key_type& key, size_t n) const
		{
			return hash(key) % n;
		}

		size_type bkt_num(const value_type& obj, size_t n) const
		{
			return bkt_num_key(get_key(obj), n);
		}

	};

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		mystl::pair<typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::iterator,
				typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::iterator>
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::equal_range(const key_type& key)
	{
		size_type bucket = bkt_num_key(key);
		for (node* first = buckets[bucket]; first != nullptr; first = first->next) {
			if (equals(get_key(first->value), key)) {
				for (node* cur = first->next; cur != nullptr; cur = cur->next) {
					if (!equals(get_key(cur->value), key))
						return pair<iterator, iterator>(iterator(first, this), iterator(cur, this));
				}
				for (size_type m = bucket + 1; m < buckets.size(); ++m) {
					if (buckets[m]) {
						return pair<iterator, iterator>(iterator(first, this), iterator(buckets[m], this));
					}
				}
				return pair<iterator, iterator>(iterator(first, this), iterator(nullptr, this));
			}
			
		}
		return pair<iterator, iterator>(iterator(nullptr, this), iterator(nullptr, this));
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
	typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::reference 
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::find_or_insert(const value_type& v)
	{
		size_type bucket = bkt_num(v);
		node* cur = buckets[bucket];
		while (cur) {
			if (equals(get_key(cur->value), get_key(v))) 
				return cur->value;
			cur = cur->next;
		}
		cur = new_node(v);
		cur->next = buckets[bucket];
		buckets[bucket] = cur;
		++num_elements;
		return cur->value;
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::erase_bucket(size_type n, node* last)
	{
		node* cur = buckets[n];
		while (cur != last) {
			buckets[n] = cur->next;
			delete_node(cur);
			cur = buckets[n];
			--num_elements;
		}
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::erase_bucket(size_type n, node* first, node* last)
	{
		node* cur = buckets[n];
		if (cur == first)
			erase_bucket(n, last);
		else {
			node* pre = cur;
			cur = cur->next;
			for (; cur != first; pre = cur, cur = cur->next)
				;
			while (cur != last) {//SGI 2.9中???
				node* tmp = cur;
				cur = cur->next;
				delete_node(tmp);
			}
			pre->next = last;
		}
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::erase(iterator first, iterator last)
	{
		size_type f_bucket = first.cur ? bkt_num(first.cur->value) : buckets.size();
		size_type l_bucket = last.cur ? bkt_num(last.cur->value) : buckets.size();

		if (first.cur == last.cur)
			return;
		else if (f_bucket == l_bucket)//同一个'桶'中
			erase_bucket(f_bucket, first.cur, last.cur);
		else {
			erase_bucket(f_bucket, first.cur, nullptr);
			for (size_type n = f_bucket + 1; n < l_bucket; ++n)
				erase_bucket(n, nullptr);
			if (l_bucket != buckets.size())
				erase_bucket(l_bucket, last.cur);
		}
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::erase(const const_iterator& iter)
	{
		erase(iterator(const_cast<node*>(it.cur), const_cast<hashtable*>(it.ht)));
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::erase(const iterator& iter)//删除会使迭代器iter失效
	{
		node*const p = iter.cur;
		if (p) {
			const size_type bucket = bkt_num_key(p->value);
			node* cur = buckets[bucket];
			if (cur == p) {//要删除的是第一个节点
				buckets[bucket] = cur->next;
				delete_node(p);
				--num_elements;
				return;
			}
			node* pre = cur;
			cur = cur->next;
			while (cur) {
				if (cur == p) {
					pre->next = cur->next;
					delete_node(p);
					--num_elements;
					return;
				}
				pre = cur;
				cur = cur->next;
			}
		}
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::size_type 
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::erase(const key_type& key)
	{
		size_type erased = 0;
		size_type bucket = bkt_num_key(key);
		node* cur = buckets[bucket];
		if (cur) {
			node* pre = cur;
			cur = cur->next;
			while (cur) {
				if (equals(get_key(cur->value), key)) {
					++erased;
					--num_elements;
					pre->next = cur->next;
					delete_node(cur);
					cur = pre->next;
				}
				else {
					pre = cur;
					cur = cur->next;
				}
			}
			if (equals(get_key(buckets[bucket]->value), key)) {//判断第一个节点是否与key相等
				++erased;
				--num_elements;
				pre = buckets[bucket];
				buckets[bucket] = pre->next;
				delete_node(pre);
			}
		}
		return erased;
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::copy_from(const hashtable& table)
	{

	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::resize(size_type num_elem_hint)
	{
		size_type old_size = buckets.size();
		if (num_elem_hint > old_size) {//元素个数大于'桶'个数时重建
			size_type n = next_size(num_elem_hint);
			vector<node*> tmp{ n, nullptr};
			for(size_type i = 0; i < old_size; ++i){//将旧桶中的每个节点转移到新桶中
				node* cur = buckets[i];
				while (cur) {
					buckets[i] = buckets[i]->next;
					size_type bucket = bkt_num(cur->value, n);//计算节点在新桶中的位置
					cur->next = tmp[bucket];
					tmp[bucket] = cur;
					cur = buckets[i];
				}
			}
			buckets.swap(tmp);
		}
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		void mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::clear()
	{
		for (size_type n = 0; n < buckets.size(); ++n) {
			if (buckets[n]) {
				auto cur = buckets[n];
				while (cur) {
					auto tmp = cur;
					cur = cur->next;
					destroy(&tmp->value);
					data_allocator::deallocate(tmp);
				}
			}
			buckets[n] = nullptr;
		}
		num_elements = 0;
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::iterator 
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::insert_equal_noresize(const value_type& v)
	{
		const size_type bucket = bkt_num(v, buckets.size());
		if (!buckets[bucket]) {
			buckets[bucket] = new_node(v);
			++num_elements;
			return iterator(buckets[bucket], this);
		}
		else {
			node* cur = buckets[bucket];
			while (cur->next) {
				if (equals(get_key(cur->value), get_key(v))) {//相等时就直接插入
					node* tmp = new_node(v);
					tmp->next = cur->next;
					cur->next = tmp;
					++num_elements;
					return iterator(tmp, this);
				}
				cur = cur->next;
			}
			cur->next = new_node(v);
			++num_elements;
			return iterator(cur->next, this);
		}
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		mystl::pair<typename  mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::iterator, bool> 
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::insert_unique_noresize(const value_type& v)
	{
		const size_type bucket = bkt_num(v, buckets.size());
		node* cur = buckets[bucket];
		while (cur) {
			if(equals(get_key(cur->value), get_key(v)))
				return pair<iterator, bool>(iterator(cur, this), false);
			cur = cur->next;
		}
		cur = new_node(v);//在起始处添加新节点
		cur->next = buckets[bucket];
		buckets[bucket] = cur;
		++num_elements;
		return pair<iterator, bool>(iterator(cur, this), true);
	}


	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::iterator
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::find(const key_type& key)
	{
		size_type bucket = bkt_num_key(key);
		node* cur = buckets[bucket];
		while (cur) {
			if (equals(get_key(cur->value), key)) {
				return iterator(cur, this);
			}
			cur = cur->next;
		}
		return iterator(nullptr, this);
	}

	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::const_iterator
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::find(const key_type& key) const
	{
		size_type bucket = bkt_num_key(key);
		node* cur = buckets[bucket];
		while (cur) {
			if (equals(get_key(cur->value), key)) {
				return const_iterator(cur, this);
			}
			cur = cur->next;
		}
		return const_iterator(nullptr, this);
	}


	template <typename Value, typename Key, typename HashFunc, typename ExtractKey,
		typename EqualKey, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		typename mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::size_type
		mystl::hashtable<Value, Key, HashFunc, ExtractKey, EqualKey, Alloc>::count(const key_type& key) const
	{
		size_type bucket = bkt_num_key(key);
		node* cur = buckets[bucket];
		size_type n = 0;
		while (cur) {
			if (equals(get_key(cur->value), key)) {
				++n;
			}
			cur = cur->next;
		}
		return n;
	}

	template <typename V, typename K, typename HF, typename ExKey,
		typename EqK, typename Alloc /*= simple_alloc<hashtable_node<Value>, alloc>*/>
		bool operator==(const hashtable<V, K, HF, ExKey, EqK, Alloc>& h1, const hashtable<V, K, HF, ExKey, EqK, Alloc>& h2) 
	{
		if (h1.buckets.size() != h2.buckets.size())
			return false;
		for (int n = 0; n < h1.buckets.size(); ++n) {
			node* cur1 = h1.buckets[n];
			node* cur2 = h2.buckets[n];
			for (; cur1 && cur2 && cur1->value == cur2->value;
				cur1 = cur1->next, cur2 = cur2->next)
			{
			}
			if (cur1 || cur2)
				return false;
		}
		return true;
	}


}
#endif
