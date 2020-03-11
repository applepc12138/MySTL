#pragma once
//负责内存的分配与释放

#ifndef STL_ALLOC
#define STL_ALLOC
//alloc类为非模板类,以字节为单位分配内存,是simple_alloc类的内部实现
namespace mystl {
	class alloc {
	private:
		static const int ALIGN = 8;
		static const int MAXBYTES = 128;
		static const int NFREELISTS = MAXBYTES / ALIGN;

		//freelists节点定义
		struct obj {
			obj *next;
		};

		static obj *freelist[NFREELISTS];

	private:
		static char *start_free;
		static char *end_free;
		static unsigned int heap_size;

	private:
		static size_t round_up(size_t bytes) {//将bytes上调至8的倍数
			return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
		}

		static size_t freelist_index(size_t bytes) {
			return (((bytes)+ALIGN - 1) / ALIGN - 1);
		}

	private:
		//为freelist重新填充区块,假设参数bytes已调整为8的倍数
		//此函数返回值为一个区块大小,供allocate()使用.同时,将其余区块接至freelist相应"洞"中
		static void *refill(size_t bytes);
		//尝试取nobjs个大小为bytes字节的区块,内存池有关操作经由它管理
		static char *chunk_alloc(size_t bytes, size_t& nobjs);


	public:
		static void *allocate(size_t bytes);//以字节为单位分配内存
		static void deallocate(void *p, size_t bytes);//释放指针p所指区块(将其重新添加至freelist中)
		static void *reallocate(void *p, size_t old_size);
	};
}
#endif // !STL_ALLOC

