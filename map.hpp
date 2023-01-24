#ifndef MAP_HPP
#define MAP_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include "redblacktree.hpp"
# include <iostream>
# include <functional>
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef std::pair<const key_type, mapped_type>	value_type;
			typedef Compare									key_compare;
			template <class Key, class T, class Compare, class Alloc>
				class map<Key,T,Compare,Alloc>::value_compare
				{
					friend class map;
					protected:
					  Compare comp;
					  value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
					public:
					  typedef bool result_type;
					  typedef value_type first_argument_type;
					  typedef value_type second_argument_type;
					  bool operator() (const value_type& x, const value_type& y) const
					  {
					    return comp(x.first, y.first);
					  }
				};
			typedef Alloc													allocator_type;
			typedef allocator_type::reference								reference;
			typedef allocator_type::const_reference							const_reference;
			typedef allocator_type::pointer									pointer;
			typedef allocator_type::const_pointer							const_pointer;
			typedef typename ft::random_access_iterator<value_type>			iterator;
    		typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
    		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename Allocator::size_type 							size_type;
    		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	
			// costructor
			map() : _comp(NULL), _buffer_size(u_nullptr) {}
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				:
					_comp(comp),
					_buffer_size(alloc)
				{}
			template <class InputIterator> map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
			map (const map& other)
			{
				this->_comp = other._comp;
				if (other._buffer_size)
					this->_buffer_size = other._buffer_size;
				else
					this->_buffer_size = std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.get_allocator());
			}

			// destructor
			~map();

			// member function
			map& operator= (const map& other);
			allocator_type get_allocator() const { return this->_buffer_size; };

			T& at( const Key& key );
			const T& at( const Key& key ) const;
			T& operator[]( const Key& key );
			T& operator[]( Key&& key );

			iterator begin();
			const_iterator begin();
			iterator end();
			const_iterator end();
			reverse_iterator rbegin();
			const_reverse_iterator rbegin();

			bool empty() const { return (this->size() == 0); };
			size_type size() const;
			size_type max_size() const;

			void clear();
			std::pair<iterator, bool> insert( const value_type& value );
			void erase( iterator pos );
			void erase( iterator first, iterator last );
			size_type erase( const Key& key );
			void swap( map& other );

			size_type count( const Key& key ) const;
			iterator find( const Key& key );
			const_iterator find( const Key& key ) const;
			std::pair<iterator,iterator> equal_range( const Key& key );
			std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
			iterator lower_bound( const Key& key );
			const_iterator lower_bound( const Key& key ) const;
			iterator upper_bound( const Key& key );
			const_iterator upper_bound( const Key& key ) const;

			key_compare key_comp() const;
			ft::map::value_compare value_comp() const;

			private:
				allocator_type	_buffer_size;
				Compare			_comp;
				Node			_node;
	};

	// Non-member function
	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
        const ft::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
		void swap( ft::map<Key,T,Compare,Alloc>& lhs,
    	ft::map<Key,T,Compare,Alloc>& rhs );
	
}

#endif