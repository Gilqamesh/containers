# include <iostream>
# include "map.hpp"
# include <map>

int main()
{
	ft::map<int, int>	a;

	// ft::red_black_tree<ft::map_node<int, int> >	t;

	// for (unsigned int i = 1; i <= 20; ++i)
	// 	t.insert(ft::pair<int, int>(i, i * 2));
	// t.print();

	for (ft::map<int, int>::iterator i = a.begin(); i != a.end(); ++i)
	{
		std::cout << i->first << std::endl;
	}
	// std::cout << "\n\n\n\n";
	// t.remove(2);
	// t.remove(4);
	// t.remove(16);
	// t.remove(7);
	// t.print();
}
