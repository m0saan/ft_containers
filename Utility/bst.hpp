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

		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;

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
				throw std::bad_exception();
			return _min(_root);
		}

		bool equals(const BST<T> &other) {
			return _equals(_root, other._root);
		}

	private: // /* Private Member Variables */

		Node *_root;

	private: // /* Private Member Functions */

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
			if(isLeaf(root))
				return 0;

			return 1 + std::max(_height(root->_leftChild), _height(root->_rightChild));
		}

		bool isLeaf(const Node *root) const { return root->_leftChild == NULL && root->_rightChild == NULL; }

		value_type _min(Node *root) const {
			if(isLeaf(root))
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

	};
}

#endif // __BST_HPP__
