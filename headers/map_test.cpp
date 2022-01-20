# include <iostream>
# include "map.hpp"
# include <map>
# include <exception>

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
	s_AllocationMetrics.TotalAlloced += size;
	return (malloc(size));
}

void operator delete(void *memory, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;
	free(memory);
}

void PrintMemoryUsage()
{
	std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes" << std::endl;
}

int main()
{
	PrintMemoryUsage();
	{
		// ft::map<int, int>	a;

		// ft::red_black_tree<ft::map_node<int, int> >	t;

		// for (unsigned int i = 1; i <= 20; ++i)
		// 	t.insert(ft::pair<int, int>(i, i * 2));
		// t.print();

		// for (ft::map<int, int>::iterator i = a.begin(); i != a.end(); ++i)
		// {
		// 	std::cout << i->first << std::endl;
		// }

		// for (ft::map<int, int>::iterator i = a.begin(); i != a.end(); ++i)
		// 	LOG(i->first);

		// a.insert(ft::make_pair<int, int>(2, 5));
		// a.insert(ft::make_pair<int, int>(5, 5));
		// a.insert(ft::make_pair<int, int>(7, 5));
		// a.insert(ft::make_pair<int, int>(-3, 5));
		// a.insert(ft::make_pair<int, int>(8, 5));
		// a.print();

		// LOG("\n");
		// for (ft::map<int, int>::iterator i = a.begin(); i != a.end(); ++i)
		// 	LOG(i->first);

		// std::cout << "\n\n\n\n";
		// t.remove(2);
		// t.remove(4);
		// t.remove(16);
		// t.remove(7);
		// t.print();

		ft::map<int, int> a;
		a.insert(ft::make_pair<int, int>(6, 8));
		a.insert(ft::make_pair<int, int>(3, 8));
		a.insert(ft::make_pair<int, int>(-5, 8));
		for (ft::map<int, int>::iterator i = a.begin(); i != a.end(); ++i)
			LOG(i->first);
		
		LOG("\n\n");
		for (ft::map<int, int>::reverse_iterator i = a.rbegin(); i != a.rend(); ++i)
			LOG(i->first);
	}
	PrintMemoryUsage();
}
