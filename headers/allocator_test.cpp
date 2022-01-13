#include <memory>
#include <iostream>

int main()
{
	typedef  std::allocator<int> 			type;
	typedef  std::allocator<int>::pointer	iter;
	type a;
	iter p = a.allocate(100);
	a.construct(p, 2);
	a.construct(p + 1, 5);
	a.construct(p + 3, -10);
	a.destroy(p + 1);

	for (iter i = p; i != p + 10; ++i)
		std::cout << *i << std::endl;
	a.deallocate(p, 100);
}