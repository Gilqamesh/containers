#include <iostream>
#include "vector.hpp"
#include <vector>
#include <stdlib.h>
#include <functional>

# define LOG(x) (std::cout << (x) << std::endl)

class entity
{
public:
	entity()
		: a(0)
	{
	}
	entity(int v)
		: a(v) { }
	entity(const entity& e)
		: a(e.a) { }
	entity& operator=(const entity& e)
	{
		if (this != &e)
		{
			a = e.a;
		}
		return (*this);
	}
	~entity()
	{
	}

	void setValue(int v) { a = v; }

	int getValue(void) const { return (a); }
private:
	int a;
};

bool operator>(const entity& a, const entity& b);

std::ostream &operator<<(std::ostream &os, const entity& e);

struct comp
{
	bool operator()(const entity& a, const entity& b)
	{
		return (operator>(a, b));
	}
};

#if 0
	#define ft std
#endif

int main()
{	
	std::vector<int> a;
	a.push_back(5);
	std::cout << "Capacity: " << a.capacity() << std::endl;
}

std::ostream &operator<<(std::ostream &os, const entity& e)
{
	os << e.getValue();
	return (os);
}

bool operator==(const entity& a, const entity& b)
{
	return (a.getValue() == b.getValue());
}

bool operator!=(const entity& a, const entity& b)
{
	return (a.getValue() != b.getValue());
}

bool operator<(const entity& a, const entity& b)
{
	return (a.getValue() < b.getValue());
}

bool operator>(const entity& a, const entity& b)
{
	return (a.getValue() > b.getValue());
}
