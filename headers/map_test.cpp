# include <iostream>
# include "map.hpp"
# include "vector.hpp"
# include <map>
# include <exception>
# include <functional>
# include <vector>

# define LOG(x) (std::cout << x << std::endl)

class AllocationMetrics
{
public:
	AllocationMetrics()
		: TotalAlloced(0), TotalFreed(0) { }
	~AllocationMetrics() { }

	size_t TotalAlloced;
	size_t TotalFreed;

	size_t CurrentUsage() { return (TotalAlloced - TotalFreed); }
};

static AllocationMetrics s_AllocationMetrics;

void *operator new(size_t size) throw(std::bad_alloc)
{
	void *ret = malloc(size);
	if (ret == NULL)
		throw std::bad_alloc();
	s_AllocationMetrics.TotalAlloced += size;
	return (ret);
}

void operator delete(void *memory, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;
	free(memory);
}

template <typename T>
struct more
{
	bool operator()(const T& a, const T& b) const
	{
		return (a > b);
	}
};

void PrintMemoryUsage()
{
	std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes" << std::endl;
}

#define TESTED_NAMESPACE ft

int main()
{
	PrintMemoryUsage();
	{
		TESTED_NAMESPACE::map<int, int> a;
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(3, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(4, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(7, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(-2, 5));

		for (TESTED_NAMESPACE::map<int, int>::reverse_iterator i = a.rbegin(); i != a.rend(); ++i)
			std::cout << i->first << std::endl;
	}
	PrintMemoryUsage();
}
