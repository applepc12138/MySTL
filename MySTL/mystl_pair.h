#pragma once
#ifndef STL_PAIR
#define STL_PAIR
namespace mystl {
	template <typename T1, typename T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

	public:
		pair() : first(first_type()), second(second_type()) {}
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
		pair(const pair& p) : first(p.first), second(p.second) {}


	};

	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return x.first == y.first && x.second == y.second;
	}

	template <class T1, class T2>
	inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y) {
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}

	template <class T1, class T2>
	inline pair<T1, T2> make_pair(const T1& x, const T2& y) {
		return pair<T1, T2>(x, y);
	}

}

#endif
