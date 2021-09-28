//
// Created by moboustt on 21/8/2021.
//

#ifndef __AVL_HPP__
#define __AVL_HPP__


/**
 * 
 * Utility includes 
 * 
 */

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "choose.hpp"
#include "pair.hpp"

#include <memory>
#include <map>

namespace ft {

    template
            <
                    typename Node, 
                    typename T,
                    typename Compare,
                    typename Alloc,
                    typename Tree
            >
    class AVLTreeIterator : public ft::iterator<std::bidirectional_iterator_tag, T> {

    public:

        typedef T value_type;
        typedef typename T::first_type key_type;
        typedef typename T::second_type mapped_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        // typedef Node<T> Node;
        // typedef AVLTree<T, Compare, Alloc> AVLTree;

        typedef T &reference;
        typedef T *pointer;

        AVLTreeIterator(Node *p, Tree *t) : _nodePtr(p), _tree(t) {}

        AVLTreeIterator(const AVLTreeIterator &other) { *this = other; }

        operator AVLTreeIterator<Node, const T, Compare, Alloc, Tree>() {
            return AVLTreeIterator<Node, const T, Compare, Alloc, Tree>(_nodePtr, _tree);
        }

        AVLTreeIterator &operator=(const AVLTreeIterator &other) {
            if (this != &other) {
                _nodePtr = other._nodePtr;
                _tree = other._tree;
            }
            return *this;
        }

        reference operator*() const {
            return _nodePtr->_value;
        }

        pointer operator->() const {
            return (&this->_nodePtr->_value);
        }

