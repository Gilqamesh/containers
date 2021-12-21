#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

// ************************************************************************** //
//                       Iterator_traits Class                                //
// ************************************************************************** //

# include "iterator.hpp"

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
