#pragma once
#ifndef STL_TYPE_TRAITS
#define STL_TYPE_TRAITS


/*****************************************
type_traits<T> 用来判断指定类型是否是"简单类型"

*****************************************/

//用作编译时函数模板参数推导的空类型
namespace mystl {
	struct _true_type {};
	struct _false_type {};

	template <class T>
	struct type_traits {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _false_type has_trivail_default_constructor;
		typedef _false_type has_trivail_copy_constructor;
		typedef _false_type has_trivail_assignment_operator;
		typedef _false_type has_truvail_destructor;
		typedef _false_type is_POD_type;
	};
	template<>
	struct type_traits<char> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<signed char> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<unsigned char> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<short> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<unsigned short> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};

	template<>
	struct type_traits<int> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<unsigned int> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<long> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<unsigned long> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<double> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<float> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	template<>
	struct type_traits<long double> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};
	//所有类型的指针都可以看成是POD:Paint Old Data,类型参数T可为const或非const
	template<class T>
	struct type_traits<T*> {
		typedef _true_type this_dummy_member_must_be_first;
		typedef _true_type has_trivail_default_constructor;
		typedef _true_type has_trivail_copy_constructor;
		typedef _true_type has_trivail_assignment_operator;
		typedef _true_type has_truvail_destructor;
		typedef _true_type is_POD_type;
	};

}

#endif

