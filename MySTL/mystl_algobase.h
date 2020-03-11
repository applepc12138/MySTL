#pragma once
#ifndef STL_ALGOBASE
#define STL_ALGOBASE
#include "mystl_iterator.h"
#include "mytype_traits.h"
#include <cstring>

namespace mystl {

	//InputIterator
	template <typename InputIterator, typename OutputIterator>
	inline OutputIterator _copy(InputIterator first, InputIterator last,
		OutputIterator result, input_iterator_tag)
	{
		for (; first != last; ++result, ++first)
			*result = *first;
		return result;
	}

	//RandomAccessIterator
	template <typename RandomAccessIterator, typename OutputIterator>
	inline OutputIterator _copy(RandomAccessIterator first, RandomAccessIterator last,
			OutputIterator result, random_access_iterator_tag)
	{
		typedef typename iterator_traits<first>::difference_type Distance;
		for (Distance n = last - first; n > 0; --n, ++first, ++result) 
			*result = *first;
		return result;
	}

	//泛化版本
	template <typename InputIterator, typename OutputIterator>
	struct _copy_dispatch{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
			typedef typename iterator_traits<first>::iterator_category t;
			return _copy(first, last, result, t());
		}
	};

	template <typename T>
	inline T* _copy_t(const T* first, const T* last, T* result, _true_type) {
		memmove(result, first, sizeof(T) * (last - first));
		return result + (last - first);
	}

	template <typename T>
	inline T* _copy_t(const T* first, const T* last, T* result, _false_type) {
		typedef typename iterator_traits<T*>::iterator_category t;
		return _copy(first, last, result, t());
	}

	//偏特化版本
	template <typename T>
	struct _copy_dispatch<T*, T*> {
		OutputIterator operator()(T* first, T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());
		}
	};

	//偏特化版本
	template <typename T>
	struct _copy_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());
		}
	};

	template <typename InputIterator, typename OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		return _copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

	inline char* copy(const char *first, const char *last, char *result) {
		memmove(result, first, last - first);
		return result + (last - first);
	}

}


#endif // !STL_ALGOBASE

