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
	typedef typename map::reference					reference;

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

	const key_type &getKey(void) const { return (data.first); }
	void swap(map_node& n1, map_node& n2) { ft::swap(n1, n2); }

	value_type		data;

private:
};

template <class Key, class T, class Compare = typename ft::less<Key>, class Allocator = typename std::allocator<ft::pair<const Key, T> > >
class map
{
friend class map_node<map>;
friend class red_black_tree<map>;
private:
	typedef map_node<map>												base_node_type;
	typedef map_node<map>*												base_node_pointer;
	typedef const map_node<map>*										base_node_const_pointer;
	typedef map_node<map>&												base_node_reference;
	typedef const map_node<map>&										base_node_const_reference;
public:
	typedef Key															key_type;
	typedef T															mapped_type;
	typedef typename ft::pair<const Key, T>								value_type;
	typedef typename std::size_t										size_type;
	typedef typename std::ptrdiff_t										difference_type;
	typedef Compare														key_compare;
	typedef Allocator													allocator_type;
	typedef value_type&													reference;
	typedef const value_type&											const_reference;
	typedef typename Allocator::pointer									pointer;
	typedef typename Allocator::const_pointer							const_pointer;
	typedef typename red_black_tree<map>::iterator 						iterator;
	typedef typename red_black_tree<map>::const_iterator 				const_iterator;
	typedef typename red_black_tree<map>::reverse_iterator 				reverse_iterator;
	typedef typename red_black_tree<map>::const_reverse_iterator 		const_reverse_iterator;

	map()
		: tree() { } // tested
	explicit map(const Compare& comp, const Allocator& alloc = Allocator()) // tested
		: tree(), allocator(alloc) { }
	template <class InputIt> // tested
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
		: tree(), allocator(alloc)
	{
		while (first != last)
			insert(*first++);
	}
	map(const map& other) // tested
		: tree(other.tree), allocator(other.allocator) { }
	~map() { }
	map& operator=(const map& other) // tested
	{
		if (this != &other)
		{
			allocator = other.allocator;
			tree = other.tree;
		}
		return (*this);
	}
	allocator_type get_allocator(void) const { return (allocator); } // tested

	// Element access
	T &at(const Key& key) // tested
	{
		node<base_node_type> *p = tree.search(key);
		if (p == NULL)
			throw std::out_of_range("The key is not in the map");
		return (p->base.data->second);
	}
	const T& at(const Key& key) const // tested
	{
		const node<base_node_type> *p = tree.search(key);
		if (p == NULL)
			throw std::out_of_range("The key is not in the map");
		return (p->base.data->second);
	}
	T& operator[](const Key& key) // tested
	{
		node<base_node_type> *p = tree.search(key);
		if (p == NULL)
			return (insert(ft::make_pair<const Key, T>(key, T())).second);
		return (p->base.data->second);
	}

	// Iterators
	iterator 		 begin()  { return (tree.begin());  } // tested
	iterator 		 end()	  { return (tree.end());    } // tested
	reverse_iterator rbegin() { return (tree.rbegin()); } // tested
	reverse_iterator rend()   { return (tree.rend());   } // tested
	const_iterator 		   begin()	const { return (tree.begin());	} // tested
	const_iterator 		   end()	const { return (tree.end());	} // tested
	const_reverse_iterator rbegin() const { return (tree.rbegin()); } // tested
	const_reverse_iterator rend()	const { return (tree.rend());	} // tested

	// Capacity
	bool empty() const { return (begin() == end()); } // tested
	size_type size() const { return (ft::distance(begin(), end())); } // tested
	size_type max_size() const { return (tree.max_size()); } // tested

	// Modifiers
	void clear() { tree.clear(); } // tested
	ft::pair<iterator, bool> insert(const value_type& value)
	{
		ft::pair<iterator, bool> result(ft::make_pair<iterator, bool>(tree.get_iterator_at(tree.insert(value)), false));
		result.second = (result.first == end() ? false : true);
		return (result);
	}

	// DEBUG
	void	  print() const { tree.print(); }
private:
	red_black_tree<map>		tree;
	allocator_type			allocator;
};

} // ft

#endif
