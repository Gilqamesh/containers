#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

// DEBUG
# include <unistd.h>

namespace ft
{

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

template <typename Iter>
class reverse_iterator
{
public:
	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;
	typedef bidirectional_iterator_tag							iterator_category;

	reverse_iterator()
		: current() { } // tested
	explicit reverse_iterator(iterator_type x) // tested
		: current(x) { }
	template <class U> // idk how to test this
	reverse_iterator(const reverse_iterator<U>& other)
		: current(other.base()) { }
	~reverse_iterator() { }
	template <class U> // idk how to test this
	reverse_iterator &operator=(const reverse_iterator<U>& other)
	{
		write(STDOUT_FILENO, "a\n", 2);
		if (this != &other)
		{
			current = other.current;
		}
		return (*this);
	}
	iterator_type base(void) const { return (current); } // tested
	reference operator*() const { return (*(current - 1)); } // tested
	pointer operator->() const { return (&(operator*())); } // tested
	reference operator[](difference_type n) const { return (*(current - n - 1)); } // tested
	reverse_iterator &operator++() // tested
	{
		current = current - 1;
		return (*this);
	}
	reverse_iterator &operator--() // tested
	{
		current = current + 1;
		return (*this);
	}
	reverse_iterator operator++(int) // tested
	{
		reverse_iterator temp(current);
		current = current - 1;
		return (temp);
	}
	reverse_iterator operator--(int) // tested
	{
		reverse_iterator temp(current);
		current = current + 1;
		return (temp);
	}
	reverse_iterator operator+(difference_type n) const { return (static_cast<reverse_iterator>(current - n)); } // tested
	reverse_iterator operator-(difference_type n) const { return (static_cast<reverse_iterator>(current + n)); } // tested
	reverse_iterator &operator+=(difference_type n) // tested
	{
		current = current - n;
		return (*this);
	}
	reverse_iterator &operator-=(difference_type n) // tested
	{
		current = current + n;
		return (*this);
	}

private:
	iterator_type	current;
};

// const_reverse_iterator

template <typename Iter1, typename Iter2> // tested
bool operator==(const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
{
	return (a.base() == b.base());
}

template <typename Iter1, typename Iter2> // tested
bool operator!=(const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
{
	return (a.base() != b.base());
}

template <typename Iter1, typename Iter2> // tested
bool operator<(const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
{
	return (a.base() > b.base());
}

template <typename Iter1, typename Iter2> // tested
bool operator<=(const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
{
	return (a.base() >= b.base());
}

template <typename Iter1, typename Iter2> // tested
bool operator>(const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
{
	return (a.base() < b.base());
}

template <typename Iter1, typename Iter2> // tested
bool operator>=(const reverse_iterator<Iter1>& a, const reverse_iterator<Iter2>& b)
{
	return (a.base() <= b.base());
}

template <typename Iter> // tested
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &a)
{
	return (a + n);
}

template <typename Iter> // tested
typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& a, const reverse_iterator<Iter>& b)
{
	return (b.base() - a.base());
}

} // ft

#endif
