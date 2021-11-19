#ifndef VECTOR_HPP
# define VECTOR_HPP

// ************************************************************************** //
//                                Vector Class                                //
// ************************************************************************** //

# include <memory>
# include "pair.hpp"

namespace ft
{

template <typename T>
class vector
{
	public:
		typedef T										value_type;
		typedef typename std::allocator<value_type>		allocator_type;
		typedef std::allocator_traits<allocator_type>	__alloc_traits;
		typedef typename __alloc_traits::size_type		size_type;
	// protected:
		typedef typename __alloc_traits::pointer		pointer;
		typedef typename __alloc_traits::const_pointer	const_pointer;
		typedef pointer									iterator;
		typedef const_pointer							const_iterator;

	public:
		vector() { }

		~vector() { }

		vector(const vector &a) { *this = a; }

		vector &operator=(const vector &a)
		{
			if (this == &a)
				return (*this);
			return (*this);
		}

		/*
		** Request to reduce capacity() to equal size()
		*/
		void		shrink_to_fit(void);

		/*
		** Number of elements 'data' can have before reallocation is necessary
		*/
		size_type	capacity(void) const
		{
			return ();
		}

		/*
		** Allocate space for at least '__n' elements
		*/
		void		reserve(size_type __n)

	private:
		allocator_type	data;
		iterator		__begin_;
		iterator		__end_;
};

} // ft

#endif /* VECTOR_HPP */
