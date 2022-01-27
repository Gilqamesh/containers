#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "utility.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"

# include <iostream>
# define PRINT_HERE() (std::cout << __FILE__ << " " << __LINE__ << std::endl)

namespace ft
{

template <typename T>
class vector_iterator
{
public:
	typedef iterator<random_access_iterator_tag, T>							iterator_type;
	typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
	typedef typename iterator_traits<iterator_type>::value_type				value_type;
	typedef typename iterator_traits<iterator_type>::pointer				pointer;
	typedef typename iterator_traits<iterator_type>::reference				reference;
	typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

	vector_iterator()
		: m_ptr(NULL) { }
	vector_iterator(pointer ptr)
		: m_ptr(ptr) { }
	vector_iterator(const vector_iterator& other)
		: m_ptr(other.base()) { }
	~vector_iterator() { }
	operator			vector_iterator<const T>() const { return (vector_iterator<const T>(base())); }
	vector_iterator&	operator=(const vector_iterator& other) { if (this != &other) m_ptr = other.m_ptr; return (*this); }
	difference_type		operator-(const vector_iterator& other) const { return (m_ptr - other.m_ptr); }
	vector_iterator&	operator++(void) { ++m_ptr; return (*this); }
	vector_iterator		operator++(int) { vector_iterator temp(*this); ++m_ptr; return (temp); }
	vector_iterator&	operator--(void) { --m_ptr; return (*this); }
	vector_iterator		operator--(int) { vector_iterator temp(*this); --m_ptr; return (temp); }
	
	reference			operator[](difference_type index) const { return (*(m_ptr + index)); }
	pointer				operator->() const { return (m_ptr); }
	reference			operator*() const { return (*m_ptr); }
	vector_iterator		&operator-=(const vector_iterator& other) { m_ptr = m_ptr - other.m_ptr; return (*this); }
	vector_iterator		operator+(difference_type n) const { return (vector_iterator(m_ptr + n)); }
	vector_iterator		operator-(difference_type n) const { return (vector_iterator(m_ptr - n)); }
	vector_iterator		&operator+=(difference_type n) { m_ptr += n; return (*this); }
	vector_iterator		&operator-=(difference_type n) { m_ptr -= n; return (*this); }

