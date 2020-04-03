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
	//��ʾT
	cout << "T=	"
		<< type_id_with_cvr<T>().pretty_name()
		<< "\n";
	//��ʾ����v����
	cout << "v=	"
		<< type_id_with_cvr<decltype(v)>().pretty_name()
		<< "\n";
}



int main()
{
	A&& rref = A{};
	func2(rref);//T���ƶ�ΪA  v������ΪA&,����һ������ΪA&&�ı���(����)rref

	const A&& crref = A{};
	//func2(crref);//T���ƶ�Ϊconst A

	func3(A{});//T���ƶ�ΪA 
	func4(A{});

	A lval;
	//func3(lval);//T���ƶ�ΪA&   v������ΪA&(A& &&�۵�ΪA&)
	func4(lval);

	A& reflval = lval;
	func3(reflval);//T���ƶ�ΪA&    v������ΪA&
	func4(reflval);

	//rref��ȻΪ��ֵ����,������ֵ�����Ǳ���,��ȻΪ��ֵ.
	func3(rref);//T���ƶ�ΪA&     v������ΪA&
	func4(rref);


	const A& creflval = lval;
	//func3(creflval);//T���ƶ�Ϊconst A&    v������Ϊconst A&   v.num����Ϊconst int

	int&& irref = int{};//1.��ֵ����ֻ�ܰ󶨼��������Ķ���  2.��ֵ�����Ǳ���,����������,������ʱ��
	int& ilref = irref;//��ֵ���ÿ��԰󶨵���ֵ�������󶨵���ʱ������  


	return 0;
}