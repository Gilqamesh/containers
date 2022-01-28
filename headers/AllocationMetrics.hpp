#ifndef ALLOCATIONMETRICS_HPP
# define ALLOCATIONMETRICS_HPP

# include <iostream>
# define s_AllocedPointersSize 10000000

// Todo: improve bookkeeping of memory addresses

class AllocationMetrics
{
public:
	friend void *operator new(size_t size) throw(std::bad_alloc);
	friend void operator delete(void *memory) throw();
	AllocationMetrics();
	~AllocationMetrics();

	static size_t CurrentUsage() { return (TotalAlloced - TotalFreed); }
	static void addAlloced(size_t size) { TotalAlloced += size; }
	static void addFreed(size_t size) { TotalFreed += size; }
private:
	static size_t TotalAlloced;
	static size_t TotalFreed;
	static std::pair<void *, size_t> s_AllocedPointers[s_AllocedPointersSize];
	static unsigned int s_AllocedPointersIndex;
};

void *operator new(size_t size) throw(std::bad_alloc);
void operator delete(void *memory) throw();

void PrintMemoryUsage(void);

#endif
