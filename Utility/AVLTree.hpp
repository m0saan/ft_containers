//
// Created by moboustt on 21/8/2021.
//

#ifndef __AVL_HPP__
#define __AVL_HPP__

#include "bst.hpp"
#include "iterator.hpp"

namespace ft {

	template<typename T>
	class AVLTree {

	private:

		class AVLTreeIterator : public ft::iterator<std::bidirectional_iterator_tag, T> {

		public:

			typedef typename T::Key key_type;
			typedef typename T::mapped_type mapped_type;
			typedef std::pair<const key_type, mapped_type> value_type;

			friend class AVLTree;


			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			//typedef typename AVLTree<T>::Compare key_compare;
			typedef value_type &reference;
			typedef const value_type &const_reference;
			typedef T *pointer;
			typedef const pointer const_pointer;
			typedef AVLTreeIterator const_iterator;
			typedef const_iterator iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename BST<value_type>::Node Node;


			explicit AVLTreeIterator(pointer _t = NULL) : _base(_t) {}

			AVLTreeIterator(const AVLTreeIterator &other) {
				*this = other;
			}

			AVLTreeIterator &operator=(const AVLTreeIterator &other) {
				if(this != &other) { _base = other._base; }
				return *this;
			}

			reference operator*() const _NOEXCEPT {
				return *_base;
			}

			pointer operator->() const _NOEXCEPT {
				return &(*_base);
			}

			AVLTreeIterator &operator++() _NOEXCEPT {
				// _ptr++;
				return *this;
			}

			AVLTreeIterator &operator--() {
				// _ptr--;
				return *this;
			}

			// postincrement
			AVLTreeIterator operator++(int) {

			}


			// postdecrement
			AVLTreeIterator operator--(int) {

			}

			friend bool operator==(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs);

			friend bool operator!=(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs);

		private:

			const Node *_nodePtr;
			const AVLTree *_tree;
		};


	public:

		typedef T value_type;
		typedef typename T::first_type first_type;
		typedef typename T::second_type second_type;
		typedef typename BST<value_type>::Node Node;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		// typedef Compare key_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;

		typedef AVLTreeIterator const_iterator;
		typedef const_iterator iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		/**
		 * Constructor and Destructor.
		 */
		AVLTree() {}

		~AVLTree() {}


		/**
		 * Insert x into the tree; duplicates are ignored.
		 */

		void insert(const T &value) {
			Node *newNode = new Node(value);
			_root = _insert(this->_root, newNode, value);
			_last = newNode;
		}

		/*
  		 *	search for item. if found, return an iterator pointing
   		 *	at it in the tree; otherwise, return end()
		*/
		const_iterator find(const value_type &value) const {
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
		 * Find the smallest item in the tree
		 *
		*/
		reference findMin() const _NOEXCEPT {

		}

		/*
		 * Find the greatest item in the tree
		*/

		reference findMax() const _NOEXCEPT {

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
		void makeEmpty();


		/**
		 * Remove x from the tree. Nothing is done if x is not found.
		 */
		void remove(const value_type &x);

		/**
		 * return an iterator pointing to the first item (inorder)
 		*/
		const_iterator begin() const _NOEXCEPT {
			return iterator(this->_root);
		}

		/**
		 * return an iterator pointing just past the end of
		 * the tree data
		 */

		iterator end() const _NOEXCEPT {
			return iterator(_last + 1);
		}

	private:

		Node *_insert(Node *root, Node *newNode, const T &value) {
			if(!root)
				return newNode;

			if(value > root->_value)
				root->_rightChild = _insert(root->_rightChild, newNode, value);
			else
				root->_leftChild = _insert(root->_leftChild, newNode, value);

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

		void traverseLevelOrder() {
			int treeHeight = height();
			for(int i = 0; i <= treeHeight; ++i)
				getNodesAtDistance(i);
		}

		/**************************/
		/* BST Depth and Height */
		/**************************/

		int height() const _NOEXCEPT {
			if(_root == NULL)
				return -1;
			return _height(_root);
		}

		value_type min() const {
			if(_root == NULL)
				throw std::logic_error("root node is null");
			return _min(_root);
		}

		bool equals(const BST<T> &other) {
			return _equals(_root, other._root);
		}

		void getNodesAtDistance(int k) {
			if(!_root)
				throw std::logic_error("root node is null");
			ft::vector<T> nodes;
			_getNodesAtDistance(_root, k, nodes);

			for(typename ft::vector<T>::size_type i = 0; i < nodes.size(); ++i)
				std::cout << nodes[i] << ' ';
			std::cout << std::endl;
		}


		/*
		 * Private Member Variables
		 */

	private:
		Node *_root;
		Node *_last;

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
			} else if(_isRightHeavy(balanceFactor))
				if(_getBalanceFactor(root->_rightChild) > 0)
					root->_rightChild = root = _rightRotate(root);
			return _leftRotate(root);
		}

		Node *_leftRotate(Node *root) {
			Node *newRoot = root->_rightChild;
			root->_rightChild = newRoot->_leftChild;
			newRoot->_leftChild = root;
			_resetHeight(root, newRoot);
			return newRoot;
		}


		Node *_rightRotate(Node *root) {
			Node *newRoot = root->_leftChild;
			root->_leftChild = newRoot->_rightChild;
			newRoot->_rightChild = root;
			_resetHeight(root, newRoot);
			return newRoot;
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

		value_type _min(Node *root) const {
			if(_isLeaf(root))
				return root->_value;

			value_type leftMin = _min(root->_leftChild);
			value_type rightMin = _min(root->_rightChild);

			return std::min(std::min(leftMin, rightMin), root->_value);
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

		void _getNodesAtDistance(Node *root, int k, ft::vector<T> &nodes) {
			if(k == 0) {
				nodes.push_back(root->_value);
				return;
			}
			_getNodesAtDistance(root->_leftChild, k - 1, nodes);
			_getNodesAtDistance(root->_rightChild, k - 1, nodes);
		}

	};

	template<typename T>
	bool operator==(const typename AVLTree<T>::AVLTreeIterator &lhs, const typename AVLTree<T>::AVLTreeIterator &rhs) {
		return lhs.equals(rhs);
	}

	template<typename T>
	bool operator!=(const typename AVLTree<T>::AVLTreeIterator &lhs, const typename AVLTree<T>::AVLTreeIterator &rhs) {
		return !(lhs.equals(rhs));
	}

}

#endif // __AVL_HPP__
