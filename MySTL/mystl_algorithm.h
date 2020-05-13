#pragma once
#ifndef STL_ALGORITHM
#define STL_ALGORITHM

#include "mystl_iterator.h"
#include "mystl_pair.h"
#include "mystl_queue.h"

namespace mystl {
	 
	//检查一元谓词 p 是否对范围 [first, last) 中所有元素返回 true
	template< class InputIt, class UnaryPredicate >
	bool all_of(InputIt first, InputIt last, UnaryPredicate p) 
	{
		for ( ; first != last; ++first) {
			if (!p(*first))
				return false;
		}
		return true;
	}

	//检查一元谓词 p 是否对范围 [first, last) 中至少一个元素返回 true
	template< class InputIt, class UnaryPredicate >
	bool any_of(InputIt first, InputIt last, UnaryPredicate p) 
	{
		for ( ; first != last; ++first) {
			if (p(*first))
				return true;
		}
		return false;
	}

	//检查一元谓词 p 是否不对范围 [first, last) 中任何元素返回 true
	template< class InputIt, class UnaryPredicate >
	bool none_of(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++first) {
			if (p(*first))
				return false;
		}
		return true;
	}

	//按顺序应用给定的一元函数对象 f 到解引用范围 [first, last) 中每个迭代器的结果
	template< class InputIt, class UnaryFunction >
	UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
	{
		for (; first != last; ++first) {
			f(*first);
		}
		return f;//隐式移动?
	}

	//返回范围 [first, last) 中满足特定判别标准的元素数
	template< class InputIt, class T >
	size_t count(InputIt first, InputIt last, const T &value)
	{
		size_t n = 0;
		for (; first != last; ++first) {
			if (*first == value)
				++n;
		}
		return n;
	}

	//返回范围 [first, last) 中满足特定判别标准的元素数
	template< class InputIt, class UnaryPredicate >
	size_t count_if(InputIt first, InputIt last, UnaryPredicate p)
	{
		size_t n = 0; 
		for (; first != last; ++first) {
			if (p(*first))
				++n;
		}
		return n;
	}

	//返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义
	//的首个不匹配对。若不提供 last2,则它指代 first2 + (last1 - first1)
	template< class InputIt1, class InputIt2 >
	mystl::pair<InputIt1, InputIt2>
		mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for ( ; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) 
				return make_pair(first1, first2);
		}
		return make_pair(first1, first2);
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	mystl::pair<InputIt1, InputIt2>
		mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for ( ; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) 
				return make_pair(first1, first2);
		}
		return make_pair(first1, first2);
	}

	//返回范围 [first, last) 中满足特定判别标准的首个元素
	template< class InputIt, class T >
	InputIt find(InputIt first, InputIt last, const T& value)
	{
		for (; first != last; ++first) {
			if (*first == value)
				return first;
		}
		return last;
	}

	//返回范围[first, last) 中满足谓词 p 对其返回 true 的首个元素
	template< class InputIt, class UnaryPredicate >
	InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++ first) {
			if (p(*first))
				return first;
		}
		return last;
	}

	//返回范围 [first, last) 中满足谓词 q 对其返回 false 的首个元素
	template< class InputIt, class UnaryPredicate >
	InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++ first) {
			if (!p(*first))
				return first;
		}
		return last;
	}


	template <typename ForwardIt1, typename ForwardIt2>
	ForwardIt1 find_end_dispatch(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2,
		forward_iterator_tag, forward_iterator_tag)
	{
		if (first2 == last2)
			return last1;
		else {
			ForwardIt1 result = last1;
			while (true) {
				ForwardIt1 new_result = mystl::search(first1, last1, first2, last2);
				if (new_result == last1)
					return result;
				else {
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	template <typename BidirectionalIt1, typename BidirectionalIt2>
	BidirectionalIt1 find_end_dispatch(BidirectionalIt1 first1, BidirectionalIt1 last1, BidirectionalIt2 first2,
		BidirectionalIt2 last2, bidirectional_iterator_tag, bidirectional_iterator_tag)
	{
		typedef reverse_iterator<BidirectionalIt1> reit1;
		typedef reverse_iterator<BidirectionalIt2> reit2;	
		reit1 rresult = search(reit1(last1), reit1(first1), reit2(last2), reit2(first2));
		if (rresult == reit1(first1))
			return last1;
		else {
			BidirectionalIt1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}

	//在范围 [first1, last1) 中搜索序列 [first2, last2) 的最后一次出现
	template< class ForwardIt1, class ForwardIt2 >
	ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
	{
		return find_end_dispatch(first1, last1, first2, last2, iterator_category(first1), iterator_category(first2));
	}




	template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
	ForwardIt1 find_end_dispatch(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2,
		forward_iterator_tag, forward_iterator_tag, BinaryPredicate p)
	{
		if (first2 == last2)
			return last1;
		else {
			ForwardIt1 result = last1;
			while (true) {
				ForwardIt1 new_result = mystl::search(first1, last1, first2, last2, p);
				if (new_result == last1)
					return result;
				else {
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	template <typename BidirectionalIt1, typename BidirectionalIt2, typename BinaryPredicate>
	BidirectionalIt1 find_end_dispatch(BidirectionalIt1 first1, BidirectionalIt1 last1, BidirectionalIt2 first2, BidirectionalIt2 last2,
		bidirectional_iterator_tag, bidirectional_iterator_tag, BinaryPredicate p)
	{
		typedef reverse_iterator<BidirectionalIt1> reit1;
		typedef reverse_iterator<BidirectionalIt2> reit2;
		reit1 rresult = search(reit1(last1), reit1(first1), reit2(last2), reit2(first2), p);
		if (rresult == reit1(first1))
			return last1;
		else {
			BidirectionalIt1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}

	//在范围 [first1, last1) 中搜索序列 [first2, last2) 的最后一次出现,用给定的二元谓词 p 比较元素
	template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
	ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, BinaryPredicate p)
	{
		find_end_dispatch(first1, last1, first2, last2, iterator_category(first1), iterator_category(first2), p);
	}


	//在范围 [first, last) 中搜索范围 [s_first, s_last) 中的任何元素,用 operator== 比较元素
	//返回指向范围 [first, last) 中等于来自范围 [s_first; s_last) 中一个元素的首个元素。若找不到这种元素，则返回 last
	template< class InputIt, class ForwardIt >
	InputIt find_first_of(InputIt first, InputIt last,
		ForwardIt s_first, ForwardIt s_last)
	{
		for (; first != last; ++first) {
			for (auto cur = s_first; cur != last; ++cur) {
				if (*first == *cur)
					return first;
			}
		}
		return last;
	}



	//在范围 [first, last) 中搜索范围 [s_first, s_last) 中的任何元素,用给定的二元谓词 p 比较元素
	//返回指向范围 [first, last) 中等于来自范围 [s_first; s_last) 中一个元素的首个元素。若找不到这种元素，则返回 last
	template< class InputIt, class ForwardIt, class BinaryPredicate >
	InputIt find_first_of(InputIt first, InputIt last,
		ForwardIt s_first, ForwardIt s_last, BinaryPredicate p)
	{
		for (; first != last; ++first) {
			for (auto cur = s_first; cur != last; ++cur) {
				if (p(*first, *cur))
					return first;
			}
		}
		return last;
	}

	//在范围 [first, last) 中搜索二个相继的等同元素,用 operator== 比较元素
	//返回指向首对等同元素的首个元素的迭代器,若找不到这种元素，则返回 last
	template< class ForwardIt >
	ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
	{
		if (first == last)
			return last;
		auto next = ++first;
		for (; next != last; ++first, ++next) {
			if (*first == *next)
				return first;
		}
		return last;
	}

	//在范围 [first, last) 中搜索二个相继的等同元素,用给定的二元谓词 p 比较元素
	//返回指向首对等同元素的首个元素的迭代器,若找不到这种元素，则返回 last
	template< class ForwardIt, class BinaryPredicate>
	ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p)
	{
		if (first == last)
			return last;
		auto next = ++first;
		for (; next != last; ++first, ++next) {
			if (p(*first, *next))
				return first;
		}
		return last;
	}

	//搜索范围 [first, last) 中元素子序列 [s_first, s_last) 的首次出现,元素用 operator== 比较
	//返回指向范围中 [first, last) 首个子序列 [s_first, s_last) 起始的迭代器。若找不到这种子序列，则返回 last 。
	template< class ForwardIt1, class ForwardIt2 >
	ForwardIt1 search(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
	{
		for( ; first != last; ++first){
			auto cur1 = first;
			auto cur2 = s_first;
			for ( ; cur1 != last && cur2 != s_last; ++cur1, ++cur2) {
				if(*cur1 != *cur2)
					break;
			}
			if (cur2 == s_last)
				return first;
		}
		return last;
	}

	//搜索范围 [first, last) 中元素子序列 [s_first, s_last) 的首次出现,元素用给定的二元谓词 p 比较
	//返回指向范围中 [first, last) 首个子序列 [s_first, s_last) 起始的迭代器。若找不到这种子序列，则返回 last 。
	template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
	ForwardIt1 search(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
	{
		for ( ; first != last; ++first) {
			auto cur1 = first;
			auto cur2 = s_first;
			for (; cur1 != last && cur2 != s_last; ++cur1, ++cur2) {
				if (p(*cur1, *cur2))
					break;
			}
			if (cur2 == s_last)
				return first;
		}
		return last;
	}

	//在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value, 用 operator== 比较元素
	//返回指向范围 [first, last) 中找到的序列起始的迭代器。若找不到这种序列，则返回 last 
	template< class ForwardIt, class Size, class T >
	ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value)
	{
		auto n = distance(first, last);
		if (n < count)
			return last;
		while (first != last) {
			auto m = count;
			auto cur = first;
			for (; m != 0 && cur != last; ++cur) {
				if (*cur != value) {
					first = ++cur;
					break;
				}
				--m;
			}
			if (m == 0)
				return first;
			else if (cur == last)
				return last;
		}
		return last;
	}

	//在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value, 用给定的二元谓词 p 比较元素
	//返回指向范围 [first, last) 中找到的序列起始的迭代器。若找不到这种序列，则返回 last 
	template< class ForwardIt, class Size, class T, class BinaryPredicate >
	ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value, BinaryPredicate p)
	{
		auto n = distance(first, last);
		if (n < count)
			return last;
		while (first != last) {
			auto m = count;
			auto cur = first;
			for (; m != 0 && cur != last; ++cur) {
				if (p(*cur,value)) {
					first = ++cur;
					break;
				}
				--m;
			}
			if (m == 0)
				return first;
			else if (cur == last)
				return last;
		}
		return last;
	}


	//若范围 [first, last) 中的所有满足 p 的元素都出现在所有不满足的元素前则返回 true 。若 [first, last) 为空亦返回 true
	template< class InputIt, class UnaryPredicate >
	bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p)
	{
		while (first != last && p(*first))
			++first;
		while (first != last && !(p(*first)))
			++first;
		return first == last;
	}

	//重排序范围 [first, last) 中的元素，使得谓词 p 对其返回 true 的元素前于谓词 p 对其返回 false 的元素。不保持相对顺序
	//返回指向第二组元素首元素的迭代器
	template< class ForwardIt, class UnaryPredicate >
	ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
	{
		ForwardIt pre = mystl::find_if_not(first, last, p);
		if (pre == last) 
			return last;

		for (ForwardIt cur = std::next(pre); cur != last; ++cur) {//前后指针法  next返回pre后继
			if (p(*cur)) {
				iter_swap(cur, pre);
				++pre;
			}
		}
		return pre;
	}

	//检查 [first, last) 中的元素是否以不降序排序,用 operator< 比较元素
	template< class ForwardIt >
	bool is_sorted(ForwardIt first, ForwardIt last)
	{
		if (first == last)
			return true;
		for (auto pre = first++; first != last; ++first, ++pre) {
			if (*first > *pre)
				return false;
		}
		return true;
	}

	//检查 [first, last) 中的元素是否以不降序排序,用给定的二元比较函数 comp 比较元素
	template< class ForwardIt, class Compare >
	bool is_sorted(ForwardIt first, ForwardIt last, Compare comp)
	{
		if (first == last)
			return true;
		for (auto pre = ++first; first != last; ++first, ++pre) {
			if (comp(*first, *pre))
				return false;
		}
		return true;
	}

	//检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围,用 operator< 比较元素。
	//返回始于 first 且其中元素已以升序排序的最大范围。即满足范围 [first, it) 已排序的最后迭代器 it 
	template< class ForwardIt >
	ForwardIt is_sorted_until(ForwardIt first, ForwardIt last)
	{
		if (first == last)
			return last;
		for (auto pre = first++; first != last; ++first, ++pre) {
			if (*pre > *first)
				return first;
		}
		return last;
	}

	//检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围,用给定的二元比较函数 comp 比较元素
	template< class ForwardIt, class Compare >
	ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)
	{
		if (first == last)
			return last;
		for (auto pre = first++; first != last; ++first, ++pre) {
			if (comp(*pre,  *first))
				return first;
		}
		return last;
	}

	//以升序排序范围 [first, last) 中的元素。不保证维持相等元素的顺序
	template< class RandomIt >
	void sort(RandomIt first, RandomIt last)
	{

	}


	template< class RandomIt, class Compare >
	void sort(RandomIt first, RandomIt last, Compare comp)
	{

	}

	//重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle - first 个最小元素。
	//不保证保持相等的元素顺序。范围[middle, last) 中剩余的元素顺序未指定,用 operator< 比较元素
	template< class RandomIt >
	void partial_sort(RandomIt first, RandomIt middle, RandomIt last)
	{
		if (first == last)
			return;
		auto n = middle - first;
		while (n-- != 0) {
			mystl::make_heap(first++, last, std::greater<typename iterator_traits<RandomIt>::value_type>{});
		}
	}


	template< class RandomIt, class Compare >
	void partial_sort(RandomIt first, RandomIt middle, RandomIt last, Compare comp)
	{
		if (first == last)
			return;
		auto n = middle - first;
		while (n-- != 0) {
			make_heap(first++, last, comp);
		}
	}

	//以升序排序范围 [first, last) 中的元素。保证保持等价元素的顺序,用 operator< 比较元素
	template< class RandomIt >
	void stable_sort(RandomIt first, RandomIt last)
	{

	}

	//以升序排序范围 [first, last) 中的元素。保证保持等价元素的顺序,用给定的比较函数 comp 比较元素
	template< class RandomIt, class Compare >
	void stable_sort(RandomIt first, RandomIt last, Compare comp)
	{

	}

	template<class ForwardIt, class T>
	ForwardIt _lower_bound(ForwardIt first, ForwardIt last, const T& value, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIt middle;
		while (len > 0)//使用[first, first + len)代表左闭右开区间
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (*middle < value)
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}
		return first;
	}

	template<class RandomIt, class T>
	RandomIt _lower_bound(RandomIt first, RandomIt last, const T& value, random_access_iterator_tag)
	{
		while (first < last) {
			auto middle = (last - first) / 2;
			if (*middle < value) {
				first = middle + 1;
			}
			else {
				last = middle;
			}
		}
		return first;
	}

	//返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器，或若找不到这种元素则返回 last 
	template< class ForwardIt, class T >
	ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
	{
		return _lower_bound(first, last, value, iterator_category(first));
	}

	template<class ForwardIt, class T, class Compare>
	ForwardIt _lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIt middle;
		while (len > 0)//使用[first, first + len)代表左闭右开区间
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (comp(*middle, value))
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}
		return first;
	}

	template<class RandomIt, class T, class Compare>
	RandomIt _lower_bound(RandomIt first, RandomIt last, const T& value,Compare comp, random_access_iterator_tag)
	{
		while (first < last) {
			auto middle = (last - first) / 2;
			if(comp(*middle, value)) {
				first = middle + 1;
			}
			else {
				last = middle;
			}
		}
		return first;
	}


	template< class ForwardIt, class T, class Compare >
	ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
	{
		return _lower_bound(first, last, value, comp, iterator_category(first));
	}

	template<class ForwardIt, class T>
	ForwardIt _upper_bound(ForwardIt first, ForwardIt last, const T& value, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIt middle;
		while (len > 0)//使用[first, first + len)代表左闭右开区间
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (value < *middle) {
				len = half;
			}
			else {
				first = middle;
				++first;
				len = len - half - 1;
			}
		}
		return first;
	}

	template<class RandomIt, class T>
	RandomIt _upper_bound(RandomIt first, RandomIt last, const T& value, random_access_iterator_tag)
	{
		while (first < last) {
			auto middle = (last - first) / 2;
			if (value < *middle) {
				last = middle;
			}
			else {
				first = middle + 1;
			}
		}
		return first;
	}

	//返回指向范围 [first, last) 中首个大于 value 的元素的迭代器，或若找不到这种元素则返回 last 。采用二分实现，所以调用前必须保证有序
	template< class ForwardIt, class T >
	ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value)
	{
		return _upper_bound(first, last, value, iterator_category(first));
	}

	template<class ForwardIt, class T, class Compare>
	ForwardIt _upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIt middle;
		while (len > 0)//使用[first, first + len)代表左闭右开区间
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (comp(value, *middle)) {
				len = half;
			}
			else {
				first = middle;
				++first;
				len = len - half - 1;
			}
		}
		return first;
	}

	template<class RandomIt, class T, class Compare>
	RandomIt _upper_bound(RandomIt first, RandomIt last, const T& value, Compare comp, random_access_iterator_tag)
	{
		while (first < last) {
			auto middle = (last - first) / 2;
			if (comp(value, *middle)) {
				last = middle;
			}
			else {
				first = middle + 1;
			}
		}
		return first;
	}

	template< class ForwardIt, class T, class Compare >
	ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
	{
		return _upper_bound(first, last, value, comp, iterator_category(first));
	}

	//检查等价于 value 的元素是否出现于范围 [first, last) 中
	template< class ForwardIt, class T >
	bool binary_search(ForwardIt first, ForwardIt last, const T& value)
	{
		auto i = mystl::lower_bound(first, last, value);
		return i != last && !(value < *i);
	}

	template< class ForwardIt, class T, class Compare >
	bool binary_search(ForwardIt first, ForwardIt last, const T& value, Compare comp)
	{
		auto i = mystl::lower_bound(first, last, value);
		return i != last && !comp(value, *i);
	}

	//返回范围 [first, last) 中含有所有等价于 value 的元素的范围
	template< class ForwardIt, class T >
	mystl::pair<ForwardIt, ForwardIt>
		equal_range(ForwardIt first, ForwardIt last, const T& value)
	{
		return mystl::make_pair(mystl::lower_bound(first, last, value),
			mystl::upper_bound(first, last, value));
	}

	template< class ForwardIt, class T, class Compare >
	mystl::pair<ForwardIt, ForwardIt>
		equal_range(ForwardIt first, ForwardIt last, const T& value, Compare comp)
	{
		return mystl::make_pair(mystl::lower_bound(first, last, value, comp),
			mystl::upper_bound(first, last, value, comp));
	}

	//归并二个已排序范围 [first1, last1) 和 [first2, last2) 到始于 d_first 的一个已排序范围中
	template< class InputIt1, class InputIt2, class OutputIt >
	OutputIt merge(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2, OutputIt d_first)
	{
		for (; first1 != last1; ++d_first) {
			if (first2 == last2) {
				return mystl::copy(first1, last1, d_first);
			}
			if (*first2 < *first1) {
				*d_first = *first2;
				++first2;
			}
			else {
				*d_first = *first1;
				++first1;
			}
		}
		return mystl::copy(first2, last2, d_first);
	}

	template< class InputIt1, class InputIt2, class OutputIt, class Compare>
	OutputIt merge(InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
	{
		for (; first1 != last1; ++d_first) {
			if (first2 == last2) {
				return mystl::copy(first1, last1, d_first);
			}
			if (comp(*first2, *first1)) {
				*d_first = *first2;
				++first2;
			}
			else {
				*d_first = *first1;
				++first1;
			}
		}
		return mystl::copy(first2, last2, d_first);
	}
}

#endif
