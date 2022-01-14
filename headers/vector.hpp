#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "pair.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"

namespace ft
{

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	typedef typename std::size_t								size_type;
	typedef T													value_type;
	typedef typename Allocator::pointer							pointer;
	typedef typename Allocator::const_pointer					const_pointer;
	typedef typename Allocator::pointer							iterator; // need to be implemented on some iterator
	typedef typename Allocator::const_pointer					const_iterator; // need to be implemented on some iterator
	typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef typename Allocator::reference						reference;
	typedef typename Allocator::const_reference					const_reference;
	typedef Allocator											allocator_type;
	
	vector() // tested
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator() { }
	explicit vector(const Allocator& alloc) // tested
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator(alloc) { }
	explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) // tested
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator(alloc)
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
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator(alloc)
	{
		start = allocator.allocate(last - first);
		finish = start + (last - first);
		end_of_storage = finish;
		for (size_type i = 0; i < static_cast<size_type>(last - first); ++i)
			allocator.construct(start + i, *(first + i));
	}
	vector(const vector& other) // tested
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator(other.allocator)
	{
		start = allocator.allocate(other.finish - other.start);
		finish = start + (other.finish - other.start);
		end_of_storage = finish;
		for (size_type i = 0; i < static_cast<size_type>(finish - start); ++i)
			allocator.construct(start + i, *(other.start + i));
	}
	~vector() // tested
	{
		for (size_type i = 0; i < static_cast<size_type>(finish - start); ++i)
			allocator.destroy(start + i);
		allocator.deallocate(start, capacity());
		start = NULL;
		finish = NULL;
		end_of_storage = NULL;
	}
	vector &operator=(const vector& other) // tested
	{
		if (this != &other)
		{
			for (size_type i = 0; i < size(); ++i)
				allocator.destroy(start + i);
			if (other.size() > capacity())
			{
				allocator.deallocate(start, capacity());
				start = allocator.allocate(other.size());
				end_of_storage = start + other.size();
			}
			finish = start + other.size();
			for (size_type i = 0; i < static_cast<size_type>(finish - start); ++i)
				allocator.construct(start + i, *(other.start + i));
		}
		return (*this);
	}
	void assign(size_type count, const T& value) // tested
	{
		for (size_type i = 0; i < size(); ++i)
			allocator.destroy(start + i);
		if (count > capacity())
		{
			allocator.deallocate(start, capacity());
			start = allocator.allocate(count);
			end_of_storage = start + count;
		}
		finish = start + count;
		for (size_type i = 0; i < count; ++i)
			allocator.construct(start + i, value);
	}
	template <typename InputIt> // tested
	void assign(InputIt first, InputIt last,
		typename enable_if< !is_integral<InputIt>::value, InputIt >::type = InputIt())
	{
		for (size_type i = 0; i < size(); ++i)
			allocator.destroy(start + i);
		if (static_cast<size_type>(last - first) > capacity())
		{
			allocator.deallocate(start, capacity());
			start = allocator.allocate(last - first);
			end_of_storage = start + (last - first);
		}
		finish = start + (last - first);
		for (size_type i = 0; i < static_cast<size_type>(last - first); ++i)
			allocator.construct(start + i, *(first + i));
	}
	allocator_type get_allocator(void) const { return (allocator); } // tested

	// Element access
	reference		at(size_type pos) // tested
	{
		if (pos >= size())
			throw std::out_of_range("vector 'at': position out of bound");
		return ((*this)[pos]);
	}
	const_reference	at(size_type pos) const
	{
		if (pos >= size())
			throw std::out_of_range("vector const 'at': position out of bound");
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
	iterator				begin(void) 	   { return (start);  } // tested
	const_iterator			begin(void)  const { return (start);  }
	iterator				end(void)		   { return (finish); } // tested
	const_iterator			end(void)	 const { return (finish); }
	reverse_iterator		rbegin(void)	   { return (reverse_iterator(finish)); } // tested
	const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(finish)); }
	reverse_iterator		rend(void)		   { return (reverse_iterator(start)); } // tested
	const_reverse_iterator	rend(void) const   { return (const_reverse_iterator(start)); }

	// Capacity
	bool		empty(void) const { return (start == finish); } // tested
	size_type	size(void) const { return (finish - start);  } // tested
	size_type	max_size(void) const { return (allocator.max_size()); } // tested, works if vector is not nested
	void		reserve(size_type new_cap) // tested
	{
		if (new_cap > max_size())
			throw std::length_error("vector 'reserve': requested size greater than max_size()");
		if (new_cap > capacity())
		{
			iterator newStart = allocator.allocate(new_cap);
			for (size_type i = 0; i < size(); ++i)
				allocator.construct(newStart + i, *(start + i));
			for (size_type i = 0; i < size(); ++i)
				allocator.destroy(start + i);
			allocator.deallocate(start, capacity());
			finish = newStart + size();
			start = newStart;
			end_of_storage = newStart + new_cap;
		}
	}
	size_type	capacity(void) const { return (end_of_storage - start); } // tested

	// Modifiers
	void		clear(void) { erase(begin(), end()); } // tested
	iterator	insert(iterator pos, const T& value) // tested
	{
		size_type offset = pos - start;
		if (size() + 1 > capacity())
			reserve(size() * 2);		
		allocator.construct(finish, *(finish - 1));
		for (iterator i = finish - 1; i != start + offset; --i)
			*i = *(i - 1);
		*(start + offset) = value;
		finish = finish + 1;
		return (start + offset);
	}
	void		insert(iterator pos, size_type count, const T& value) // tested
	{
		size_type offset = pos - start;
		if (size() + count > capacity())
			reserve(std::max(size() * 2, size() + count));
		for (iterator i = finish + count - 1; i != finish - 1; --i)
			allocator.construct(i, *(i - count));		
		for (iterator i = finish - 1; i > start + offset + count - 1; --i)
			*i = *(i - count);
		for (iterator i = start + offset; i != start + offset + count; ++i)
			*i = value;
		finish = finish + count;
	}
	template <typename InputIt> // tested
	void		insert(iterator pos, InputIt first, InputIt last,
		typename enable_if< !is_integral<InputIt>::value, InputIt >::type = InputIt())
	{
		size_type offset = pos - start;
		if (size() + (last - first) > capacity())
			reserve(std::max(size() * 2, size() + (last - first)));
		for (iterator i = finish + (last - first) - 1; i != finish - 1; --i)
			allocator.construct(i, *(i - (last - first)));
		for (iterator i = finish - 1; i > start + offset + (last - first) - 1; --i)
			*i = *(i - (last - first));
		for (size_type i = 0; i < static_cast<size_type>(last - first); ++i)
			*(start + offset + i) = *(first + i);
		finish = finish + (last - first);
	}
	iterator	erase(iterator pos) // tested
	{
		for (iterator i = pos; i != finish - 1; ++i)
			*i = *(i + 1);
		allocator.destroy(finish - 1);
		finish = finish - 1;
		return (pos);
	}
	iterator	erase(iterator first, iterator last) // tested
	{
		for (size_type i = 0; i < static_cast<size_type>(finish - last); ++i)
			*(first + i) = *(last + i);
		for (iterator i = first + (finish - last); i != finish; ++i)
			allocator.destroy(i);
		finish = first + (finish - last);
		return (last);
	}
	void		push_back(const T& value) // tested
	{
		if (size() + 1 > capacity())
			reserve(std::max(size() * 2, static_cast<size_type>(1)));
		allocator.construct(finish, value);
		finish = finish + 1;
	}
	void		pop_back(void) // tested
	{
		allocator.destroy(finish - 1);
		finish = finish - 1;
	}
	void		resize(size_type count, T value = T()) // tested
	{
		if (size() > count)
		{
			for (size_type i = size(); i > count; --i)
				pop_back();
		}
		else if (size() < count)
		{
			reserve(count);
			insert(end(), count - size(), value);
		}
	}
	void		swap(vector& other)
	{
		iterator temp_start = start;
		iterator temp_finish = finish;
		iterator temp_end_of_storage = end_of_storage;
		Allocator temp_allocator = allocator;
		start = other.start;
		finish = other.finish;
		end_of_storage = other.end_of_storage;
		allocator = other.allocator;
		other.start = temp_start;
		other.finish = temp_finish;
		other.end_of_storage = temp_end_of_storage;
		other.allocator = temp_allocator;
	}

private:
	iterator	start;
	iterator	finish;
	iterator	end_of_storage;
	Allocator	allocator;
};

template <typename T, typename Alloc> // tested
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T, typename Alloc> // tested
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <typename T, typename Alloc> // tested
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename Alloc> // tested
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs > rhs));
}

template <typename T, typename Alloc> // tested
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <typename T, typename Alloc> // tested
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template <typename T, typename Alloc> // tested
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}

}

#endif