#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "functional.hpp"
# include "utility.hpp"

namespace ft
{

template <class base_node>
class red_black_tree;

/*
* each node in the red_black_tree is going to have this as a base type
*/
template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<Key, T> > >
class map_node
{
public:
	typedef Key							key_type;
	typedef T							mapped_type;
	typedef typename ft::pair<Key, T>	value_type;
	typedef Compare						compare_type;
	typedef Allocator					allocator_type;

	map_node()
		: data() { }
	map_node(const map_node& other)
		: data(other.data) { }
	map_node(const value_type& item)
		: data(item) { }
	map_node& operator=(const map_node& other)
	{
		if (this != &other)
		{
			data = other.data;
		}
		return (*this);
	}
	~map_node() { }

	inline const Key &getKey(void) const { return (data.first); }
	void swap(map_node& n1, map_node& n2) { ft::swap(n1, n2); }

private:
	value_type		data;
};

template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<const Key, T> > >
class map
{
public:
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef typename ft::pair<Key, T>			value_type;
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
	red_black_tree<map_node<Key, T, Compare, Allocator> >	tree;
};

} // ft

#endif
