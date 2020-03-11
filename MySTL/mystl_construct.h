#pragma once
/*
此头文件包含全局函数construct()和destroy(),分别负责对象的构造与析构
*/

#ifndef STL_CONSTRUCT
#define STL_CONSTRUCT
#include <new>
#include "mytype_traits.h"
#include "mystl_iterator.h"


namespace mystl {
	template <typename T1, typename T2>
	inline void construct(T1* p, const T2& value) {//p显然不能是const类型
		new(p) T1(value);
	}

	//版本一
	template <typename T>
	inline void destroy(T* p) {
		p->~T();
	}

	template <typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last) {
		_destroy(frist, last, value_type(first));// 第三个参数等同于(iterator_traits<first>::pointer)0
	}

	template <typename ForwardIterator, typename T>
	inline void _destroy(ForwardIterator first, ForwardIterator last, T*) {//第三个参数传指针,减小开销
		typename type_traits<T>::has_trivial_destructor destructor;
		_destroy_aux(first, last, destructor);
	}

	template <typename ForwardIterator>
	inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _true_type) {
		//什么也不需要做	
	}
	template <typename ForwardIterator>
	inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _false_type) {
		for (; first != last; ++first) {
			destroy(&(*first));//调用版本一
		}
	}
}
#endif // !STL_CONSTRUCT

