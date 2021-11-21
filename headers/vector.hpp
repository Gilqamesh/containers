#ifndef VECTOR_HPP
# define VECTOR_HPP

// ************************************************************************** //
//                                Vector Class                                //
// ************************************************************************** //

# include <memory>
# include <stdexcept>
# include "pair.hpp"
// # include "iterator_traits.hpp"
# define MAX_RAM 4294967296

namespace ft
{

template <typename T>
class vector
{
	public:
		typedef T											value_type;
		typedef typename std::allocator<value_type>			allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef std::allocator_traits<allocator_type>		__alloc_traits;
		typedef typename __alloc_traits::size_type			size_type;

		// TODO: iterators and traits must be reimplemented	
		typedef typename __alloc_traits::pointer			pointer;
		typedef typename __alloc_traits::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer								const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		// Construct/copy/destroy
		explicit vector (const allocator_type& __a = allocator_type())
			: __begin_(nullptr), __end_(nullptr), __end_cap_(make_pair(nullptr, __a)) { }
		explicit vector (size_type __n, const value_type& __x = value_type(),
                 const allocator_type &__a = allocator_type())
			: __begin_(nullptr), __end_(nullptr), __end_cap_(make_pair(nullptr, __a))
		{
			reserve(__n);
			insert(begin(), __n, __x);
		}
		template <typename _InputIterator>
			vector(_InputIterator __first, _InputIterator __last,
					const allocator_type &__a = allocator_type())
			: __begin_(nullptr), __end_(nullptr), __end_cap_(make_pair(nullptr, __a))
		{
			reserve(__last - __first);
			insert(begin(), __first, __last);
		}
		vector(const vector &a): __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr) { *this = a; }
		~vector() { }
		vector &operator=(const vector &a)
		{
			if (this == &a)
				return (*this);
			assign(a.begin(), end());
			return (*this);
		}
		// Assigns new contents to the vector, replacing its current contents, 
		// and modifying its size accordingly
		template <typename _InputIterator>
			void	assign(_InputIterator __first, _InputIterator __last)
		{
			erase(begin(), end());
			insert(begin(), __first, __last);
		}
		void	assign(size_type __n, const value_type &__u)
		{
			erase(begin(), end());
			insert(begin(), __n, __u);
		}
		// Returns a copy of the allocator object associated with the vector
		allocator_type	get_allocator() const { return (__end_cap_.second); }

