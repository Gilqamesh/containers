#include "AllocationMetrics.hpp"

#include <iostream>

size_t AllocationMetrics::TotalAlloced = 0;
size_t AllocationMetrics::TotalFreed = 0;
unsigned int AllocationMetrics::s_AllocedPointersIndex = 0;
std::pair<void *, size_t> AllocationMetrics::s_AllocedPointers[s_AllocedPointersSize];

AllocationMetrics::AllocationMetrics() { }

AllocationMetrics::~AllocationMetrics() { }

void *operator new(size_t size) throw(std::bad_alloc)
{
	void *ret = malloc(size);
	if (ret == NULL)
		throw std::bad_alloc();
	AllocationMetrics::addAlloced(size);
	AllocationMetrics::s_AllocedPointers[AllocationMetrics::s_AllocedPointersIndex].first = ret;
	AllocationMetrics::s_AllocedPointers[AllocationMetrics::s_AllocedPointersIndex].second = size;
	++AllocationMetrics::s_AllocedPointersIndex;
	return (ret);
}

void operator delete(void *memory) throw()
{
	unsigned int index = 0;
	while (AllocationMetrics::s_AllocedPointers[index].first != memory)
		++index;
	AllocationMetrics::addFreed(AllocationMetrics::s_AllocedPointers[index].second);
	for (unsigned int i = index; i < AllocationMetrics::s_AllocedPointersIndex - 1; ++i)
		AllocationMetrics::s_AllocedPointers[i] = AllocationMetrics::s_AllocedPointers[i + 1];
	--AllocationMetrics::s_AllocedPointersIndex;
	free(memory);
}

void PrintMemoryUsage(void)
{
	std::cout << "Memory Usage: " << AllocationMetrics::CurrentUsage() << " bytes" << std::endl;
}
