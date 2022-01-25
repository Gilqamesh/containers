#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

namespace ft
{

// iterator_traits
struct input_iterator_tag	{ };
struct output_iterator_tag	{ };
struct forward_iterator_tag			: public input_iterator_tag			{ };
struct bidirectional_iterator_tag	: public forward_iterator_tag		{ };
struct random_access_iterator_tag	: public bidirectional_iterator_tag	{ };

template <typename Iter>
struct iterator_traits
{
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template <typename T>
struct iterator_traits<T*>
{
	typedef std::ptrdiff_t				difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <typename T>
struct iterator_traits<const T*>
{
	typedef std::ptrdiff_t				difference_type;
	typedef const T						value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <typename Category, typename T, typename Distance = std::ptrdiff_t,
		  typename Pointer = T*, typename Reference = T&>
struct iterator
{
	typedef Distance	difference_type;
	typedef T			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};
// iterator_traits

// reverse_iterator
template <typename Iterator>
class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
										 typename iterator_traits<Iterator>::value_type,
										 typename iterator_traits<Iterator>::difference_type,
										 typename iterator_traits<Iterator>::pointer,
										 typename iterator_traits<Iterator>::reference>
{
public:
	typedef Iterator													iterator_type;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename iterator_traits<iterator_type>::reference			reference;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;

	reverse_iterator()
		: current() { }
	explicit reverse_iterator(iterator_type other)
		: current(other) { }
	template <class U>
	reverse_iterator(const reverse_iterator<U>& other)
		: current(other.base()) { }
	template <class U>
	reverse_iterator& operator=(const reverse_iterator<U>& other)
	{
		current = other.base();
		return (*this);
	}
	~reverse_iterator() { }
	// operator			reverse_iterator<Iterator<const value_type> >() const { return (reverse_iterator<Iterator<const value_type> >(base())); }
	iterator_type		base() const { return (current); } // tested
	reference			operator*() const { iterator_type tmp(current); return (*--tmp); } // tested
	pointer				operator->() const { iterator_type tmp(current); return ((--tmp).operator->()); } // tested
	reference			operator[](difference_type n) const { return (*(*this + n)); } // tested
	reverse_iterator 	&operator++() { --current; return (*this); } // tested
	reverse_iterator	&operator--() { ++current; return (*this); } // tested
	reverse_iterator	operator++(int) { reverse_iterator tmp(*this); --current; return (tmp); } // tested
	reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++current; return (tmp); } // tested
	reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(current - n)); } // tested
	reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(current + n)); } // tested
	reverse_iterator	&operator+=(difference_type n) { current -= n; return (*this); } // tested
	reverse_iterator	&operator-=(difference_type n) { current += n; return (*this); } // tested

private:
	iterator_type	current;
};

template <class Iterator1, class Iterator2> // tested
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2> // tested
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator1, class Iterator2> // tested
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator1, class Iterator2> // tested
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator1, class Iterator2> // tested
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator1, class Iterator2> // tested
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iter> // tested
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{
	return (reverse_iterator<Iter>(it.base() - n));
}

template <class Iter1, class Iter2> // tested
typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
{
	return (rhs.base() - lhs.base());
}
// reverse_iterator

// wrap_iter
template <class Iterator>
class wrap_iter
{
public:
	typedef Iterator													iterator_type;
	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;

	wrap_iter()
		: it() { }
	explicit wrap_iter(iterator_type i)
		: it(i) { }
	template <class U>
	wrap_iter(const wrap_iter<U>& other)
		: it(other.base()) { }
	wrap_iter& operator=(const wrap_iter& other)
	{
		if (this != &other)
		{
			it = other.base();
		}
		return (*this);
	}
	~wrap_iter() { }
	reference operator*() const { return (*it); }
	pointer operator->() const { return (it.operator->()); }
	wrap_iter &operator++() { ++it; return (*this); }
	wrap_iter operator++(int) { wrap_iter tmp(*this); ++*this; return (tmp); }
	wrap_iter &operator--() { --it; return (*this); }
	wrap_iter operator--(int) { wrap_iter tmp(*this); --*this; return (tmp); }
	wrap_iter operator+(difference_type n) const { wrap_iter tmp(*this); tmp += n; return (tmp); }
	wrap_iter &operator+=(difference_type n) { it += n; return (*this); }
	wrap_iter operator-(difference_type n) const { wrap_iter tmp(*this); tmp -= n; return (tmp); }
	wrap_iter &operator-=(difference_type n) { it -= n; return (*this); }
	reference operator[](difference_type n) const { return (it[n]); }
	iterator_type base() const { return (it); }

private:
	iterator_type	it;
};

template <class Iterator1, class Iterator2>
bool operator==(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator!=(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<=(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator>(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator>=(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iter>
wrap_iter<Iter> operator+(typename wrap_iter<Iter>::difference_type n, const wrap_iter<Iter>& it)
{
	return (wrap_iter<Iter>(it.base() + n));
}

template <class Iter>
typename wrap_iter<Iter>::difference_type operator-(const wrap_iter<Iter>& lhs, const wrap_iter<Iter>& rhs)
{
	return (lhs.base() - rhs.base());
}
// wrap_iter

// Distance
template <class InputIt>
typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
{
	typename iterator_traits<InputIt>::difference_type result = 0;
	while (first != last)
	{
		++first;
		++result;
	}
	return (result);
}
// Distance

} // ft

#endif
