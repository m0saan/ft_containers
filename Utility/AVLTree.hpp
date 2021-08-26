//
// Created by moboustt on 21/8/2021.
//

#ifndef __AVL_HPP__
#define __AVL_HPP__

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "choose.hpp"

#include <map>

namespace ft {

	template<typename T, typename Compare>
	class AVLTree {

	private:

		class Node {
		public:
			explicit Node(T const &value, Node *left = NULL, Node *right = NULL, Node *par = NULL)
					: _value(value), _leftChild(left), _rightChild(right), _parent(par), _height(0) {}

			T _value;
			Node *_leftChild, *_rightChild, *_parent;
			std::size_t _height;
		};

		class AVLTreeIterator : public ft::iterator<std::bidirectional_iterator_tag, T> {

		public:

			typedef T value_type;
			typedef typename T::first_type key_type;
			typedef typename T::second_type mapped_type;
			// typedef value_type* pointer;
			// typedef value_type& reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			//typedef typename AVLTree<T>::Compare key_compare;
			typedef AVLTreeIterator const_iterator;
			typedef const_iterator iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename ft::choose<is_const<value_type>::value, const value_type &, value_type &>::type reference;
			typedef typename ft::choose<is_const<value_type>::value, const value_type *, value_type *>::type pointer;


			friend class AVLTree;

			AVLTreeIterator() : _nodePtr(), _tree() {}

			AVLTreeIterator(const AVLTreeIterator &other) {
				*this = other;
			}


			AVLTreeIterator &operator=(const AVLTreeIterator &other) {
				if(this != &other) {
					_nodePtr = other._nodePtr;
					_tree = other._tree;
				}
				return *this;
			}

			reference operator*() const _NOEXCEPT {
				return _nodePtr->_value;
			}

			pointer operator->() const {
				return (&this->_nodePtr->_value);
			}

			AVLTreeIterator &operator++() {

				Node *p;

				if(_nodePtr == NULL) {

					// ++ from end(). get the root of the tree
					_nodePtr = _tree->_root;

					// error! ++ requested for an empty tree
					if(_nodePtr == NULL)
						throw std::logic_error("Underflow Exception.");

					// move to the smallest value in the tree,
					// which is the first node inorder
					while(_nodePtr->_leftChild != NULL) {
						_nodePtr = _nodePtr->_leftChild;
					}
				} else {
					if(_nodePtr->_rightChild) {

						/*	next Node is the farthest left node of
						 *	right subtree
						 */
						_nodePtr = _nodePtr->_rightChild;
						while(!_nodePtr)
							_nodePtr = _nodePtr->_leftChild;
					} else {
						// have already processed the left subtree, and
						// there is no right subtree. move up the tree,
						// looking for a parent for which nodePtr is a left child,
						// stopping if the parent becomes NULL. a non-NULL parent
						// is the successor. if parent is NULL, the original node
						// was the last node inorder, and its successor
						// is the end of the list
						p = _nodePtr->_parent;
						while(p != NULL && _nodePtr == p->_rightChild) {
							_nodePtr = p;
							p = p->_parent;
						}

						// if we were previously at the right-most node in
						// the tree, nodePtr = nullptr, and the iterator specifies
						// the end of the list
						_nodePtr = p;
					}
				}
				return *this;
			}

			AVLTreeIterator &operator--() {
				Node *p;
				if(_nodePtr == NULL) {

					// -- from end(). get the root of the tree
					_nodePtr = _tree->max()->_parent;

					// error! ++ requested for an empty tree
					if(_nodePtr == NULL)
						throw std::logic_error("Underflow Exception.");

					// move to the farthest value in the tree,
					// which is the last node inorder
					while(_nodePtr->_rightChild != NULL) {
						_nodePtr = _nodePtr->_rightChild;
					}
				} else {
					if(_nodePtr->_leftChild) {

						/*	next Node is the farthest left node of
						 *	right subtree
						 */
						_nodePtr = _nodePtr->_leftChild;
						while(!_nodePtr)
							_nodePtr = _nodePtr->_rightChild;
					} else {
						// have already processed the left subtree, and
						// there is no right subtree. move up the tree,
						// looking for a parent for which nodePtr is a left child,
						// stopping if the parent becomes NULL. a non-NULL parent
						// is the successor. if parent is NULL, the original node
						// was the last node inorder, and its successor
						// is the end of the list
						p = _nodePtr->_parent;
						while(p != NULL && _nodePtr == p->_leftChild) {
							_nodePtr = p;
							p = p->_parent;
						}

						// if we were previously at the right-most node in
						// the tree, nodePtr = nullptr, and the iterator specifies
						// the end of the list
						_nodePtr = p;
					}
				}
				return *this;
			}

