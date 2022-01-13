#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

// DEBUG
# include <unistd.h>

namespace ft
{

struct input_iterator_tag	{ };
struct output_iterator_tag	{ };
struct forward_iterator_tag			: public input_iterator_tag			{ };
struct bidirectional_iterator_tag	: public forward_iterator_tag		{ };
struct random_access_iterator_tag	: public bidirectional_iterator_tag	{ };

template <typename Iter>
struct iterator_traits
{
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template <typename T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <typename T>
struct iterator_traits<const T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <typename Category, typename T, typename Distance = ptrdiff_t,
		  typename Pointer = T*, typename Reference = T&>
struct iterator
{
	typedef Distance	difference_type;
	typedef T			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

template <typename Iter>
class reverse_iterator
{
public:
	typedef Iter												iterator_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;
	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

	reverse_iterator()
		: current()
	{
		write(STDOUT_FILENO, "a\n", 2);
	}
	// explicit reverse_iterator(iterator_type x)
	// 	: current(x)
	// {
	// 	write(STDOUT_FILENO, "b\n", 2);
	// }
	// template <class U>
	// reverse_iterator(const reverse_iterator<U>& other)
	// 	: current(other)
	// {
	// 	write(STDOUT_FILENO, "c\n", 2);
	// }
	// ~reverse_iterator() { }

private:
	iterator_type	current;
};

} // ft

#endif /* ITERATOR_HPP */
