#pragma once
//全局函数,用于填充和复制数据,属于STL标准
#ifndef STL_UNINITIALIZED
#define STL_UNINITIALIZED

#include "mystl_iterator.h" 
#include "mytype_traits.h"
#include "mystl_construct.h"
#include "mystl_algobase.h"
#include <memory>

namespace mystl {

	/************************************************************************/
	template <class InputIt, class ForwardIt>
	inline ForwardIt
	_uninitialized_copy_aux(InputIt first, InputIt last, ForwardIt result, _true_type) {
		return mystl::copy(first, last, result);//为什么要加上命名空间限制????
	}

	template <class InputIt, class ForwardIt>
	ForwardIt
	_uninitialized_copy_aux(InputIt first, InputIt last, ForwardIt result, _false_type) {
		ForwardIt cur = result;
		for (; first != last; ++first, ++cur)
			construct(&*cur, *first);
		return cur;
	}

	//将以result为起点的欲初始化空间用[first, last)内的元素初始化
	template <typename InputIt,typename ForwardIt>
	ForwardIt
	uninitialized_copy(InputIt first, InputIt last, ForwardIt result) {
		return _uninitialized_copy_aux(first, last, result,
			typename type_traits<typename iterator_traits<InputIt>::value_type>::is_POD_type());
	}

	inline char* uninitialized_copy(const char* first, const char* last,
		char* result) {
		memmove(result, first, last - first);
		return result + (last - first);
	}

	inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last,
		wchar_t* result) {
		memmove(result, first, sizeof(wchar_t) * (last - first));
		return result + (last - first);
	}

	/***************************************************************************/


	template<class ForwardIt, class T>
	void _uninitialized_fill_aux(ForwardIt first, ForwardIt last,
		const T& value, _true_type) {
		fill(first, last, value);
	}
	template<class ForwardIt, class T>
	void _uninitialized_fill_aux(ForwardIt first, ForwardIt last,
		const T& value, _false_type) {
		for (; first != last; ++first) {
			construct(&*first, value);
		}
	}

	//将[first, last)范围内的未初始化空间用value初始化
	template<class ForwardIt, class T>
	void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value) {
		typedef typename type_traits<T>::is_POD_type isPODType;
		_uninitialized_fill_aux(first, last, value, isPODType());
	}

	/***************************************************************************/

	template<class ForwardIt, class Size, class T>
	ForwardIt _uninitialized_fill_n_aux(ForwardIt first,
		Size n, const T& x, _true_type) {
		return mystl::fill_n(first, n, x);
	}
	template<class ForwardIt, class Size, class T>
	ForwardIt _uninitialized_fill_n_aux(ForwardIt first,
		Size n, const T& x, _false_type) {
		for (; n > 0; --n, ++first) {
			construct(&*first, x);
		}
		return first;
	}

	//将以first为起点的空间的前n个元素用x初始化
	template<class ForwardIt, class Size, class T>
	inline ForwardIt uninitialized_fill_n(ForwardIt first,
		Size n, const T& x) {
		typedef typename type_traits<T>::is_POD_type isPODType;
		return _uninitialized_fill_n_aux(first, n, x, isPODType());
	}

	/*****************************************************************************************/
	//C++17标准
	using std::uninitialized_move;
	using std::uninitialized_move_n;
}



#endif // !STL_UNINITIALIZED

