# include <iostream>
# include "map.hpp"
# include "vector.hpp"
# include <map>
# include <exception>
# include <functional>
# include <vector>
// # include "AllocationMetrics.hpp"
# include "vector.hpp"

#ifndef PRINT_HERE
# define PRINT_HERE() (std::cout << __FILE__ << " " << __LINE__ << std::endl)
#endif
# define LOG(x) (std::cout << x << std::endl)

template <typename T>
struct more
{
	bool operator()(const T& a, const T& b) const
	{
		return (a > b);
	}
};

#define TESTED_NAMESPACE std

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::map<Key, T>& m)
{
	for (typename TESTED_NAMESPACE::map<Key, T>::const_reverse_iterator i = m.rbegin(); i != m.rend(); ++i)
		os << i->first << " " << i->second << std::endl;
	return (os);
}

int main()
{
	// PrintMemoryUsage();
	{
		TESTED_NAMESPACE::map<int, int> test;
		TESTED_NAMESPACE::map<int, int>::iterator hint = test.begin();
		for (size_t i = 0; i < 10000000; ++i)
		{
			test.insert(TESTED_NAMESPACE::make_pair<int, int>(i ,i));
		}
	}
	// PrintMemoryUsage();
}
