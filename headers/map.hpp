#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "functional.hpp"
# include "utility.hpp"
# include "tree.hpp"

namespace ft
{

template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::pair<const Key, T>				value_type;
	typedef typename std::size_t				size_type;
	typedef typename std::ptrdiff_t				difference_type;
	typedef Compare								key_compare;
	typedef Allocator							allocator_type;
	typedef value_type&							reference;
	typedef const value_type&					const_reference;
	typedef value_type*							pointer;
	typedef const value_type*					const_pointer;
	// NEED ITERATOR
	// NEED CONST_ITERATOR
	typedef typename Allocator::pointer			iterator;
	typedef typename Allocator::const_pointer	const_iterator;
	// NEED REVERSE_ITERATOR
	// NEED CONST_REVERSE_ITERATOR

	map()
		: tree() { }
	explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: tree() { } 

private:
	red_black_tree<Key, T, Compare, Allocator>	tree;
};

} // ft

#endif
