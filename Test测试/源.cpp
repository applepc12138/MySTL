#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <type_traits>

using namespace std;

class A {
public:
	int num = 0;
};

template <typename T>
void func1(T v) {
}

template <typename T>
void func2(T& v) {
	v.num = 5;
}
template <typename T>
void func3(T&& v) {
	T n = A{};
}

int main()
{
	A&& rref = A{};
	//func2(rref);//T被推断为A  v的类型为A&,引用一个类型为A&&的变量(对象)rref

	const A&& crref = A{};
	//func2(crref);//T被推断为const A

	func3(A{});//T被推断为A 

	A lval;
	//func3(lval);//T被推断为A&   v的类型为A&(A& &&折叠为A&)

	A& reflval = lval;
	//func3(reflval);//T被推断为A&    v的类型为A&

	const A& creflval = lval;
	//func3(creflval);//T被推断为const A&    v的类型为const A&   v.num类型为const int

	int&& irref = int{};//1.右值引用只能绑定即将消亡的对象  2.右值引用是变量,具有生存期,不是临时量
	int& ilref = irref;//左值引用可以绑定到右值引用所绑定的临时对象上  


	return 0;
}