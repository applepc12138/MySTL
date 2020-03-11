#include "mystl_alloc.h"
#include <cstdlib>

namespace mystl {
	alloc::obj *alloc::freelist[NFREELISTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char *alloc::start_free = nullptr;
	char *alloc::end_free = nullptr;
	unsigned int alloc::heap_size = 0;

	void * alloc::refill(size_t bytes)
	{
		size_t nobjs = 20;
		char *chunk = chunk_alloc(bytes, nobjs);
		if (nobjs == 1) 
			return chunk;

		size_t hole = freelist_index(bytes);
		freelist[hole] = (obj*)(chunk + bytes);
		obj *nextnode = freelist[hole];
		for (int i = 1; i < nobjs - 1; ++i) {
			nextnode->next = (obj*)((char*)nextnode + bytes);//注意nextnode需要强转为char*
			nextnode = nextnode->next;
		}
		nextnode->next = nullptr;
		return chunk;
	}

	char * alloc::chunk_alloc(size_t bytes, size_t & nobjs)
	{
		size_t total_bytes = bytes * nobjs;
		size_t left_bytes = end_free - start_free;
		char *res = nullptr;
		if (left_bytes >= total_bytes) {//内存池所剩空间完全满足需求
			res = start_free;
			start_free += total_bytes;
			return res;
		}
		else if (left_bytes >= bytes) {//满足部分需求
			nobjs = left_bytes / bytes;
			res = start_free;
			start_free += nobjs * bytes;
			return res;
		}
		else {//内存池剩余空间连一个区块的大小多无法提供
			if (left_bytes > 0) {//将内存池中剩余空间分配给适当freelist节点
				size_t hole = freelist_index(left_bytes);
				((obj *)start_free)->next = freelist[hole];
				freelist[hole] = (obj *)start_free;
			}
			size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
			start_free = (char *)malloc(bytes_to_get);
			if (!start_free) {//申请堆空间失败
				obj *my_free_list = nullptr;
				obj *p = nullptr;
				for (int i = bytes; i <= MAXBYTES; i += ALIGN) {
					my_free_list = freelist[freelist_index(i)];
					p = my_free_list;
					if (p != nullptr) {
						my_free_list = p->next;
						start_free = (char *)p;
						end_free = start_free + i;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end_free = 0;
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}
	}

	void * alloc::allocate(size_t bytes)
	{
		if (bytes > (size_t)MAXBYTES)//大于128字节?采用malloc分配 
			return malloc(bytes);

		bytes = round_up(bytes);
		size_t hole = freelist_index(bytes);
		obj *res = freelist[hole];
		if (res != nullptr) {
			freelist[hole] = res->next;
			return res;
		}
		return refill(bytes);
	}

	void alloc::deallocate(void * p, size_t bytes)
	{
		if (bytes > (size_t)MAXBYTES)
			free(p);
		else {
			bytes = round_up(bytes);
			obj *tmp = (obj*)p;
			size_t hole = freelist_index(bytes);
			tmp->next = freelist[hole];
			freelist[hole] = tmp;
		}
	}

	void * alloc::reallocate(void * p, size_t old_size)
	{
		return nullptr;
	}
}
