# include <iostream>
# include "tree.hpp"
# include "map.hpp"
# include <random>
# include <functional>
# include <string>
# include <map>
# include <utility>
# include "utility.hpp"

int main()
{
	ft::red_black_tree<ft::map_node<int, int> >	t;

	for (unsigned int i = 1; i <= 20; ++i)
		t.insert(ft::pair<int, int>(i, i * 2));
	t.print();
	std::cout << "\n\n\n\n";
	t.remove(2);
	t.remove(4);
	t.remove(16);
	t.remove(7);
	t.print();
}
