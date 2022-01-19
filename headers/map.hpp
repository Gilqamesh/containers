#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "functional.hpp"
# include "utility.hpp"
# include "algorithm.hpp"
# include "tree.hpp"

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

private:
	allocator_type	allocator;
	pointer			data;
};

template <typename map>
class map_iterator
{
private:
	typedef typename red_black_tree<map_node<map> >::node_pointer	node_pointer;
public:
	typedef typename map::value_type									value_type;
	typedef typename map::reference										reference;
	typedef typename map::pointer										pointer;

	map_iterator()
		: root(), ptr(NULL) { }
	map_iterator(red_black_tree<map_node<map> >& tree)
		: root(tree), ptr(NULL) { }
	map_iterator(red_black_tree<map_node<map> >& tree, node_pointer a)
		: root(tree), ptr(a) { }
	map_iterator(const map_iterator& other)
		: root(other.root), ptr(other.ptr) { }
	map_iterator& operator=(const map_iterator &other)
	{
		if (this != &other)
		{
			root = other.root;
			ptr = other.ptr;
		}
		return (*this);
	}
	~map_iterator() { }

	pointer operator->()
	{
		return (ptr->getValue());
	}
	map_iterator& operator++()
	{
		ptr = root.get_successor(ptr);
		return (*this);
	}
	map_iterator operator++(int)
	{
		map_iterator tmp(*this);
		ptr = root.get_successor(ptr);
		return (tmp);
	}
	map_iterator& operator--()
	{
		ptr = root.get_predecessor(ptr);
		return (*this);
	}
	map_iterator operator--(int)
	{
		map_iterator tmp(*this);
		ptr = root.get_predecessor(ptr);
		return (tmp);
	}
	bool operator==(const map_iterator& other) const { return (ptr == other.ptr); }
	bool operator!=(const map_iterator&other) const  { return (!(ptr == other.ptr)); }

private:
	red_black_tree<map_node<map> >	&root;
	node_pointer					ptr;
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
	typedef map_iterator<map>												iterator;
	typedef value_type*														pointer;
	// NEED REVERSE_ITERATOR
	// NEED CONST_REVERSE_ITERATOR

	map()
		: root(), it(root) { }
	explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: root(), it(root) { }
	~map() { }

	iterator begin(void) { return (iterator(root, root.find_left_most_leaf(root.root)));  }
	iterator end(void)	 { return (iterator(root, root.find_right_most_leaf(root.root))); }
private:
	red_black_tree<map_node<map> >	root;
	iterator						it;
};

} // ft

#endif
