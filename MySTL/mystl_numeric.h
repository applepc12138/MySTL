#pragma once
#ifndef STL_NUMERIC
#define STL_NUMERIC

namespace mystl {

	//以始于 value 并重复地求值 ++value 的顺序递增值填充范围 [first, last) 
	template< class ForwardIt, class T >
	void iota(ForwardIt first, ForwardIt last, T value)
	{
		while (first != last) {
			*first++ = value++;
		}
	}

	//计算给定值 init 与给定范围 [first, last) 中元素的和
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

	//计算内积（即积之和）或在范围 [first1, last1) 和始于 first2 的范围上进行有序映射/规约操作
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

	//计算 [first, last) 范围中每对相邻元素的第二个和第一个的差，并写入它们到始于 d_first + 1 的范围。
	//写入不修改的 *first 副本到 *d_first 
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

	//计算范围 [first, last) 的子范围中元素的部分和，并写入到始于 d_first 的范围
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


