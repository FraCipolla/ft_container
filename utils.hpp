#ifndef UTILS_HPP
#define UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>
#include "reverse_iterator.hpp"

const                         /* this is a const object...     */
class nullptr_t
{
public:
   template<class T>          /* convertible to any type       */
   operator T*() const        /* of null non-member            */
      { return 0; }           /* pointer...                    */

   template<class C, class T> /* or any type of null           */
      operator T C::*() const /* member pointer...             */
      { return 0; }   

private:
   void operator&() const;    /* Can't take address of nullptr */

} u_nullptr = {};             /* and whose name is nullptr     */
		
namespace ft
{
	template <class BidirectionalIterator>
	void reverse (BidirectionalIterator first, BidirectionalIterator last)
	{
	  while ((first!=last)&&(first!=--last))
	  {
	    std::iter_swap (first,last);
	    ++first;
	  }
	}
	
	template <typename T>
    std::string to_string(T n)
    {
        std::ostringstream ss;
        ss << n;
        return (ss.str());
    }

	template <class Arg1, class Arg2, class Result>
		struct binary_function
		{
			typedef Arg1 first_argument_type;
			typedef Arg2 second_argument_type;
			typedef Result result_type;
		};
	
	template <class T>
        struct less : binary_function<T, T, bool>
        {
            bool operator() (const T& x, const T& y) const { return (x < y); }
        };

    template <class T1, class T2>
        struct pair
        {
            public :
                typedef T1 first_type;
                typedef T2 second_type;

                first_type first;
                second_type second;

                pair()
                :
                    first(),
                    second()
                {}

                template<class U, class V>
                    pair (const pair<U, V>& pr)
                    :
                        first(pr.first),
                        second(pr.second)
                    {}

                pair (const first_type& a, const second_type& b)
                :
                    first(a),
                    second(b)
                {}

                pair& operator= (const pair& pr)
                {
                    if (*this == pr)
                        return (*this);
                    this->first = pr.first;
                    this->second = pr.second;
                    return (*this);
                }
        };

    template <class T1, class T2>
        bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (lhs.first == rhs.first && lhs.second == rhs.second);
        }
    template <class T1, class T2>
        bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(lhs == rhs);
        }
    template <class T1, class T2>
        bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
        }
    template <class T1, class T2>
        bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(rhs < lhs);
        }
    template <class T1, class T2>
        bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (rhs < lhs);
        }
    template <class T1, class T2>
        bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(lhs < rhs);
        }
    template <class T1, class T2>
        ft::pair<T1,T2> make_pair(T1 x, T2 y)
        {
            return (ft::pair<T1, T2>(x, y));
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
		struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};
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

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag { };
	struct bidirectional_iterator_tag { };
	struct random_access_iterator_tag { };

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

template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type       difference_type;
        typedef typename Iterator::value_type            value_type;
        typedef typename Iterator::pointer               pointer;
        typedef typename Iterator::reference             reference;
        typedef typename Iterator::iterator_category     iterator_category;
	};

 template <class T>
 	struct iterator_traits<T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

template <class T>
	class iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
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
			public:
            	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
            	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
            
            private:
                pointer _elem;
        };

}

#endif