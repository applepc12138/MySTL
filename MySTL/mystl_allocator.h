#pragma once

#ifndef STL_ALLOCATOR
#define STL_ALLOCATOR

#include "mystl_alloc.h"
#include "mystl_construct.h"
//空间配置,以对象个数为单位
namespace mystl {
	template <typename T, typename Alloc>
	class simple_alloc {
	public:
		static T *allocate();
		static T *allocate(size_t n);
		static void deallocate(T *ptr);
		static void deallocate(T *ptr, size_t n);

	};
	template<typename T, typename Alloc>
	inline T * simple_alloc<T, Alloc>::allocate()
	{
		return (T*) Alloc::allocate(sizeof(T));
	}
	template<typename T, typename Alloc>
	inline T * simple_alloc<T, Alloc>::allocate(size_t n)
	{
		return (T*) Alloc::allocate(sizeof(T) * n);
	}
	template<typename T, typename Alloc>
	inline void simple_alloc<T, Alloc>::deallocate(T * ptr)
	{
		Alloc::deallocate(ptr, sizeof(T));
	}
	template<typename T, typename Alloc>
	inline void simple_alloc<T, Alloc>::deallocate(T * ptr, size_t n)
	{
		Alloc::deallocate(ptr, sizeof(T));
	}
}

#endif // !STL_ALLOCATOR

