#pragma once
#ifndef STL_ALGORITHM
#define STL_ALGORITHM

#include "mystl_iterator.h"
#include "mystl_pair.h"
#include "mystl_queue.h"

namespace mystl {
	 
	//���һԪν�� p �Ƿ�Է�Χ [first, last) ������Ԫ�ط��� true
	template< class InputIt, class UnaryPredicate >
	bool all_of(InputIt first, InputIt last, UnaryPredicate p) 
	{
		for ( ; first != last; ++first) {
			if (!p(*first))
				return false;
		}
		return true;
	}

	//���һԪν�� p �Ƿ�Է�Χ [first, last) ������һ��Ԫ�ط��� true
	template< class InputIt, class UnaryPredicate >
	bool any_of(InputIt first, InputIt last, UnaryPredicate p) 
	{
		for ( ; first != last; ++first) {
			if (p(*first))
				return true;
		}
		return false;
	}

	//���һԪν�� p �Ƿ񲻶Է�Χ [first, last) ���κ�Ԫ�ط��� true
	template< class InputIt, class UnaryPredicate >
	bool none_of(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++first) {
			if (p(*first))
				return false;
		}
		return true;
	}

	//��˳��Ӧ�ø�����һԪ�������� f �������÷�Χ [first, last) ��ÿ���������Ľ��
	template< class InputIt, class UnaryFunction >
	UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
	{
		for (; first != last; ++first) {
			f(*first);
		}
		return f;//��ʽ�ƶ�?
	}

	//���ط�Χ [first, last) �������ض��б��׼��Ԫ����
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

	//���ط�Χ [first, last) �������ض��б��׼��Ԫ����
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

	//�������Զ�����Χ��һ���� [first1, last1) �������һ���� [first2,last2) ����
	//���׸���ƥ��ԡ������ṩ last2,����ָ�� first2 + (last1 - first1)
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

	//���ط�Χ [first, last) �������ض��б��׼���׸�Ԫ��
	template< class InputIt, class T >
	InputIt find(InputIt first, InputIt last, const T& value)
	{
		for (; first != last; ++first) {
			if (*first == value)
				return first;
		}
		return last;
	}

	//���ط�Χ[first, last) ������ν�� p ���䷵�� true ���׸�Ԫ��
	template< class InputIt, class UnaryPredicate >
	InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
	{
		for (; first != last; ++ first) {
			if (p(*first))
				return first;
		}
		return last;
	}

	//���ط�Χ [first, last) ������ν�� q ���䷵�� false ���׸�Ԫ��
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

	//�ڷ�Χ [first1, last1) ���������� [first2, last2) �����һ�γ���
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

	//�ڷ�Χ [first1, last1) ���������� [first2, last2) �����һ�γ���,�ø����Ķ�Ԫν�� p �Ƚ�Ԫ��
	template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
	ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, BinaryPredicate p)
	{
		find_end_dispatch(first1, last1, first2, last2, iterator_category(first1), iterator_category(first2), p);
	}


	//�ڷ�Χ [first, last) ��������Χ [s_first, s_last) �е��κ�Ԫ��,�� operator== �Ƚ�Ԫ��
	//����ָ��Χ [first, last) �е������Է�Χ [s_first; s_last) ��һ��Ԫ�ص��׸�Ԫ�ء����Ҳ�������Ԫ�أ��򷵻� last
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



	//�ڷ�Χ [first, last) ��������Χ [s_first, s_last) �е��κ�Ԫ��,�ø����Ķ�Ԫν�� p �Ƚ�Ԫ��
	//����ָ��Χ [first, last) �е������Է�Χ [s_first; s_last) ��һ��Ԫ�ص��׸�Ԫ�ء����Ҳ�������Ԫ�أ��򷵻� last
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

	//�ڷ�Χ [first, last) ������������̵ĵ�ͬԪ��,�� operator== �Ƚ�Ԫ��
	//����ָ���׶Ե�ͬԪ�ص��׸�Ԫ�صĵ�����,���Ҳ�������Ԫ�أ��򷵻� last
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

	//�ڷ�Χ [first, last) ������������̵ĵ�ͬԪ��,�ø����Ķ�Ԫν�� p �Ƚ�Ԫ��
	//����ָ���׶Ե�ͬԪ�ص��׸�Ԫ�صĵ�����,���Ҳ�������Ԫ�أ��򷵻� last
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

	//������Χ [first, last) ��Ԫ�������� [s_first, s_last) ���״γ���,Ԫ���� operator== �Ƚ�
	//����ָ��Χ�� [first, last) �׸������� [s_first, s_last) ��ʼ�ĵ����������Ҳ������������У��򷵻� last ��
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

	//������Χ [first, last) ��Ԫ�������� [s_first, s_last) ���״γ���,Ԫ���ø����Ķ�Ԫν�� p �Ƚ�
	//����ָ��Χ�� [first, last) �׸������� [s_first, s_last) ��ʼ�ĵ����������Ҳ������������У��򷵻� last ��
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

	//�ڷ�Χ [first, last) ������ count ����ͬԪ�ص����У�ÿ�������ڸ�����ֵ value, �� operator== �Ƚ�Ԫ��
	//����ָ��Χ [first, last) ���ҵ���������ʼ�ĵ����������Ҳ����������У��򷵻� last 
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

	//�ڷ�Χ [first, last) ������ count ����ͬԪ�ص����У�ÿ�������ڸ�����ֵ value, �ø����Ķ�Ԫν�� p �Ƚ�Ԫ��
	//����ָ��Χ [first, last) ���ҵ���������ʼ�ĵ����������Ҳ����������У��򷵻� last 
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


	//����Χ [first, last) �е��������� p ��Ԫ�ض����������в������Ԫ��ǰ�򷵻� true ���� [first, last) Ϊ���෵�� true
	template< class InputIt, class UnaryPredicate >
	bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p)
	{
		while (first != last && p(*first))
			++first;
		while (first != last && !(p(*first)))
			++first;
		return first == last;
	}

	//������Χ [first, last) �е�Ԫ�أ�ʹ��ν�� p ���䷵�� true ��Ԫ��ǰ��ν�� p ���䷵�� false ��Ԫ�ء����������˳��
	//����ָ��ڶ���Ԫ����Ԫ�صĵ�����
	template< class ForwardIt, class UnaryPredicate >
	ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
	{
		ForwardIt pre = mystl::find_if_not(first, last, p);
		if (pre == last) 
			return last;

		for (ForwardIt cur = std::next(pre); cur != last; ++cur) {//ǰ��ָ�뷨  next����pre���
			if (p(*cur)) {
				iter_swap(cur, pre);
				++pre;
			}
		}
		return pre;
	}

	//��� [first, last) �е�Ԫ���Ƿ��Բ���������,�� operator< �Ƚ�Ԫ��
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

	//��� [first, last) �е�Ԫ���Ƿ��Բ���������,�ø����Ķ�Ԫ�ȽϺ��� comp �Ƚ�Ԫ��
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

	//���鷶Χ [first, last) ����Ѱ��ʼ�� first ������Ԫ������������������Χ,�� operator< �Ƚ�Ԫ�ء�
	//����ʼ�� first ������Ԫ������������������Χ�������㷶Χ [first, it) ��������������� it 
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

	//���鷶Χ [first, last) ����Ѱ��ʼ�� first ������Ԫ������������������Χ,�ø����Ķ�Ԫ�ȽϺ��� comp �Ƚ�Ԫ��
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

	//����������Χ [first, last) �е�Ԫ�ء�����֤ά�����Ԫ�ص�˳��
	template< class RandomIt >
	void sort(RandomIt first, RandomIt last)
	{

	}


	template< class RandomIt, class Compare >
	void sort(RandomIt first, RandomIt last, Compare comp)
	{

	}

	//����Ԫ�أ�ʹ�÷�Χ [first, middle) ���з�Χ [first, last) ��������� middle - first ����СԪ�ء�
	//����֤������ȵ�Ԫ��˳�򡣷�Χ[middle, last) ��ʣ���Ԫ��˳��δָ��,�� operator< �Ƚ�Ԫ��
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

	//����������Χ [first, last) �е�Ԫ�ء���֤���ֵȼ�Ԫ�ص�˳��,�� operator< �Ƚ�Ԫ��
	template< class RandomIt >
	void stable_sort(RandomIt first, RandomIt last)
	{

	}

	//����������Χ [first, last) �е�Ԫ�ء���֤���ֵȼ�Ԫ�ص�˳��,�ø����ıȽϺ��� comp �Ƚ�Ԫ��
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
		while (len > 0)//ʹ��[first, first + len)��������ҿ�����
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

	//����ָ��Χ [first, last) ���׸���С�ڣ������ڻ���ڣ� value ��Ԫ�صĵ������������Ҳ�������Ԫ���򷵻� last 
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
		while (len > 0)//ʹ��[first, first + len)��������ҿ�����
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
		while (len > 0)//ʹ��[first, first + len)��������ҿ�����
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

	//����ָ��Χ [first, last) ���׸����� value ��Ԫ�صĵ������������Ҳ�������Ԫ���򷵻� last �����ö���ʵ�֣����Ե���ǰ���뱣֤����
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
		while (len > 0)//ʹ��[first, first + len)��������ҿ�����
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

	//���ȼ��� value ��Ԫ���Ƿ�����ڷ�Χ [first, last) ��
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

	//���ط�Χ [first, last) �к������еȼ��� value ��Ԫ�صķ�Χ
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

	//�鲢����������Χ [first1, last1) �� [first2, last2) ��ʼ�� d_first ��һ��������Χ��
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
