#include <iostream>
#include <string>
#include <deque>
#include <ctime>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "set.hpp"
#define TESTED_NAMESPACE ft
#ifdef STDSTL
# undef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
#endif

# define VECTOR_TEST	1
# define MAP_TEST		1
# define STACK_TEST		1
# define SET_TEST		1

#include <stdlib.h>

#ifndef LOG
# define LOG(x) (std::cout << x << std::endl)
#endif

template <typename T>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::vector<T>& v);
template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::map<Key, T>& m);
template <typename first, typename second>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::pair<first, second>& p);
template <typename Key>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::set<Key>& s);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		return (1);
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	#if VECTOR_TEST
	// Vector
	{
	// Basic functionality
		TESTED_NAMESPACE::vector<int, std::allocator<int> > vectorTest;
		// non-iterator assign
			vectorTest.assign(5, 20);
			LOG("5 * 20: " << vectorTest);
		// get allocator test
			TESTED_NAMESPACE::vector<int>::allocator_type vectorAllocator = vectorTest.get_allocator();
			int *intPointer = vectorAllocator.allocate(1);
			vectorAllocator.construct(intPointer, 5);
			LOG("allocated 1 int with value of 5: " << *intPointer);
			vectorAllocator.destroy(intPointer);
			vectorAllocator.deallocate(intPointer, 1);
		// copy construct
			TESTED_NAMESPACE::vector<int> vectorTest2(vectorTest);
			LOG("After copy construct, vectorTest2: " << vectorTest2);
		// at
			// non-const version
				try
				{
					LOG("vectorTest.at(0): " << vectorTest.at(0));
					vectorTest2.at(1) = 42;
					LOG("vectorTest2.at(1): " << vectorTest2.at(1));
					LOG(vectorTest.at(10)); // should throw exception
				}
				catch (std::exception &e)
				{
					LOG("Exception caught: " << e.what());
				}
			// const-version
				const TESTED_NAMESPACE::vector<int>& vectorTestConstReference = vectorTest;
				LOG("Still 5 * 20: " << vectorTestConstReference);
				// vectorTestConstReference.at(0) = 5; can't assign to const reference
		// operator[]
			vectorTest[0] = 8;
			vectorTest2[0] = 10;
			vectorTest[4] = -12;
			vectorTest2[4] = 9;
			LOG("vectorTest[0] = 8: " << vectorTest[0]);
			LOG("vectorTest2[0] = 10: " << vectorTest2[0]);
			LOG("vectorTest[4] = -12: " << vectorTest[4]);
			LOG("vectorTest2[4] = 9: " << vectorTest2[4]);
		// front, back, data
			LOG("vectorTest.front(): " << vectorTest.front());
			LOG("vectorTest.back(): " << vectorTest.back());
			LOG("vectorTest.data(): " << vectorTest.data() << " *vectorTest.data(): " << *vectorTest.data());
			LOG("vectorTest2.front(): " << vectorTest2.front());
			LOG("vectorTest2.back(): " << vectorTest2.back());
			LOG("vectorTest2.data(): " << vectorTest2.data() << " *vectorTest.data(): " << *vectorTest2.data());
		// empty, size, max_size, reserve, capacity, resize
			TESTED_NAMESPACE::vector<double> vectorTest3;
			LOG("vectorTest.empty(): " << vectorTest.empty());
			LOG("vectorTest2.empty(): " << vectorTest2.empty());
			LOG("vectorTest3.empty(): " << vectorTest3.empty());
			LOG("vectorTest.size(): " << vectorTest.size());
			LOG("vectorTest3.size(): " << vectorTest3.size());
			LOG("vectorTest.max_size(): " << vectorTest.max_size());
			LOG("vectorTest3.max_size(): " << vectorTest3.max_size());
			LOG("vectorTest.capacity(): " << vectorTest.capacity());
			LOG("vectorTest3.capacity(): " << vectorTest3.capacity());
			vectorTest.reserve(100);
			LOG("vectorTest.reserve(100);");
			LOG("vectorTest.capacity(): " << vectorTest.capacity());
			LOG("vectorTest.resize(1000);"); vectorTest.resize(1000);
			LOG("vectorTest: " << vectorTest);
		// assign iterator version
			vectorTest.assign(vectorTest2.begin(), vectorTest2.end());
			LOG("vectorTest.assign(vectorTest2.begin(), vectorTest2.end());");
			LOG("vectorTest2: " << vectorTest2);
			LOG("vectorTest: " << vectorTest);
			LOG("vectorTest.capacity(): " << vectorTest.capacity());
			LOG("vectorTest.size(): " << vectorTest.size());
		// iterators
			LOG("*vectorTest.begin(): " << *vectorTest.begin());
			LOG("*--vectorTest.end(): " << *--vectorTest.end());
			LOG("Const iterator");
			LOG("for (TESTED_NAMESPACE::vector<int>::const_iterator cit = vectorTest.begin(); cit != vectorTest.end(); ++cit)\n"\
				"\tLOG(\"*cit: \" << *cit);\n{");
			for (TESTED_NAMESPACE::vector<int>::const_iterator cit = vectorTest.begin(); cit != vectorTest.end(); ++cit)
				LOG("\t*cit: " << *cit);
			LOG("}");
			LOG("Non-const iterator");
			LOG("for (TESTED_NAMESPACE::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end(); ++it)\n"\
				"\tLOG(\"*cit: \" << *cit);\n{");
			for (TESTED_NAMESPACE::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end(); ++it)
				LOG("\t*it: " << *it);
			LOG("}");
		// clear, insert, erase
			LOG("vectorTest.clear()"); vectorTest.clear();
			LOG("vectorTest.size(): " << vectorTest.size() << " vectorTest: " << vectorTest << "vectorTest.capacity(): " << vectorTest.capacity());
			LOG("vectorTest.insert(vectorTest.end(), 3, 10);"); vectorTest.insert(vectorTest.end(), 3, 10);
			LOG("vectorTest: " << vectorTest);
			LOG("vectorTest.erase(vectorTest.begin());"); vectorTest.erase(vectorTest.begin());
			LOG("vectorTest: " << vectorTest);
			LOG("vectorTest.insert(vectorTest.begin(), vectorTest2.begin(), vectorTest2.end());"); vectorTest.insert(vectorTest.begin(), vectorTest2.begin(), vectorTest2.end());
			LOG("for (TESTED_NAMESPACE::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end();)\n"\
				"\tit = vectorTest.erase(it);;\n\tLOG(\"vectorTest: \" << vectorTest);\n{");
			for (TESTED_NAMESPACE::vector<int>::iterator it = vectorTest.begin(); it != vectorTest.end();)
			{
				it = vectorTest.erase(it);
				LOG("\tvectorTest: " << vectorTest);
			}
			LOG("}");
		// push_back, pop_back
			LOG("vectorTest.push_back(5);"); vectorTest.push_back(5);
			LOG("vectorTest.push_back(4);"); vectorTest.push_back(4);
			LOG("vectorTest.push_back(3);"); vectorTest.push_back(3);
			LOG("vectorTest.push_back(2);"); vectorTest.push_back(2);
			LOG("vectorTest.push_back(1);"); vectorTest.push_back(1);
			LOG("vectorTest: " << vectorTest);
			LOG("vectorTest.pop_back();"); vectorTest.pop_back();
			LOG("vectorTest.pop_back();"); vectorTest.pop_back();
			LOG("vectorTest.pop_back();"); vectorTest.pop_back();
			LOG("vectorTest.pop_back();"); vectorTest.pop_back();
			LOG("vectorTest: " << vectorTest);
		// swap
			LOG("vectorTest.swap(vectorTest2);"); vectorTest.swap(vectorTest2);
			LOG("vectorTest: " << vectorTest << " vectorTest2: " << vectorTest2);
			LOG("vectorTest.size(): " << vectorTest.size() << " vectorTest2.size(): " << vectorTest2.size());
			LOG("vectorTest.capacity(): " << vectorTest.capacity() << " vectorTest2.capacity(): " << vectorTest2.capacity());
			LOG("swap(vectorTest, vectorTest2);"); swap(vectorTest, vectorTest2);
			LOG("vectorTest: " << vectorTest << " vectorTest2: " << vectorTest2);
			LOG("vectorTest.size(): " << vectorTest.size() << " vectorTest2.size(): " << vectorTest2.size());
			LOG("vectorTest.capacity(): " << vectorTest.capacity() << " vectorTest2.capacity(): " << vectorTest2.capacity());
		// compare operators
			LOG("vectorTest == vectorTest2: " << (vectorTest == vectorTest2));
			LOG("vectorTest != vectorTest2: " << (vectorTest != vectorTest2));
			LOG("vectorTest < vectorTest2: " << (vectorTest < vectorTest2));
			LOG("vectorTest <= vectorTest2: " << (vectorTest <= vectorTest2));
			LOG("vectorTest > vectorTest2: " << (vectorTest > vectorTest2));
			LOG("vectorTest >= vectorTest2: " << (vectorTest >= vectorTest2));
		// iterator constructor
			LOG("TESTED_NAMESPACE::vector<int> vectorTest4(vectorTest2.begin(), vectorTest2.end());");
			TESTED_NAMESPACE::vector<int> vectorTest4(vectorTest2.begin(), vectorTest2.end());
			LOG("vectorTest4: " << vectorTest4);
			LOG("vectorTest2: " << vectorTest2);
	// Performance test
		clock_t begin = std::clock();
		LOG("push_back 100.000.000 ints");
		for (size_t i = 0; i < 100000000; ++i)
			vectorTest.push_back(std::rand());
		LOG("vectorTest.size(): " << vectorTest.size());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
		begin = std::clock();
		LOG("vectorTest5(vectorTest);");
		TESTED_NAMESPACE::vector<int> vectorTest5(vectorTest);
		LOG("vectorTest5.size(): " << vectorTest5.size());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
		begin = std::clock();
		LOG("vectorTest2.assign(vectorTest5.begin(), vectorTest5.end());"); vectorTest2.assign(vectorTest5.begin(), vectorTest5.end());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");
	}
	LOG("Leak check:");
	#ifndef STDSTL
		system("leaks mycontainer | tail -3");
	#else
		system("leaks defaultcontainer | tail -3");
	#endif
	#endif // vector test

	#if MAP_TEST
	// Map
	{
	// Basic functionality
		TESTED_NAMESPACE::map<int, std::string> mapTest;
		// non-iterator, non-hint insert
			TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<int, std::string>::iterator, bool> mapPair
				= mapTest.insert(TESTED_NAMESPACE::make_pair<int, std::string>(5, "so long"));
			LOG("Inserting (5, \"so long\"): " << *mapPair.first << " successful insertion: " << mapPair.second);
			mapPair = mapTest.insert(TESTED_NAMESPACE::make_pair<int, std::string>(5, "so long 2"));
			LOG("Inserting (5, \"so long2\"): " << *mapPair.first << " successful insertion: " << mapPair.second);
			LOG("mapTest: " << mapTest);
			LOG("mapTest[5] = \"blah\";"); mapTest[5] = "blah";
			LOG("mapTest[1] = \"get_next_line\";"); mapTest[1] = "get_next_line";
			LOG("mapTest: " << mapTest);
		// at
			try
			{
				LOG("mapTest.at(1): " << mapTest.at(1));
				LOG("mapTest.at(5): " << mapTest.at(5));
				LOG("mapTest.at(2): " << mapTest.at(2));
			}
			catch (std::exception &e)
			{
				LOG("Exception caught: " << e.what());
			}
		// empty, size, max_size, clear
			TESTED_NAMESPACE::map<int, std::string> mapTest2;
			LOG("mapTest.empty(): " << mapTest.empty());
			LOG("mapTest2.empty(): " << mapTest2.empty());
			LOG("mapTest.size(): " << mapTest.size());
			LOG("mapTest.max_size(): " << mapTest.max_size());
			LOG("mapTest.clear();"); mapTest.clear();
			LOG("mapTest: " << mapTest);
		// order check
			LOG("mapTest[42] = \"The Hitchhiker's Guide to the Galaxy\";"); mapTest[42] = "The Hitchhiker's Guide to the Galaxy";
			LOG("mapTest[-1] = \"born to be root\";"); mapTest[-1] = "born to be root";
			LOG("mapTest[11] = \"push_swap\";"); mapTest[11] = "push_swap";
			LOG("mapTest[0] = \"libft\";"); mapTest[0] = "libft";
			LOG("mapTest[14] = \"ft_containers\";"); mapTest[14] = "ft_containers";
			LOG("mapTest.size(): " << mapTest.size());
			LOG("mapTest: " << mapTest);
		// iterators, copy constructor, assignment operator
			LOG("for (TESTED_NAMESPACE::map<int, std::string>::const_iterator cit = mapTest.begin(); cit != mapTest.end(); ++cit)"\
				"\n\tLOG(*cit);\n{");
			for (TESTED_NAMESPACE::map<int, std::string>::const_iterator cit = mapTest.begin(); cit != mapTest.end(); ++cit)
				LOG("\t" << *cit);
			LOG("}");
			TESTED_NAMESPACE::map<int, std::string> mapTest3(mapTest);
			LOG("mapTest3(mapTest): " << mapTest3);
			LOG("for (TESTED_NAMESPACE::map<int, std::string>::iterator it = mapTest.begin(); it != mapTest.end(); ++it)"\
				"\n\tLOG(*it);\n{");
			for (TESTED_NAMESPACE::map<int, std::string>::iterator it = mapTest.begin(); it != mapTest.end(); ++it)
			{
				it->second = "override amazing projects with nonsense";
				LOG("\t" << *it);
			}
			LOG("}");
			LOG("mapTest: " << mapTest);
			LOG("mapTest = mapTest3;"); mapTest = mapTest3;
			LOG("mapTest: " << mapTest);
		// lower bound, upper bound, equal range
			LOG("mapTest.lower_bound(0): " << *mapTest.lower_bound(0));
			LOG("mapTest.lower_bound(1): " << *mapTest.lower_bound(1));
			LOG("mapTest.upper_bound(0): " << *mapTest.upper_bound(0));
			LOG("mapTest.upper_bound(1): " << *mapTest.upper_bound(1));
			TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<int, std::string>::const_iterator,
				TESTED_NAMESPACE::map<int, std::string>::const_iterator> constIterPair = mapTest.equal_range(0);
			LOG("mapTest.equal_range(0): " << *constIterPair.first << " " << *constIterPair.second);
			constIterPair = mapTest.equal_range(1);
			LOG("mapTest.equal_range(1): " << *constIterPair.first << " " << *constIterPair.second);
		// erase, swap
			LOG("mapTest.erase(100): " << mapTest.erase(100));
			LOG("mapTest.erase(0): " << mapTest.erase(0));
			LOG("mapTest.erase(-123): " << mapTest.erase(-123));
			LOG("mapTest.erase(14): " << mapTest.erase(14));
			LOG("mapTest: " << mapTest);
			LOG("mapTest.swap(mapTest3);"); mapTest.swap(mapTest3);
			LOG("mapTest: " << mapTest);
			LOG("mapTest3: " << mapTest3);
			LOG("mapTest.size(): " << mapTest.size() << " mapTest3.size(): " << mapTest3.size());
			LOG("swap(mapTest, mapTest3);"); swap(mapTest, mapTest3);
			LOG("mapTest: " << mapTest);
			LOG("mapTest3: " << mapTest3);
			LOG("mapTest.size(): " << mapTest.size() << " mapTest3.size(): " << mapTest3.size());
		// count, find
			LOG("mapTest3.count(0): " << mapTest3.count(0));
			LOG("mapTest3.count(1): " << mapTest3.count(1));
			LOG("mapTest3.count(2): " << mapTest3.count(2));
			LOG("mapTest3.count(14): " << mapTest3.count(14));
			if (mapTest3.find(0) == mapTest3.end())
				LOG("mapTest3.find(0): -");
			else
				LOG("mapTest3.find(0): " << *mapTest3.find(0));
			if (mapTest3.find(1) == mapTest3.end())
				LOG("mapTest3.find(1): -");
			else
				LOG("mapTest3.find(1): " << *mapTest3.find(1));
			if (mapTest3.find(2) == mapTest3.end())
				LOG("mapTest3.find(2): -");
			else
				LOG("mapTest3.find(2): " << *mapTest3.find(2));
			if (mapTest3.find(14) == mapTest3.end())
				LOG("mapTest3.find(14): -");
			else
				LOG("mapTest3.find(14): " << *mapTest3.find(14));
		// compare operators
			LOG("mapTest == mapTest3: " << (mapTest == mapTest3));
			LOG("mapTest != mapTest3: " << (mapTest != mapTest3));
			LOG("mapTest < mapTest3: " << (mapTest < mapTest3));
			LOG("mapTest <= mapTest3: " << (mapTest <= mapTest3));
			LOG("mapTest > mapTest3: " << (mapTest > mapTest3));
			LOG("mapTest >= mapTest3: " << (mapTest >= mapTest3));
		// key_comp, value_comp
			TESTED_NAMESPACE::map<int, std::string>::key_compare mapKeyComp = mapTest.key_comp();
			TESTED_NAMESPACE::map<int, std::string>::value_compare mapValueComp = mapTest.value_comp();
			LOG("mapKeyComp(3, 6): " << mapKeyComp(3, 6));
			LOG("mapValueComp(*mapTest3.find(0), *mapTest3.find(14)): " << mapValueComp.operator()(*mapTest3.find(0), *mapTest3.find(14)));
			LOG("mapValueComp(*mapTest3.find(14), *mapTest3.find(0)): " << mapValueComp.operator()(*mapTest3.find(14), *mapTest3.find(0)));
	// Performance test
		LOG("Insert 10.000.000 pairs without hint");
		clock_t begin = std::clock();
		for (size_t i = 0; i < 10000000; ++i)
			mapTest.insert(TESTED_NAMESPACE::make_pair<int, std::string>(std::rand() % 1000000, "text number: " + std::to_string(i)));
		LOG("mapTest.size(): " << mapTest.size());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("mapTest4(mapTest);");
		begin = std::clock();
		TESTED_NAMESPACE::map<int, std::string> mapTest4(mapTest);
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("mapTest4.clear();");
		begin = std::clock();
		mapTest4.clear();
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("Iterator insert from mapTest to mapTest5");
		begin = std::clock();
		TESTED_NAMESPACE::map<int, std::string> mapTest5(mapTest.begin(), mapTest.end());
		LOG("mapTest5.size(): " << mapTest5.size());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("Erase 10.000.000 random elements");
		begin = std::clock();
		for (size_t i = 0; i < 10000000; ++i)
			mapTest.erase(std::rand() % 10000000);
		LOG("mapTest.size(): " << mapTest.size());
	}
	LOG("Leak check:");
	#ifndef STDSTL
		system("leaks mycontainer | tail -3");
	#else
		system("leaks defaultcontainer | tail -3");
	#endif
	#endif // map test

	#if STACK_TEST
	{ // Stack
	// Basic functionality
		TESTED_NAMESPACE::stack<int> stackTest;
		LOG("stackTest.size(): " << stackTest.size() << " stackTest.empty(): " << stackTest.empty());
		LOG("Pushing 100 elements to stackTest");
		for (size_t i = 0; i < 100; ++i)
		{
			stackTest.push(std::rand() % 10000);
			std::cout << stackTest.top() << " ";
		}
		std::cout << std::endl;
		TESTED_NAMESPACE::stack<int> stackTest2(stackTest);
		LOG("stackTest2(stackTest);");
		LOG("stackTest2.size(): " << stackTest2.size() << " stackTest2.empty(): " << stackTest2.empty());
		LOG("stackTest.size(): " << stackTest.size() << " stackTest.empty(): " << stackTest.empty());
		LOG("Popping 100 elements from stackTest");
		while (!stackTest.empty())
		{
			std::cout << stackTest.top() << " ";
			stackTest.pop();
		}
		std::cout << std::endl;
		LOG("stackTest.size(): " << stackTest.size() << " stackTest.empty(): " << stackTest.empty());
		LOG("stackTest2 = stackTest;"); stackTest2 = stackTest;
		LOG("stackTest2.size(): " << stackTest2.size() << " stackTest2.empty(): " << stackTest2.empty());
	}
	LOG("Leak check:");
	#ifndef STDSTL
		system("leaks mycontainer | tail -3");
	#else
		system("leaks defaultcontainer | tail -3");
	#endif
	#endif // stack test
	
	#if SET_TEST
	// Set
	{
	// Basic functionality
		TESTED_NAMESPACE::set<int> setTest;
		// non-iterator, non-hint insert
			TESTED_NAMESPACE::pair<TESTED_NAMESPACE::set<int>::iterator, bool> setPair = setTest.insert(5);
			LOG("Inserting 5: " << *setPair.first << " successful insertion: " << setPair.second);
			setPair = setTest.insert(5);
			LOG("Inserting 5: " << *setPair.first << " successful insertion: " << setPair.second);
			LOG("setTest: " << setTest);
		// empty, size, max_size, clear
			TESTED_NAMESPACE::set<int> setTest2;
			LOG("setTest.empty(): " << setTest.empty());
			LOG("setTest2.empty(): " << setTest2.empty());
			LOG("setTest.size(): " << setTest.size());
			LOG("setTest.max_size(): " << setTest.max_size());
			LOG("setTest.clear();"); setTest.clear();
			LOG("setTest: " << setTest);
		// order check
			LOG("setTest.insert(42);"); setTest.insert(42);
			LOG("setTest.insert(-1);"); setTest.insert(-1);
			LOG("setTest.insert(11);"); setTest.insert(11);
			LOG("setTest.insert(0);"); setTest.insert(0);
			LOG("setTest.insert(14);"); setTest.insert(14);
			LOG("setTest.size(): " << setTest.size());
			LOG("setTest: " << setTest);
		// iterators, copy constructor, assignment operator
			LOG("for (TESTED_NAMESPACE::set<int>::const_iterator cit = setTest.begin(); cit != setTest.end(); ++cit)"\
				"\n\tLOG(*cit);\n{");
			for (TESTED_NAMESPACE::set<int>::const_iterator cit = setTest.begin(); cit != setTest.end(); ++cit)
				LOG("\t" << *cit);
			LOG("}");
			TESTED_NAMESPACE::set<int> setTest3(setTest);
			LOG("setTest3(setTest): " << setTest3);
		// lower bound, upper bound, equal range
			LOG("setTest.lower_bound(0): " << *setTest.lower_bound(0));
			LOG("setTest.lower_bound(1): " << *setTest.lower_bound(1));
			LOG("setTest.upper_bound(0): " << *setTest.upper_bound(0));
			LOG("setTest.upper_bound(1): " << *setTest.upper_bound(1));
			TESTED_NAMESPACE::pair<TESTED_NAMESPACE::set<int>::const_iterator,
				TESTED_NAMESPACE::set<int>::const_iterator> constIterPair = setTest.equal_range(0);
			LOG("setTest.equal_range(0): " << *constIterPair.first << " " << *constIterPair.second);
			constIterPair = setTest.equal_range(1);
			LOG("setTest.equal_range(1): " << *constIterPair.first << " " << *constIterPair.second);
		// erase, swap
			LOG("setTest.erase(100): " << setTest.erase(100));
			LOG("setTest.erase(0): " << setTest.erase(0));
			LOG("setTest.erase(-123): " << setTest.erase(-123));
			LOG("setTest.erase(14): " << setTest.erase(14));
			LOG("setTest: " << setTest);
			LOG("setTest.swap(setTest3);"); setTest.swap(setTest3);
			LOG("setTest: " << setTest);
			LOG("setTest3: " << setTest3);
			LOG("setTest.size(): " << setTest.size() << " setTest3.size(): " << setTest3.size());
			LOG("swap(setTest, setTest3);"); swap(setTest, setTest3);
			LOG("setTest: " << setTest);
			LOG("setTest3: " << setTest3);
			LOG("setTest.size(): " << setTest.size() << " setTest3.size(): " << setTest3.size());
		// count, find
			LOG("setTest3.count(0): " << setTest3.count(0));
			LOG("setTest3.count(1): " << setTest3.count(1));
			LOG("setTest3.count(2): " << setTest3.count(2));
			LOG("setTest3.count(14): " << setTest3.count(14));
			if (setTest3.find(0) == setTest3.end())
				LOG("setTest3.find(0): -");
			else
				LOG("setTest3.find(0): " << *setTest3.find(0));
			if (setTest3.find(1) == setTest3.end())
				LOG("setTest3.find(1): -");
			else
				LOG("setTest3.find(1): " << *setTest3.find(1));
			if (setTest3.find(2) == setTest3.end())
				LOG("setTest3.find(2): -");
			else
				LOG("setTest3.find(2): " << *setTest3.find(2));
			if (setTest3.find(14) == setTest3.end())
				LOG("setTest3.find(14): -");
			else
				LOG("setTest3.find(14): " << *setTest3.find(14));
		// compare operators
			LOG("setTest == setTest3: " << (setTest == setTest3));
			LOG("setTest != setTest3: " << (setTest != setTest3));
			LOG("setTest < setTest3: " << (setTest < setTest3));
			LOG("setTest <= setTest3: " << (setTest <= setTest3));
			LOG("setTest > setTest3: " << (setTest > setTest3));
			LOG("setTest >= setTest3: " << (setTest >= setTest3));
		// key_comp, value_comp
			TESTED_NAMESPACE::set<int>::key_compare setKeyComp = setTest.key_comp();
			TESTED_NAMESPACE::set<int>::value_compare setValueComp = setTest.value_comp();
			LOG("setKeyComp(3, 6): " << setKeyComp(3, 6));
			LOG("setValueComp(*setTest3.find(0), *setTest3.find(14)): " << setValueComp.operator()(*setTest3.find(0), *setTest3.find(14)));
			LOG("setValueComp(*setTest3.find(14), *setTest3.find(0)): " << setValueComp.operator()(*setTest3.find(14), *setTest3.find(0)));
	// Performance test
		LOG("Insert 10.000.000 pairs without hint");
		clock_t begin = std::clock();
		for (size_t i = 0; i < 10000000; ++i)
			setTest.insert(std::rand() % 1000000);
		LOG("setTest.size(): " << setTest.size());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("setTest4(setTest);");
		begin = std::clock();
		TESTED_NAMESPACE::set<int> setTest4(setTest);
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("setTest4.clear();");
		begin = std::clock();
		setTest4.clear();
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("Iterator insert from mapTest to mapTest5");
		begin = std::clock();
		TESTED_NAMESPACE::set<int> setTest5(setTest.begin(), setTest.end());
		LOG("setTest5.size(): " << setTest5.size());
		LOG("Time taken: " << static_cast<double>((std::clock() - begin)) / CLOCKS_PER_SEC << " seconds");

		LOG("Erase 10.000.000 random elements");
		begin = std::clock();
		for (size_t i = 0; i < 10000000; ++i)
			setTest.erase(std::rand() % 10000000);
		LOG("setTest.size(): " << setTest.size());
	}
	LOG("Leak check:");
	#ifndef STDSTL
		system("leaks mycontainer | tail -3");
	#else
		system("leaks defaultcontainer | tail -3");
	#endif
	#endif // set test

	return (0);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::vector<T>& v)
{
	for (typename TESTED_NAMESPACE::vector<T>::const_iterator cit = v.begin(); cit != v.end(); ++cit)
		os << "[" << *cit << "]" << " ";
	return (os);
}

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::map<Key, T>& m)
{
	for (typename TESTED_NAMESPACE::map<Key, T>::const_iterator cit = m.begin(); cit != m.end(); ++cit)
		os << *cit << " ";
	return (os);
}

template <typename first, typename second>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::pair<first, second>& p)
{
	os << "[" << p.first << ", " << p.second << "]";
	return (os);
}

template <typename Key>
std::ostream &operator<<(std::ostream &os, const TESTED_NAMESPACE::set<Key>& s)
{
	for (typename TESTED_NAMESPACE::set<Key>::const_iterator cit = s.begin(); cit != s.end(); ++cit)
		os << *cit << " ";
	return (os);
}
