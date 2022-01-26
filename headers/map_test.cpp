# include <iostream>
# include "map.hpp"
# include "vector.hpp"
# include <map>
# include <exception>
# include <functional>
# include <vector>
# include "AllocationMetrics.hpp"

# define LOG(x) (std::cout << x << std::endl)

template <typename T>
struct more
{
	bool operator()(const T& a, const T& b) const
	{
		return (a > b);
	}
};

#define TESTED_NAMESPACE ft

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::map<Key, T>& m)
{
	for (typename TESTED_NAMESPACE::map<Key, T>::const_reverse_iterator i = m.rbegin(); i != m.rend(); ++i)
		os << i->first << " " << i->second << std::endl;
	return (os);
}

int main()
{
	PrintMemoryUsage();
	{
		TESTED_NAMESPACE::map<int, int> a;
		LOG("Size: " << a.size());
		std::cout << a << std::endl;
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(3, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(4, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(7, 5));
		TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<int, int>::iterator, bool > p = a.insert(TESTED_NAMESPACE::make_pair<int, int>(-2, 5));
		LOG("p.first->first: " << p.first->first);
		LOG("p.first->second: " << p.first->second);
		LOG("p.second: " << p.second);

		std::cout << a << std::endl;
		LOG("Size: " << a.size());
		a.clear();
		LOG("Size: " << a.size());
	}
	PrintMemoryUsage();
}
