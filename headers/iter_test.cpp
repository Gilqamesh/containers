#include "iterator.hpp"
#include <iterator>
#include <iostream>

int main()
{
	int c = 5;
	int x = 1;
	int* b = &c;
	int* y = &x;
	std::reverse_iterator<int *> a(b);
	std::reverse_iterator<int *> g(y);
	std::reverse_iterator<int *> e(b);
	ft::reverse_iterator<int *> d(b);
	ft::reverse_iterator<int *> z(y);
	ft::reverse_iterator<int *> f(b);
	
	std::cout << a.base() << std::endl;
	std::cout << (g - a) << std::endl;
	std::cout << a.base() << std::endl;

	std::cout << d.base() << std::endl;
	std::cout << (z - d) << std::endl;
	std::cout << d.base() << std::endl;
}
