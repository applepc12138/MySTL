#pragma once
#ifndef STL_ALGOBASE
#define STL_ALGOBASE
#include "mystl_iterator.h"
#include "mytype_traits.h"
#include "mystl_algorithm.h"
#include <cstring>

namespace mystl {

	/***********************************copy*****************************************/
	//InputIt
	template <typename InputIt, typename OutputIt>
	inline OutputIt _copy(InputIt first, InputIt last,
		OutputIt result, input_iterator_tag)
	{
		for (; first != last; ++result, ++first)
			*result = *first;
		return result;
	}


	//RandomAccessIterator
	template <typename RandomAccessIterator, typename OutputIt>
	inline OutputIt _copy(RandomAccessIterator first, RandomAccessIterator last,
			OutputIt result, random_access_iterator_tag)
	{
		typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
		for (Distance n = last - first; n > 0; --n, ++first, ++result) 
			*result = *first;
		return result;
	}



	//�����汾
	template <typename InputIt, typename OutputIt>
	struct _copy_dispatch{
		OutputIt operator()(InputIt first, InputIt last, OutputIt result) {
			typedef typename iterator_traits<InputIt>::iterator_category t;//
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
	template <typename InputIt, typename OutputIt>
	inline OutputIt copy(InputIt first, InputIt last, OutputIt result) {
		return _copy_dispatch<InputIt, OutputIt>()(first, last, result);
	}

	inline char* copy(const char *first, const char *last, char *result) {
		memmove(result, first, last - first);
		return result + (last - first);
	}

	/***********************************copy_n***************************************/


	template <class InputIt, class Size, class OutputIt>
	pair<InputIt, OutputIt> _copy_n(InputIt first, Size count,
		OutputIt result, input_iterator_tag) 
	{
		for (; count > 0; --count, ++first, ++result)
			*result = *first;
		return pair<InputIt, OutputIt>(first, result);
	}

	template <class RandomAccessIterator, class Size, class OutputIt>
	inline pair<RandomAccessIterator, OutputIt>
		_copy_n(RandomAccessIterator first, Size count,
			OutputIt result, random_access_iterator_tag) 
	{
		RandomAccessIterator last = first + count;
		return pair<RandomAccessIterator, OutputIt>(last,
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

	template <class OutputIt, class Size, class T>
	OutputIt fill_n(OutputIt first, Size n, const T& value) {
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

	template <class BidirIt>
	void _reverse(BidirIt first, BidirIt last,
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


	/**************************************unique_copy********************************************/
	//forward_iterator_tag
	template <class InputIt, class ForwardIt>
	ForwardIt _unique_copy(InputIt first, InputIt last,
		ForwardIt result, forward_iterator_tag) {
		*result = *first;
		while (++first != last)
			if (*result != *first)
				*++result = *first;
		return ++result;
	}


	template <class InputIt, class OutputIt, class T>
	OutputIt _unique_copy(InputIt first, InputIt last,
		OutputIt result, T*) {
		T value = *first;
		*result = value;
		while (++first != last)
			if (value != *first) {//? ע�ⲻ��*result
				value = *first;
				*++result = value;
			}
		return ++result;
	}

	//output_iterator_tag
	// ���� output iterator ֻ�ܽ���д���������Բ����� *result != *first �������ж�
	template <class InputIt, class OutputIt>
	inline OutputIt _unique_copy(InputIt first, InputIt last,
		OutputIt result,
		output_iterator_tag) {
		return _unique_copy(first, last, result, value_type(first));
	}


	//�ӷ�Χ [first, last) ����Ԫ�ص�ʼ�� d_first ����һ��Χ��ʹ�������������Ԫ�ء�ֻ����ÿ��ȼ�Ԫ�ص���Ԫ��
	//�� operator== �Ƚ�Ԫ��,����ָ�����д��Ԫ�غ�һԪ�ص����������
	template <class InputIt, class OutputIt>
	inline OutputIt unique_copy(InputIt first, InputIt last,
		OutputIt d_first) {
		if (first == last) return d_first;
		return _unique_copy(first, last, d_first, iterator_category(d_first));
	}

	template <class InputIt, class ForwardIt, class BinaryPredicate>
	ForwardIt _unique_copy(InputIt first, InputIt last,
		ForwardIt result,
		BinaryPredicate p,
		forward_iterator_tag) {
		*result = *first;
		while (++first != last)
			if (!p(*result, *first)) *++result = *first;
		return ++result;
	}

	template <class InputIt, class OutputIt, class BinaryPredicate,
		class T>
		OutputIt _unique_copy(InputIt first, InputIt last,
			OutputIt result,
			BinaryPredicate p, T*) {
		T value = *first;
		*result = value;
		while (++first != last)
			if (!p(value, *first)) {
				value = *first;
				*++result = value;
			}
		return ++result;
	}

	template <class InputIt, class OutputIt, class BinaryPredicate>
	inline OutputIt _unique_copy(InputIt first, InputIt last,
		OutputIt result,
		BinaryPredicate p,
		output_iterator_tag) {
		return _unique_copy(first, last, result, p, value_type(first));
	}


	//�ӷ�Χ [first, last) ����Ԫ�ص�ʼ�� d_first ����һ��Χ��ʹ�������������Ԫ�ء�ֻ����ÿ��ȼ�Ԫ�ص���Ԫ��
	//�ø����Ķ�Ԫν�� p �Ƚ�Ԫ��,����ָ�����д��Ԫ�غ�һԪ�ص����������
	template <class InputIt, class OutputIt, class BinaryPredicate>
	inline OutputIt unique_copy(InputIt first, InputIt last,
		OutputIt d_first,
		BinaryPredicate p) {
		if (first == last) return d_first;
		return _unique_copy(first, last, d_first, p,
			iterator_category(d_first));
	}


	//�����Է�Χ [first, last) ����̵ȼ�Ԫ�����Ƴ���ͬ��Ԫ�أ����б��������� operator== �Ƚ�Ԫ��,�����ط�Χ�����߼���β��β�������
	template< class ForwardIt >
	ForwardIt unique(ForwardIt first, ForwardIt last)
	{
		first = adjacent_find(first, last);
		return unique_copy(first, last, first);
	}


	//�����Է�Χ [first, last) ����̵ȼ�Ԫ�����Ƴ���ͬ��Ԫ�أ����б��������ø�����ν�� p �Ƚ�Ԫ��,�����ط�Χ�����߼���β��β�������
	template< class ForwardIt, class BinaryPredicate >
	ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
	{
		first = adjacent_find(first, last, p);
		return unique_copy(first, last, first, p);
	}

}


#endif // !STL_ALGOBASE

