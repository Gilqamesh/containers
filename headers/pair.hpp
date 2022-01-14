#ifndef PAIR_HPP
# define PAIR_HPP

// ************************************************************************** //
//                                  Pair Class                                //
// ************************************************************************** //

namespace ft
{

template <typename T1, typename T2>
class pair
{
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair() { }

		pair(const T1 &a, const T2 &b): first(a), second(b) { }

		~pair() { }

		pair(const pair &a) { *this = a; }

		pair &operator=(const pair &a)
		{
			if (this == &a)
				return (*this);
			first = a.first;
			second = a.second;
			return (*this);
		}
};

template <typename T1, typename T2>
bool	operator==(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return (a.first == b.first && a.second == b.second);
}

template <typename T1, typename T2>
bool	operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return (!operator==(a, b));
}

template <typename T1, typename T2>
bool	operator<(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return (a.first < b.second || (!(b.second < a.second) && a.second < b.second));
}

template <typename T1, typename T2>
bool	operator>(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return (a.first > b.second || (!(b.second > a.second) && a.second > b.second));
}

template <typename T1, typename T2>
bool	operator<=(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return (operator==(a, b) || operator<(a, b));
}

template <typename T1, typename T2>
bool	operator>=(const pair<T1, T2> &a, const pair<T1, T2> &b)
{
	return (operator==(a, b) || operator>(a, b));
}

template <typename T1, typename T2>
pair<T1, T2>	make_pair(const T1 &a, const T2 &b)
{
	return (pair<T1, T2>(a, b));
}

} // ft

#endif /* PAIR_HPP */