		// Iterators
		iterator				begin() { return (__begin_); }
		const_iterator			begin() const { return (begin()); }
		iterator				end() { return (__end_); }
		const_iterator			end() const { return (end()); }
		reverse_iterator		rbegin() { return (reverse_iterator(end())); };
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator		rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }

		// Capacity
		// Returns the number of elements in the container
		size_type	size() const { return (__end_ - __begin_); }

		// Returns the maximum number of elements the container can hold
		size_type	max_size() const { return (MAX_RAM / (int)sizeof(size_type)); }

		// Resizes the container so that it contains __sz elements
		void		resize(size_type __sz, value_type c = value_type())
		{
			if (__sz < size())
				erase(begin() + __sz, end());
			else if (__sz > size())
			{
				if (__sz > capacity())
					// probably reserve more to optimize
					reserve(__sz);
				insert(end(), __sz - size(), c);
			}
		}

		// Number of elements container can have before reallocation is necessary
		size_type	capacity(void) const { return (__end_cap_.first - __begin_); }

		// Returns whether the container is empty
		bool	empty(void) const { return (__begin_ == __end_); }

		// Allocate space for at least '__n' elements
		void		reserve(size_type __n)
		{
			if (__n > max_size())
				throw std::length_error("requested amount too much in reserve");
			if (__n > capacity())
			{
				__end_cap_.second = allocator_type::allocate(__n);
				std::uninitialized_copy(__begin_, __end_, __end_cap_.second);
				size_type	prev_size = size();
				clear();
				allocator_type::deallocate(__begin_, prev_size);
				__begin_ = __end_cap_.second;
				__end_ = __end_cap_.second + prev_size;
				__end_cap_.first = __end_cap_.second + __n;
			}
		}

		// Element access
		reference		operator[](size_type __n) { return (__end_cap_.second[__n]); }
		const_reference	operator[](size_type __n) const { return (__end_cap_.second[__n]); }
		reference		at(size_type __n)
		{
			if (__n < 0 || __n >= size())
				throw std::out_of_range("index is out of range []");
			return (__end_cap_.second[__n]);
		}
		const_reference	at(size_type __n) const
		{
			if (__n < 0 || __n >= size())
				throw std::out_of_range("index is out of range []");
			return (__end_cap_.second[__n]);
		}
		reference		front() { return (*__begin_); }
		const_reference	front() const { return (*__begin_); }
		reference		back() { return (*(__end_ - 1)); }
		const_reference	back() const { return (*(__end_ - 1)); }

		// Modifiers
		void	push_back(const value_type &__x) { insert(__end_, __x); }
		void	pop_back() { if (size() > 0) erase(end() - 1); }
		// Insert new element(s) at the specified position, effectively increasing the size 
		// by the number of element(s) inserted. Returns an iterator that points to the first
		// of the newly inserted element(s).
		iterator	insert(iterator __position, const value_type &__x)
		{
			if (capacity() == size())
				reserve(size() * 2);
			iterator	i = end();
			while (i > __position)
			{
				*i = *(i - 1);
				--i;
			}
			__end_cap_.second.construct(i, __x);
			++__end_;
			return (i);
		}
		void		insert(iterator __position, size_type __n, const value_type &__u)
		{
			if (__n + size() > capacity())
				reserve((__n + size()) * 2);
			for (size_t i = 0; i < __n; ++i)
			{
				if (__position + __n + i < __end_)
					*(__position + __n + i) = *(__position + i);
				else
					__end_cap_.second.construct(__position + __n + i, *(__position + i));
			}
			for (size_t i = 0; i < __n; ++i)
			{
				if (__position + i < __end_)
					*(__position + i) = __u;
				else
					__end_cap_.second.construct(__position + i, __u);
			}
			__end_ += __n;
		}
		template <typename _InputIterator>
			void	insert(iterator __position,
							_InputIterator __first, _InputIterator __last)
		{
			size_t	diff = __last - __first;
			if (diff + size() > capacity())
				reserve((diff + size()) * 2);
			for (size_t i = 0; i < diff; ++i)
			{
				if (__position + diff + i < __end_)
					*(__position + diff + i) = *(__position + i);
				else
					__end_cap_.second.construct(__position + diff + i, *(__position + i));
			}
			for (size_t i = 0; i < diff; ++i)
			{
				if (__position + i < __end_)
					*(__position + i) = *__first++;
				else
					__end_cap_.second.construct(__position + i, *__first++);
			}
			__end_ += diff;
		}
		// Removes from the vector either a single or range of elements, effectively reducing 
		// the size of the container. Returns an iterator to the new location of the element 
		// that followed the last element erased.
		iterator	erase(iterator __position)
		{
			iterator	i = __position;
			while (i < end() - 1)
			{
				*i = *(i + 1);
				++i;
			}
			__end_cap_.second.destroy(i);
			--__end_;
			return (__position);
		}
		iterator	erase(iterator __first, iterator __last)
		{
			size_t		diff = __last - __first;
			iterator	i = __first;
			while (i < __last - 1)
			{
				*i = *(i + diff);
				__end_cap_.second.destroy(i + diff);
			}
			__end_ -= diff;
			return (__last);
		}
		void		swap(vector<T> &__x)
		{
			vector<T>	a(*this);
			*this = __x;
			__x = a;
		}
		void		clear() { while (__end_ != __begin_) allocator_type::destroy(--__end_); }

	protected:
		pointer							__begin_;
		pointer							__end_;
		pair<pointer, allocator_type>	__end_cap_;
};

template <typename T>
bool	operator==(const vector<T> &v1, const vector<T> &v2)
{
	typename vector<T>::const_iterator	i = v1.begin();
	typename vector<T>::const_iterator	i2 = v2.begin();
	while (i != v1.end() && i2 != v2.end())
		if (*i++ != *i2++)
			return (false);
	return (i == v1.end() && i2 == v2.end());
}

template <typename T>
bool	operator!=(const vector<T> &v1, const vector<T> &v2)
{
	return (!operator==(v1, v2));
}

template <typename T>
bool	operator<(const vector<T> &v1, const vector<T> &v2)
{
	typename vector<T>::const_iterator	i = v1.begin();
	typename vector<T>::const_iterator	i2 = v2.begin();
	while (i != v1.end() && i2 != v2.end())
	{
		if (*i++ == *i2++)
			continue ;
		return (*i < *i2);
	}
	return (i == v1.end() && i2 != v2.end());
}

template <typename T>
bool	operator<=(const vector<T> &v1, const vector<T> &v2)
{
	typename vector<T>::const_iterator	i = v1.begin();
	typename vector<T>::const_iterator	i2 = v2.begin();
	while (i != v1.end() && i2 != v2.end())
		if (*i++ > *i2++)
			return (false);
	return (i == v1.end());
}

template <typename T>
bool	operator>(const vector<T> &v1, const vector<T> &v2)
{
	typename vector<T>::const_iterator	i = v1.begin();
	typename vector<T>::const_iterator	i2 = v2.begin();
	while (i != v1.end() && i2 != v2.end())
	{
		if (*i++ == *i2++)
			continue ;
		return (*i > *i2);
	}
	return (i2 == v2.end() && i != v1.end());
}

template <typename T>
bool	operator>=(const vector<T> &v1, const vector<T> &v2)
{
	typename vector<T>::const_iterator	i = v1.begin();
	typename vector<T>::const_iterator	i2 = v2.begin();
	while (i != v1.end() && i2 != v2.end())
		if (*i++ < *i2++)
			return (false);
	return (i2 == v2.end());
}

} // ft

#endif /* VECTOR_HPP */
