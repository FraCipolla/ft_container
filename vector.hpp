#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include "utils.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector {

    public:

    // typedefs
    typedef T 														value_type;
    typedef Allocator 												allocator_type;
    typedef typename Allocator::reference 							reference;
    typedef typename Allocator::const_reference 					const_reference;
    typedef typename Allocator::pointer 							pointer;
    typedef typename Allocator::const_pointer 						const_pointer;
	typedef typename ft::random_access_iterator<value_type>			iterator;
    typedef typename ft::random_access_iterator<const value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
    typedef typename Allocator::size_type 							size_type;

	private:
    	allocator_type	_buffer_size;
    	pointer			_buffer_start;
    	pointer			_current_end;
    	pointer			_end_of_buffer;
	
	public:
    // Constructor
    explicit vector (const Allocator& alloc = Allocator())
		:
			_buffer_size(alloc),
			_buffer_start (u_nullptr),
			_current_end (u_nullptr),
			_end_of_buffer (u_nullptr)
		{}
    // explicit vector (size_type sz);
    explicit vector(size_type sz, const T& value = value_type(), const Allocator& alloc = Allocator()) : _buffer_size(alloc)
	{
		_buffer_start = _buffer_size.allocate(sz);
		_end_of_buffer = _buffer_start + sz;
		_current_end = _buffer_start;
		for (; sz > 0; sz--, _current_end++)
			_buffer_size.construct(_current_end, value);
	}
    template <class InputIterator>
    	vector(InputIterator start, InputIterator finish, const Allocator& alloc = Allocator(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
		:
			_buffer_size(alloc)
		{
			size_type sz = ft::distance(start, finish);
			_buffer_start = _buffer_size.allocate(sz);
			_current_end = _buffer_start;
			_end_of_buffer = _buffer_start + sz;
			for (; sz > 0; sz--, _current_end++)
				_buffer_size.construct(_current_end, *start++);
		}
    vector(const vector& x) : _buffer_size(x._buffer_size)
	{
		if (this == &x || x._buffer_start == 0)
			return ;
	    size_type n = x.size();
	    this->_buffer_start = this->_buffer_size.allocate(n);
	    this->_end_of_buffer = this->_buffer_start + n;
	    this->_current_end = this->_buffer_start;
	
	    pointer other = x._buffer_start;
	    while (n--) this->_buffer_size.construct(this->_current_end++, *other++);
	}
	
	// Destructor
    ~vector()
	{
		if (_buffer_start)
		{	
			this->clear();
			_buffer_size.deallocate(_buffer_start, this->capacity());
		}
	}

	// Assign operator
 	vector &operator=(const vector& x)
	{
		if (&x == this || x.size() == 0)
			return (*this);
		this->clear();
		if (this->capacity() > 0 && this->capacity() < x.size())
		{
			_buffer_size.deallocate(_buffer_start, this->capacity());
			_buffer_start = _buffer_size.allocate(x.size());
		}
		allocator_type cpy_alloc = x.get_allocator();
		if (this->capacity() == 0)
		{
			_buffer_start = _buffer_size.allocate(x.size());
			_end_of_buffer = _buffer_start + x.size();
		}
		_current_end = _buffer_start;
		pointer cpy = x._buffer_start;
		for (size_type i = 0; i < x.size(); _current_end++, i++)
			cpy_alloc.construct(_current_end, *cpy++);
		return (*this);
	}

	// Allocator
    allocator_type get_allocator () const { return _buffer_size; };
    

    // Iterators

    iterator begin () { return _buffer_start; };
    const_iterator begin () const { return _buffer_start; };
    iterator end ()
	{ 
		if (this->empty())
			return this->begin();
		return _current_end;
	}
    const_iterator end () const
	{ 
		if (this->empty())
			return this->begin();
		return _current_end;
	}
    reverse_iterator rbegin () { return (reverse_iterator(_current_end)); };
    const_reverse_iterator rbegin () const { return (const_reverse_iterator(_current_end)); };
    reverse_iterator rend () { return (reverse_iterator(_buffer_start)); };
    const_reverse_iterator rend () const { return (const_reverse_iterator(_buffer_start)); };

    // Capacity

    bool empty () const { return (this->size() == 0 ? true : false); };
    size_type size () const { return (_current_end - _buffer_start); };
    size_type max_size () const { return _buffer_size.max_size(); };
	size_type capacity(void) const { return (this->_end_of_buffer - this->_buffer_start); };
	void reserve (size_type n)
	{
		if (n > this->max_size())
			throw (std::length_error("vector::reserve"));
		else if (n > this->capacity())
		{
			pointer prev_start = _buffer_start;
			pointer prev_end = _current_end;
			size_type prev_size = this->size();
			size_type prev_capacity = this->capacity();
			
			_buffer_start = _buffer_size.allocate( n );
			_end_of_buffer = _buffer_start + n;
			_current_end = _buffer_start;
			while (prev_start != prev_end)
			{
				_buffer_size.construct(_current_end, *prev_start);
				_buffer_size.destroy(prev_start);
				_current_end++;
				prev_start++;
			}
			if (prev_capacity > 0)
				_buffer_size.deallocate(prev_start - prev_size, prev_capacity);
		}
	}

    void resize (size_type n, value_type val = value_type())
	{
		if (n > this->size())
			this->insert(this->end(), n - this->size(), val);
		else if (n < this->size())
		{
			for (; n < this->size();)
				_buffer_size.destroy(--_current_end);
		}
	}

    // Element Access

	reference operator[](size_type n) { return (*(_buffer_start + n)); };
	const_reference operator[](size_type n) const { return (*(_buffer_start + n)); };
    reference front () { return (*(_buffer_start)); };
    const_reference front () const { return (*(_buffer_start)); };
    reference back ()
	{
		if (this->empty())
			std::cout << "call back on empty container: undefined behavior" << std::endl;
		return (*(_current_end - 1)); 
	};
    const_reference back () const
	{
		if (this->empty())
			std::cout << "call back on empty container: undefined behavior" << std::endl;
		return (*(_current_end - 1)); 
	};
	reference at (size_type n)
	{
		if (n >= this->size())
			throw (std::out_of_range("vector::at"));
		return ((*this)[n]);
	}
	const_reference at (size_type n) const
	{
		if (n >= this->size())
			throw (std::out_of_range("vector::at"));
		return ((*this)[n]);
	}

    // Modifiers

	template <class InputIterator>
    	void assign (InputIterator start, InputIterator finish,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = u_nullptr)
		{
			this->clear();
			size_type sz = ft::distance(start, finish);
			if (sz > this->capacity())
			{
				if (this->capacity() > 0)
					_buffer_size.deallocate(_buffer_start, this->capacity());
				_buffer_start = _buffer_size.allocate(sz);
				_end_of_buffer = _buffer_start + sz;
				_current_end = _buffer_start;
			}
			for (; sz > 0; start++, _current_end++, sz--)
				_buffer_size.construct(_current_end, *start);
		}
    void assign (size_type n, const T& c)
	{
		this->clear();
		if (n == 0)
			return ;
		if (size_type(_end_of_buffer - _buffer_start) >= n)
		{
			for (; n > 0; n--, _current_end++)
				_buffer_size.construct(_current_end, c);
		}
		else
		{
			if (this->capacity() > 0)
				_buffer_size.deallocate(_buffer_start, this->capacity());
			_buffer_start = _buffer_size.allocate (n);
			_current_end = _buffer_start;
			_end_of_buffer = _buffer_start + n;
			for (; n > 0; n--, _current_end++)
				_buffer_size.construct(_current_end, c);
		}	
		
	}
    void push_front (const T& c);
    void pop_front ();
    void push_back (const T& c)
	{
		if (_current_end == _end_of_buffer)
		{
			size_type sz = this->size() > 0 ? this->size() * 2 : 1;
			reserve(sz);
		}
		_buffer_size.construct(_current_end, c);
		_current_end++;
	}
    void pop_back () { _buffer_size.destroy(&this->back()); _current_end--; };

    iterator insert (iterator position, const T& c)
	{
		size_type pos_len = &(*position) - _buffer_start;
		if (size_type(_end_of_buffer - _current_end) >= this->size() + 1)
		{
			for (size_type i = 0; i < pos_len; i++)
				_buffer_size.construct(_current_end - i, *(_current_end - i - 1));
			_current_end++;
			_buffer_size.construct(&(*position), c);
		}
		else
		{
			pointer new_start = pointer();
			pointer new_end = pointer();
			pointer new_end_capacity = pointer();

			int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1; 
			new_start = _buffer_size.allocate( next_capacity );
			new_end = new_start + this->size() + 1;
			new_end_capacity = new_start + next_capacity;

			for (size_type i = 0; i < pos_len; i++)
				_buffer_size.construct(new_start + i, *(_buffer_start + i));
			_buffer_size.construct(new_start + pos_len, c);
			for (size_type j = 0; j < this->size() - pos_len; j++)
				_buffer_size.construct(new_end - j - 1, *(_current_end - j - 1));
			for (size_type l = 0; l < this->size(); l++)
				_buffer_size.destroy(_buffer_start + l);
			if (_buffer_start)
				_buffer_size.deallocate(_buffer_start, this->capacity());
			
			_buffer_start = new_start;
			_current_end = new_end;
			_end_of_buffer = new_end_capacity;
		}
		return (iterator(_buffer_start + pos_len));
	}
    void insert (iterator position, size_type n, const T& x)
	{
		if (n == 0)
			return ;
		if (n > this->max_size())
			throw (std::length_error("vector::insert (fill)"));
		size_type pos_len = &(*position) - _buffer_start;
		if (this->size() + n < this->capacity() && pos_len > this->size())
		{
			size_type new_size = this->size() + n;
			for (size_type i = 0; i < this->size() - pos_len; i++)
			{
				_buffer_size.construct(_current_end + n - i, *(_current_end - i - n));
				_buffer_size.destroy(_current_end - i - n);
			}
			_current_end = &(*position);
			for (; n > 0; _current_end++, n--)
				_buffer_size.construct(_current_end, x);
			_current_end = _buffer_start + new_size;

		}
		else
		{
			pointer new_start = pointer();
			pointer new_end = pointer();
			pointer new_end_capacity = pointer();
			
			int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
			new_start = _buffer_size.allocate(next_capacity);
			new_end_capacity = new_start + next_capacity;

			if (size_type(new_end_capacity - new_start) < this->size() + n)
			{
				_buffer_size.deallocate(new_start, new_end_capacity - new_start);
				next_capacity = this->size() + n;
				new_start = _buffer_size.allocate(next_capacity);
				new_end = new_start + this->size() + n;
				new_end_capacity = new_start + next_capacity;
			}
			new_end = new_start + this->size() + n;
			for (int i = 0; i < (&(*position) - _buffer_start); i++)
				_buffer_size.construct(new_start + i, *(_buffer_start + i));
			for (size_type k = 0; k < n; k++)
				_buffer_size.construct(new_start + pos_len + k, x);
			for (size_type j = 0; j < (this->size() - pos_len); j++)
				_buffer_size.construct(new_end - j - 1, *(_current_end - j - 1));
			for (size_type u = 0; u < this->size(); u++)
				_buffer_size.destroy(_buffer_start + u);
			_buffer_size.deallocate(_buffer_start, this->capacity());
			_buffer_start = new_start;
			_current_end= new_end;
			_end_of_buffer = new_end_capacity;
		}
	}
    template <class InputIterator>
    	void insert (iterator position, InputIterator start, InputIterator finish,
		typename ft::enable_if<!ft::is_integral< InputIterator >::value >::type* = u_nullptr)
		{
			size_type pos_at = &(*position) - this->_buffer_start;
			size_type n = ft::distance(start, finish);

    	if (this->capacity() >= this->size() + n) {
      		for (size_type i = 0; i < this->size() - pos_at; ++i) {
        		this->_buffer_size.construct(this->_current_end + n - i, *(this->_current_end - i));
        		this->_buffer_size.destroy(this->_current_end - i);
      		}
      		this->_current_end = this->_buffer_start + this->size() + n;
      		for (size_type i = 0; i < n; ++i) {
        		this->_buffer_size.construct(this->_buffer_start + pos_at + i, *start++);
      		}
      		return;
    	}

   		size_type next_capacity = this->size() + n;

    	pointer prev_start = this->_buffer_start;
    	pointer prev_end = this->_current_end;
    	size_type prev_size = this->size();
    	size_type prev_capacity = this->capacity();

    	this->_buffer_start = this->_buffer_size.allocate(next_capacity);
    	this->_current_end = this->_buffer_start + prev_size + n;
    	this->_end_of_buffer = this->_current_end;

    	for (size_type i = 0; i < pos_at; ++i) {
    		this->_buffer_size.construct(this->_buffer_start + i, *(prev_start + i));
    		this->_buffer_size.destroy(prev_start + i);
    	}

    	for (size_type i = 0; i < prev_size - pos_at; ++i) {
    		this->_buffer_size.construct(this->_current_end - i - 1, *(prev_end - i - 1));
    		this->_buffer_size.destroy(prev_end - i - 1);
    	}

    	for (size_type i = 0; i < n; ++i) {
     		this->_buffer_size.construct(this->_buffer_start + pos_at + i, *start++);
    	}
		if (prev_capacity > 0)
    		this->_buffer_size.deallocate(prev_start, prev_capacity);
    	return;
  	}

    iterator erase (iterator position)
	{
		pointer tmp = _current_end - 1;
		_current_end = &(*position);
		pointer ret = _current_end;
		_buffer_size.destroy(&(*position));
		for (; _current_end < tmp; _current_end++)
		{
			_buffer_size.construct(_current_end, *(_current_end + 1));
			_buffer_size.destroy(_current_end + 1);
		}
		return (iterator(ret));
	}
    iterator erase (iterator start, iterator finish)
	{
			if (&(*start) == &(*finish))
				return (iterator(_buffer_start));
			size_type sz = ft::distance(start, finish);
			size_type cpy_sz = ft::distance(finish, iterator(_current_end));
			if (sz == this->size())
			{
				this->clear();
				return (_current_end);
			}
			_current_end = &(*start);
			pointer ret = &(*finish);
			for (size_type i = 0; i < sz; i++, start++)
			{
				_buffer_size.destroy(&(*start));
			}
			for (; cpy_sz > 0;cpy_sz--, _current_end++, finish++)
			{
				_buffer_size.construct(_current_end, *(&(*finish)));
				_buffer_size.destroy(&(*finish));
			}
			return (iterator(ret));
	}

    void swap (vector<T, Allocator>& x)
	{
		if (x == *this)
			return ;
		
		pointer save_start = x._buffer_start;
		pointer save_end = x._current_end;
		pointer save_end_capacity = x._end_of_buffer;
		allocator_type save_alloc = x._buffer_size;

		x._buffer_start = this->_buffer_start;
		x._current_end = this->_current_end;
		x._end_of_buffer = this->_end_of_buffer;
		x._buffer_size = this->_buffer_size;

		this->_buffer_start = save_start;
		this->_current_end = save_end;
		this->_end_of_buffer = save_end_capacity;
		this->_buffer_size = save_alloc;
	}
    void clear ()
	{
		while (this->size() > 0)
		{
			_current_end--;
			_buffer_size.destroy(_current_end);
		}
	}
  };

	// Nonmember vector Operators
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