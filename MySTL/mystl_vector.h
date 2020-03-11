#pragma once

#ifndef STL_VECTOR
#define STL_VECTOR
#include "mystl_allocator.h"
#include "mystl_alloc.h"
#include "mystl_uninitialized.h"

namespace mystl {

	template <typename T, typename Alloc = simple_alloc<T, alloc>>
	class vector {
	private:
		T *start_ = nullptr;
		T *end_ = nullptr;
		T *endofstorge_ = nullptr;

	public:
		typedef T value_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	private:
		typedef Alloc data_allocator;

	public:
		//构造,复制,赋值,析构相关函数
		vector()
			:start_(0), end_(0), endOfStorage_(0) {}
		explicit vector(const size_type n) {
			fill_initialize(n, T());
		}
		vector(const size_type n, const value_type& value) {
			fill_initialize(n, value);
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& v);
		vector(vector&& v);
		vector& operator = (const vector& v);
		vector& operator = (vector&& v);
		~vector();

		//访问相关
		iterator begin() { return start_; }
		const_iterator begin() const { return start_; }
		iterator end() { return end_; }
		const_iterator end() const { return end_; }
		//reverse_iterator rbegin() { return reverse_iterator(end()); }
		//const_reverse_iterator rbegin() const {
		//	return const_reverse_iterator(end());
		//}
		//reverse_iterator rend() { return reverse_iterator(begin()); }
		//const_reverse_iterator rend() const {
		//	return const_reverse_iterator(begin());
		//}
		reference operator[](size_type n) { return *(begin() + n); }
		const_reference operator[](size_type n) const { return *(begin() + n); }
		reference front() { return *(begin()); }
		const_reference front() const { return *(begin()); }
		reference back() { return *(end() - 1); }
		const_reference back() const { return *(end() - 1); }

		size_type size() const { return size_type(end() - begin()); }
		size_type max_size() const { return size_type(-1) / sizeof(T); }
		size_type capacity() const { return size_type(end_of_storage - begin()); }
		bool empty() const { return begin() == end(); }

		//添加删除元素相关
		//void clear();
		//void swap(vector& v);
		void push_back(const value_type& value);
		void pop_back();
		iterator insert(iterator position, const value_type& val);//元素动态增长由此实现
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
	
	protected:
		//配置空间并初始化
		iterator allocate_and_fill(size_type n, const T& value) {
			iterator res = data_allocator::allocate(n);
			uninitialized_fill_n(res, n, value);
			return res;
		}
		//初始化前n个已配置空间	
		void fill_initialize(size_type n, const T& value) {
			start_ = allocate_and_fill(n, value);
			end_ = start_ + n;
			endofstorge_ = end_;
		}
		//用[first, last)元素初始化vector
		template <typename InputIterator>
		void fill_initialize(InputIterator first, InputIterator last) {
			iterator start = data_allocator::allocate(size_type(last - first));
			end_ = uninitialized_copy(first, last, start);
			start_ = start;
			endofstorge_ = end_;
		}


		//释放已分配空间	
		deallocate() {
			data_allocator::deallocate(start_, endofstorge_ - start_);
		}

	};

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(const vector & v)
	{
		fill_initialize(v.begin(), v.end());
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(vector && v)
	{

	}

	template<typename T, typename Alloc>
	template<class InputIterator>
	inline vector<T, Alloc>::vector(InputIterator first, InputIterator last)
	{
		fill_initialize(first, last);
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::~vector()
	{
		destroy(start_, end_);
		deallocate();
	}


	template<typename T, typename Alloc>
	inline vector & vector<T, Alloc>::operator=(const vector & v)
	{
		// TODO: 在此处插入 return 语句
	}

	template<typename T, typename Alloc>
	inline vector & vector<T, Alloc>::operator=(vector && v)
	{
		// TODO: 在此处插入 return 语句
	}



	template<typename T, typename Alloc>
	inline void mystl::vector<T, Alloc>::push_back(const value_type & value)
	{
	}

	template<typename T, typename Alloc>
	inline iterator mystl::vector<T, Alloc>::insert(iterator position, const value_type & val)
	{
		return iterator();
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::insert(iterator position, const size_type & n, const value_type & val)
	{

	}

	template<typename T, typename Alloc>
	template<class InputIterator>
	inline void vector<T, Alloc>::
	insert(iterator position, InputIterator first, InputIterator last)
	{

	}

	template<typename T, typename Alloc>
	inline iterator vector<T, Alloc>::erase(iterator position)
	{
		return iterator();
	}

	template<typename T, typename Alloc>
	inline iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		return iterator();
	}

}

#endif // !STL_VECTOR

