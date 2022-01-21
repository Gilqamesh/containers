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
	typedef typename map::value_type				value_type;
	typedef typename map::key_type					key_type;
	typedef typename map::pointer					pointer;

	map_node()
	{
		data = map::allocator.allocate(sizeof(value_type));
	}
	map_node(const map_node& other)
	{
		data = map::allocator.allocate(sizeof(value_type));
		map::allocator.construct(data, value_type(*other.data));
	}
	map_node(const value_type& item)
	{
		data = map::allocator.allocate(sizeof(value_type));
		map::allocator.construct(data, value_type(item));
	}
	map_node& operator=(const map_node& other)
	{
		if (this != &other)
		{
			map::allocator.destroy(data);
			map::allocator.construct(data, value_type(*other.data));
		}
		return (*this);
	}
	~map_node()
	{
		map::allocator.destroy(data);
		map::allocator.deallocate(data, sizeof(value_type));
	}

	inline const key_type &getKey(void) const { return (data->first); }
	void swap(map_node& n1, map_node& n2) { ft::swap(n1, n2); }
	inline pointer getValue(void) { return (data); }

	pointer			data;
};

template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<const Key, T> > >
class map
{
friend class map_node<map>;
friend class red_black_tree<map>;
private:
	typedef map_node<map>														base_node_type;
	typedef map_node<map>*														base_node_pointer;
	typedef const map_node<map>*												base_node_const_pointer;
	typedef map_node<map>&														base_node_reference;
	typedef const map_node<map>&												base_node_const_reference;
public:
	typedef Key																	key_type;
	typedef T																	mapped_type;
	typedef typename ft::pair<const Key, T>										value_type;
	typedef typename std::size_t												size_type;
	typedef typename std::ptrdiff_t												difference_type;
	typedef Compare																key_compare;
	typedef Allocator															allocator_type;
	typedef value_type&															reference;
	typedef const value_type&													const_reference;
	typedef typename Allocator::pointer											pointer;
	typedef typename Allocator::const_pointer									const_pointer;
	typedef tree_iterator<red_black_tree<map> > 								iterator;
	typedef tree_const_iterator<red_black_tree<map> >							const_iterator;
	typedef tree_reverse_iterator<red_black_tree<map> >							reverse_iterator;
	typedef tree_const_reverse_iterator<red_black_tree<map> >					const_reverse_iterator;

	map()
		: tree() { } // tested
	explicit map(const Compare& comp, const Allocator& alloc = Allocator()) // tested
		: tree()
	{
		compare = comp;
		allocator = alloc;
	}
	template <class InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
		: tree()
	{
		std::cout << "Hello\n";
		// It's called.
		while (first != last)
			insert(*first++);
	}
	~map() { }

	iterator begin(void) { return (tree.begin()); } // tested
	iterator end(void)	 { return (tree.end()); } // tested
	reverse_iterator rbegin(void) { return (tree.rbegin()); } // tested
	reverse_iterator rend(void) { return (tree.rend()); } // tested

	// DEBUG
	void insert(const value_type& item) { tree.insert(item); }
	void print() const { tree.print(); }
private:
	red_black_tree<map>			tree;
	static Compare				compare;
	static Allocator			allocator;
};

template <class Key, class T, class Compare, class Allocator>
Compare map<Key, T, Compare, Allocator>::compare;

template <class Key, class T, class Compare, class Allocator>
Allocator map<Key, T, Compare, Allocator>::allocator;

} // ft

#endif
