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

#include "my_iterator.hpp"
#include "utils.hpp"
# include <iostream>
# include <string>
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
       typedef typename Allocator::reference							reference;
       typedef typename Allocator::const_reference						const_reference;
       typedef typename Allocator::pointer								pointer;
       typedef typename Allocator::const_pointer						const_pointer;
       typedef typename ft::random_access_iterator<value_type>			iterator;
       typedef typename ft::random_access_iterator<const value_type>	const_iterator;
       typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
       typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;
       typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
       typedef typename Allocator::size_type							size_type;

       // Construct/Copy/Destroy
       explicit vector(const allocator_type& alloc = allocator_type())
              :
       		_alloc(alloc),
       		_start(u_nullptr),
       		_end(u_nullptr),
       		_end_capacity(u_nullptr)
       	{}
       vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
              :
                     _alloc(alloc),
                     _start(u_nullptr),
                     _end(u_nullptr),
                     _end_capacity(u_nullptr)
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
       vector(const vector& x)
              :
       		_alloc(x._alloc),
       		_start(u_nullptr),
       		_end(u_nullptr),
       		_end_capacity(u_nullptr)
       	{
       		this->insert(this->begin(), x.begin(), x.end());
       	}
		~vector()
		{
			this->clear();
			_alloc.deallocate(_start, this->capacity());
		}

template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:
				_alloc(alloc)
			{
				bool is_valid;
				if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				
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

	vector &operator=(const vector& x)
	{
		if (x == *this)
			return (*this);
		this->clear();
		this->insert(this->end(), x.begin(), x.end());
		return (*this);
	}

	template <class InputIterator>
				void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
				{
					bool is_valid;
					if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
						throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
					this->clear();
					size_type dist = ft::distance(first, last);
					if (size_type(_end_capacity - _start) >= dist)
					{
						for(; &(*first) != &(*last); first++, _end++)
							_alloc.construct(_end, *first);
					}
					else
					{
						pointer new_start = pointer();
						pointer new_end = pointer();
						pointer new_end_capacity = pointer();

						new_start = _alloc.allocate(dist);
						new_end = new_start;
						new_end_capacity = new_start + dist;

						for(; &(*first) != &(*last); first++, new_end++)
							_alloc.construct(new_end, *first);
						
						_alloc.deallocate(_start, this->capacity());

						_start = new_start;
						_end = new_end;
						_end_capacity = new_end_capacity;
					}
				}
	
	void assign(size_type n, const value_type& t)
	{
		this->clear();
		if (n == 0)
			return ;
		if (size_type(_end_capacity - _start) >= n)
		{
			while (n)
			{
				_alloc.construct(_end, t);
				n--;
				_end++;
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
				n--;
				_end++;
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
	// void resize(size_type sz)
	// {
	// 	if (sz > this->size())
	// 	{
	// 		this->insert(this->end(), sz - this->size(), _alloc);
	// 	}
	// 	else
	// 	{
	// 		while (sz < this->size())
	// 		{
	// 			_end--;
	// 			_alloc.destroy(_end);
	// 		}
	// 	}
	// }
	// void resize(size_type sz, T c)
	// {
	//        if (sz > this->size())
	//        {
	//               this->insert(this->end(), sz - this->size(), c);
	//        }
	//        else
	//        {
	//               while (sz < this->size())
	//               {
	//                      _end--;
	//                      _alloc.destroy(_end);
	//               }
	//        }
	// }
	void	resize (size_type n, value_type val = value_type())
	{
		if (n > this->max_size())
			throw (std::length_error("vector::resize"));
		else if (n < this->size())
		{
			while (this->size() > n)
			{
				--_end;
				_alloc.destroy(_end);
			}
		}
		else
			this->insert(this->end(), n - this->size(), val);
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
		checkRange(n);
		return ((*this)[n]);
	}
	const_reference at(size_type n) const
	{
		checkRange(n);
		return ((*this)[n]);
	}
	reference front() { return (*_start); };
	const_reference front() const { return (*_start); };
	reference back() { return (*(_end - 1)); };
	const_reference back() const { return (*(_end - 1)); };

	// Modifiers
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
	void pop_back()
	{
	       _alloc.destroy(&(this->back()));
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
	template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			{
				bool is_valid;
				if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				
				size_type dist = ft::distance(first, last);
				if (size_type(_end_capacity - _end) >= dist)
				{
					for(size_type i = 0; i < this->size() - (&(*position) - _start); i++)
						_alloc.construct(_end - i + (dist - 1), *(_end - i - 1));
					_end += dist;
					for (; &(*first) != &(*last); first++, position++)
						_alloc.construct(&(*position), *first);
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();

					new_start = _alloc.allocate( this->size() * 2 );
					new_end = new_start + this->size() + dist;
					new_end_capacity = new_start + ( this->size() * 2 );

					if (size_type(new_end_capacity - new_start) < this->size() + dist)
					{
						if (new_start)
							_alloc.deallocate(new_start, new_end_capacity - new_start);
						new_start = _alloc.allocate (this->size() + dist);
						new_end = new_start + this->size() + dist;
						new_end_capacity = new_end;
					}

					for (int i = 0; i < &(*position) - _start; i++)
						_alloc.construct(new_start + i, *(_start + i));
					for (int j = 0; &(*first) != &(*last); first++, j++)
						_alloc.construct(new_start + (&(*position) - _start) + j, *first);
					for (size_type k = 0; k < this->size() - (&(*position) - _start); k++)
						_alloc.construct(new_start + (&(*position) - _start) + dist + k, *(_start + (&(*position) - _start) + k));

					for (size_type l = 0; l < this->size(); l++)
						_alloc.destroy(_start + l);
					_alloc.deallocate(_start, this->capacity());

					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
			}
	iterator erase(iterator position)
	{
	       _alloc.destroy((*this)[position]);
	       _end--;
	       if (position + 1 == end())
	              return (end());
	       return ((*this)[position]);
	}
	iterator erase(iterator start, iterator finish)
	{
	       this->_end = start;
	       while (_end < finish)
	       {
	              _alloc.destroy(this->_end);
	              _end++; _end_capacity--;
	       }
	}
	void swap(vector& x)
	{
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
			if (*a != *b || b == y.end())
				return (false);
			a++;
			b++;
		}
		return true;
	}
template <class T, class Allocator>
    bool operator!=(const ft::vector<T,Allocator>& x, const ft::vector <T,Allocator>& y) { return (!(x == y)); };
template <class T, class Allocator>
    bool operator<(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}
template <class T, class Allocator>
    bool operator<=(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y) { return (!(y < x)); };
template <class T, class Allocator>
    bool operator>(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y) { return (y < x); };
template <class T, class Allocator>
    bool operator>=(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y) { return (!(x < y)); };

// Specialized Algorithms
template <class T, class Allocator>
	void swap (vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif