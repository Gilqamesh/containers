# include <iostream>
# include "tree.hpp"
# include <random>
# include <functional>

int main()
{
	ft::red_black_tree<int>	tree;

	// for (unsigned int i = 0; i < 100; ++i)
	// 	tree.insert(std::rand() % 10000);
	for (unsigned int i = 1; i <= 20; ++i)
		tree.insert(i);
	tree.print();
	std::cout << "\n\n\n\n\n";
	tree.remove(2);
	tree.remove(4);
	tree.remove(7);
	tree.remove(8);
	tree.remove(5);
	tree.remove(16);
	tree.remove(1);
	tree.remove(19);
	tree.remove(13);
	tree.print();
}
