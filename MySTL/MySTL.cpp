#include <iostream>
#include "mystl_allocator.h"
#include "mystl_construct.h"
#include "mystl_vector.h"
#include "mystl_list.h"
#include <string>
#include <vector>
#include <list>
#include <typeinfo>
#include "mystl_list.h"
#include "mystl_queue.h"

using std::cout;
using std::endl;
using std::ends;
using mystl::vector;
using mystl::list;
using mystl::queue;
using mystl::list_node;
using mystl::list_iterator;

template <typename T>
void output(T& container) {
	for (auto p = container.begin(); p != container.end(); ++p)
		cout << *p << ends;
	cout << endl;
}

int main()
{
/*	{
		vector<int> vec1(5);

		vec1.insert(vec1.begin(), 5);
		for (auto &p : vec1)
			cout << p << ends;

		cout << endl;

		std::vector<std::string> v{ "jhh","hehe", "heij", "fdf" };
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
	}
*/
	{
		list_node<int>* const p = new list_node<int>();//头指针
		list_node<int>* tmp = p;
		for (int i = 0; i < 20; ++i) {
			auto q = new list_node<int>();
			tmp->next = q;
			q->pre = tmp;
			tmp = (list_node<int>*)tmp->next;
			tmp->data = i;
		}
		list_iterator<int> iter(p);
		for (int i = 0; i < 20; ++i) {
			cout << *iter << ends;
			++iter;
		}
		cout << endl << "*****************************************************************" << endl;
		list<int> l;
		for (int i = 0; i < 20; ++i)
			l.push_back(i);
		cout << endl;
		cout << "l = ";
		output(l);
		cout << endl;
		l.pop_back();
		l.pop_front();
		output(l);
		cout << endl;
		l.push_front(-520);
		output(l);
		cout << endl;
		l.push_back(4);
		l.push_back(4);
		l.push_back(4);
		l.push_back(4);
		l.push_front(4);
		output(l);
		cout << endl;
		l.remove(4);
		output(l);
		cout << endl;
		cout << l.size() << endl;
		//l.clear();
		cout << l.size() << endl;
		cout << endl;

		list<int> l2;
		for (int i = 50; i < 60; ++i)
			l2.push_back(i);
		cout << endl;
		cout << "l2 = ";
		output(l2);
		list<int> l3(l), l4(l2);
		l.splice(l.begin(), l2);
		cout << "l = ";
		output(l);
		cout << endl << "l2 = ";
		output(l2);
		cout << endl;
		cout << "l3 = ";
		output(l3);
		cout << "l4 = ";
		output(l4);
		l3.merge(l4);
		cout << "l3 = ";
		output(l3);
		cout << "l4 = ";
		output(l4);
		cout << "l3.reverse() = ";
		l3.reverse();
		output(l3);
		cout << endl;

		while (!l3.empty()) {
			cout << l3.front() << ends;
			l3.pop_front();
		}
		cout << endl;
		cout << "l2 == l3 :  " << (l2 == l3) << endl;
	}

	{
		queue<int> q;
		for (int i = 0; i < 20; ++i)
			q.push(i);
		while (q.empty()) {
			cout << q.front() << ends;
			q.pop();
		}
		cout << endl;
		queue<int> q2;
		for (int i = 0; i < 20; ++i)
			q2.push(i);
		cout << "q == q2 : " << (q == q2) << endl;
		cout << "q < q2 : " << (q < q2) << endl;
	}

	return 0;
}