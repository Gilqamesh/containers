#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "functional.hpp"
# include "utility.hpp"
# include "algorithm.hpp"
# include "tree.hpp"

# include <iostream>
# define PRINT_HERE() (std::cout << __FILE__ << " " << __LINE__ << std::endl)

namespace ft
{

template <class map>
class map_node
{
public:
	typedef typename map::key_type					key_type;
	typedef typename map::mapped_type				mapped_type;
	typedef typename map::value_type				value_type;
	typedef typename map::key_compare				key_compare;
	typedef typename map::allocator_type			allocator_type;
	typedef typename allocator_type::pointer		pointer;

	map_node()
	{
		data = allocator.allocate(sizeof(value_type));
	}
	map_node(const map_node& other)
	{
		data = allocator.allocate(sizeof(value_type));
		allocator.construct(data, value_type(*other.data));
	}
	map_node(const value_type& item)
	{
		data = allocator.allocate(sizeof(value_type));
		allocator.construct(data, value_type(item));
	}
	map_node& operator=(const map_node& other)
	{
		if (this != &other)
		{
			allocator.destroy(data);
			allocator.construct(data, value_type(*other.data));
		}
		return (*this);
	}
	~map_node()
	{
		allocator.destroy(data);
		allocator.deallocate(data, sizeof(value_type));
	}

	inline const key_type &getKey(void) const { return (data->first); }
	void swap(map_node& n1, map_node& n2) { ft::swap(n1, n2); }
	inline pointer getValue(void) { return (data); }

	allocator_type	allocator;
	pointer			data;
};

template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<const Key, T> > >
class map
{
public:
	typedef Key																key_type;
	typedef T																mapped_type;
	typedef typename ft::pair<const Key, T>									value_type;
	typedef typename std::size_t											size_type;
	typedef typename std::ptrdiff_t											difference_type;
	typedef Compare															key_compare;
	typedef Allocator														allocator_type;
	typedef value_type&														reference;
	typedef typename red_black_tree<map_node<map> >::iterator				iterator;
	typedef typename red_black_tree<map_node<map> >::reverse_iterator		reverse_iterator;
	typedef value_type*														pointer;
	// NEED REVERSE_ITERATOR
	// NEED CONST_REVERSE_ITERATOR

	map()
		: root() { }
	explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: root() { }
	~map() { }

	iterator begin(void) { return (root.begin()); }
	iterator end(void)	 { return (root.end()); }
	reverse_iterator rbegin(void) { return (root.rbegin()); }
	reverse_iterator rend(void) { return (root.rend()); }
	void insert(const value_type& item) { root.insert(item); }

	// DEBUG
	void print() const { root.print(); }
private:
	red_black_tree<map_node<map> >	root;
};

} // ft

#endif
