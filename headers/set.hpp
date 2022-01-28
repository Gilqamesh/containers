#ifndef SET_HPP
# define SET_HPP

# include "functional.hpp"
# include <memory>

namespace ft
{

template <class Key, class Compare = ft::less<Key>, class Allocator = std::allocator<Key> >
class set
{
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
	typedef typename Allocator::const_pointe						const_pointer;
	typedef typename red_black_tree<set>::iterator					iterator;
	typedef typename red_black_tree<set>::const_iterator			const_iterator;
	typedef typename red_black_tree<set>::reverse_iteartor			reverse_iterator;
	typedef typename red_black_tree<set>::const_reverse_iterator	const_reverse_iterator;

private:
};

}

#endif
