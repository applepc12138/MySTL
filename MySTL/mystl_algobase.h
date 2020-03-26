#pragma once
#ifndef STL_ALGOBASE
#define STL_ALGOBASE
#include "mystl_iterator.h"
#include "mytype_traits.h"
#include "mystl_algorithm.h"
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

	/***********************************copy_n***************************************/


	template <class InputIterator, class Size, class OutputIterator>
	pair<InputIterator, OutputIterator> _copy_n(InputIterator first, Size count,
		OutputIterator result, input_iterator_tag) 
	{
		for (; count > 0; --count, ++first, ++result)
			*result = *first;
		return pair<InputIterator, OutputIterator>(first, result);
	}

	template <class RandomAccessIterator, class Size, class OutputIterator>
	inline pair<RandomAccessIterator, OutputIterator>
		_copy_n(RandomAccessIterator first, Size count,
			OutputIterator result, random_access_iterator_tag) 
	{
		RandomAccessIterator last = first + count;
		return pair<RandomAccessIterator, OutputIterator>(last,
			mystl::copy(first, last, result));
	}

	template< class InputIt, class Size, class OutputIt >
	OutputIt copy_n(InputIt first, Size count, OutputIt result)
	{
		_copy_n(first, count, result, iterator_category(first));
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

	/************************************generate***************************************/
	//�Ը����������� g �����ɵ�ֵ��ֵ��Χ [first, last) �е�ÿ��Ԫ��
	template< class ForwardIt, class Generator >
	void generate(ForwardIt first, ForwardIt last, Generator g)
	{
		for (; first != last; ++first) {
			*first = g();
		}
	}

	//�� count>0 ����ֵ������������ g �����ɵ�ֵ��ʼ�� first �ķ�Χ���� count ��Ԫ�ء��������κ���
	template< class OutputIt, class Size, class Generator >
	void generate_n(OutputIt first, Size count, Generator g)
	{
		if (count > 0) {
			for (; count != 0 && first != last; ++first) {
				*first = g();
			}
		}
	}

	//�������Է�Χ [first, last) ��Ԫ�ص�ʼ�� d_first ����һ��Χ��ʡ�������ض��б��׼��Ԫ�ء�Դ��Ŀ�귶Χ�����ص�
	//�������е��� value ��Ԫ��,����ָ����󱻸���Ԫ�صĵ�����
	template< class InputIt, class OutputIt, class T >
	OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, const T& value)
	{
		for (; first != last; ++first) {
			if (*first != value)
				*d_first++ = *first;
		}
		return d_first;
	}

	//�������Է�Χ [first, last) ��Ԫ�ص�ʼ�� d_first ����һ��Χ��ʡ�������ض��б��׼��Ԫ�ء�Դ��Ŀ�귶Χ�����ص�
	//��������ν�� p ���䷵�� true ��Ԫ��,����ָ����󱻸���Ԫ�صĵ�����
	template< class InputIt, class OutputIt, class UnaryPredicate >
	OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p)
	{
		for (; first != last; ++first) {
			if (!p(*first))
				*d_first++ = *first;
		}
		return d_first;
	}
	
	//�ӷ�Χ [first, last) �Ƴ����е��� value ��Ԫ�أ������ط�Χ�½�β��β�������
	//���� remove�ɺ������������ erase ������������δָ��ֵ����С�����������С����ƥ�����µ��߼���С
	template< class ForwardIt, class T >
	ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
	{
		first = find(first, last, value);
		ForwardIt next = first;
		return first == last ? last: remove_copy(++next, last, first, value);
	}

	//�ӷ�Χ [first, last) �Ƴ����� p ���������� true ��Ԫ�أ��� operator== �Ƚ����ǣ������ط�Χ�½�β��β�������
	template< class ForwardIt, class UnaryPredicate >
	ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
	{
		first = find_if(first, last, p);
		ForwardIt next = first;
		return first == last ? last : remove_copy_if(++next, last, first, p);
	}

	//�� new_value �滻��Χ [first, last) �����е��� old_value ��Ԫ��
	template< class ForwardIt, class T >
	void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value)
	{
		for (; first != last; ++first) {
			if (*first == old_value)
				*first = new_value;
		}
	}

	//�� new_value �滻��Χ [first, last) ������ν�� p ���䷵�� true ��Ԫ��
	template< class ForwardIt, class UnaryPredicate, class T >
	void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value)
	{
		for (; first != last; ++first) {
			if (p(*first))
				*first = new_value;
		}
	}

	//���� a �� b
	template< class T >
	void swap(T& a, T& b) noexcept
	{
		auto tmp = a;
		a = b;
		b = tmp;
	}

	//���� a �� b ����
	template< class T2, std::size_t N >
	void swap(T2(&a)[N], T2(&b)[N]) noexcept
	{

	}

	//���������ĵ�������ָ���Ԫ�ص�ֵ
	template<class ForwardIt1, class ForwardIt2>
	constexpr void iter_swap(ForwardIt1 a, ForwardIt2 b) 
	{
		swap(*a, *b);
	}

	template <class BidirectionalIt>
	void _reverse(BidirectionalIt first, BidirectionalIt last,
		bidirectional_iterator_tag) {
		while (true)
			if (first == last || first == --last)
				return;
			else
				iter_swap(first++, last);
	}

	template <class RandomAccessIt>
	void _reverse(RandomAccessIt first, RandomAccessIt last,
		random_access_iterator_tag) {
		while (first < last) 
			iter_swap(first++, --last);
	}

	//��ת [first, last) ��Χ�е�Ԫ��˳��
	template< class BidirIt >
	void reverse(BidirIt first, BidirIt last)
	{
		_reverse(first, last);
	}

	//�����Է�Χ [first, last) ����̵ȼ�Ԫ�����Ƴ���ͬ��Ԫ�أ����б��������� operator== �Ƚ�Ԫ��,�����ط�Χ�����߼���β��β�������
	template< class ForwardIt >
	ForwardIt unique(ForwardIt first, ForwardIt last)
	{
		
	}


	//�����Է�Χ [first, last) ����̵ȼ�Ԫ�����Ƴ���ͬ��Ԫ�أ����б��������ø�����ν�� p �Ƚ�Ԫ��,�����ط�Χ�����߼���β��β�������
	template< class ForwardIt, class BinaryPredicate >
	ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
	{

	}

}


#endif // !STL_ALGOBASE

