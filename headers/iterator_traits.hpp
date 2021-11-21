#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

// ************************************************************************** //
//                       Iterator_traits Class                                //
// ************************************************************************** //

# include <cstddef>

template <typename Category, typename T, typename Distance = ptrdiff_t,
		  typename Pointer = T*, typename Reference = T&>
class iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

template <typename Iterator>
class iterator_traits
{
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::value_type		value_type;
	typedef typename Iterator::pointer			pointer;
	typedef typename Iterator::reference		reference;
};

template <typename T>
class iterator_traits<T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
};

#endif /* ITERATOR_TRAITS_HPP */
