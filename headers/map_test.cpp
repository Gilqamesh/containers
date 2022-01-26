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

static std::pair<void *, size_t> s_AllocedPointers[100000];
static unsigned int s_AllocedPointersIndex = 0;

void *operator new(size_t size) throw(std::bad_alloc)
{
	void *ret = malloc(size);
	if (ret == NULL)
		throw std::bad_alloc();
	s_AllocationMetrics.TotalAlloced += size;
	s_AllocedPointers[s_AllocedPointersIndex].first = ret;
	s_AllocedPointers[s_AllocedPointersIndex].second = size;
	++s_AllocedPointersIndex;
	return (ret);
}

void operator delete(void *memory) noexcept
{
	unsigned int index = 0;
	while (s_AllocedPointers[index].first != memory)
		++index;
	s_AllocationMetrics.TotalFreed += s_AllocedPointers[index].second;
	for (unsigned int i = index; i < s_AllocedPointersIndex - 1; ++i)
		s_AllocedPointers[i] = s_AllocedPointers[i + 1];
	--s_AllocedPointersIndex;
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
		LOG(a.max_size());
		std::cout << a << std::endl;
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(3, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(4, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(7, 5));
		a.insert(TESTED_NAMESPACE::make_pair<int, int>(-2, 5));

		std::cout << a << std::endl;
		LOG(a.max_size());
	}
	PrintMemoryUsage();
}
