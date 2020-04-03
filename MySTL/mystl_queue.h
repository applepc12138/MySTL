#pragma once
#ifndef STL_QUEUE
#define STL_QUEUE
#include "mystl_list.h"
#include "mystl_vector.h"
#include "mystl_iterator.h"
#include <functional>

namespace mystl {

	template <typename T, typename Container = list<T>>
	class queue {
		friend bool operator== <T, Container> (const queue<T, Container>& x, const queue<T, Container>& y);
		friend bool operator< <T, Container> (const queue<T, Container>& x, const queue<T, Container>& y);
	private:
		Container c;
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::difference_type  difference_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	public:
		queue() {}
		~queue() {}

		size_type size()const { return c.size(); }
		bool empty()const { return c.empty(); }

		reference front() { return c.front(); }
		const_reference front()const { return c.front(); }
		reference back() { return c.back(); }
		const_reference back()const { return c.back(); }
		
		void push(const value_type& v) { c.push_back(v); }
		void pop() { c.pop_front(); }
	};

	template <typename T, typename Container /*= list<T>*/>
	bool operator==(const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return x.c == y.c;
	}

	template <typename T, typename Container /*= list<T>*/>
	bool operator<(const queue<T, Container>& x, const queue<T, Container>& y)
	{
		return x.c < y.c;
	}


/*************************************************************************************************/

	//firstΪָ��������һ��Ԫ�ص�����, holeIndexΪ���������һ��Ԫ��֮�������(Ҫ���Ԫ������)
	//topIndexΪ������������˵�Ԫ������,valueΪ��Ҫ��ӵ�Ԫ��
	template <class RandomAccessIterator, class Distance, class T, class Compare>
	void _push_heap(RandomAccessIterator first, Distance holeIndex,
		Distance topIndex, T value, Compare comp) {
		Distance parent = (holeIndex - 1) / 2;
		while (holeIndex > topIndex && comp(*(first + parent), value)) {//����
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			parent = (holeIndex - 1) / 2;
		}
		*(first + holeIndex) = value;
	}

	//����λ��λ�� last-1 ��Ԫ�ص���Χ [first, last-1) �������������
	template <class RandomAccessIterator, class Compare>
	inline void push_heap(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<typename iterator_traits<RandomAccessIterator>::value_type>()) {
		typedef typename iterator_traits<RandomAccessIterator>::difference_type  Distance;
		typedef typename iterator_traits<RandomAccessIterator>::value_type Value_type;
		_push_heap(first, Distance((last - first) - 1), Distance(0), Value_type(*(last - 1)), comp);
	}

	//
	template <class RandomAccessIterator, class Distance, class T, class Compare>
	void _adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance len, T value, Compare comp) {//holeIndexΪ��Ҫ�µ���Ԫ������,lenΪ�����鳤��
		Distance topIndex = holeIndex;
		Distance secondChild = 2 * holeIndex + 2;//���µ��ڵ�����ӽڵ�����
		while (secondChild < len) {//�µ�
			if (comp(*(first + secondChild), *(first + (secondChild - 1))))
				secondChild--;
			*(first + holeIndex) = *(first + secondChild);
			holeIndex = secondChild;
			secondChild = 2 * (secondChild + 1);
		}
		if (secondChild == len) {
			*(first + holeIndex) = *(first + (secondChild - 1));
			holeIndex = secondChild - 1;
		}
		_push_heap(first, holeIndex, topIndex, value, comp);
	}

	template <class RandomAccessIterator, class T, class Compare, class Distance>
	inline void _pop_heap(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator result, T value, Compare comp,
		Distance*) {
		*result = *first;//���õ�������β
		_adjust_heap(first, Distance(0), Distance(last - first), value, comp);
	}

	//������λ�� first ����λ�� last-1 ��ֵ�������ӷ�Χ [first, last-1) ���±�Ϊ��
	//��ӵ�дӷ�Χ [first, last) ������Ķ��Ƴ��׸�Ԫ�ص�Ч��
	template <class RandomAccessIterator, class Compare>
	inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<typename iterator_traits<RandomAccessIterator>::value_type>()) {
		typedef typename iterator_traits<RandomAccessIterator>::difference_type  Distance;
		typedef typename iterator_traits<RandomAccessIterator>::value_type Value_type;
		_pop_heap(first, last - 1, last - 1, Value_type(*(last - 1)), comp, (Distance*)(0));
	}

	template <class RandomAccessIterator, class Compare>
	inline void make_heap(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<typename iterator_traits<RandomAccessIterator>::value_type>()) {
		typedef typename iterator_traits<RandomAccessIterator>::difference_type  Distance;
		typedef typename iterator_traits<RandomAccessIterator>::value_type Value_type;
		if (last - first < 2) 
			return;
		Distance len = last - first;
		Distance parent = (len - 2) / 2;

		while (true) {
			_adjust_heap(first, parent, len, Value_type(*(first + parent)), comp);
			if (parent == 0) return;
			parent--;
		}
	}

	template <class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
		Compare comp = std::less<typename iterator_traits<RandomAccessIterator>::value_type>()) {
		while (last - first > 1) 
			pop_heap(first, last--, comp);
	}                          

	template <typename T, typename Container = vector<T>, typename Comp = std::less<T>>
	class priority_queue {
	private:
		Container c;
		Comp comp;
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	public:
		priority_queue() = default;
		template <typename InputIterator>
		priority_queue(InputIterator first, InputIterator last) : c(first, last) {
			mystl::make_heap(c.begin(), c.end(), comp);
		}
		bool empty()const { return c.empty(); }
		size_type size()const { return c.size(); }
		const_reference top()const { return c.front(); }
		void push(const value_type& x) {
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		void pop() {
			mystl::pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
	};

}

#endif // !STL_QUEUE


