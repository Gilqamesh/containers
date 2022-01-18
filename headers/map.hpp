#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "functional.hpp"
# include "utility.hpp"
# include "algorithm.hpp"
# include "tree.hpp"

namespace ft
{

/*
* each node in the red_black_tree is going to have this as a base type
*/
template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<Key, T> > >
class map_node
{
public:
	typedef Key										key_type;
	typedef T										mapped_type;
	typedef typename ft::pair<Key, T>				value_type;
	typedef Compare									compare_type;
	typedef Allocator								allocator_type;
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

	inline const Key &getKey(void) const { return (data->first); }
	void swap(map_node& n1, map_node& n2) { ft::swap(n1, n2); }

private:
	allocator_type	allocator;
	pointer			data;
};

template <typename map>
class map_iterator
{
public:
	typedef typename map::pointer	pointer;
	typedef typename map::reference	reference;

	map_iterator()
		: ptr(NULL) { }
	map_iterator(const map_iterator& other)
		: ptr(other.ptr) { }
	map_iterator& operator=(const map_iterator& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
		}
		return (*this);
	}
	~map_iterator() { }

	reference operator*()
	{
		return (*ptr);
	}
	pointer operator->()
	{
		return (ptr);
	}
	map_iterator &operator++()
	{
		ptr = ptr->get_successor(ptr);
		return (*this);
	}
	map_iterator &operator++(int)
	{
		map_iterator temp(*this);
		ptr = ptr->get_successor(ptr);
		return (temp);
	}
	map_iterator &operator--()
	{
		ptr = ptr->get_predecessor(ptr);
		return (*this);
	}
	map_iterator &operator--(int)
	{
		map_iterator temp(*this);
		ptr = ptr->get_predecessor(ptr);
		return (temp);
	}
	bool operator==(const map_iterator& other) const { return (ptr == other.ptr);  }
	bool operator!=(const map_iterator& other) const { return (!(*this == other)); }
	
private:
	pointer	ptr;
};

template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<const Key, T> > >
class map
{
public:
	typedef Key																key_type;
	typedef T																mapped_type;
	typedef typename ft::pair<Key, T>										value_type;
	typedef typename std::size_t											size_type;
	typedef typename std::ptrdiff_t											difference_type;
	typedef Compare															key_compare;
	typedef Allocator														allocator_type;
	typedef red_black_tree<map_node<Key, T, Compare, Allocator> >&			reference;
	typedef red_black_tree<map_node<Key, T, Compare, Allocator> >*			pointer;
	typedef map_iterator<map>												iterator;
	// NEED REVERSE_ITERATOR
	// NEED CONST_REVERSE_ITERATOR

	map()
		: root(new iterator()) { }
	explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: root(new iterator()) { }
	~map() { delete root; }

	iterator	begin(void) { return (root->find_left_most_leaf(root));  }
	iterator	end(void)	{ return (root->find_right_most_leaf(root)); }

private:
	iterator	root;
};

} // ft

#endif