        AVLTreeIterator &operator++() {

            Node *p;

            if (_nodePtr == NULL) {

                // ++ from end(). get the root of the tree
                _nodePtr = _tree->_root;

                // error! ++ requested for an empty tree
                if (_nodePtr == NULL)
                    throw std::logic_error("Underflow Exception.");

                // move to the smallest value in the tree,
                // which is the first node inorder
                while (_nodePtr->_leftChild != NULL) {
                    _nodePtr = _nodePtr->_leftChild;
                }
            } else {
                if (_nodePtr->_rightChild) {

                    /*	next Node is the farthest left node of
                     *	right subtree
                     */
                    _nodePtr = _nodePtr->_rightChild;
                    while (_nodePtr->_leftChild != NULL)
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
                    while (p != NULL && _nodePtr == p->_rightChild) {
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
            if (_nodePtr == NULL) {

                // -- from end(). get the root of the tree
                _nodePtr = _tree->max()->_parent;

                // error! ++ requested for an empty tree
                if (_nodePtr == NULL)
                    throw std::logic_error("Underflow Exception.");

                // move to the farthest value in the tree,
                // which is the last node inorder
                while (_nodePtr->_rightChild != NULL) {
                    _nodePtr = _nodePtr->_rightChild;
                }
            } else {
                if (_nodePtr->_leftChild) {

                    /*	next Node is the farthest left node of
                     *	right subtree
                     */
                    _nodePtr = _nodePtr->_leftChild;
                    while (!_nodePtr)
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
                    while (p != NULL && _nodePtr == p->_leftChild) {
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
            AVLTreeIterator tmp(*this);
            ++(*this);
            return tmp;
        }


        // postdecrement
        AVLTreeIterator operator--(int) {
            AVLTreeIterator tmp(*this);
            --(*this);
            return tmp;
        }

        friend bool operator==(const AVLTreeIterator &lhs, const AVLTreeIterator &rhs) {
            if (!lhs._nodePtr && !rhs._nodePtr)
                return true;
            return (!lhs._nodePtr && !rhs._nodePtr) && (lhs._nodePtr->_value == rhs._nodePtr->_value);
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
        Tree *_tree;
        Compare _comp;
    };


    template<
            typename T,
            typename Compare = std::less<typename T::first_type>,
            typename Alloc = std::allocator<ft::pair<const typename T::first_type, typename T::second_type> >
    >
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

    public:
        typedef T value_type;
        typedef typename T::first_type first_type;
        typedef typename T::second_type second_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        // typedef Node Node;
        typedef value_type &reference;
        typedef T *pointer;

        typedef AVLTreeIterator<Node, T, Compare, Alloc, AVLTree> iterator;
        typedef AVLTreeIterator<Node, const T, Compare, Alloc, AVLTree> const_iterator;

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        friend class AVLTreeIterator<Node, T, Compare, Alloc, AVLTree>;

        /**
         * Constructor and Destructor.
         */
        AVLTree() : _root(NULL), _size(0) {}

        ~AVLTree() {}


        /**
         * Insert x into the tree; duplicates are ignored.
         */

        ft::pair<iterator, bool> insert(const T &value) {
            Node *newNode = new Node(value);
            bool isInserted(false);
            Node *out = _insert(this->_root, newNode, value, isInserted);
            if (isInserted) {
                _root = out;
                ++_size;
                return ft::make_pair(iterator(newNode, this), true);
            }
            return ft::make_pair(iterator(NULL, this), false);
        }

        /*
           *	search for item. if found, return an iterator pointing
            *	at it in the tree; otherwise, return end()
        */
        bool findByKey(const value_type &value) const {
            Node *current = _root;
            while (current != NULL) {
                if (value.first > current->_value.first)
                    current = current->_rightChild;
                else if (value.first < current->_value.first)
                    current = current->_leftChild;
                else
                    return true;
            }
            return false;
        }

        Node *find(const value_type &value) const {
            Node *current = _root;
            while (current != NULL) {
                if (!_comp(value.first, current->_value.first) && !_comp(current->_value.first, value.first))
                    return current;
                if (!_comp(value.first, current->_value.first))
                    current = current->_rightChild;
                else
                    current = current->_leftChild;
            }
            return NULL;
        }

        /*
         * returns true if found otherwise false
         */

        bool contains(const value_type &x) const _NOEXCEPT {

        }

        std::size_t size() const _NOEXCEPT {
            return _size;
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
        void remove(const value_type &x) {
            /*
             * 1. Find the element we wish to remove
             * 2. Replace the node we want to remove with its successor if any
             *      to maintain the bst invariant.
             */

            /*
             * There are Four main cases concerning removing a node.
             *  -> Case 1: Node to remove is a leaf Node.
             *  -> Case 2: Node to remove has a left but no right subtree.
             *  -> Case 3: Node to remove has a right but no left subtree.
             *  -> Case 4: Node to remove has both left and right subtree.
             */

            // Case 1
            Node *nodeToRemove = find(x);
            if (nodeToRemove != NULL) {
                --_size;
                if (_isLeaf(nodeToRemove)) {
                    if (nodeToRemove->_parent) {
                        if (nodeToRemove->_parent->_leftChild->_value == x)
                            nodeToRemove->_parent->_leftChild = NULL;
                        else
                            nodeToRemove->_parent->_leftChild = NULL;
                    }
                    nodeToRemove->_parent = NULL;
                    delete nodeToRemove;
                    nodeToRemove = NULL;
                }
            }
        }


        /**
         * return an iterator pointing to the first item (inorder)
         */
        iterator begin() {
            return iterator(min(), this);
        }

        const_iterator begin() const {
            return const_iterator(min(), this);
        }


        /**
         * return an iterator pointing just past the end of
         * the tree data
         */

        iterator end() {
            return iterator(NULL, this);
        }

        const_iterator end() const {
            return const_iterator(NULL, this);
        }


        /**
         * Relational Operators
         *
         */

        friend bool operator==(const AVLTree &lhs, const AVLTree &rhs) {
            return lhs.equals(rhs);
        }

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

    private:

        Node *_insert(Node *cur_node, Node *newNode, const T &value, bool &isInserted, Node *parent = NULL) {
            if (!cur_node) {
                newNode->_parent = parent;
                isInserted = true;
                return newNode;
            }

            //
            if (!_comp(value.first, cur_node->_value.first) && !_comp(cur_node->_value.first, value.first))
                return cur_node;
            if (!_comp(value.first, cur_node->_value.first))
                cur_node->_rightChild = _insert(cur_node->_rightChild, newNode, value, isInserted, cur_node);
            else
                cur_node->_leftChild = _insert(cur_node->_leftChild, newNode, value, isInserted, cur_node);
            cur_node->_height = 1 + std::max(_getHeight(cur_node->_leftChild), _getHeight(cur_node->_rightChild));

            return _balanceTree(cur_node);
        }

        /**************************/
        /* BST Traversal Methods */
        /**************************/

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
            if (_root == NULL)
                return -1;
            return _height(_root);
        }

        Node *min() {
            return _min(_root);
        }

        Node *max() {
            return _max(_root);
        }

        bool equals(const AVLTree &other) const {
            return _equals(_root, other._root);
        }

        /*
        void getNodesAtDistance(int k) {
            if(!_root)
                throw std::logic_error("root node is null");
            ft::Vector<T> nodes;
            _getNodesAtDistance(_root, k, nodes);

            for(typename ft::Vector<T>::size_type i = 0; i < nodes.size(); ++i)
                std::cout << nodes[i] << ' ';
            std::cout << std::endl;
        }
*/

        /*
         * Private Member Variables
         */

    private:
        Node *_root;
        std::size_t _size;
        Compare _comp;

        /*
         * Private Member Functions
         */

    private:

        Node *_balanceTree(Node *root) {
            int balanceFactor = _getBalanceFactor(root);

            if (_isLeftHeavy(balanceFactor)) {
                if (_getBalanceFactor(root->_leftChild) < 0)
                    root->_leftChild = _leftRotate(root->_leftChild);
                return _rightRotate(root);
            } else if (_isRightHeavy(balanceFactor)) {
                if (_getBalanceFactor(root->_rightChild) > 0)
                    root->_rightChild = _rightRotate(root->_rightChild);
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
            if (!root->_parent) {
                newRoot->_parent = NULL;
                root->_parent = newRoot;
                return;
            }
            newRoot->_parent = root->_parent;
            root->_parent = newRoot;
        }

        void _resetHeight(Node *root, Node *newRoot) {
            root->_height = 1 + std::max(_getHeight(root->_leftChild), _getHeight(root->_rightChild));
            newRoot->_height = 1 + std::max(_getHeight(newRoot->_leftChild), _getHeight(newRoot->_rightChild));
        }

        bool _isRightHeavy(int balanceFactor) const { return balanceFactor < -1; }

        bool _isLeftHeavy(int balanceFactor) const { return balanceFactor > 1; }

        int _getBalanceFactor(Node *root) { return _getHeight(root->_leftChild) - _getHeight(root->_rightChild); }

        int _getHeight(Node *node) {
            if (!node) return -1;
            return node->_height;
        }

        void _preOrderTraversal(Node *root) const _NOEXCEPT {
            if (root == NULL)
                return;

            std::cout << root->_value << ' ';
            _preOrderTraversal(root->_leftChild);
            _preOrderTraversal(root->_rightChild);
        }

        void _inOrderTraversal(Node *root) const _NOEXCEPT {
            if (root == NULL)
                return;

            _inOrderTraversal(root->_leftChild);
            std::cout << root->_value.first << ' ' << root->_value.second << std::endl;
            _inOrderTraversal(root->_rightChild);
        }

        void _postOrderTraversal(Node *root) const _NOEXCEPT {
            if (root == NULL)
                return;

            _postOrderTraversal(root->_leftChild);
            _postOrderTraversal(root->_rightChild);
            std::cout << root->_value << ' ';
        }

        std::size_t _height(Node *root) const _NOEXCEPT {
            if (_isLeaf(root))
                return 0;

            return 1 + std::max(_height(root->_leftChild), _height(root->_rightChild));
        }

        bool _isLeaf(const Node *root) const { return root->_leftChild == NULL && root->_rightChild == NULL; }

        Node *_min(Node *root) { // O(Log(n)) time complexity.
            if (!_root)
                throw std::logic_error("root node is null");
            Node *current = _root;
            Node *minNode = _root;
            while (current != NULL) {
                minNode = current;
                current = current->_leftChild;
            }
            return minNode;
        }

        Node *_max(Node *root) { // O(Log(n)) time complexity.
            if (!_root)
                throw std::logic_error("root node is null");
            Node *current = _root;
            Node *maxNode = _root;
            while (current != NULL) {
                maxNode = current;
                current = current->_rightChild;
            }
            return maxNode;
        }

        bool _equals(Node *root, Node *other) const {
            if (root == NULL && other == NULL)
                return true;

            if (root != NULL && other != NULL)
                return (root->_value == other->_value
                        && _equals(root->_leftChild, other->_leftChild)
                        && _equals(root->_rightChild, other->_rightChild));
            return false;
        }
    };

}

#endif // __AVL_HPP__

