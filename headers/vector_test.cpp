#include <iostream>
#include "vector.hpp"
#include <vector>
#include <stdlib.h>
#include <functional>

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

int main()
{
	// std::cout << (ft::is_same< std::size_t, ft::vector<int>::size_type >::value) << std::endl;
	// std::cout << (ft::is_same< double, ft::vector<int>::size_type >::value) << std::endl;
	std::vector<int>::iterator it;
	
	ft::vector<entity> a;
	a.push_back(entity(2));
	a.push_back(entity(-3));
	a.push_back(entity(12));
	a.push_back(entity(42));
	a.push_back(entity(1));

	ft::vector<entity> d;
	d.push_back(entity(-100));

	ft::swap(a, d);

	std::cout << "Size of a: " << a.size() << ", Capacity: " << a.capacity() << std::endl;
	std::cout << "Size of d: " << d.size() << ", Capacity: " << d.capacity() << std::endl;
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