			// postincrement
			AVLTreeIterator operator++(int) {
				AVLTreeIterator tmp = *this;
				operator++();
				return tmp;
			}


			// postdecrement
			AVLTreeIterator operator--(int) {
				AVLTreeIterator tmp = *this;
				operator--();
				return tmp;
			}

			friend bool operator==(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs) {
				if (!lhs._nodePtr && !rhs._nodePtr)
					return true;
				return lhs._nodePtr->_value == rhs._nodePtr->_value;
			}

			friend bool operator!=(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs) {
				return !(lhs == rhs);
			}

		private:

			/*
				-> nodePtr is the current location in the tree. we can move
			freely about the tree using left, right, and parent.
				-> tree is the address of the stree object associated
			with this iterator. it is used only to access the
			root pointer, which is needed for ++ and --
			when the iterator value is end.
			 */
			Node *_nodePtr;
			const AVLTree *_tree;

			AVLTreeIterator(Node *p, const AVLTree *t) : _nodePtr(p), _tree(t) {}
		};


	public:

		typedef T value_type;
		typedef typename T::first_type first_type;
		typedef typename T::second_type second_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		// typedef Compare key_compare;
		typedef value_type &reference;
		typedef T *pointer;

		typedef AVLTreeIterator iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		/**
		 * Constructor and Destructor.
		 */
		AVLTree() : _root(NULL) {}

		~AVLTree() {}


		/**
		 * Insert x into the tree; duplicates are ignored.
		 */

		void insert(const T &value) {
			Node *newNode = new Node(value);
			_root = _insert(this->_root, newNode, value);
		}

		/*
  		 *	search for item. if found, return an iterator pointing
   		 *	at it in the tree; otherwise, return end()
		*/
		iterator find(const value_type &value) const {
			Node *current = _root;
			while(current != NULL) {
				if(value > current->_value)
					current = current->_rightChild;
				else if(value < current->_value)
					current = current->_leftChild;
				else
					break;
			}
			return current != NULL;
		}

		/*
		 * returns true if found otherwise false
		 */

		bool contains(const value_type &x) const _NOEXCEPT {

		}

		/* Test if the tree is logically empty.
		* Return true if empty, false otherwise.
		*/
		bool isEmpty() const { return this->_root == NULL; }

		/*
 		* Make the tree logically empty.
 		*/
		void makeEmpty() {}

		/**
		 * Remove x from the tree. Nothing is done if x is not found.
		 */
		void remove(const value_type &x) {}

		/**
		 * return an iterator pointing to the first item (inorder)
 		*/
		iterator inline begin() const _NOEXCEPT {
			return iterator(min(), this);
		}


		/**
		 * return an iterator pointing just past the end of
		 * the tree data
		 */

		iterator inline end() const _NOEXCEPT {
			return iterator(NULL, this);
		}

	private:

		Node *_insert(Node *root, Node *newNode, const T &value, Node *parent = NULL) {
			if(!root) {
				newNode->_parent = parent;
				return newNode;
			}

			if(value > root->_value)
				root->_rightChild = _insert(root->_rightChild, newNode, value, root);
			else
				root->_leftChild = _insert(root->_leftChild, newNode, value, root);

			root->_height = 1 + std::max(_getHeight(root->_leftChild), _getHeight(root->_rightChild));

			return _balanceTree(root);
		}

		/**************************/
		/* BST Traversal Methods */
		/**************************/

		void preOrderTraversal() const _NOEXCEPT {
			_preOrderTraversal(_root);
			std::cout << std::endl;
		}

		void inOrderTraversal() const _NOEXCEPT {
			_inOrderTraversal(_root);
			std::cout << std::endl;
		}

		void postOrderTraversal() const _NOEXCEPT {
			_postOrderTraversal(_root);
			std::cout << std::endl;
		}

		/*
		void traverseLevelOrder() {
			int treeHeight = height();
			for(int i = 0; i <= treeHeight; ++i)
				getNodesAtDistance(i);
		}
*/
		/**************************/
		/* BST Depth and Height */
		/**************************/

		int height() const _NOEXCEPT {
			if(_root == NULL)
				return -1;
			return _height(_root);
		}

		Node *min() const {
			return _min(_root);
		}

		Node *max() const {
			return _max(_root);
		}

		bool equals(const AVLTree &other) {
			return _equals(_root, other._root);
		}

		/*
		void getNodesAtDistance(int k) {
			if(!_root)
				throw std::logic_error("root node is null");
			ft::vector<T> nodes;
			_getNodesAtDistance(_root, k, nodes);

			for(typename ft::vector<T>::size_type i = 0; i < nodes.size(); ++i)
				std::cout << nodes[i] << ' ';
			std::cout << std::endl;
		}
*/

