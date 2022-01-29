#ifndef SET_HPP
# define SET_HPP

# include "tree.hpp"
# include "functional.hpp"
# include <memory>

namespace ft
{

template <class set>
class set_node
{
public:
	typedef typename set::value_type				value_type;
	typedef typename set::key_type					key_type;
	typedef typename set::pointer					pointer;
	typedef typename set::reference					reference;

	set_node()
		: data() { }
	set_node(const set_node& other)
		: data(other.data) { }
	set_node(const value_type& item)
		: data(item) { }
	set_node& operator=(const set_node& other)
	{
		if (this != &other)
		{
			data = other.data;
		}
		return (*this);
	}
	~set_node() { }

	const key_type &getKey(void) const { return (data); }

	value_type		data;

private:
};

template <class Key, class Compare = ft::less<Key>, class Allocator = std::allocator<Key> >
class set
{
friend class set_node<set>;
friend class red_black_tree<set>;
private:
	typedef set_node<set>											base_node_type;
	typedef set_node<set>*											base_node_pointer;
	typedef const set_node<set>*									base_node_const_pointer;
	typedef set_node<set>&											base_node_reference;
	typedef const set_node<set>&									base_node_const_reference;
public:
	typedef Key														key_type;
	typedef Key														value_type;
	typedef std::size_t												size_type;
	typedef std::ptrdiff_t											difference_type;
	typedef Compare													key_compare;
	typedef Compare													value_compare;
	typedef Allocator												allocator_type;
	typedef value_type&												reference;
	typedef const value_type&										const_reference;
	typedef typename Allocator::pointer								pointer;
	typedef typename Allocator::const_pointer						const_pointer;
	typedef typename red_black_tree<set>::const_iterator			iterator;
	typedef typename red_black_tree<set>::const_iterator			const_iterator;
	typedef typename red_black_tree<set>::const_reverse_iterator	reverse_iterator;
	typedef typename red_black_tree<set>::const_reverse_iterator	const_reverse_iterator;

	set()
		: tree(), allocator(), compare(), set_size(0) { }
	explicit set(const Compare& comp, const Allocator& alloc = Allocator())
		: tree(), allocator(alloc), compare(comp), set_size(0) { }
	template <class InputIt>
	set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
		: tree(), allocator(alloc), compare(comp), set_size(0)
	{
		while (first != last)
			insert(*first++);
	}
	set(const set& other)
		: tree(other.tree), allocator(other.allocator), compare(other.compare), set_size(other.set_size) { }
	~set() { }
	set& operator=(const set& other)
	{
		if (this != &other)
		{
			allocator = other.allocator;
			tree = other.tree;
			compare = other.compare;
			set_size = other.set_size;
		}
		return (*this);
	}
	allocator_type get_allocator() const { return (allocator); }

	// Iterators
	iterator begin() { return (tree.begin()); }
	iterator end()   { return (tree.end());   }
	reverse_iterator rbegin() { return (tree.rbegin()); }
	reverse_iterator rend()   { return (tree.rend());   }
	const_iterator begin() const { return (tree.begin()); }
	const_iterator end() const   { return (tree.end());   }
	const_reverse_iterator rbegin() const { return (tree.rbegin()); }
	const_reverse_iterator rend() const   { return (tree.rend());   }

	// Capacity
	bool empty() const { return (begin() == end()); }
	size_type size() const { return (set_size); }
	size_type max_size() const { return (tree.max_size()); }

	// Modifiers
	void clear() { tree.clear(); set_size = 0; }
	ft::pair<iterator, bool> insert(const value_type& value)
	{
		ft::pair<iterator, bool> result(tree.get_iterator_at(tree.insert(value, value)));
		if (result.second == true)
			++set_size;
		return (result);
	}
	iterator insert(iterator hint, const value_type& value)
	{
		if (!size())
		{
			++set_size;
			return(tree.get_iterator_at(tree.insert(value, value)).first);
		}
		ft::pair<iterator, bool> ret = tree.get_iterator_at(tree.insert(hint, value, value, false));
		if (ret.second == true)
			++set_size;
		return (ret.first);
	}
	template <class InputIt>
	void insert(InputIt first, InputIt last)
	{
		iterator hint = begin();
		while (first != last)
			hint = insert(hint, *first++);
	}
	void erase(iterator pos)
	{
		if (tree.remove(*pos) == true)
			--set_size;
	}
	void erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator cur = first++;
			if (tree.remove(*cur) == true)
				--set_size;
		}
	}
	size_type erase(const Key& key)
	{
		if (tree.remove(key) == true)
		{
			--set_size;
			return (1);
		}
		return (0);
	}
	void swap(set& other)
	{
		tree.swap(other.tree);
		ft::swap(allocator, other.allocator);
		ft::swap(compare, other.compare);
		ft::swap(set_size, other.set_size);
	}

	// Lookup
	size_type count(const Key& key) const { return (find(key) == end() ? 0 : 1); }
	iterator find(const Key& key) { return (tree.get_iterator_at(tree.search(key))); }
	const_iterator find(const Key& key) const { return (tree.get_iterator_at(tree.search(key))); }
	ft::pair<iterator, iterator> equal_range(const Key& key)
	{
		return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
	}
	ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
	}
	iterator lower_bound(const Key& key)
	{
		iterator i = begin();
		while (i != end() && *i < key)
			++i;
		return (i);
	}
	const_iterator lower_bound(const Key& key) const
	{
		const_iterator ci = begin();
		while (ci != end() && *ci < key)
			++ci;
		return (ci);
	}
	iterator upper_bound(const Key& key)
	{
		iterator i = begin();
		while (i != end() && *i <= key)
			++i;
		return (i);
	}
	const_iterator upper_bound(const Key& key) const
	{
		const_iterator ci = begin();
		while (ci != end() && *ci <= key)
			++ci;
		return (ci);
	}

public:
	// Observers
	key_compare key_comp() const { return (key_compare()); }
	value_compare value_comp() const { return (key_compare()); }

	// DEBUG
	void print() const { tree.print(); }

private:
	red_black_tree<set>		tree;
	allocator_type			allocator;
	value_compare			compare;
	size_type				set_size;
};

template <class Key, class Compare, class Alloc>
bool operator==(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class Compare, class Alloc>
bool operator!=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class Key, class Compare, class Alloc>
bool operator<(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class Key, class Compare, class Alloc>
bool operator<=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class Key, class Compare, class Alloc>
bool operator>(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool operator>=(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs)
{
	lhs.swap(rhs);
}

}

#endif
