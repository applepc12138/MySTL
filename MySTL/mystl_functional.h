#pragma once
#ifndef STL_FUNCTIONAL
#define STL_FUNCTIONAL

namespace mystl {

	// ����һԪ�����Ĳ����ͱ�ͷ���ֵ�ͱ�
	//c++11����
	template <class Arg, class Result>
	struct unarg_function
	{
		typedef Arg       argument_type;
		typedef Result    result_type;
	};

	// �����Ԫ�����Ĳ����ͱ�ķ���ֵ�ͱ�
	//c++11����
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1      first_argument_type;
		typedef Arg2      second_argument_type;
		typedef Result    result_type;
	};

	// �������󣺼ӷ�
	template <class T>
	struct plus :public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const { return x + y; }
	};

	// �������󣺼���
	template <class T>
	struct minus :public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const { return x - y; }
	};

	// �������󣺳˷�
	template <class T>
	struct multiplies :public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const { return x * y; }
	};

	// �������󣺳���
	template <class T>
	struct divides :public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const { return x / y; }
	};

	// ��������ģȡ
	template <class T>
	struct modulus :public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const { return x % y; }
	};

	// �������󣺷�
	template <class T>
	struct negate :public unarg_function<T, T>
	{
		T operator()(const T& x) const { return -x; }
	};

	// �ӷ���֤ͬԪ��
	template <class T>
	T identity_element(plus<T>) { return T(0); }

	// �˷���֤ͬԪ��
	template <class T>
	T identity_element(multiplies<T>) { return T(1); }

	// �������󣺵���
	template <class T>
	struct equal_to :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x == y; }
	};

	// �������󣺲�����
	template <class T>
	struct not_equal_to :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x != y; }
	};

	// �������󣺴���
	template <class T>
	struct greater :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x > y; }
	};

	// ��������С��
	template <class T>
	struct less :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x < y; }
	};

	// �������󣺴��ڵ���
	template <class T>
	struct greater_equal :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x >= y; }
	};

	// ��������С�ڵ���
	template <class T>
	struct less_equal :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x <= y; }
	};

	// ���������߼���
	template <class T>
	struct logical_and :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x && y; }
	};

	// ���������߼���
	template <class T>
	struct logical_or :public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const { return x || y; }
	};

	// ���������߼���
	template <class T>
	struct logical_not :public unarg_function<T, bool>
	{
		bool operator()(const T& x) const { return !x; }
	};

	// ֤ͬ����������ı�Ԫ�أ����ر���
	template <class T>
	struct identity :public unarg_function<T, bool>
	{
		const T& operator()(const T& x) const { return x; }
	};


}

#endif
