#pragma once
#ifndef STL_QUEUE
#define STL_QUEUE
#include "mystl_list.h"

namespace mystl {

	template <typename T, typename Container = list<T>>
	class queue {
		friend bool operator== <T, Container> (const queue& x, const queue& y);
		friend bool operator< <T, Container> (const queue& x, const queue& y);

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
}

#endif // !STL_QUEUE


