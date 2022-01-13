#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "pair.hpp"
# include "type_traits.hpp"

// DEBUG
# include <iostream>

namespace ft
{

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	typedef typename std::size_t				size_type;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef typename Allocator::pointer			iterator;
	typedef typename Allocator::const_pointer	const_iterator;
	typedef iterator							reverse_iterator;
	typedef const_iterator						const_reverse_iterator;
	typedef typename Allocator::reference		reference;
	typedef typename Allocator::const_reference	const_reference;
	typedef Allocator							allocator_type;
	
	vector() // tested
		: start(nullptr), finish(nullptr), end_of_storage(nullptr), allocator() { }
	explicit vector(const Allocator& alloc) // tested
		: start(nullptr), finish(nullptr), end_of_storage(nullptr), allocator(alloc) { }
	explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) // tested
		: start(nullptr), finish(nullptr), end_of_storage(nullptr), allocator(alloc)
	{
		start = allocator.allocate(count);
		finish = start + count;
		end_of_storage = finish;
		for (size_type i = 0; i < count; ++i)
			allocator.construct(start + i, value);
	}
	template <typename InputIt> // tested
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		typename enable_if< !is_integral<InputIt>::value, InputIt >::type = InputIt())
		: start(nullptr), finish(nullptr), end_of_storage(nullptr), allocator(alloc)
	{
		start = allocator.allocate(last - first);
		finish = start + (last - first);
		end_of_storage = finish;
		for (size_type i = 0; i < last - first; ++i)
			allocator.construct(start + i, *(first + i));
	}
	vector(const vector& other) // tested
		: start(nullptr), finish(nullptr), end_of_storage(nullptr), allocator(other.allocator)
	{
		start = allocator.allocate(other.finish - other.start);
		finish = start + (other.finish - other.start);
		end_of_storage = finish;
		for (size_type i = 0; i < finish - start; ++i)
			allocator.construct(start + i, *(other.start + i));
	}
	~vector() // tested
	{
		for (size_type i = 0; i < finish - start; ++i)
			allocator.destroy(start + i);
		allocator.deallocate(start, end_of_storage - start);
		start = nullptr;
		finish = nullptr;
		end_of_storage = nullptr;
	}
	vector &operator=(const vector& other) // tested
	{
		if (this != &other)
		{
			this->~vector(); // using 
			start = allocator.allocate(other.finish - other.start);
			finish = start + (other.finish - other.start);
			end_of_storage = finish;
			for (size_type i = 0; i < finish - start; ++i)
				allocator.construct(start + i, *(other.start + i));
		}
		return (*this);
	}
	void assign(size_type count, const T& value) // tested
	{
		this->~vector();
		start = allocator.allocate(count);
		finish = start + count;
		end_of_storage = finish;
		for (size_type i = 0; i < count; ++i)
			allocator.construct(start + i, value);
	}
	template <typename InputIt> // tested
	void assign(InputIt first, InputIt last,
		typename enable_if< !is_integral<InputIt>::value, InputIt >::type = InputIt())
	{
		this->~vector();
		start = allocator.allocate(last - first);
		finish = start + (last - first);
		end_of_storage = finish;
		for (size_type i = 0; i < last - first; ++i)
			allocator.construct(start + i, *(first + i));
	}
	allocator_type get_allocator(void) const { return (allocator); } // tested

	// Element access
	reference		at(size_type pos) // tested
	{
		if (pos >= size())
			throw std::out_of_range("vector at method: position out of bound");
		return ((*this)[pos]);
	}
	const_reference	at(size_type pos) const
	{
		if (pos >= size())
			throw std::out_of_range("vector const at method: position out of bound");
		return ((*this)[pos]);
	}
	reference		operator[](size_type pos) 		{ return (*(start + pos)); } // tested
	const_reference	operator[](size_type pos) const { return (*(start + pos)); }
	reference		front(void)		  { return (*start);	 } // tested
	const_reference	front(void) const { return (*start);	 }
	reference		back(void)		  { return (*(finish - 1)); } // tested
	const_reference	back(void)  const { return (*(finish - 1)); }
	pointer			data(void)		  { return (start);		 } // tested
	const_pointer	data(void) const  { return (start);		 }

	// Iterators
	iterator		begin(void) 	  { return (start);  } // tested
	const_iterator	begin(void) const { return (start);  }
	iterator		end(void)		  { return (finish); } // tested
	const_iterator	end(void)	const { return (finish); }

	// Capacity
	size_type	size(void) const { return (finish - start); } // tested

private:
	iterator	start;
	iterator	finish;
	iterator	end_of_storage;
	Allocator	allocator;
};

}

#endif
