//
// Created by moboustt on 19/8/2021.
//

#ifndef __BST_HPP__
#define __BST_HPP__

namespace ft {

	template<typename T>
	class BST {

	private:

		class Node {
		public:
			explicit Node(T const &value, Node *left = NULL, Node *right = NULL)
					: _value(value), _leftChild(left), _rightChild(right) {}

			T _value;
			Node *_leftChild, *_rightChild;
		};


	public:
		BST() : _root(NULL) {}

		void insert(const T &value) {
			Node *newNode = new Node(value);
			if(_root == NULL)
				_root = newNode;
			else {
				Node *current = _root;
				while(true) {
					if(value > current->_value) {
						if(current->_rightChild == NULL) {
							current->_rightChild = newNode;
							break;
						}
						current = current->_rightChild;
					} else {
						if(current->_leftChild == NULL) {
							current->_leftChild = newNode;
							break;
						}
						current = current->_leftChild;
					}
				}
			}
		}

		bool find(const T &value) {
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

		void preOrderTraversal() {
			_preOrderTraversal(_root);
			std::cout << std::endl;
		}

		void inOrderTraversal() {
			_inOrderTraversal(_root);
			std::cout << std::endl;
		}

		void postOrderTraversal() {
			_postOrderTraversal(_root);
			std::cout << std::endl;
		}

	private: // /* Private Member Variables */

		Node *_root;

	private: // /* Private Member Functions */

		void _preOrderTraversal(Node *root) {
			if (root == NULL)
				return;

			std::cout << root->_value << ' ';
			_preOrderTraversal(root->_leftChild);
			_preOrderTraversal(root->_rightChild);
		}

		void _inOrderTraversal(Node* root) {
			if (root == NULL)
				return;

			_inOrderTraversal(root->_leftChild);
			std::cout << root->_value << ' ';
			_inOrderTraversal(root->_rightChild);
		}

		void _postOrderTraversal(Node* root) {
			if (root == NULL)
				return;

			_postOrderTraversal(root->_leftChild);
			_postOrderTraversal(root->_rightChild);
			std::cout << root->_value << ' ';
		}

	};
}

#endif // __BST_HPP__
