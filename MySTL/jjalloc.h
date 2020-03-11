#pragma once
#ifndef JJALLOC
#define JJALLOC

#include <new>
#include <cstddef>
#include <cstdlib>
#include <iostream>

namespace JJ
{
	template <class T>
	inline T* _allocate(ptrdiff_t size, T*) {
		set_new_handler(0);
		T* temp = (T*)::operator new((size_t)(sizeof(T) * size));
		if (temp)
			return tmep;
		std::cout << "oom" << std::endl;
		exit(1);
	}

	template <class T>
	inline void _deallocate(T* buf) {
		::operator delete(buf);
	}

	template <class T1, class T2>
	inline void _construct(T1* p, const T2& value) {
		new(p) T1(value);//在p所指向的内存调用T1类型的相应构造函数
	}

	template <class T> 
	void _destroy(T* p) {
		p->~T();
	}

	template <class T>
	class allocater {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		pointer allocate(size_type n) {
			return _allocate(n, (pointer)0);
		}

		void deallocate(pointer p) {
			_deallocate(p);
		}

		void construct(pointer p, const T& value) {
			_construct(p, value);
		}

		void destroy(pointer p) {
			_destroy(p);
		}
	};
	
}

#endif // JJALLOC

