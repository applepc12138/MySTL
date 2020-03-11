#pragma once
/*
��ͷ�ļ�����ȫ�ֺ���construct()��destroy(),�ֱ������Ĺ���������
*/

#ifndef STL_CONSTRUCT
#define STL_CONSTRUCT
#include <new>
#include "mytype_traits.h"
#include "mystl_iterator.h"


namespace mystl {
	template <typename T1, typename T2>
	inline void construct(T1* p, const T2& value) {//p��Ȼ������const����
		new(p) T1(value);
	}

	//�汾һ
	template <typename T>
	inline void destroy(T* p) {
		p->~T();
	}

	template <typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last) {
		_destroy(frist, last, value_type(first));// ������������ͬ��(iterator_traits<first>::pointer)0
	}

	template <typename ForwardIterator, typename T>
	inline void _destroy(ForwardIterator first, ForwardIterator last, T*) {//������������ָ��,��С����
		typename type_traits<T>::has_trivial_destructor destructor;
		_destroy_aux(first, last, destructor);
	}

	template <typename ForwardIterator>
	inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _true_type) {
		//ʲôҲ����Ҫ��	
	}
	template <typename ForwardIterator>
	inline void _destroy_aux(ForwardIterator first, ForwardIterator last, _false_type) {
		for (; first != last; ++first) {
			destroy(&(*first));//���ð汾һ
		}
	}
}
#endif // !STL_CONSTRUCT