	pointer				base() const { return (m_ptr); }
private:
	pointer	m_ptr;
};

template <class Iterator1, class Iterator2>
bool operator==(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator!=(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator<=(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator>(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator1, class Iterator2>
bool operator>=(const vector_iterator<Iterator1>& lhs, const vector_iterator<Iterator2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iter>
vector_iterator<Iter> operator+(typename vector_iterator<Iter>::difference_type n, const vector_iterator<Iter>& it)
{
	return (vector_iterator<Iter>(it.base() + n));
}

template <class Iter>
typename vector_iterator<Iter>::difference_type operator-(const vector_iterator<Iter>& lhs, const vector_iterator<Iter>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <class Iter1, class Iter2>
typename vector_iterator<Iter1>::difference_type operator-(const vector_iterator<Iter1>& lhs, const vector_iterator<Iter2>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	typedef T													value_type;
	typedef Allocator											allocator_type;
	typedef typename std::size_t								size_type;
	typedef typename std::ptrdiff_t								difference_type;
	typedef value_type&											reference;
	typedef const value_type&									const_reference;
	typedef value_type*											pointer;
	typedef const value_type*									const_pointer;
	typedef vector_iterator<value_type>							iterator;
	typedef vector_iterator<const value_type>					const_iterator;
	typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	
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
			allocator.construct(start.base() + i, value);
	}
	template <typename InputIt> // tested
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		typename ft::enable_if< !is_integral<InputIt>::value, InputIt >::type = InputIt())
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator(alloc)
	{
		difference_type dist = ft::distance(first, last);
		start = allocator.allocate(dist);
		finish = start + dist;
		end_of_storage = finish;
		for (difference_type i = 0; i < dist; ++i)
			allocator.construct(start.base() + i, *first++);
	}
	vector(const vector& other) // tested
		: start(NULL), finish(NULL), end_of_storage(NULL), allocator(other.allocator)
	{
		start = allocator.allocate(other.finish - other.start);
		finish = start + (other.finish - other.start);
		end_of_storage = finish;
		for (difference_type i = 0; i < finish - start; ++i)
			allocator.construct(start.base() + i, *(other.start + i));
	}
	~vector() // tested
	{
		for (difference_type i = 0; i < finish - start; ++i)
			allocator.destroy(start.base() + i);
		allocator.deallocate(start.base(), capacity());
		start = NULL;
		finish = NULL;
		end_of_storage = NULL;
	}
	vector &operator=(const vector& other) // tested
	{
		if (this != &other)
		{
			for (size_type i = 0; i < size(); ++i)
				allocator.destroy(start.base() + i);
			if (other.size() > capacity())
			{
				allocator.deallocate(start.base(), capacity());
				start = allocator.allocate(other.size());
				end_of_storage = start + other.size();
			}
			finish = start + other.size();
			for (difference_type i = 0; i < finish - start; ++i)
				allocator.construct(start.base() + i, *(other.start + i));
		}
		return (*this);
	}
	void assign(size_type count, const T& value) // tested
	{
		for (size_type i = 0; i < size(); ++i)
			allocator.destroy(start.base() + i);
		if (count > capacity())
		{
			allocator.deallocate(start.base(), capacity());
			start = allocator.allocate(count);
			end_of_storage = start + count;
		}
		finish = start + count;
		for (size_type i = 0; i < count; ++i)
			allocator.construct(start.base() + i, value);
	}
	template <typename InputIt> // tested
	void assign(InputIt first, InputIt last,
		typename enable_if< !is_integral<InputIt>::value, InputIt >::type = InputIt())
	{
		difference_type dist = ft::distance(first, last);
		for (size_type i = 0; i < size(); ++i)
			allocator.destroy(start.base() + i);
		if (static_cast<size_type>(dist) > capacity())
		{
			allocator.deallocate(start.base(), capacity());
			start = allocator.allocate(dist);
			end_of_storage = start + dist;
		}
		finish = start + dist;
		for (difference_type i = 0; i < dist; ++i)
			allocator.construct(start.base() + i, *first++);
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
	const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(finish)); } // tested
	reverse_iterator		rend(void)		   { return (reverse_iterator(start)); } // tested
	const_reverse_iterator	rend(void)	 const { return (const_reverse_iterator(start)); } // tested

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
				allocator.construct(newStart.base() + i, *(start + i));
			for (size_type i = 0; i < size(); ++i)
				allocator.destroy(start.base() + i);
			if (capacity() > 0)
				allocator.deallocate(start.base(), capacity());
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
		difference_type offset = pos - start;
		if (size() + 1 > capacity())
			reserve(std::max(size() * 2, static_cast<size_type>(1)));
		if (offset == finish - start)
		{
			allocator.construct(finish.base(), value);
			++finish;
			return (start + offset);
		}
		allocator.construct(finish.base(), *(finish - 1));
		for (iterator i = finish - 1; i != start + offset; --i)
			*i = *(i - 1);
		*(start + offset) = value;
		finish = finish + 1;
		return (start + offset);
	}
	void		insert(iterator pos, size_type count, const T& value) // tested
	{
		difference_type offset = pos - start;
		if (size() + count > capacity())
			reserve(std::max(size() * 2, size() + count));
		for (iterator i = finish + count - 1; i != finish - 1; --i)
			allocator.construct(i.base(), *(i - count));		
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
		difference_type dist = ft::distance(first, last);
		size_type offset = pos - start;
		if (size() + static_cast<size_type>(dist) > capacity())
			reserve(std::max(size() * 2, size() + static_cast<size_type>(dist)));
		for (iterator i = finish + dist - 1; i != finish - 1; --i)
			allocator.construct(i.base(), *(i - dist));
		for (iterator i = finish - 1; i > start + offset + dist - 1; --i)
			*i = *(i - dist);
		for (difference_type i = 0; i < dist; ++i)
			*(start + offset + i) = *first++;
		finish = finish + dist;
	}
	iterator	erase(iterator pos) // tested
	{
		for (iterator i = pos; i != finish - 1; ++i)
			*i = *(i + 1);
		allocator.destroy(finish.base() - 1);
		finish = finish - 1;
		return (pos);
	}
	iterator	erase(iterator first, iterator last) // tested
	{
		for (difference_type i = 0; i < finish - last; ++i)
			*(first + i) = *(last + i);
		for (iterator i = first + (finish - last); i != finish; ++i)
			allocator.destroy(i.base());
		finish = first + (finish - last);
		return (first); // wrong return
	}
	void		push_back(const T& value) // tested
	{
		if (size() + 1 > capacity())
			reserve(std::max(size() * 2, static_cast<size_type>(1)));
		allocator.construct(finish.base(), value);
		finish = finish + 1;
	}
	void		pop_back(void) // tested
	{
		allocator.destroy(finish.base() - 1);
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

// DEBUG
template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
	for (typename vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
		os << *i << " ";
	return (os);
}

} // ft

#endif
