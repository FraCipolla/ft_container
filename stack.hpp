#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {

		public:
		typedef Container								container_type;
		typedef T										value_type;
		typedef typename Container::size_type			size_type;
		typedef typename Container::reference			reference;
		typedef typename Container::const_reference		const_reference;

		protected:
			container_type	_ctnr;

		public:
		// costructor
		explicit stack (const container_type& ctnr = container_type()) { this->_ctnr = ctnr; };
		// ~stack() {};
		
		// member functions
		stack& operator=( const stack& other )
		{
			_ctnr = other._ctnr;
			return *this;
		}
		bool empty() const { return (this->_ctnr.empty()); };
		size_type size() const { return (this->_ctnr.size()); };
		value_type& top () { return (this->_ctnr.back()); };
		void push (const value_type& val) { return (this->_ctnr.push_back(val)); };
		void pop () { return (this->_ctnr.pop_back()); };
		// template <class... Args> void emplace (Args&&... args) { this->_ctnr.emplace_back(args); };
		// void swap (stack& x) noexcept { ft::swap(*this, x); };

	template <class Tn, class ContainerN>  
		friend bool operator== (const ft::stack<Tn,ContainerN>& lhs, const ft::stack<Tn,ContainerN>& rhs);
	template <class Tn, class ContainerN> 
		friend bool operator!= (const ft::stack<Tn,ContainerN>& lhs, const ft::stack<Tn,ContainerN>& rhs);
	template <class Tn, class ContainerN> 
		friend bool operator<  (const ft::stack<Tn,ContainerN>& lhs, const ft::stack<Tn,ContainerN>& rhs);
	template <class Tn, class ContainerN> 
		friend bool operator<= (const ft::stack<Tn,ContainerN>& lhs, const ft::stack<Tn,ContainerN>& rhs);
	template <class Tn, class ContainerN>
		friend bool operator>  (const ft::stack<Tn,ContainerN>& lhs, const ft::stack<Tn,ContainerN>& rhs);
	template <class Tn, class ContainerN>
		friend bool operator>= (const ft::stack<Tn,ContainerN>& lhs, const ft::stack<Tn,ContainerN>& rhs);

	};
	
	// non member function
	
	// template <class T, class Container>  void swap (stack<T,Container>& x, stack<T,Container>& y)
	// 	noexcept(noexcept(x.swap(y)));

	template <class T, class Container>  
		bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{ return (lhs._ctnr == rhs._ctnr); };
	template <class T, class Container> 
		bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{ return (lhs._ctnr != rhs._ctnr); };
	template <class T, class Container> 
		bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{ return (lhs._ctnr < rhs._ctnr); };
	template <class T, class Container> 
		bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{ return (lhs._ctnr <= rhs._ctnr); };
	template <class T, class Container>
		bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{ return (lhs._ctnr > rhs._ctnr); };
	template <class T, class Container>
		bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{ return (lhs._ctnr >= rhs._ctnr); };

}

#endif