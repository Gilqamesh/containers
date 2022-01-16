#ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft
{

// less
template <class T>
struct less
{
	bool operator()(const T& lsh, const T& rhs) const
	{
		return (lsh < rhs);
	}
};

} // ft

#endif
