#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utils.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
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
	reverse_iterator()
		:
			_elem()
		{}
	explicit reverse_iterator (iterator_type it) : _elem(it) {}
	template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it)
		:
			_elem(rev_it.base())
		{}
	virtual ~reverse_iterator() {}
	
	// member functions
	iterator_type base() const { return (_elem); };
	// operator reverse_iterator< const Iterator >() const { return this->current; }
	reference operator*() const
	{
		iterator_type ret = _elem;
		return (*(--ret));
	}
	reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_elem - n)); };
	reverse_iterator& operator++()
	{
		--_elem;
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
		++_elem;
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
	reference operator[] (difference_type n) const { return (_elem[-n-1]); };

	private:
    	iterator_type     _elem;
	};

	template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
    template <class Iterator_L, class Iterator_R>
        bool operator== (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }
    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
    template <class Iterator_L, class Iterator_R>
        bool operator!= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }
    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
    template <class Iterator_L, class Iterator_R>
        bool operator< (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }
    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }
    template <class Iterator_L, class Iterator_R>
        bool operator<= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }
    template <class Iterator>
        bool operator> (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
    template <class Iterator_L, class Iterator_R>
        bool operator> (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }
    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }
    template <class Iterator_L, class Iterator_R>
        bool operator>= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator>
        reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs) { return (rhs.base() - lhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator- (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (rhs.base() - lhs.base()); }

    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) return false;
                else if (*first1 < *first2) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }
    template <class InputIterator1, class InputIterator2, class Compare>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2,
                                        Compare comp)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || comp(*first2, *first1)) return false;
                else if (comp(*first1, *first2)) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }
		
template <typename T>
    struct BST_Node
    {
        public :

            typedef T   value_type;
            value_type value;
            BST_Node* parent;
            BST_Node* left;
            BST_Node* right;

            BST_Node ()
            :
                value(),
                parent(u_nullptr),
                left(u_nullptr),
                right(u_nullptr)
            {}

            BST_Node (BST_Node* parent = u_nullptr,
                    BST_Node* left = u_nullptr, BST_Node* right = u_nullptr)
            :
                value(),
                parent(parent),
                left(left),
                right(right)
            {}
            
            BST_Node (const value_type& val, BST_Node* parent = u_nullptr,
                    BST_Node* left = u_nullptr, BST_Node* right = u_nullptr)
            :
                value(val),
                parent(parent),
                left(left),
                right(right)
            {}

            BST_Node (const BST_Node& nd)
            :
                value(nd.value),
                parent(nd.parent),
                left(nd.left),
                right(nd.right)
            {}

            virtual ~BST_Node() {}

            BST_Node &operator=(const BST_Node& nd)
            {
                if (nd == *this)
                    return (*this);
                
                this->value = nd.value;
                this->parent = nd.parent;
                this->left = nd.left;
                this->right = nd.right;
                
                return (*this);
            }

            bool operator==(const BST_Node& nd)
            {
                if (value == nd.value)
                    return (true);
                return (false);
            }
    };

template <class Data_T>
    struct Doubly_Linked_Node 
    {
        public :

            Doubly_Linked_Node  *prev;
            Doubly_Linked_Node  *next;
            Data_T              data;

            Doubly_Linked_Node()
            :
                prev(u_nullptr),
                next(u_nullptr)
            {}

            Doubly_Linked_Node(const Data_T& val)
            :
                prev(u_nullptr),
                next(u_nullptr),
                data(val)
            {}

            Doubly_Linked_Node(const Data_T& val,
                Doubly_Linked_Node *prev, Doubly_Linked_Node *next)
            :
                prev(prev),
                next(next),
                data(val)
            {}
    };
}

#endif