#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::ends;
using std::vector;
using std::string;

int main()
{
	vector<int> vec1{ 4,131,4,23,5,3,5,4,434,34,5432,232,3,5,3,4,4,24,5,23,45 };
	vector<int> vec2(30);
	copy(vec1.begin(), vec1.end(), vec2.begin());
	for (auto &p : vec2)
		cout << p << ends;

	//func1("fdfd");
	func2();

    return 0;
}

void func1(string s) {
	cout << "s = " << s << endl;
	cout << "未声明就调用" << endl;
}


