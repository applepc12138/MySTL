#pragma once
//�����ڴ�ķ������ͷ�

#ifndef STL_ALLOC
#define STL_ALLOC
//alloc��Ϊ��ģ����,���ֽ�Ϊ��λ�����ڴ�,��simple_alloc����ڲ�ʵ��
namespace mystl {
	class alloc {
	private:
		static const int ALIGN = 8;
		static const int MAXBYTES = 128;
		static const int NFREELISTS = MAXBYTES / ALIGN;

		//freelists�ڵ㶨��
		struct obj {
			obj *next;
		};

		static obj *freelist[NFREELISTS];

	private:
		static char *start_free;
		static char *end_free;
		static unsigned int heap_size;

	private:
		static size_t round_up(size_t bytes) {//��bytes�ϵ���8�ı���
			return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
		}

		static size_t freelist_index(size_t bytes) {
			return (((bytes)+ALIGN - 1) / ALIGN - 1);
		}

	private:
		//Ϊfreelist�����������,�������bytes�ѵ���Ϊ8�ı���
		//�˺�������ֵΪһ�������С,��allocate()ʹ��.ͬʱ,�������������freelist��Ӧ"��"��
		static void *refill(size_t bytes);
		//����ȡnobjs����СΪbytes�ֽڵ�����,�ڴ���йز�������������
		static char *chunk_alloc(size_t bytes, size_t& nobjs);


	public:
		static void *allocate(size_t bytes);//���ֽ�Ϊ��λ�����ڴ�
		static void deallocate(void *p, size_t bytes);//�ͷ�ָ��p��ָ����(�������������freelist��)
		static void *reallocate(void *p, size_t old_size);
	};
}
#endif // !STL_ALLOC

