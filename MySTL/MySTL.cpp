// MySTL.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>
#include "mystl_allocator.h"
#include "mystl_construct.h"
#include <vector>

using std::cout;
using std::endl;
using namespace mystl;

int main()
{
	int * nums = simple_alloc<int, alloc>::allocate(20);
	int *tmp = nums;
	for (int i = 0; i < 20; ++i)
		construct(tmp++, 520);
	for (int j = 0; j < 20; ++j)
		cout << nums[j] << std::ends;
    return 0;
}

