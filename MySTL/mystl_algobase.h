#pragma once
#ifndef STL_ALGOBASE
#define STL_ALGOBASE
#include "mystl_iterator.h"
#include "mytype_traits.h"
#include <cstring>

namespace mystl {

	/***********************************copy*****************************************/
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
		typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
		for (Distance n = last - first; n > 0; --n, ++first, ++result) 
			*result = *first;
		return result;
	}



	//�����汾
	template <typename InputIterator, typename OutputIterator>
	struct _copy_dispatch{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
			typedef typename iterator_traits<InputIterator>::iterator_category t;//
			//std::cout << typeid(&t()).name() << std::endl; //����Ϊstruct std::random_access_iterator_tag *
			return _copy(first, last, result, t());//ע��!����ض�����������͵Ļ�,�����random_access_iterator_tag��std::random_access_iterator_tag��ͬ
		}
	};

	template <typename T>
	inline T* _copy_t(const T* first, const T* last, T* result, _true_type) {
		memmove(result, first, sizeof(T) * (last - first));//?
		return result + (last - first);
	}

	template <typename T>
	inline T* _copy_t(const T* first, const T* last, T* result, _false_type) {
		return _copy(first, last, result, random_access_iterator_tag());//ָ��Ҳ��һ��RandomAccessIterator
		//return _copy_d(first, last, result, (ptrdiff_t*)0);
	}

	//ƫ�ػ��汾
	template <typename T>
	struct _copy_dispatch<T*, T*> {
		T* operator()(T* first, T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());//�����ð汾ȡ�����Ƿ���Ҫ����
		}
	};

	//ƫ�ػ��汾
	template <typename T>
	struct _copy_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());//�����ð汾ȡ�����Ƿ���Ҫ����
		}
	};

	//����ӿ�
	template <typename InputIterator, typename OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		return _copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

	inline char* copy(const char *first, const char *last, char *result) {
		memmove(result, first, last - first);
		return result + (last - first);
	}

	/*********************************copy_backward**********************************/

	//����
	template <typename BidirectionalIterator1, typename BidirectionalIterator2>
	struct _copy_backward_dispatch
	{
		BidirectionalIterator2 operator()(BidirectionalIterator1 first,
			BidirectionalIterator1 last,
			BidirectionalIterator2 result) {//��������BidirectionalIterator,�ڲ���ת����
			while (first != last)
				*--result = *--last;
			return result;
		}
	};

	template <typename T>
	inline T* _copy_backward_t(const T* first, const T* last, T* result,
		_true_type) {
		const ptrdiff_t N = last - first;
		memmove(result - N, first, sizeof(T) * N);
		return result - N;
	}

	template <typename T>
	inline T* _copy_backward_t(const T* first, const T* last, T* result,
		_false_type) {
		while (first != last)
			*--result = *--last;
		return result;
	}
	//ƫ�ػ�
	template <typename T>
	struct _copy_backward_dispatch<T*, T*>
	{
		T* operator()(T* first, T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	//ƫ�ػ�
	template <typename T>
	struct _copy_backward_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	//����ӿ�
	template <typename BidirectionalIterator1, typename BidirectionalIterator2>
	inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
		BidirectionalIterator2 result) {
		return _copy_backward_dispatch<BidirectionalIterator1,
			BidirectionalIterator2>()(first, last,
				result);
	}

	/************************************fill***************************************/
	//������
	template <class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value) {
		for (; first != last; ++first)
			*first = value;
	}

	template <class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}

}


#endif // !STL_ALGOBASE

