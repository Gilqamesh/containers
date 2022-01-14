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
	std::vector<int> e(d.begin(), d.end());

	std::vector<int>::reverse_iterator f = e.rend();
	ft::vector<int>::reverse_iterator b = a.rend();
	std::cout << "standard" << std::endl;
	for (int i = 4; i >= -1; --i)
		std::cout << *(f + i) << std::endl;
	std::cout << "mine" << std::endl;
	for (int i = 4; i >= -1; --i)
		std::cout << *(b + i) << std::endl;
}
