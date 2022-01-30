#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{

template <class T1, class T2>
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	pair()
		: first(), second() { }
	pair(const T1 &a, const T2 &b)
		: first(a), second(b) { }
	template <class U1, class U2>
	pair(const pair<U1, U2>& p)
		: first(p.first), second(p.second) { }
	~pair() { }
	pair(const pair &other)
		: first(other.first), second(other.second) { }
	pair &operator=(const pair &a)
	{
		if (this != &a)
		{
			first = a.first;
			second = a.second;
		}
		return (*this);
	}

	first_type	first;
	second_type	second;
};

template <class T1, class T2>
bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <class T1, class T2>
bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (!(lhs == rhs));
}

template <class T1, class T2>
bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	if (lhs.first < rhs.first)
		return (true);
	if (rhs.first < lhs.first)
		return (false);
	return (lhs.second < rhs.second);
}

template <class T1, class T2>
bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (rhs < lhs);
}

template <class T1, class T2>
bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (!(rhs < lhs));
}

template <class T1, class T2>
bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return (!(lhs < rhs));
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 a, T2 b)
{
	return (pair<T1, T2>(a, b));
}

} // ft

#endif
