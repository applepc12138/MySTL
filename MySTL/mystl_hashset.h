#pragma once
#ifndef STL_HASHSET
#define STL_HASHSET
#include <functional>
#include "mystl_allocator.h"
#include "mystl_hashtable.h"

namespace mystl {

	template <class T>
	struct identity {//ÒÑ·ÏÆú
		const T& operator()(const T& x) const { return x; }
	};

	template <typename Value, typename HashFunc = std::hash<Value>, 
		typename EqualKey = std::equal_to<Value>, typename Alloc = simple_alloc<Value, alloc>>
	class hash_set {
	private:
		typedef hashtable<Value, Value, HashFcn, identity<Value>,
			EqualKey, Alloc> ht;
		ht rep;

	public:
		typedef typename ht::key_type key_type;
		typedef typename ht::value_type value_type;
		typedef typename ht::hasher hasher;
		typedef typename ht::key_equal key_equal;

		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::const_pointer pointer;//?
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::const_reference reference;//?
		typedef typename ht::const_reference const_reference;

		typedef typename ht::const_iterator iterator;
		typedef typename ht::const_iterator const_iterator;

		hasher hash_funct() const { return rep.hash_funct(); }
		key_equal key_eq() const { return rep.key_eq(); }

	public:
		hash_set() : rep(100, hasher(), key_equal()) {}
		explicit hash_set(size_type n) : rep(n, hasher(), key_equal()) {}
		hash_set(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
		hash_set(size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {}
		template <class InputIterator>
		hash_set(InputIterator f, InputIterator l)
			: rep(100, hasher(), key_equal()) {
			rep.insert_unique(f, l);
		}
		template <class InputIterator>
		hash_set(InputIterator f, InputIterator l, size_type n)
			: rep(n, hasher(), key_equal()) {
			rep.insert_unique(f, l);
		}
		template <class InputIterator>
		hash_set(InputIterator f, InputIterator l, size_type n,
			const hasher& hf)
			: rep(n, hf, key_equal()) {
			rep.insert_unique(f, l);
		}
		template <class InputIterator>
		hash_set(InputIterator f, InputIterator l, size_type n,
			const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {
			rep.insert_unique(f, l);
		}
	};

}

#endif
