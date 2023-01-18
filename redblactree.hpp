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
			Node		*_root;
			int			_color;
		
		explicit Node(const value_type& val = value_type())
			:
				_data(val),
				_left(u_nullptr),
				_right(u_nullptr),
				_parent(u_nullptr),
				_root(u_nullptr),
				_color(1)
			{}
		// explicit Node(const Node* _parent, const Node* _left, const Node* _right,
		// const value_type& val = value_type())
		// 	:
		// 		_parent(_parent),
		// 		_left(_left),
		// 		_right(_right),
		// 		_data(val),
		// 		_color(1)
		// 	{}
		~Node()
		{
			if (this->_left)
				delete this->_left;
			if (this->_right)
				delete this->_right;
		}

		bool	isBlack() { return this->_color == 1; };
		bool	isRed() { return this->_color == 0; };
		Node	getRoot() { return this->_root; };
		Node	min(Node node)
		{
			while (node->_left != u_nullptr)
				node = node->_left;
			return node;
		}
		Node	max(Node node)
		{
			while (node->_right != u_nullptr)
				node = node->_right;
			return node;
		}
		Node	successor(Node x)
		{
			if (x->_right != u_nullptr)
				return (min(x->_right));
			Node y = x->_parent;
			while (y != u_nullptr && x == y->_right)
			{
				x = y;
				y = y->_parent;
			}
			return (y);
		}
		Node	predecessor(Node x)
		{
			if (x->_left != u_nullptr)
				return (max(x->_left));
			Node y = x->_parent;
			while (y != u_nullptr && x == y->_left)
			{
				x = y;
				y = y->_parent;
			}
			return (y);
		}
		void	printHelper(Node root, std::string indent, bool last)
		{
			if (root != NULL)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "   ";
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}
				std::string sColor = root->_color ? "RED" : "BLACK";
      			std::cout << root->_data << "(" << sColor << ")" << std::endl;
      			printHelper(root->_left, indent, false);
      			printHelper(root->_right, indent, true);
			}
		}
		void	print()
		{
			if (_root)
				printHelper(this->_root, "", true);
		}

		Node	searchElHelper(Node node, const value_type& val = value_type())
		{
			if (node == NULL || val == node->_data)
				return node;
			if (val < node->_data)
				return (searchEl(node->_left, val));
			return (searchEl(node->_right, val));
		}

		Node SearchEl(const value_type& val = value_type())
		{ return searchElHelper(this->_root, val); };

		void insertFix(Node k)
		{
    		Node u;
    		while (k->_parent->_color == 1)
			{
    			if (k->_parent == k->_parent->_parent->_right)
				{
					u = k->_parent->_parent->_left;
    		    	if (u->_color == 1)
					{
						u->_color = 0;
    		    		k->_parent->_color = 0;
    		    		k->_parent->_parent->_color = 1;
    		    		k = k->_parent->_parent;
					}
					else
					{
						if (k == k->_parent->_left)
						{
							k = k->_parent;
							rightRotate(k);
						}
    		    		k->_parent->_color = 0;
    		    		k->_parent->_parent->_color = 1;
    		    		leftRotate(k->_parent->_parent);
    		   		}
				}
				else
				{
					u = k->_parent->_parent->_right;
					if (u->_color == 1)
					{
						u->_color = 0;
						k->_parent->_color = 0;
						k->_parent->_parent->_color = 1;
						k = k->_parent->_parent;
					}
					else
					{
						if (k == k->_parent->_right)
						{
							k = k->_parent;
							leftRotate(k);
						}
						k->_parent->_color = 0;
						k->_parent->_parent->_color = 1;
						rightRotate(k->_parent->_parent);
					}
				}
				if (k == _root)
					break;
    		}
			_root->_color = 0;
		}

		void deleteFix(NodePtr x)
		{
			Node s;
			while (x != _root && x->_color == 0)
			{
				if (x == x->_parent->_left)
				{
			    	s = x->_parent->_right;
			    	if (s->_color == 1)
					{
			    		s->_color = 0;
			    		x->_parent->_color = 1;
			    		leftRotate(x->_parent);
			    		s = x->_parent->_right;
			    	}	
			    	if (s->_left->_color == 0 && s->_right->_color == 0)
					{
			    		s->_color = 1;
			    		x = x->_parent;
			    	}
					else
					{
			    		if (s->_right->_color == 0)
						{
			    			s->_left->_color = 0;
			    			s->_color = 1;
			    			rightRotate(s);
			    			s = x->_parent->_right;
			    		}	
			    		s->_color = x->_parent->_color;
			    		x->_parent->_color = 0;
			    		s->_right->_color = 0;
			    		leftRotate(x->_parent);
			    		x = _root;
			    	}
				}
				else
				{
			    	s = x->_parent->_left;
			    	if (s->_color == 1)
					{
			    		s->_color = 0;
			    		x->_parent->_color = 1;
			    		rightRotate(x->_parent);
			    		s = x->_parent->_left;
			    	}	
			    	if (s->_right->_color == 0 && s->_right->_color == 0)
					{
			    		s->_color = 1;
			    		x = x->_parent;
			    	}
					else
					{
			    		if (s->_left->_color == 0)
						{
			        		s->_right->_color = 0;
			        		s->_color = 1;
			        		leftRotate(s);
			        		s = x->_parent->_left;
			      		}	
			      		s->_color = x->_parent->_color;
			      		x->_parent->_color = 0;
			      		s->_left->_color = 0;
			      		rightRotate(x->_parent);
			      		x = _root;
			    	}
				}
			}
			x->_color = 0;
		}

		void leftRotate(Node x)
		{
    		Node y = x->_right;
    		x->_right = y->_left;
    		if (y->_left != u_nullptr)
				y->_left->_parent = x;
    		y->_parent = x->_parent;
    		if (x->_parent == nullptr)
    			this->_root = y;
			else if (x == x->_parent->_left)
				x->_parent->_left = y;
			else
				x->_parent->_right = y;
    		y->_left = x;
    		x->_parent = y;
		}

  		void rightRotate(Node x)
  		{
  			Node y = x->_left;
  			x->_left = y->_right;
  			if (y->_right != u_nullptr)
				y->_right->_parent = x;
  			y->_parent = x->_parent;
  			if (x->_parent == nullptr)
  				this->_root = y;
  			else if (x == x->_parent->_right)
  				x->_parent->_right = y;
  			else
  				x->_parent->_left = y;
  			y->_right = x;
  			x->_parent = y;
  		}

		void	insert(const value_type& val = value_type())
		{
			Node	node = new Node;
			node->_parent = u_nullptr;
			node->_data = val;
			node->_left = u_nullptr;
			node->_right = u_nullptr;
			node->_color = 1;

			Node y = u_nullptr;
			Node x = this->_root;

			while (x != u_nullptr)
			{
				y = x;
      			if (node->data < x->data)
        			x = x->_left;
      			else
    				x = x->_right;
			}
			node->_parent = y;
			if (y == u_nullptr)
				_root = node;
			else if (node->_data < y->_data)
				y->_left = node;
			else
				y->_right = node;
			
			if (node->_parent == u_nullptr)
			{
				node->_color = 0;
				return ;
			}
			if (node->_parent->_parent == u_nullptr)
				return ;
			insertFix(node);
		}
		
		void rbTransplant(Node u, Node v)
		{
    		if (u->_parent == u_nullptr)
				_root = v;
			else if (u == u->_parent->_left)
    			u->_parent->_left = v;
    		else
    			u->_parent->_right = v;
    		v->_parent = u->_parent;
		}

		void	deleteNodeHelper(Node node, const value_type& val = value_type())
		{
			Node z = u_nullptr;
			Node x, y;
			while (node != u_nullptr)
			{
				if (node->data == val)
					z = node;
				if (node->data <= val)
					node = node->_right;
				else
					node = node->_left;
      		}
    		if (z == u_nullptr)
			{
				std::cout << "Key not found in the tree" << std::endl;
				return;
			}

    		y = z;
			int y_original_color = y->_color;
			if (z->_left == u_nullptr)
			{
				x = z->_right;
				rbTransplant(z, z->_right);
			}
			else if (z->_right == u_nullptr)
			{
				x = z->_left;
				rbTransplant(z, z->_left);
			}
			else
			{
    			y = minimum(z->_right);
				y_original_color = y->_color;
				x = y->_right;
				if (y->_parent == z)
					x->_parent = y;
				else
				{
					rbTransplant(y, y->_right);
					y->_right = z->_right;
					y->_right->_parent = y;
				}
    			rbTransplant(z, y);
    			y->_left = z->_left;
    			y->_left->_parent = y;
    			y->_color = z->_color;
			}
			delete z;
			if (y_original_color == 0)
				deleteFix(x);
		}
		void deleteNode(const value_type& val = value_type())
		{ deleteNodeHelper(this->_root, val); };
	};
}

#endif