		/*
		 * Private Member Variables
		 */

	private:
		Node *_root;

		/*
		 * Private Member Functions
		 */

	private:

		Node *_balanceTree(Node *root) {
			int balanceFactor = _getBalanceFactor(root);

			if(_isLeftHeavy(balanceFactor)) {
				if(_getBalanceFactor(root->_leftChild) < 0)
					root->_leftChild = _leftRotate(root);
				return _rightRotate(root);
			} else if(_isRightHeavy(balanceFactor)) {
				if(_getBalanceFactor(root->_rightChild) > 0)
					root->_rightChild = _rightRotate(root);
				return _leftRotate(root);
			}
			return root;
		}

		Node *_leftRotate(Node *root) {
			Node *newRoot = root->_rightChild;
			root->_rightChild = newRoot->_leftChild;
			newRoot->_leftChild = root;
			_resetHeight(root, newRoot);
			_resetParent(root, newRoot);
			return newRoot;
		}


		Node *_rightRotate(Node *root) {
			Node *newRoot = root->_leftChild;
			root->_leftChild = newRoot->_rightChild;
			newRoot->_rightChild = root;
			_resetHeight(root, newRoot);
			_resetParent(root, newRoot);
			return newRoot;
		}

		void _resetParent(Node *root, Node *newRoot) const {
			root->_parent = newRoot;
			newRoot->_parent = NULL;
		}

		void _resetHeight(Node *root, Node *newRoot) {
			root->_height = 1 + std::max(_getHeight(root->_leftChild), _getHeight(root->_rightChild));
			newRoot->_height = 1 + std::max(_getHeight(newRoot->_leftChild), _getHeight(newRoot->_rightChild));
		}

		bool _isRightHeavy(int balanceFactor) const { return balanceFactor < -1; }

		bool _isLeftHeavy(int balanceFactor) const { return balanceFactor > 1; }

		int _getBalanceFactor(Node *root) { return _getHeight(root->_leftChild) - _getHeight(root->_rightChild); }

		int _getHeight(Node *node) {
			if(!node) return -1;
			return node->_height;
		}

		void _preOrderTraversal(Node *root) const _NOEXCEPT {
			if(root == NULL)
				return;

			std::cout << root->_value << ' ';
			_preOrderTraversal(root->_leftChild);
			_preOrderTraversal(root->_rightChild);
		}

		void _inOrderTraversal(Node *root) const _NOEXCEPT {
			if(root == NULL)
				return;

			_inOrderTraversal(root->_leftChild);
			std::cout << root->_value << ' ';
			_inOrderTraversal(root->_rightChild);
		}

		void _postOrderTraversal(Node *root) const _NOEXCEPT {
			if(root == NULL)
				return;

			_postOrderTraversal(root->_leftChild);
			_postOrderTraversal(root->_rightChild);
			std::cout << root->_value << ' ';
		}

		std::size_t _height(Node *root) const _NOEXCEPT {
			if(_isLeaf(root))
				return 0;

			return 1 + std::max(_height(root->_leftChild), _height(root->_rightChild));
		}

		bool _isLeaf(const Node *root) const { return root->_leftChild == NULL && root->_rightChild == NULL; }

		Node *_min(Node *root) const { // O(Log(n)) time complexity.
			if(!_root)
				throw std::logic_error("root node is null");
			Node *current = _root;
			Node *minNode = _root;
			while(current != NULL) {
				minNode = current;
				current = current->_leftChild;
			}
			return minNode;
		}

		Node *_max(Node *root) const { // O(Log(n)) time complexity.
			if(!_root)
				throw std::logic_error("root node is null");
			Node *current = _root;
			Node *maxNode = _root;
			while(current != NULL) {
				maxNode = current;
				current = current->_rightChild;
			}
			return maxNode;
		}

		bool _equals(Node *root, Node *other) {
			if(root == NULL && other == NULL)
				return true;

			if(root != NULL && other != NULL)
				return (root->_value == other->_value
						&& _equals(root->_leftChild, other->_leftChild)
						&& _equals(root->_rightChild, other->_rightChild));
			return false;
		}

		/*
		void _getNodesAtDistance(Node *root, int k, ft::vector<T> &nodes) {
			if(k == 0) {
				nodes.push_back(root->_value);
				return;
			}
			_getNodesAtDistance(root->_leftChild, k - 1, nodes);
			_getNodesAtDistance(root->_rightChild, k - 1, nodes);
		}
*/
	};

}

#endif // __AVL_HPP__



// std::__1::pair<const int, std::__1::basic_string<char> > *
// std::__1::pair<int, std::__1::basic_string<char> > *