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
#include "mystl_hashtable.h"
#include "mystl_hashset.h"
#include "mystl_hashmap.h"
#include "mystl_algorithm.h"

//#include <boost/type_index.hpp>
//using boost::typeindex::type_id_with_cvr;

using std::cout;
using std::endl;
using std::ends;
using mystl::vector;
using mystl::list;
using mystl::queue;
using mystl::priority_queue;
using mystl::list_node;
using mystl::list_iterator;
using mystl::hashtable;
using mystl::hash_set;
using mystl::hash_map;
using mystl::hash_multimap;

template <typename T>
void output(T& container) {
	cout << endl << "/*****************output*******************/" << endl;
	for (auto p = container.begin(); p != container.end(); ++p)
		cout << *p << ends;
	cout << endl << "/*******************end********************/" << endl;
}

struct hashint {
	size_t operator()(int i)const {
		return i;
	}
};

struct identityint {
	int operator()(int i)const {
		return i;
	}
};

struct equalint
{
	bool operator()(const int a, const int b)const {
		return a == b;
	}
};

int main()
{
	//vector
	{
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

		vector<std::string> vec5{ "heh", "emoji", "c++", "hah", "hello" };
		output(vec5);
		cout << vec5.front() << ends << vec5.back() << ends << vec5.size() << endl;
		vector<std::string> vec6;
		vec6 = vec5;
		output(vec6);

		vec6.emplace_back("show");
		output(vec6);
		cout << vec6.front() << ends << vec6.back() << ends << vec6.size() << endl;

		//vec6.emplace(vec6.cbegin(), std::string("come"));
		output(vec6);
		cout << vec6.front() << ends << vec6.back() << ends << vec6.size() << endl;

	}


	//list
	{
		cout << endl << "list:" << endl;
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
		l3.erase(l3.begin(), l3.end());
		output(l3);
		cout << endl;

		while (!l3.empty()) {
			cout << l3.front() << ends;
			l3.pop_front();
		}
		cout << endl;
		cout << "l2 == l3 :  " << (l2 == l3) << endl;

		cout << endl << " end list" << endl;
	}

	//queue
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

	//priority_queue
	{
		int nums[10]{ 1,2,3,4,5,67,87,8,520,5 };
		priority_queue<int> q(std::begin(nums), std::end(nums));
		cout << q.top() << endl;
		while (!q.empty()) {
			cout << q.top() << ends;
			q.pop();
		}
		cout << endl;
	}

	//hashtable
	{
		hashtable<int, int, hashint, identityint, equalint> ht;
		ht.insert_unique(520);
		ht.insert_unique(520);
		ht.insert_unique(520);
		ht.insert_equal(520);
		ht.insert_equal(520);
		ht.insert_equal(520);
		for (int i = 0; i < 60; ++i)
			ht.insert_equal(i);
		cout << *ht.begin() << endl;
		cout << "size = " << ht.size() << endl;
		cout << ht.bucket_count() << endl;
	}

	//hashset
	{
		hash_set<std::string> hs1;
		std::vector<std::string> v{ "gd","ojfs","hahha","haha", "hehe", "world", "hello" };
		hs1.insert(v.begin(), v.end());
		cout << "hs1.size() : " << hs1.size() << endl;
		cout << "hs1.find(ojfs) : " << *hs1.find(std::string("ojfs"));
		cout << "hs1.find(hello) : " << *hs1.find("hello");
		cout << "hs1.find(hahe) : " << (hs1.find("hahe") == hs1.end());

	}

	//hashmap
	{
		cout << endl;
		hash_map<std::string, int> hm1
			;
		hm1["hello"] = 2520;
		hm1["hello"] = 5220;
		hm1["hllo"] = 5520;
		hm1["hell"] = 52;
		hm1["helo"] = 502;
		hm1["ello"] = 205;
		hm1["world"] = 250;
		hm1["orld"] = 52;
		hm1["wrld"] = 20;
		hm1["wold"] = 50;

		cout << "first : " <<(hm1.find("hello"))->first << " second : " << (hm1.find("hello"))->second << endl;
		cout << "hm1.size : " << hm1.size() << endl;
		auto p = hm1.equal_range("hello");//p返回两个迭代器(迭代器指向value_type类型)
		auto f = p.first;
		auto l = p.second;
		cout << "hm1.equal_range : " << endl;
		cout << "f->first : " << f->first << "   f->second : " << f->second << endl;
		cout << " l->first : " << l->first << "    l->second : " << l->second << endl;
		hm1.erase("hello");
		cout << "hm1.find(hello) : " << (hm1.find("hello") == hm1.end()) << endl;

		hash_multimap<std::string, int> hmm1;
		cout << "***********************" << endl;
		hmm1.insert(hm1.begin(), hm1.end());
		for(int i = 0; i < 10; ++i)
			hmm1.insert(*hm1.begin());
		cout << "hmm1.size() : " << hmm1.size() << endl;
		cout << "hmm1.bucket_count : " << hmm1.bucket_count() << endl;
		cout << "hmm1.elems_in_bucket(20) : " << hmm1.elems_in_bucket(20) << endl;
	}



	{
		std::vector<int> tmp{ 34,5,65,5,6,58,9,8,7,6,0,2,3,4,2,1,4,15,5,3,15,31,1,3,4,4,5,6,376,23,5,4,23,24,5,56 };
		vector<int> nums(tmp.begin(), tmp.end());
		output(nums);
		auto p = [](const auto& i)->bool {return i > 50; };
		cout << mystl::is_partitioned(nums.begin(), nums.end(), p) << endl;
		mystl::partition(nums.begin(), nums.end(), p);
		output(nums);
		cout << mystl::is_partitioned(nums.begin(), nums.end(), p) << endl;

		cout << *mystl::is_sorted_until(nums.begin(), nums.end()) << endl;
		cout << "partion_sort : ";
		mystl::partial_sort(nums.begin(), nums.begin() + 15, nums.end());
		output(nums);

	}

	return 0;
}