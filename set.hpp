#ifndef SET_HPP
#define SET_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include "redblactree.hpp"
# include <iostream>
# include <functional>
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

namespace ft
{
	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> > 
	class set
	{
		public:
			typedef typename Key::key_type									key_type;
			typedef typename Key::value_type								value_type;
			typedef std::size_t												size_type;
			typedef std::ptrdiff_t											difference_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Allocator												allocator_type;
			typedef typename Allocator::reference							reference;
			typedef typename Allocator::const_reference 					const_reference;
    		typedef typename Allocator::pointer 							pointer;
    		typedef typename Allocator::const_pointer 						const_pointer;
			typedef typename ft::random_access_iterator<value_type>			iterator;
   			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
    		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
    		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		
		private:
			allocator_type	_buffer_size;
			Compare			_compare;
			ft::Node			_node;

		public:
			set() : _buffer_size(u_nullptr), _compare(u_nullptr), _node(u_nullptr) {};
			explicit set( const Compare& comp, const Allocator& alloc = Allocator() )
				:
					_compare(comp),
					_buffer_size(alloc)
				{
					_node = _buffer_size.allocate(1);
					this->_construct(_node);
				
				}
	};
} // namespace ft


#endif