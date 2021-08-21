//
// Created by moboustt on 21/8/2021.
//

#ifndef __AVL_HPP__
#define __AVL_HPP__

#include "bst.hpp"

namespace ft {

	template<typename T>
	class AVL : public BST<T> {
	public:

		typedef typename BST<T>::Node Node;

		AVL() {}

		~AVL() {}

		void insert(const T &value) {
			Node *newNode = new Node(value);
			this->_root = _insert(this->_root, newNode, value);
		}

	private:

		Node *_insert(Node *root, Node *newNode, const T &value) {
			if(!root)
				return newNode;

			if (value > root->_value)
				root->_rightChild = _insert(root->_rightChild, newNode, value);
			else
				root->_leftChild = _insert(root->_leftChild, newNode, value);

			root->_height = 1 + std::max(getHeight(root->_leftChild), getHeight(root->_rightChild));

			return balanceTree(root);;
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

			return root;
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

	};
}

#endif // __AVL_HPP__
