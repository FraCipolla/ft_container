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

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:

// Types
typedef T value_type;
typedef Allocator	allocator_type;
typedef typename	Allocator::reference reference;
typedef typename	Allocator::const_reference const_reference;
class iterator;
class const_iterator;
typedef typename	Allocator::size_type size_type;
typedef typename	Allocator::difference_type difference_type;
typedef typename	Allocator::pointer pointer;
typedef typename	Allocator::const_pointer const_pointer;
typedef typename	std::reverse_iterator<iterator> reverse_iterator;
typedef typename     std::reverse_iterator<const iterator> const_reverse_iterator;

// Construct/Copy/Destroy
explicit vector(const Allocator& alloc = Allocator())
       :
		_alloc(alloc),
		_start(nullptr),
		_end(nullptr),
		_end_capacity(nullptr)
	{}
explicit vector(size_type n, const Allocator& alloc = Allocator ())
       :
              _alloc(alloc),
              _start(nullptr),
              _end(nullptr),
              _end_capacity(nullptr)
       {
              _start = _alloc.allocate(n);
              _end_capacity = _start + n;
              _end = _start;
              while (n--)
              {
                     _alloc.construt(_end);
                     _end++;
              }
       }
vector(size_type n, const T& value, const Allocator& alloc = Allocator())
       :
              _alloc(alloc),
              _start(nullptr),
              _end(nullptr),
              _end_capacity(nullptr)
       {
              _start = _alloc.allocate(n);
              _end_capacity = _start + n;
              _end = _start;
              while (n--)
              {
                    _alloc.construct(_end, value);
                     _end++;
              }
       }
vector(const vector<T, Allocator>& x)
       :
		_alloc(x._alloc),
		_start(nullptr),
		_end(nullptr),
		_end_capacity(nullptr)
	{
		this->insert(this->begin(), x.begin(), x.end());
	}
template <class InputIterator>
       vector(InputIterator start, InputIterator finish, 
              const Allocator& alloc = Allocator())
       :
              _alloc(alloc)
       {
              difference_type n = std::distance(start, finish);  // make function
              _start = alloc.allocate(n);
              _end_capacity = _start + n;
              _end = start;
              while (n--)
              {
                     _alloc.construct(_end, *start);
                     _end++; *start++;
              }
       }
vector<T,Allocator>& operator=(const vector<T, Allocator>& x)
{
	if (x == *this)
		return (*this);
	this->clear();
	this->insert(this->end(), x.begin(), x.end());
	return (*this);
}
template <class InputIterator>
       void assign(InputIterator start, InputIterator finish); //make function
void assign(size_type n, const T& t)
{
       this->clear();
       if (n == 0)
              return ;
       if (size_type(_end_capacity - _start) >= n)
       {
              while (n)
              {
                     _alloc.construct(_end, t);
                     n--; _end++;
              }
       }
       else
       {
              _alloc.deallocate(_start, this->capacity());
		_start = _alloc.allocate( n );
		_end = _start;
		_end_capacity = _start + n;
		while (n)
		{
			_alloc.construct(_end, t);
			n--; _end++;
		}
	}
}
allocator_type get_allocator () const { return (this->_alloc); };

// Iterators
iterator begin(){ return (_start); };
const_iterator begin() const {return (_start); };
iterator end(){
       if (this->empty())
              return (this->begin());
       return (_end); 
}
const_iterator end() const {
       if (this->empty())
              return (this->begin());
       return (_end); 
}
reverse_iterator rbegin() { return (reverse_iterator(this->end())); };
const_reverse_iterator rbegin() const { return (reverse_iterator(this->end())); };
reverse_iterator rend() { return (reverse_iterator(this->begin())); };
const_reverse_iterator rend() const { return (reverse_iterator(this->begin())); };

// Capacity
size_type size() const { return (this->_end - this->_start); };
size_type max_size() const { return allocator_type().max_size(); };
void resize(size_type sz)
{
       if (sz > this->size())
       {
              this->insert(this->end(), sz - this->size(), _alloc);
       }
       else
       {
              while (sz < this->size())
              {
                     _end--;
                     _alloc.destroy(_end);
              }
       }
}
void resize(size_type sz, T c)
{
       if (sz > this->size())
       {
              this->insert(this->end(), sz - this->size(), c);
       }
       else
       {
              while (sz < this->size())
              {
                     _end--;
                     _alloc.destroy(_end);
              }
       }
}
size_type capacity() const { return (this->_end_capacity - this->_start); };
bool empty() const { return (size() == 0 ? true : false); };
void reserve(size_type n)
{
       if (n > this->max_size())
              throw (std::length_error("vector::reserve"));
       else if (n < this->capacity())
              return ;
       else if (n > this->max_size())
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
       if (n < 0 || n > this->size() - 1)
              return ;
       return ((*this)[n]);
}
const_reference at(size_type n) const
{
       if (n < 0 || n > this->size() - 1)
              return ;
       return ((*this)[n]);
}
reference front() { return (*_start); };
const_reference front() const { return (*_start); };
reference back() { return (*(_end - 1)); };
const_reference back() const { return (*(_end - 1)); };

// Modifiers
void push_back(const T& x)
{
       if (_end == _end_capacity)
       {
              int next = (this->size() ? > 0) ? (int)(this->size() * 2) : 1;
              this->reserve(next);
       }
       _alloc.construct(_end, x);
       _end++;
}
void pop_back()
{
       _alloc.destroy(&(this->back()));
       _end--;
}
iterator insert(iterator position, const T& x);
void insert(iterator position, size_type n, const T& x);
template <class InputIterator>
       void insert(iterator position, InputIterator start, InputIterator finish);
iterator erase(iterator position);
iterator erase(iterator start, iterator finish);
void swap(vector<T, Allocator>& x);
void clear();

private:
       allocator_type  _alloc;
	pointer         _start;
	pointer         _end;
	pointer         _end_capacity;
};

// Nonmember Operators
template <class T, class Allocator>
       bool operator==(const vector<T,Allocator>& x, const vector <T,Allocator>& y);
template <class T, class Allocator>
       bool operator!=(const vector<T,Allocator>& x, const vector <T,Allocator>& y);
template <class T, class Allocator>
       bool operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
       bool operator>(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
       bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator>
       bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

// Specialized Algorithms
template <class T, class Allocator>
       void swap (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
}

#endif