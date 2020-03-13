#include <iostream>
#include "mystl_allocator.h"
#include "mystl_construct.h"
#include "mystl_vector.h"
#include <string>
#include <vector>
#include "mystl_iterator.h"
#include <typeinfo>

using std::cout;
using std::endl;
using std::ends;
//using namespace mystl;
using mystl::vector;

int main()
{
	vector<int> vec1(5);

	vec1.insert(vec1.begin(), 5);
	for (auto &p : vec1)
		cout << p << ends;
	
	cout << endl;

	std::vector<std::string> v{ "jhh","hehe", "heij", "fdf"};
	vector<std::string> vec2(v.begin(), v.end());
	for (auto &p : vec2)
		cout << p << ends;

	cout << endl;

	std::vector<int> vint{ 2,3,4,5,6,3,4,34,5342 };
	vector<int> vec3(vint.begin(), vint.end());
	vec3.insert(vec3.begin(), vint.begin(), vint.end());
	for (auto &p : vec3)
		cout << p << ends;

	cout << endl;

	vector<std::string> vec4(50);
	mystl::copy(v.begin(), v.end(), vec4.begin());
	for (auto &p : vec4)
		cout << p << ends;

	return 0;
}

