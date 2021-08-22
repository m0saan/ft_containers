//
// Created by moboustt on 21/8/2021.
//

#ifndef __AVL_HPP__
#define __AVL_HPP__

#include "bst.hpp"
#include "iterator.hpp"

namespace ft {

	template<typename AVL>
	class AVLTreeIterator : public ft::iterator<std::bidirectional_iterator_tag, typename AVL::value_type> {

	public:

		typedef typename AVL::Key key_type;
		typedef typename AVL::mapped_type mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename AVL::Compare key_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename AVL::pointer pointer;
		typedef typename AVL::const_pointer const_pointer;
		typedef AVLTreeIterator<value_type> iterator;
		typedef AVLTreeIterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


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
		AVLTreeIterator operator++ (int) {

		}


		// postdecrement
		AVLTreeIterator  operator-- (int) {

		}

		friend bool operator==(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs);

		friend bool operator!=(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs);

	private:
		pointer _base;
	};

	template<typename AVL>
	bool operator==(const AVLTreeIterator<AVL> &lhs, const AVLTreeIterator<AVL> &rhs) {
		return lhs.equals(rhs);
	}

	template<typename AVL>
	bool operator!=(const AVLTreeIterator<AVL> &lhs, const AVLTreeIterator<AVL> &rhs) {
		return !(lhs.equals(rhs));
	}


	template<typename T, typename Compare>
	class AVL : public BST<T> {
	public:

		typedef T value_type;
		typedef typename T::first_type first_type;
		typedef typename T::second_type second_type;
		typedef typename BST<value_type>::Node Node;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;

		typedef AVLTreeIterator<value_type> const_iterator;
		typedef const_iterator iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		/**
		 * Constructor and Destructor.
		 */
		AVL() {}

		~AVL() {}


		/**
		 * Insert x into the tree; duplicates are ignored.
		 */

		void insert(const T &value) {
			Node *newNode = new Node(value);
			this->_root = _insert(this->_root, newNode, value);
			_last = newNode;
		}

		/*
  		 *	search for item. if found, return an iterator pointing
   		 *	at it in the tree; otherwise, return end()
		*/
		const_iterator find(const value_type &item) const {

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

			root->_height = 1 + std::max(getHeight(root->_leftChild), getHeight(root->_rightChild));

			return balanceTree(root);
		}

		Node *balanceTree(Node *root) {
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
			root->_height = 1 + std::max(getHeight(root->_leftChild), getHeight(root->_rightChild));
			newRoot->_height = 1 + std::max(getHeight(newRoot->_leftChild), getHeight(newRoot->_rightChild));
		}

		bool _isRightHeavy(int balanceFactor) const { return balanceFactor < -1; }

		bool _isLeftHeavy(int balanceFactor) const { return balanceFactor > 1; }

		int _getBalanceFactor(Node *root) { return getHeight(root->_leftChild) - getHeight(root->_rightChild); }

		int getHeight(Node *node) {
			if(!node) return -1;
			return node->_height;
		}

	private:
		Node *_last;

	};
}

#endif // __AVL_HPP__
