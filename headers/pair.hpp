#ifndef PAIR_HPP
# define PAIR_HPP

// ************************************************************************** //
//                                  Pair Class                                //
// ************************************************************************** //

template <typename T1, typename T2>
class pair
{
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		pair() { }

		~pair() { }

		pair(const pair &a) { *this = a; }

		pair &operator=(const pair &a)
		{
			if (this == &a)
				return (*this);
			return (*this);
		}

	private:
		first_type	first;
		second_type	second;
};

#endif /* PAIR_HPP */
