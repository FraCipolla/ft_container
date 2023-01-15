#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <new>
#include <cassert>

namespace ft
{
	template <typename T>
	class Node {
	
	public:
		Node<T> 	*parent;
		Node<T> 	*left;
		Node<T> 	*right;
		T 			data;

	// costructor
	Node() : parent(NULL), left(NULL), right(NULL) {}
	Node(T data) : data(data),  parent(NULL), left(NULL), right(NULL) {}
	Node(T data, Node<T> *parent, Node<T> *left, Node<T> *right)
	:
		data(data),
		parent(parent),
		left(left),
		right(right)
	{}

 	static void walk(const Node<T> *tree);
 	static Node<T> *find(Node<T> *tree, T value);
 	static Node<T> *minimum(Node<T> *tree);
 	static Node<T> *maximum(Node<T> *tree);
 	static Node<T> *successor(Node<T> *tree);

	// Always returns the root of the tree, whether it had to be modified or not
 	static Node<T> *insertNode(Node<T> *tree, Node<T> *node);
 	static Node<T> *deleteNode(Node<T> *tree, Node<T> *node);

	private:
	 	static Node<T> *transplant(Node<T> *tree, Node<T> *u, Node<T> *v);
	};

	template<typename T> std::ostream &operator<<(std::ostream &output, Node<T> node);

	template <typename T> void Node<T>::walk(const Node<T> *tree)
	{
		if (tree == NULL) return;

		walk(tree -> left);
		std::cout << tree -> data << "\n";
		walk(tree -> right);
	}

	template <typename T> Node<T> *Node<T>::insertNode(Node<T> *tree, Node<T> *node)
	{
		if (!tree)
		{
			tree = node;
			node -> parent = NULL;
		}
		else
		{
			Node<T> *parent, *search = tree;
			bool left = false;
			while (search != NULL)
			{
				parent = search;
				if (node -> data <= search -> data)
				{
					search = search -> left;
					left = true;
				}
				else
				{
					search = search -> right;
					left = false;
				}
			}
			node -> parent = parent;
			if (left) parent -> left = node;
			else parent -> right = node;
		}

		return tree;
	}

	template <typename T> Node<T> *Node<T>::find(Node<T> *tree, T value)
	{
		if (!tree || tree -> data == value) return tree;
		if (value < tree -> data) return find(tree -> left, value);
		else return find(tree -> right, value);
	}

	template <typename T> Node<T> *Node<T>::minimum(Node<T> *tree)
	{
		if (!tree) return NULL;

		while (tree -> left) {
			tree = tree -> left;
		}

		return tree;
	}

	template <typename T> Node<T> *Node<T>::maximum(Node<T> *tree) {
		if (!tree) return NULL;

		while (tree -> right) {
			tree = tree -> right;
		}

		return tree;
	}

	template <typename T> Node<T> *Node<T>::successor(Node<T> *node) {
		if (!node) return NULL;

		if (node -> right) {
			return minimum(node -> right);
		} else {
			// We need to traverse upwards in the tree to find a node where
			// the node is the left child of a parent
			// parent is the successor

			Node<T> *parent = node -> parent;
			while(parent && node != parent -> left) {
				node = parent;
				parent = node -> parent;
			}

			return parent;
		}

	}

	// make node U's paarent have node v has its child
	template <typename T> Node<T> *Node<T>::transplant(Node<T> *tree, Node<T> *u, Node<T> *v) {
		if (!u -> parent) tree = v;
		else if (u -> parent -> left == u) {
			u -> left = v;
		} else if (u -> parent -> right == u) {
			u -> right = v;
		}
		if (v) v -> parent = u -> parent;
		return tree;
	}

	template <typename T> Node<T> *Node<T>::deleteNode(Node<T> *tree, Node<T> *node) {
		if (!node -> left) {
			tree = transplant(tree, node, node -> right);
		} else if (!node -> right) {
			tree = transplant(tree, node, node -> left);
		} else {
			// Has two children -- successor must be on the right
			Node <int> *successor = minimum(node -> right);
			assert(successor -> left == NULL);
			if (successor != node -> right) {
				tree = transplant(tree, successor, successor -> right);
				successor -> right = node -> right;
				successor -> right -> parent = successor;
			}

			tree = transplant(tree, node, successor);
			successor -> left = node -> left;
			successor -> left -> parent = successor;
		}
		return tree;
	}

	template<typename T> std::ostream &operator<<(std::ostream &output, Node<T> node) {
		output << "Value: " << node.data;
		if (node.parent) output << " Parent: " << node.parent -> data;
		if (node.left) output << " Left: " << node.left -> data;
		if (node.right) output << " Right: " << node.right -> data;
		output << "\n";
		return output;
	}
}
#endif



// Implementing Red-Black Tree in C++

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

typedef Node *NodePtr;

class RedBlackTree {
   private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
  void preOrderHelper(NodePtr node) {
    if (node != TNULL) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key) {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};

int main() {
  RedBlackTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();
}