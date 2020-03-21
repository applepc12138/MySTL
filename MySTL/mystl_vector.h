#pragma once

#ifndef STL_VECTOR
#define STL_VECTOR
#include "mystl_allocator.h"
#include "mystl_alloc.h"
#include "mystl_uninitialized.h"
#include "mystl_algobase.h"

namespace mystl {

	template <typename T, typename Alloc = simple_alloc<T, alloc>>
	class vector {
		friend bool operator==(const vector&x, const vector&y);
		friend bool operator<(const vector&x, const vector&y);

	private:
		T * start_ = nullptr;
		T *end_ = nullptr;
		T *endofstorage_ = nullptr;

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
		vector() {}
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
		size_type capacity() const { return size_type(endofstorage_ - begin()); }
		bool empty() const { return begin() == end(); }

		//添加删除元素相关
		void clear();
		void swap(vector& v);
		void push_back(const value_type& value);
		void pop_back() { destroy(--end_); }
		iterator insert(iterator position, const value_type& val);//元素动态增长由此实现
		void insert(iterator position, const size_type& n, const value_type& val);
		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void reserve(size_type n);

	private:
		void insert_aux(iterator pos, const T& value);
		void insert_aux(iterator pos, size_type n, const T& value);
		template <typename InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last);

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
			endofstorage_ = end_;
		}
		//用[first, last)元素初始化vector
		template <typename InputIterator>
		void fill_initialize(InputIterator first, InputIterator last) {
			start_ = data_allocator::allocate(size_type(last - first));
			end_ = uninitialized_copy(first, last, start_);
			endofstorage_ = end_;
		}

		//释放已分配空间	
		void deallocate() {
			if(start_)
				data_allocator::deallocate(start_, endofstorage_ - start_);
		}

	};

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(const vector & v)
	{
		fill_initialize(v.begin(), v.end());
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc>::vector(vector && v)
		:start_(v.start_), end_(v.end_), endofstorage_(v.endofstorage_)
	{
		v.start_ = nullptr;
		v.end_ = nullptr;
		v.endofstorage_ = nullptr;
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
		if (capacity() != 0) {
			destroy(start_, end_);
			deallocate();
		}
	}


	template<typename T, typename Alloc>
	inline vector<T, Alloc> & vector<T, Alloc>::operator=(const vector & v)
	{
		if (&v != this) {
			destroy(start_, end_);
			size_type vcap = v.capacity();
			end_ = start_;
			if (capacity() >= vcap) {
				uninitialized_copy(v.begin(), v.end(), start_);
				end_ = start_ + v.size();
				endofstorage_ = vcap;
			}
			else {
				deallocate();
				fill_initialize(v.begin(), v.end());
			}

		}
		return *this;
	}

	template<typename T, typename Alloc>
	inline vector<T, Alloc> & vector<T, Alloc>::operator=(vector && v)
	{
		destroy(start_, end_);
		deallocate();
		start_ = v.start_;
		end_ = v.end_;
		endofstorage_ = v.endofstorage_;
		v.start_ = nullptr;
		v.end_ = nullptr;
		v.endofstorage_ = nullptr;
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::push_back(const value_type & value)
	{
		if (end_ != endofstorage_)
			construct(end_++, value);
		else {
			insert_aux(end_, value);
		}
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
	{
		copy(position + 1, end_, position);
		destroy(--end_);
		return position;
	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		iterator end = copy(last, end_, first);
		destroy(end, end_);
		end_ = end;
		return end_;

	}

	template<typename T, typename Alloc>
	inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type & val)
	{
		size_type n = position - begin();
		if (end_ != endofstorage_ && position == end_) {
			construct(end_++, val);
		}
		else
			insert_aux(position, val);
		return start_ + n;
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::insert_aux(iterator pos, const T & value)
	{
		if (end_ != endofstorage_) {
			copy_backward(pos, end_, end_ + 1);//?
			*pos = value;
			++end_;
		}
		else {//无备用空间
			size_type oldsize = size();
			const size_type newsize = oldsize == 0 ? 1 : 2 * oldsize;
			T* newstart = data_allocator::allocate(newsize);
			T* insertpos = uninitialized_copy(start_, pos, newstart);
			construct(insertpos, value);
			T* newend_ = uninitialized_copy(pos, end_, insertpos + 1);
			destroy(start_, end_);
			deallocate();
			start_ = newstart;
			end_ = newend_;
			endofstorage_ = start_ + newsize;
		}
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::insert(iterator position, const size_type & n, const value_type & val)
	{
		insert_aux(position, n, val);
	}

	template<typename T, typename Alloc>
	inline void vector<T, Alloc>::insert_aux(iterator pos, size_type n, const T & value)
	{
		if (n != 0) {
			if (size_type(endofstorage_ - start_) >= n) {
				T x_copy = value;
				const size_type elems_after = end_ - pos;
				iterator oldend = end_;
				if (elems_after > n) {
					uninitialized_copy(end_ - n, end_, end_);
					end_ += n;
					mystl::copy_backward(pos, oldend - n, oldend);
					mystl::fill(pos, pos + n, x_copy);
				}
				else {
					uninitialized_fill_n(end_, n - elems_after, x_copy);
					end_ += n - elems_after;
					uninitialized_copy(pos, oldend, end_);
					end_ += elems_after;
					mystl::fill(pos, oldend, x_copy);
				}
			}
			else {
				const size_type old_size = size();
				const size_type len = old_size + (old_size > n ? old_size : n);//?
				iterator new_start = data_allocator::allocate(len);
				iterator new_finish = new_start;
				new_finish = uninitialized_copy(start_, pos, new_start);
				new_finish = uninitialized_fill_n(new_finish, n, value);
				new_finish = uninitialized_copy(pos, end_, new_finish);

				destroy(start_, end_);
				deallocate();
				start_ = new_start;
				end_ = new_finish;
				endofstorage_ = new_start + len;
			}
		}
	}

	template<typename T, typename Alloc>
	template<class InputIterator>
	inline void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
	{
		insert_aux(position, first, last);
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	inline void vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last)
	{
		if (first != last) {
			size_type n = 0;
			distance(first, last, n);
			if (size_type(endofstorage_ - end_) >= n) {
				const size_type elems_after = end_ - position;
				iterator old_finish = end_;
				if (elems_after > n) {
					uninitialized_copy(end_ - n, end_, end_);
					end_ += n;
					copy_backward(position, old_finish - n, old_finish);
					mystl::copy(first, last, position);
				}
				else {
					uninitialized_copy(first + elems_after, last, end_);
					end_ += n - elems_after;
					uninitialized_copy(position, old_finish, end_);
					end_ += elems_after;
					mystl::copy(first, first + elems_after, position);
				}
			}
			else {
				const size_type old_size = size();
				const size_type len = old_size + (old_size > n ? old_size : n);
				iterator new_start = data_allocator::allocate(len);
				iterator new_finish = new_start;
				new_finish = uninitialized_copy(start_, position, new_start);
				new_finish = uninitialized_copy(first, last, new_finish);
				new_finish = uninitialized_copy(position, end_, new_finish);

				destroy(start_, end_);
				deallocate();
				start_ = new_start;
				end_ = new_finish;
				endofstorage_ = start_ + len;
			}
		}
	}

	template<typename T, typename Alloc>
	bool operator==(const vector<T, Alloc>&x, const vector<T, Alloc>&y) {
		
	}

	template<typename T, typename Alloc>
	bool operator<(const vector<T, Alloc>&x, const vector<T, Alloc>&y) {

	}

	template <typename T, typename Alloc /*= simple_alloc<T, alloc>*/>
	void mystl::vector<T, Alloc>::reserve(size_type n)
	{
		if (capacity() < n) {
			iterator result = data_allocator::allocate(n);
			iterator newend = uninitialized_copy(start_, end_, result);
			destroy(start_, end_);
			deallocate();
			start_ = result;
			end_ = newend;
			endofstorage_ = start_ + n;
		}
	}

	template <typename T, typename Alloc>
	void mystl::vector<T, Alloc>::swap(vector& v) {
		pointer tmp = start_;
		start_ = v.start_;
		v.start_ = tmp;

		tmp = end_;
		end_ = v.end_;
		v.end_ = tmp;

		tmp = endofstorage_;
		endofstorage_ = v.endofstorage_;
		v.endofstorage_ = tmp;
	}
}

#endif // !STL_VECTOR

