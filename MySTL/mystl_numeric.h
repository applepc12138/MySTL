#pragma once
#ifndef STL_NUMERIC
#define STL_NUMERIC

namespace mystl {

	//��ʼ�� value ���ظ�����ֵ ++value ��˳�����ֵ��䷶Χ [first, last) 
	template< class ForwardIt, class T >
	void iota(ForwardIt first, ForwardIt last, T value)
	{
		while (first != last) {
			*first++ = value++;
		}
	}

	//�������ֵ init �������Χ [first, last) ��Ԫ�صĺ�
	template< class InputIt, class T >
	T accumulate(InputIt first, InputIt last, T init)
	{
		while (first != last) {
			init += *first;
		}
		return init;
	}


	template< class InputIt, class T, class BinaryOperation >
	T accumulate(InputIt first, InputIt last, T init,
		BinaryOperation op)
	{
		while (first != last) {
			init = op(init, *first);
		}
		return init;
	}

	//�����ڻ�������֮�ͣ����ڷ�Χ [first1, last1) ��ʼ�� first2 �ķ�Χ�Ͻ�������ӳ��/��Լ����
	template< class InputIt1, class InputIt2, class T >
	T inner_product(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, T init)
	{
		for (; first1 != last1; ++first1, ++first2) {
			init = init + (*first1 * *first2);
		}
		return init;
	}


	template<class InputIt1, class InputIt2, class T,
		class BinaryOperation1, class BinaryOperation2>
		T inner_product(InputIt1 first1, InputIt1 last1,
			InputIt2 first2, T init, BinaryOperation1 op1, BinaryOperation2 op2)
	{
		for (; first1 != last1; ++first1, ++first2) {
			init = op1(init, op2(*first1, *first2));
		}
		return init
	}

	//���� [first, last) ��Χ��ÿ������Ԫ�صĵڶ����͵�һ���Ĳ��д�����ǵ�ʼ�� d_first + 1 �ķ�Χ��
	//д�벻�޸ĵ� *first ������ *d_first 
	template< class InputIt, class OutputIt >
	OutputIt adjacent_difference(InputIt first, InputIt last,
		OutputIt d_first)
	{
		if (first != last) {
			*d_first++ = *first;
			decltype(*first) pre;
			while (first != last) {
				pre = *first;
				*d_first++ = *++first - pre;
			}
		}
		return d_first;
	}


	template< class InputIt, class OutputIt, class BinaryOperation >
	OutputIt adjacent_difference(InputIt first, InputIt last,
		OutputIt d_first, BinaryOperation op)
	{
		if (first != last) {
			*d_first++ = *first;
			decltype(*first) pre;
			while (first != last) {
				pre = *first;
				*d_first++ = op(*++first, pre);
			}
		}
		return d_first;
	}

	//���㷶Χ [first, last) ���ӷ�Χ��Ԫ�صĲ��ֺͣ���д�뵽ʼ�� d_first �ķ�Χ
	template< class InputIt, class OutputIt >
	OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first)
	{
		if (first == last) 
			return d_first;

		auto sum = *first;
		*d_first = sum;

		while (++first != last) {
			sum = sum + *first; 
			*++d_first = sum;
		}
		return ++d_first;
	}


	template< class InputIt, class OutputIt, class BinaryOperation >
	OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first,
		BinaryOperation op)
	{
		if (first == last) return d_first;

		auto sum = *first;
		*d_first = sum;

		while (++first != last) {
			sum = op(sum, *first); 
			*++d_first = sum;
		}
		return ++d_first;
	}

}

#endif


