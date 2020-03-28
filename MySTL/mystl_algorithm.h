#pragma once
#ifndef STL_ALGORITHM
#define STL_ALGORITHM

#include "mystl_iterator.h"
#include "mystl_pair.h"

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
	//���׸���ƥ��ԡ������ṩ last2,����ָ�� first2 + (last1 - first1) ��
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
	BidirectionalIt1 find_end_dispatch(BidirectionalIt1 first1, BidirectionalIt1 last1, BidirectionalIt2 first2, BidirectionalIt2 last2,
		bidirectional_iterator_tag, bidirectional_iterator_tag)
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
		find_end_dispatch(first1, last1, first2, last2, iterator_category(first1), iterator_category(first2));
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
				if (P(*cur1, *cur2))
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
		while (first != last && !p(*first))
			++first;
		return first == last;
	}

	//������Χ [first, last) �е�Ԫ�أ�ʹ��ν�� p ���䷵�� true ��Ԫ��ǰ��ν�� p ���䷵�� false ��Ԫ�ء����������˳��
	//����ָ��ڶ���Ԫ����Ԫ�صĵ�����
	template< class ForwardIt, class UnaryPredicate >
	ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
	{
		auto pre = find_if_not(first, last, p);
		if (pre == last) 
			return last;

		for (ForwardIt cur = ++pre; cur != last; ++cur) {//ǰ��ָ�뷨
			if (p(*cur)) {
				iter_swap(cur, pre);
				++pre;
			}
		}
		return pre;
	}

}

#endif
