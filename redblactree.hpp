#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <iostream>
#include <new>
#include <cassert>
#include "utils.hpp"

namespace ft
{
	template <class T>
	class Node
	{
		public:
			typedef T	value_type;
		private:
			value_type	_data;
			Node		*_left;
			Node		*_right;
			Node		*_parent;
			int			_color;
		
		explicit Node(const value_type& val = value_type())
			:
				_data(val),
				_left(u_nullptr),
				_right(u_nullptr),
				_parent(u_nullptr),
				_color(1)
			{}
		explicit Node(const Node* parent, const Node* left, const Node* right,
		const value_type& val = value_type())
			:
				_parent(parent),
				_left(left),
				_right(right),
				_data(val),
				_color(1)
			{}
		~Node()
		{
			if (this->_left)
				delete this->_left;
			if (this->_right)
				delete this->_right;
		}

		bool	isBlack() { return this->_color == 1; };
		bool	isRed() { return this->_color == 0; };

		void	insert()
		{
			
		}

	};
}

#endif