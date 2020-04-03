#include <iostream>
#include <vector>
#include <string>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

class A {
public:
	int num = 0;
};

template <typename T>
void func1(T v) {
}

template <typename T>
void func2(T& v) {
	T type;
	v.num = 5;
}
template <typename T>
void func3(T&& v) {
	A a;
	T n = a;
}


template <typename T>
void func4(T&& v) {
	//显示T
	cout << "T=	"
		<< type_id_with_cvr<T>().pretty_name()
		<< "\n";
	//显示参数v类型
	cout << "v=	"
		<< type_id_with_cvr<decltype(v)>().pretty_name()
		<< "\n";
}



int main()
{
	A&& rref = A{};
	func2(rref);//T被推断为A  v的类型为A&,引用一个类型为A&&的变量(对象)rref

	const A&& crref = A{};
	//func2(crref);//T被推断为const A

	func3(A{});//T被推断为A 
	func4(A{});

	A lval;
	//func3(lval);//T被推断为A&   v的类型为A&(A& &&折叠为A&)
	func4(lval);

	A& reflval = lval;
	func3(reflval);//T被推断为A&    v的类型为A&
	func4(reflval);

	//rref虽然为右值引用,但是右值引用是变量,仍然为左值.
	func3(rref);//T被推断为A&     v的类型为A&
	func4(rref);


	const A& creflval = lval;
	//func3(creflval);//T被推断为const A&    v的类型为const A&   v.num类型为const int

	int&& irref = int{};//1.右值引用只能绑定即将消亡的对象  2.右值引用是变量,具有生存期,不是临时量
	int& ilref = irref;//左值引用可以绑定到右值引用所绑定的临时对象上  


	return 0;
}