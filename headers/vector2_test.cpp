#include <iostream>
#include "vector2.hpp"
#include <vector>

int main()
{
	std::vector<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(42);
	d.push_back(5);

	ft::vector<int> a(d.begin(), d.end());

	ft::vector<int>::iterator b = a.end();
	for (unsigned int i = 0; i < 4; ++i)
		std::cout << *(b - i - 1) << std::endl;
}
