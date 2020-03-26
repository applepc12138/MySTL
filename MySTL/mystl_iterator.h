#pragma once
#ifndef STL_ITERATOR
#define STL_ITERATOR
#include <iterator>

namespace mystl 
{

	//struct input_iterator_tag {};
	//struct output_iterator_tag {};
	//struct forward_iterator_tag : public input_iterator_tag {};
	//struct bidirectional_iterator_tag : public forward_iterator_tag {};
	//struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	typedef std::input_iterator_tag			 input_iterator_tag;
	typedef std::output_iterator_tag		 output_iterator_tag;
	typedef std::forward_iterator_tag		 forward_iterator_tag;
	typedef std::bidirectional_iterator_tag	 bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag  random_access_iterator_tag;


	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T * , class Reference = T & >
		struct iterator {
		typedef Category  iterator_category;
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef const T*                   pointer;
		typedef const T&                   reference;
	};


	template <typename Iterator>
	typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator& iter) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	template <typename Iterator>
	typename iterator_traits<Iterator>::difference_type*
		difference_type(const Iterator& iter) {
		return static_cast < typename iterator_traits<Iterator>::difference_type*>(0);
	}

	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}
	

	template <typename InputIterator, typename Distance>
	inline void _advance(InputIterator& i, Distance n, input_iterator_tag) {
		while (n--)
			++i;
	}
	template <typename bidirectional_iterator_tag, typename Distance>
	inline void _advance(bidirectional_iterator_tag& i, Distance n, bidirectional_iterator_tag) {
		if (n > 0)
			while (n--)
				++i;
		else
			while (n++)
				--i;
	}
	template <typename RandomAccessIterator, typename Distance>
	inline void _advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
		return i += n;
	}
	template <typename InputIterator, typename Distance>
	inline void advance(InputIterator& i, Distance n) {
		_advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
	}

	template <typename InputIterator, typename Distance>
	inline void _distance(InputIterator first, InputIterator last, Distance& n, input_iterator_tag) {
		while (first != last) {
			++first;
			++n;
		}
	}

	template <typename RandomAccessIterator, typename Distance>
	inline void _distance(RandomAccessIterator first, RandomAccessIterator last, Distance& n, random_access_iterator_tag) {
		n = last - first;
	}

	template <typename InputIterator, typename Distance>
	inline void distance(InputIterator first, InputIterator last, Distance& n) {
		_distance(first, last, n, typename iterator_traits<InputIterator>::iterator_category());
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
		typename iterator_traits<InputIterator>::difference_type n;
		typedef typename iterator_traits<InputIterator>::difference_type diff_type;
		_distance(first, last, n, diff_type());
		return n;
			
	}

	template <typename Container>
	struct insert_iterator {
	public:
		typedef insert_iterator<container> self;

		typedef output_iterator_tag iterator_category;
		typedef void value_type;
		typedef void pointer;
		typedef void reference;
		typedef void difference_type;

	private:
		Container * container;//绑定插入元素容器的指针
	public:
		insert_iterator(Container& c) : container(&c) {}
		self& operator=(typename Container::value_type& v) {
			container->insert(v);
			return *this;
		}

		self& operator*() { return *this; }
		self& operator++() { return *this; }
		self& operator++(int) { return *this; }
	};

	template <typename Container>
	struct front_insert_iterator {
	public:
		typedef front_insert_iterator<container> self;

		typedef output_iterator_tag iterator_category;
		typedef void value_type;
		typedef void pointer;
		typedef void reference;
		typedef void difference_type;

	private:
		Container * container;//绑定插入元素的指针
	public:
		front_insert_iterator(Container& c) : container(&c) {}
		self& operator=(typename Container::value_type& v) {
			container->push_front(v);
			return *this;
		}

		self& operator*() { return *this; }
		self& operator++() { return *this; }
		self& operator++(int) { return *this; }
	};
	template <typename Container>
	struct back_insert_iterator {
	public:
		typedef back_insert_iterator<container> self;

		typedef output_iterator_tag iterator_category;
		typedef void value_type;
		typedef void pointer;
		typedef void reference;
		typedef void difference_type;

	private:
		Container * container;//绑定插入元素的指针
	public:
		insert_iterator(container& c) : container(&c) {}
		self& operator=(typename Container::value_type& v) {
			container->push_back(v);
			return *this;
		}

		self& operator*() { return *this; }
		self& operator++() { return *this; }
		self& operator++(int) { return *this; }
	};

	template <typename Iterator>
	struct reverse_iterator {
	private:
		Iterator current;
	public:
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef	typename iterator_traits<Iterator>::difference_type difference_type;
		typedef	typename iterator_traits<Iterator>::value_type value_type;
		typedef	typename iterator_traits<Iterator>::pointer pointer;
		typedef	typename iterator_traits<Iterator>::reference reference;

		typedef reverse_iterator<Iterator> self;
		typedef Iterator iterator_type;
	public:
		explicit reverse_iterator(iterator_type iter) : current(iter) {}
		reverse_iterator(const self& x) : current(x.current) {}
	public:
		iterator_type base()const { return current; }

		reference operator*()const {
			iterator_type tmp = current;//this.current 其中this类型为 const self*const currentb被赋予const属性
			return *--tmp;
		}
		pointer operator->()const { return &(operator*()); }
		self& operator++() {
			--current;
			return *this;
		}
		self operator++(int) {
			iterator_type tmp = current;
			--current;
			return reverse_iterator(tmp);
		}
		self& operator--() {
			++current;
			return *this;
		}
		self operator--(int) {
			iterator_type tmp = current;
			++current;
			return reverse_iterator(tmp);
		}
		self& operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		self operator+(difference_type n)const {
			return current - n;
		}
		self& operator-=(difference_type n) {
			current += n;
			return *this;
		}
		self operator-(difference_type n)const {
			return current + n;
		}
	};

	// 重载比较操作符
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() < lhs.base();
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return rhs < lhs;
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs < rhs);
	}
}


#endif // !STL_ITERATOR
