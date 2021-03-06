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


	//RandomIt
	template <typename RandomIt, typename OutputIt>
	inline OutputIt _copy(RandomIt first, RandomIt last,
			OutputIt result, random_access_iterator_tag)
	{
		typedef typename iterator_traits<RandomIt>::difference_type Distance;
		for (Distance n = last - first; n > 0; --n, ++first, ++result)//不需要判断 first != last 
			*result = *first;
		return result;
	}



	//泛化版本
	template <typename InputIt, typename OutputIt>
	struct _copy_dispatch{
		OutputIt operator()(InputIt first, InputIt last, OutputIt result) {
			typedef typename iterator_traits<InputIt>::iterator_category t;//
			//std::cout << typeid(&t()).name() << std::endl; //可能为struct std::random_access_iterator_tag *
			return _copy(first, last, result, t());//注意!如果重定义迭代器类型的话,这里的random_access_iterator_tag与std::random_access_iterator_tag不同
		}
	};

	template <typename T>
	inline T* _copy_t(const T* first, const T* last, T* result, _true_type) {
		memmove(result, first, sizeof(T) * (last - first));//?
		return result + (last - first);
	}

	template <typename T>
	inline T* _copy_t(const T* first, const T* last, T* result, _false_type) {
		return _copy(first, last, result, random_access_iterator_tag());//指针也是一种RandomIt
		//return _copy_d(first, last, result, (ptrdiff_t*)0);
	}

	//偏特化版本
	template <typename T>
	struct _copy_dispatch<T*, T*> {
		T* operator()(T* first, T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());//被调用版本取决于是否需要析构
		}
	};

	//偏特化版本
	template <typename T>
	struct _copy_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_t(first, last, result, t());//被调用版本取决于是否需要析构
		}
	};

	//对外接口
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

	template <class RandomIt, class Size, class OutputIt>
	inline pair<RandomIt, OutputIt>
		_copy_n(RandomIt first, Size count,
			OutputIt result, random_access_iterator_tag) 
	{
		RandomIt last = first + count;
		return pair<RandomIt, OutputIt>(last,
			mystl::copy(first, last, result));
	}

	template< class InputIt, class Size, class OutputIt >
	OutputIt copy_n(InputIt first, Size count, OutputIt result)
	{
		_copy_n(first, count, result, iterator_category(first));
	}


	/*********************************copy_backward**********************************/

	//泛化
	template <typename BidirIt1, typename BidirIt2>
	struct _copy_backward_dispatch
	{
		BidirIt2 operator()(BidirIt1 first,
			BidirIt1 last,
			BidirIt2 result) {//仅适用于BidirIt,内部无转调用
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
	//偏特化
	template <typename T>
	struct _copy_backward_dispatch<T*, T*>
	{
		T* operator()(T* first, T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	//偏特化
	template <typename T>
	struct _copy_backward_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result) {
			typedef typename type_traits<T>::has_trivial_assignment_operator t;
			return _copy_backward_t(first, last, result, t());
		}
	};

	//对外接口
	template <typename BidirIt1, typename BidirIt2>
	inline BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last,
		BidirIt2 result) {
		return _copy_backward_dispatch<BidirIt1,
			BidirIt2>()(first, last,
				result);
	}

	/************************************fill***************************************/
	//待完善
	template <class ForwardIt, class T>
	void fill(ForwardIt first, ForwardIt last, const T& value) {
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
	//以给定函数对象 g 所生成的值赋值范围 [first, last) 中的每个元素
	template< class ForwardIt, class Generator >
	void generate(ForwardIt first, ForwardIt last, Generator g)
	{
		for (; first != last; ++first) {
			*first = g();
		}
	}

	//若 count>0 ，则赋值给定函数对象 g 所生成的值给始于 first 的范围的首 count 个元素。否则不做任何事
	template< class OutputIt, class Size, class Generator >
	void generate_n(OutputIt first, Size count, Generator g)
	{
		if (count > 0) {
			for (; count != 0 && first != last; ++first) {
				*first = g();
			}
		}
	}

	//复制来自范围 [first, last) 的元素到始于 d_first 的另一范围，省略满足特定判别标准的元素。源与目标范围不能重叠
	//忽略所有等于 value 的元素,返回指向最后被复制元素的迭代器
	template< class InputIt, class OutputIt, class T >
	OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, const T& value)
	{
		for (; first != last; ++first) {
			if (*first != value)
				*d_first++ = *first;
		}
		return d_first;
	}

	//复制来自范围 [first, last) 的元素到始于 d_first 的另一范围，省略满足特定判别标准的元素。源与目标范围不能重叠
	//忽略所有谓词 p 对其返回 true 的元素,返回指向最后被复制元素的迭代器
	template< class InputIt, class OutputIt, class UnaryPredicate >
	OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p)
	{
		for (; first != last; ++first) {
			if (!p(*first))
				*d_first++ = *first;
		}
		return d_first;
	}
	
	//从范围 [first, last) 移除所有等于 value 的元素，并返回范围新结尾的尾后迭代器
	//调用 remove可后随调用容器的 erase 方法，它擦除未指定值并减小容器的物理大小，以匹配其新的逻辑大小
	template< class ForwardIt, class T >
	ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
	{
		first = find(first, last, value);
		ForwardIt next = first;
		return first == last ? last: remove_copy(++next, last, first, value);
	}

	//从范围 [first, last) 移除所有 p 对于它返回 true 的元素，用 operator== 比较它们，并返回范围新结尾的尾后迭代器
	template< class ForwardIt, class UnaryPredicate >
	ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
	{
		first = find_if(first, last, p);
		ForwardIt next = first;
		return first == last ? last : remove_copy_if(++next, last, first, p);
	}

	//以 new_value 替换范围 [first, last) 中所有等于 old_value 的元素
	template< class ForwardIt, class T >
	void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value)
	{
		for (; first != last; ++first) {
			if (*first == old_value)
				*first = new_value;
		}
	}

	//以 new_value 替换范围 [first, last) 中所有谓词 p 对其返回 true 的元素
	template< class ForwardIt, class UnaryPredicate, class T >
	void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value)
	{
		for (; first != last; ++first) {
			if (p(*first))
				*first = new_value;
		}
	}

	//交换 a 与 b
	template< class T >
	void swap(T& a, T& b) noexcept
	{
		auto tmp = a;
		a = b;
		b = tmp;
	}

	//交换 a 与 b 数组
	template< class T2, std::size_t N >
	void swap(T2(&a)[N], T2(&b)[N]) noexcept
	{

	}

	//交换给定的迭代器所指向的元素的值
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

	//反转 [first, last) 范围中的元素顺序
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
			if (value != *first) {//? 注意不能*result
				value = *first;
				*++result = value;
			}
		return ++result;
	}

	//output_iterator_tag
	// 由于 output iterator 只能进行写操作，所以不能有 *result != *first 这样的判断
	template <class InputIt, class OutputIt>
	inline OutputIt _unique_copy(InputIt first, InputIt last,
		OutputIt result,
		output_iterator_tag) {
		return _unique_copy(first, last, result, value_type(first));
	}


	//从范围 [first, last) 复制元素到始于 d_first 的另一范围，使得无连续的相等元素。只复制每组等价元素的首元素
	//用 operator== 比较元素,返回指向最后被写入元素后一元素的输出迭代器
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


	//从范围 [first, last) 复制元素到始于 d_first 的另一范围，使得无连续的相等元素。只复制每组等价元素的首元素
	//用给定的二元谓词 p 比较元素,返回指向最后被写入元素后一元素的输出迭代器
	template <class InputIt, class OutputIt, class BinaryPredicate>
	inline OutputIt unique_copy(InputIt first, InputIt last,
		OutputIt d_first,
		BinaryPredicate p) {
		if (first == last) return d_first;
		return _unique_copy(first, last, d_first, p,
			iterator_category(d_first));
	}


	//从来自范围 [first, last) 的相继等价元素组移除相同的元素，序列必须有序，用 operator== 比较元素,并返回范围的新逻辑结尾的尾后迭代器
	template< class ForwardIt >
	ForwardIt unique(ForwardIt first, ForwardIt last)
	{
		first = adjacent_find(first, last);
		return unique_copy(first, last, first);
	}


	//从来自范围 [first, last) 的相继等价元素组移除相同的元素，序列必须有序，用给定的谓词 p 比较元素,并返回范围的新逻辑结尾的尾后迭代器
	template< class ForwardIt, class BinaryPredicate >
	ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
	{
		first = adjacent_find(first, last, p);
		return unique_copy(first, last, first, p);
	}



}


#endif // !STL_ALGOBASE

