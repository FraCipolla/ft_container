#ifndef MAP_HPP
#define MAP_HPP

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
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
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				:
					_comp(comp),
					_buffer_size(alloc)
				{}
			template <class InputIterator> map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
			map (const map& x);

			// destructor
			~map();

			// member function
			map& operator= (const map& x);

			private:
				allocator_type	_buffer_size;
				Compare			_comp;
	};
	
}

#endif