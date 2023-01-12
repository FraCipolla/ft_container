/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:42:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/27 17:30:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_PROTO_HPP
#define VECTOR_PROTO_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include "utils.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector 
       {

    public:
       typedef T														value_type;
       typedef Allocator												allocator_type;
       typedef typename allocator_type::reference							reference;
       typedef typename allocator_type::const_reference						const_reference;
       typedef typename allocator_type::pointer								pointer;
       typedef typename allocator_type::const_pointer						const_pointer;
       typedef ft::random_access_iterator<value_type>					iterator;
       typedef ft::random_access_iterator<const value_type>				const_iterator;
       typedef ft::reverse_iterator<iterator>							reverse_iterator;
       typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
       typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
       typedef typename allocator_type::size_type							size_type;
	
	private:
	    allocator_type  _alloc;
		pointer         _start;
		pointer         _end;
		pointer         _end_capacity;


		void checkRange(const size_type& n) const
			{
				if (n >= this->size())
					throw (std::out_of_range("vector::checkRange: n (which is "
							+ ft::to_string(n) + ") >= this->size() (which is "
							+ ft::to_string(this->size()) + ")"));
			}
	public:
       // Construct/Copy/Destroy
       explicit vector(const allocator_type& alloc = allocator_type())
              :
       		_alloc(alloc),
       		_start(u_nullptr),
       		_end(u_nullptr),
       		_end_capacity(u_nullptr)
       	{}
       explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
              :
                    _alloc(alloc),
					_start(u_nullptr),
					_end(u_nullptr),
					_end_capacity(u_nullptr)
              {

                     _start = _alloc.allocate(n);
                     _end = _start;
                     while (n--)
                     {
                        _alloc.construct(_end, value);
						_end++;
                     }
					 _end_capacity = _end;
              }

template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:
				_alloc(alloc)
			{
				difference_type n = ft::distance(first, last);
				_start = _alloc.allocate( n );
				_end_capacity = _start + n;
				_end = _start;
				while (n--)
				{
					_alloc.construct(_end, *first++);
					_end++;
				}
			}

    vector(const vector& x) : _alloc(x._alloc)
	{
		if (this == &x || x._start == 0)
			return ;
	    size_type n = x.size();
	    this->_start = this->_alloc.allocate(n);
	    this->_end_capacity = this->_start + n;
	    this->_end = this->_start;
	
	    pointer other = x._start;
	    while (n--) this->_alloc.construct(this->_end++, *other++);
	}
		

	vector &operator=(const vector& x)
	{
		if (&x == this)
			return (*this);
		this->clear();
		this->insert(this->end(), x.begin(), x.end());
		return (*this);
	}
	~vector()
	{
		this->clear();
		this->_alloc.deallocate(this->_start, this->capacity());
	}

	allocator_type get_allocator () const { return (this->_alloc); };

	// Iterators
	iterator begin(){ return (this->_start); };
	const_iterator begin() const {return (this->_start); };
	iterator end()
	{
		if (this->empty())
			return (this->begin());
		return (_end);
	}
	const_iterator end() const 
	{
		if (this->empty())
			return (this->begin());
		return (_end);
	}
	reverse_iterator rbegin() { return (reverse_iterator(iterator(this->_end))); };
	const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); };
	reverse_iterator rend() { return (reverse_iterator(this->begin())); };
	const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); };

	// Capacity
	size_type size(void) const { return (this->_end - this->_start); };
	size_type max_size(void) const { return (this->_alloc.max_size()); };
	void	resize (size_type n, value_type val = value_type())
	{
		if (n > this->max_size())
			throw (std::length_error("vector::resize"));
		size_type prev_size = this->size();
    	if (prev_size > n)
		{
      		while (prev_size-- > n)
			{
				this->_alloc.destroy(--this->_end);
			}
			return ;
		}
		this->insert(this->_end, n - prev_size, val);
	};

	size_type capacity(void) const { return (this->_end_capacity - this->_start); };
	bool empty(void) const { return (this->size() == 0); };
	void reserve(size_type n)
	{
		if (n > this->max_size())
			throw (std::length_error("vector::reserve"));
		else if (n > this->capacity())
		{
			pointer prev_start = _start;
			pointer prev_end = _end;
			size_type prev_size = this->size();
			size_type prev_capacity = this->capacity();
			
			_start = _alloc.allocate( n );
			_end_capacity = _start + n;
			_end = _start;
			while (prev_start != prev_end)
			{
				_alloc.construct(_end, *prev_start);
				_end++;
				prev_start++;
			}
			_alloc.deallocate(prev_start - prev_size, prev_capacity);
		}
	}	
	// Element Access
	reference operator[](size_type n) { return (*(_start + n)); };
	const_reference operator[](size_type n) const { return (*(_start + n)); };
	reference at(size_type n)
	{
		checkRange(n);
		return ((*this)[n]);
	}
	const_reference at(size_type n) const
	{
		checkRange(n);
		return ((*this)[n]);
	}
	reference front() { return (*_start); };	// ok
	const_reference front() const { return (*_start); };	// ok
	reference back() { return (*(_end - 1)); };		// ok
	const_reference back() const { return (*(_end - 1)); };		// ok

	// Modifiers
	template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = u_nullptr)
		{
			this->clear();
			size_type dist = ft::distance(first, last);
			if (this->capacity() < dist)
			{
				this->_start = this->_alloc.allocate(dist);
				this->_end_capacity = this->_start + dist;
				this->_end = this->_start;
			}
			while (dist--)
			{
				this->_alloc.construct(_end++, *first++);
			}
		};

	void assign(size_type n, const value_type& t)
	{
		if (this->capacity() > 0)
			this->clear();
		if (n == 0)
			return ;
		if (size_type(_end_capacity - _start) >= n)
		{
			while (n)
			{
				_alloc.construct(_end++, t);
				n--;
			}
		}
		else
		{
			if (this->capacity() > 0)
				_alloc.deallocate(_start, this->capacity());
			_start = _alloc.allocate( n );
			_end = _start;
			_end_capacity = _start + n;
			while (n)
			{
				_alloc.construct(_end++, t);
				n--;
			}
		}
	}

	void push_back(const value_type& x)
	{
	       if (_end == _end_capacity)
	       {
	              int next = (this->size() > 0) ? (int)(this->size() * 2) : 1;
	              this->reserve(next);
	       }
	       _alloc.construct(_end, x);
	       _end++;
	}
	void pop_back()		// ok
	{
	       _alloc.destroy(&this->back());
	       _end--;
	}
	iterator insert(iterator position, const value_type& x)
	{
		size_type pos_len = &(*position) - _start;
		if (size_type(_end_capacity - _end) >= this->size() + 1)
		{
			for (size_type i = 0; i < pos_len; i++)
				_alloc.construct(_end - i, *(_end - i - 1));
			_end++;
			_alloc.construct(&(*position), x);
		}
		else
		{
			pointer new_start = pointer();
			pointer new_end = pointer();
			pointer new_end_capacity = pointer();

			int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1; 
			new_start = _alloc.allocate( next_capacity );
			new_end = new_start + this->size() + 1;
			new_end_capacity = new_start + next_capacity;

			for (size_type i = 0; i < pos_len; i++)
				_alloc.construct(new_start + i, *(_start + i));
			_alloc.construct(new_start + pos_len, x);
			for (size_type j = 0; j < this->size() - pos_len; j++)
				_alloc.construct(new_end - j - 1, *(_end - j - 1));
			for (size_type l = 0; l < this->size(); l++)
				_alloc.destroy(_start + l);
			if (_start)
				_alloc.deallocate(_start, this->capacity());
			
			_start = new_start;
			_end = new_end;
			_end_capacity = new_end_capacity;
		}
		return (iterator(_start + pos_len));
	}

	void insert(iterator position, size_type n, const value_type& x)
	{
		if (n == 0)
			return ;
		if (n > this->max_size())
			throw (std::length_error("vector::insert (fill)"));
		size_type pos_len = &(*position) - _start;
		if (size_type(_end_capacity - _end) >= n)
		{
			for (size_type i = 0; i < this->size() - pos_len; i++)
				_alloc.construct(_end - i + (n - 1), *(_end - i - 1));
			_end += n;
			while (n)
			{
				_alloc.construct(&(*position) + (n - 1), x);
				n--;
			}
		}
		else
		{
			pointer new_start = pointer();
			pointer new_end = pointer();
			pointer new_end_capacity = pointer();
			
			int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
			new_start = _alloc.allocate(next_capacity);
			new_end_capacity = new_start + next_capacity;

			if (size_type(new_end_capacity - new_start) < this->size() + n)
			{
				if (new_start)
					_alloc.deallocate(new_start, new_start - new_end_capacity);
				next_capacity = this->size() + n;
				new_start = _alloc.allocate(next_capacity);
				new_end = new_start + this->size() + n;
				new_end_capacity = new_start + next_capacity;
			}
			new_end = new_start + this->size() + n;
			for (int i = 0; i < (&(*position) - _start); i++)
				_alloc.construct(new_start + i, *(_start + i));
			for (size_type k = 0; k < n; k++)
				_alloc.construct(new_start + pos_len + k, x);
			for (size_type j = 0; j < (this->size() - pos_len); j++)
				_alloc.construct(new_end - j - 1, *(_end - j - 1));
			for (size_type u = 0; u < this->size(); u++)
				_alloc.destroy(_start + u);
			_alloc.deallocate(_start, this->capacity());
			_start = new_start;
			_end = new_end;
			_end_capacity = new_end_capacity;
		}
	}

	template < class InputIterator >
  		void insert(iterator position, InputIterator first, InputIterator last, 
		typename ft::enable_if<!ft::is_integral< InputIterator >::value >::type* = u_nullptr)
		{
			size_type pos_at = &(*position) - this->_start;
			size_type n = ft::distance(first, last);

    	if (this->capacity() >= this->size() + n) {
      		for (size_type i = 0; i < this->size() - pos_at; ++i) {
        		this->_alloc.construct(this->_end + n - i, *(this->_end - i));
        		this->_alloc.destroy(this->_end - i);
      		}
      		this->_end = this->_start + this->size() + n;
      		for (size_type i = 0; i < n; ++i) {
        		this->_alloc.construct(this->_start + pos_at + i, *first++);
      		}
      		return;
    	}

   		size_type next_capacity = this->size() + n;

    	pointer prev_start = this->_start;
    	pointer prev_end = this->_end;
    	size_type prev_size = this->size();
    	// size_type prev_capacity = this->capacity();

    	this->_start = this->_alloc.allocate(next_capacity);
    	this->_end = this->_start + prev_size + n;
    	this->_end_capacity = this->_end;

    	for (size_type i = 0; i < pos_at; ++i) {
    		this->_alloc.construct(this->_start + i, *(prev_start + i));
    		this->_alloc.destroy(prev_start + i);
    	}

    	for (size_type i = 0; i < prev_size - pos_at; ++i) {
    		this->_alloc.construct(this->_end - i - 1, *(prev_end - i - 1));
    		this->_alloc.destroy(prev_end - i - 1);
    	}

    	for (size_type i = 0; i < n; ++i) {
     		this->_alloc.construct(this->_start + pos_at + i, *first++);
    	}
    	// this->_alloc.deallocate(prev_start, prev_capacity);
    	return;
  	}
	iterator erase(iterator position)
	{
		size_type pos_at = &(*position) - this->_start;
    	this->_alloc.destroy(&(*position));
    	for (size_type i = 0; i < this->size() - pos_at; ++i) {
    	  this->_alloc.construct(this->_start + pos_at + i,
    	                         *(this->_start + pos_at + i + 1));
    	  this->_alloc.destroy(this->_start + pos_at + i + 1);
    	}
    	--this->_end;
    	return this->_start + pos_at;
	}
	iterator erase(iterator start, iterator finish)
	{
		size_type pos_at = &(*start) - this->_start;
    	size_type n = finish - start;
    	for (size_type i = 0; i < n; ++i) {
    	  this->_alloc.destroy(&(*(start + i)));
    	}
    	for (size_type i = 0; i < this->size() - pos_at; ++i) {
    	  this->_alloc.construct(this->_start + pos_at + i,
    	                         *(this->_start + pos_at + i + n));
    	  this->_alloc.destroy(this->_start + pos_at + i + n);
    	}
    	this->_end = this->_start + this->size() - n;
    	return this->_start + pos_at;
	}

	void swap(vector& x)
	{
		if (x == *this)
			return ;
		
		pointer save_start = x._start;
		pointer save_end = x._end;
		pointer save_end_capacity = x._end_capacity;
		allocator_type save_alloc = x._alloc;

		x._start = this->_start;
		x._end = this->_end;
		x._end_capacity = this->_end_capacity;
		x._alloc = this->_alloc;

		this->_start = save_start;
		this->_end = save_end;
		this->_end_capacity = save_end_capacity;
		this->_alloc = save_alloc;
	}
	
	void clear()
	{
		size_type save_size = this->size();
		for (size_type i = 0; i < save_size; i++)
		{
			_end--;
			_alloc.destroy(_end);
		}
	}

};

// Nonmember Operators
template <class T, class Allocator>
	bool operator==(const ft::vector<T,Allocator>& x, const ft::vector <T,Allocator>& y)
	{
		if (x.size() != y.size())
			return (false);
		typename ft::vector<T>::const_iterator a = x.begin();
		typename ft::vector<T>::const_iterator b = y.begin();
		while (a != x.end())
		{
			if (b == y.end() || *a != *b)
				return (false);
			++a;
			++b;
		}
		return true;
	}
template <class T, class Allocator>
    bool operator!=(const vector<T,Allocator>& x, const vector <T,Allocator>& y) { return (!(x == y)); };
template <class T, class Allocator>
    bool operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}
template <class T, class Allocator>
    bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) { return (!(y < x)); };
template <class T, class Allocator>
    bool operator>(const vector<T,Allocator>& x, const vector<T,Allocator>& y) { return (y < x); };
template <class T, class Allocator>
    bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) { return (!(x < y)); };

// Specialized Algorithms
template <class T, class Allocator>
	void swap (vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif