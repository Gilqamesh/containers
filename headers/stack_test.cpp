#include <stack>
#include <iostream>
#include "stack.hpp"

# define TESTED_NAMESPACE std
#ifndef LOG
# define LOG(x) (std::cout << (x) << std::endl)
#endif

int main()
{
	TESTED_NAMESPACE::stack<int> a;
	a.push(4);
	LOG(a.top());
	a.pop();
	LOG(a.top());
}
