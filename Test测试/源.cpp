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
	//func2(rref);//T���ƶ�ΪA  v������ΪA&,����һ������ΪA&&�ı���(����)rref

	const A&& crref = A{};
	//func2(crref);//T���ƶ�Ϊconst A

	func3(A{});//T���ƶ�ΪA 

	A lval;
	//func3(lval);//T���ƶ�ΪA&   v������ΪA&(A& &&�۵�ΪA&)

	A& reflval = lval;
	//func3(reflval);//T���ƶ�ΪA&    v������ΪA&

	const A& creflval = lval;
	//func3(creflval);//T���ƶ�Ϊconst A&    v������Ϊconst A&   v.num����Ϊconst int

	int&& irref = int{};//1.��ֵ����ֻ�ܰ󶨼��������Ķ���  2.��ֵ�����Ǳ���,����������,������ʱ��
	int& ilref = irref;//��ֵ���ÿ��԰󶨵���ֵ�������󶨵���ʱ������  


	return 0;
}