#ifndef MY_ITERATOR_HPP
#define MY_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	template <typename T>
        std::string to_string(T n)
        {
            std::ostringstream ss;
            ss << n;
            return (ss.str());
        }
	
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

    template <bool is_integral, typename T>
        struct is_integral_res {
            typedef T type;
            static const bool value = is_integral;
            };

    template <typename>
        struct is_integral_type : public is_integral_res<false, bool> {};
    template <>
        struct is_integral_type<bool> : public is_integral_res<true, bool> {};
    template <>
        struct is_integral_type<char> : public is_integral_res<true, char> {};
    template <>
        struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
    template <>
        struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    template <>
        struct is_integral_type<int> : public is_integral_res<true, int> {};
    template <>
        struct is_integral_type<long int> : public is_integral_res<true, long int> {};
    template <>
        struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
    template <>
        struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
    template <>
        struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
    template <>
        struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
    template <>
        struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    template <>
        struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};
    template <typename T>
        struct is_integral : public is_integral_type<T> { };

	class random_access_iterator_tag { };
	class bidirectional_iterator_tag { };
	class forward_iterator_tag { };
	class input_iterator_tag { };
	class output_iterator_tag { };

	template <bool is_valid, typename T>
    	struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };

	template <typename T>
        struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };
	template <>
        struct is_input_iterator_tagged<ft::random_access_iterator_tag>
			: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };
	template <>
        struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };
	template <>
        struct is_input_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };
	template <>
        struct is_input_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };
	template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string _msg;
        
        public :
            InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
            InvalidIteratorException (const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };

	template <typename T>
		struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    template <>
		struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
			: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };
    template <>
		struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
			: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };
    template <>
		struct is_ft_iterator_tagged<ft::forward_iterator_tag>
			: public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };
    template <>
		struct is_ft_iterator_tagged<ft::input_iterator_tag>
			: public valid_iterator_tag_res<true, ft::input_iterator_tag> { };
    template <>
		struct is_ft_iterator_tagged<ft::output_iterator_tag>
			: public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

template <class Iterator> struct iterator_traits
	{
		typedef typename Iterator::difference_type       difference_type;
        typedef typename Iterator::value_type            value_type;
        typedef typename Iterator::pointer               pointer;
        typedef typename Iterator::reference             reference;
        typedef typename Iterator::iterator_category     iterator_category;
	};

 template <class T>	struct iterator_traits<T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

template <class T>	class iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

template<class InputIterator>
        typename ft::iterator_traits<InputIterator>::difference_type 
		distance(InputIterator first, InputIterator last)
        {
            typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
            while (first != last)
            {
                first++;
                rtn++;
            }
            return (rtn);
        }

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
    		typedef T         value_type;
    		typedef Distance  difference_type;
    		typedef Pointer   pointer;
    		typedef Reference reference;
    		typedef Category  iterator_category;
	};

template <class T>
        class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
        {  
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
            
            private:
                pointer _elem;
        };

template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator   													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category 	iterator_category;
    	typedef typename ft::iterator_traits<Iterator>::value_type      	value_type;
    	typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
    	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
    	typedef typename ft::iterator_traits<Iterator>::reference   		reference;

	// constructors
	reverse_iterator() : _elem() {}
	explicit reverse_iterator (iterator_type it) : _elem(it) {}
	template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it)
		:
			_elem(rev_it.base())
		{}
	virtual ~reverse_iterator() {}
	
	// member functions
	iterator_type base() const { return (_elem); };
	reference operator*() const
	{
		iterator_type ret = _elem;
		return (*(--ret));
	}
	reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_elem - n)); };
	reverse_iterator& operator++()
	{
		_elem--;
		return (*this);
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator temp = *this;
		++(*this);
		return temp;
	}
	reverse_iterator& operator+= (difference_type n)
	{
		_elem -= n;
		return (*this);
	}
	reverse_iterator operator- (difference_type n) const {return (reverse_iterator(_elem + n)); };
	reverse_iterator& operator--()
	{
		_elem++;
		return (*this);
	}
	reverse_iterator  operator--(int)
	{
		reverse_iterator temp = *this;
		--(*this);
		return temp;
	}
	reverse_iterator& operator-= (difference_type n)
	{
		_elem += n;
		return (*this);
	}
	pointer operator->() const { return &(operator*()); };
	reference operator[] (difference_type n) const { return (this->base()[-n-1]); };

	private:
    	iterator_type     _elem;
	};

	template <typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef T*              pointer;
            typedef T&				reference;

			//costructor
			random_access_iterator() : _elem(nullptr) {}
			explicit random_access_iterator(pointer el) : _elem(el) {}
			random_access_iterator(const random_access_iterator& op)
                :
                    _elem(op._elem)
                {}
			random_access_iterator &operator=(const random_access_iterator& op)
                {
                    if (this == &op)
		                return (*this);
                    this->_elem = op._elem;
                    return (*this);
                }
			virtual ~random_access_iterator() {}

			// member function
			pointer base () const { return (this->_elem); };
			reference operator*(void) const { return (*_elem); };
			pointer operator->(void) { return &(this->operator*()); };
			random_access_iterator& operator++(void)
            	{
                	_elem++;
                	return (*this);
            	}
			random_access_iterator operator++(int)
            	{
                    random_access_iterator rtn(*this);
                    operator++();
                    return (rtn);
                }
			random_access_iterator& operator--(void)
                {
                    _elem--;
                    return (*this);
                }
			random_access_iterator operator--(int)
                {
                    random_access_iterator rtn(*this);
                    operator--();
                    return (rtn);
                }
			random_access_iterator operator+(difference_type n) const { return (_elem + n); }
			random_access_iterator operator-(difference_type n) const { return (_elem - n); }
			random_access_iterator& operator+=(difference_type n)
                {
                    _elem += n;
                    return (*this);
                }
			random_access_iterator& operator-=(difference_type n)
                {
                    _elem -= n;
                    return (*this);
                }
			reference operator[](difference_type n) { return (*(operator+(n))); };
			operator random_access_iterator<const T> () const { return (random_access_iterator<const T>(this->_elem)); };
		
		private:
			pointer _elem;
	};
template <typename T>
    typename ft::random_access_iterator<T>::difference_type operator==(const ft::random_access_iterator<T> x, 
	const ft::random_access_iterator<T> y)
    {
        return (x.base() == y.base());
    }
template <typename T>
    typename ft::random_access_iterator<T>::difference_type operator!=(const ft::random_access_iterator<T> x, 
	const ft::random_access_iterator<T> y)
    {
        return (x.base() != y.base());
    }
}

#endif