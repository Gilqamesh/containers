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

int main()
{	
	PrintMemoryUsage();
	{
		ft::map<int, int> b;
		ft::vector<ft::pair<int, int> > pairs;
		pairs.push_back(ft::make_pair<int, int>(5, 6));
		pairs.push_back(ft::make_pair<int, int>(2, 4));
		pairs.push_back(ft::make_pair<int, int>(1, 3));
		pairs.push_back(ft::make_pair<int, int>(-8, 3));
		pairs.push_back(ft::make_pair<int, int>(93, 3));
		{
			ft::map<int, int> a(pairs.begin(), pairs.end());
			b = a;
		}
		for (ft::map<int, int>::iterator i = b.begin(); i != b.end(); ++i)
		{
			LOG(i->first << " " << i->second);
		}
		
		LOG("\n\n");
		for (ft::map<int, int>::reverse_iterator i = b.rbegin(); i != b.rend(); ++i)
		{
			LOG(i->first << " " << i->second);
		}

		ft::map<int, int> c;
		LOG(c[3]);
		LOG(b[2]);
	}
	PrintMemoryUsage();
}
