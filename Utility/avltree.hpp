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

namespace ft
{

    template <
        typename Node,
        typename T,
        typename Compare,
        typename Alloc,
        typename Tree>
    class Iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
    {

    public:
        typedef T value_type;
        typedef std::bidirectional_iterator_tag iterator_type;
        typedef typename T::first_type key_type;
        typedef typename T::second_type mapped_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef T &reference;
        typedef T *pointer;

        Iterator() : _nodePtr(), _tree() {}

        Iterator(Node *p, Tree *t) : _nodePtr(p), _tree(t) {}

        Iterator(const Iterator &other) { *this = other; }

        operator Iterator<Node, const T, Compare, Alloc, Tree>()
        {
            return Iterator<Node, const T, Compare, Alloc, Tree>(_nodePtr, _tree);
        }

        Iterator &operator=(const Iterator &other)
        {
            if (this != &other)
            {
                _nodePtr = other._nodePtr;
                _tree = other._tree;
            }
            return *this;
        }

        reference operator*() const
        {
            return *_nodePtr->_value;
        }

        pointer operator->() const
        {
            return (&this->_nodePtr->_value);
        }

        Iterator &operator++()
        {

            Node *p;

            if (_nodePtr == NULL)
            {

                // ++ from end(). get the root of the tree
                _nodePtr = _tree->_root;

                // error! ++ requested for an empty tree
                if (_nodePtr == NULL)
                    throw std::logic_error("Underflow Exception.");

                // move to the smallest value in the tree,
                // which is the first node inorder
                while (_nodePtr->_leftChild != NULL)
                {
                    _nodePtr = _nodePtr->_leftChild;
                }
            }
            else
            {
                if (_nodePtr->_rightChild)
                {

                    /*	next Node is the farthest left node of
                     *	right subtree
                     */
                    _nodePtr = _nodePtr->_rightChild;
                    while (_nodePtr->_leftChild != NULL)
                        _nodePtr = _nodePtr->_leftChild;
                }
                else
                {
                    // have already processed the left subtree, and
                    // there is no right subtree. move up the tree,
                    // looking for a parent for which nodePtr is a left child,
                    // stopping if the parent becomes NULL. a non-NULL parent
                    // is the successor. if parent is NULL, the original node
                    // was the last node inorder, and its successor
                    // is the end of the list
                    p = _nodePtr->_parent;
                    while (p != NULL && _nodePtr == p->_rightChild)
                    {
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

        Iterator &operator--()
        {
            Node *p;
            if (_nodePtr == NULL)
            {

                // -- from end(). get the root of the tree
                _nodePtr = _tree->max()->_parent;

                // error! ++ requested for an empty tree
                if (_nodePtr == NULL)
                    throw std::logic_error("Underflow Exception.");

                // move to the farthest value in the tree,
                // which is the last node inorder
                while (_nodePtr->_rightChild != NULL)
                {
                    _nodePtr = _nodePtr->_rightChild;
                }
            }
            else
            {
                if (_nodePtr->_leftChild)
                {

                    /*	next Node is the farthest left node of
                     *	right subtree
                     */
                    _nodePtr = _nodePtr->_leftChild;
                    while (_nodePtr->_rightChild != NULL)
                        _nodePtr = _nodePtr->_rightChild;
                }
                else
                {
                    // have already processed the left subtree, and
                    // there is no right subtree. move up the tree,
                    // looking for a parent for which nodePtr is a left child,
                    // stopping if the parent becomes NULL. a non-NULL parent
                    // is the successor. if parent is NULL, the original node
                    // was the last node inorder, and its successor
                    // is the end of the list
                    p = _nodePtr->_parent;
                    while (p != NULL && _nodePtr == p->_leftChild)
                    {
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
        Iterator operator++(int)
        {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        // postdecrement
        Iterator operator--(int)
        {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            if (!lhs._nodePtr && !rhs._nodePtr)
                return true;
            return (!lhs._nodePtr && !rhs._nodePtr) && (lhs._nodePtr->_value == rhs._nodePtr->_value);
        }

        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
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

    template <
        typename T,
        typename Compare = std::less<typename T::first_type>,
        typename Alloc = std::allocator<T> >
    class avltree
    {

    private:
        class Node
        {
        public:
            T *_value;
            Node *_leftChild, *_rightChild, *_parent;
            std::size_t _height;
        };

    public:
        typedef T value_type;
        typedef typename T::first_type first_type;
        typedef typename T::second_type second_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef T *pointer;

        typedef Iterator<Node, T, Compare, Alloc, avltree> iterator;
        typedef Iterator<Node, const T, Compare, Alloc, avltree> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        friend class Iterator<Node, T, Compare, Alloc, avltree>;

        Node *_createNode(value_type value)
        {
            Node *newNode;
            newNode = _node_alloc.allocate(1);
            newNode->_value = _alloc.allocate(1);
            newNode->_leftChild = newNode->_rightChild = newNode->_parent = NULL;
            newNode->_height = 0;
            _alloc.construct(newNode->_value, value);
            return newNode;
        }

        void _deleteNode(Node *node)
        {
            _alloc.destroy(node->_value);
            _alloc.deallocate(node->_value, 1);
            _node_alloc.deallocate(node, 1);
            node = NULL;
        }

        /**
         * Constructor and Destructor.
         */
        avltree() : _root(NULL), _size(0), _comp(), _alloc() {}

        ~avltree() {}

        avltree getRoot() const { return _root; }

        /**
         * Insert x into the tree; duplicates are ignored.
         */

        ft::pair<iterator, bool> insert(const T &value)
        {
            Node *newNode(_createNode(value));
            bool isInserted(false);
            Node *out = _insert(this->_root, newNode, value, isInserted);
            if (isInserted)
            {
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
        bool findByKey(const value_type &value) const
        {
            Node *current = _root;
            while (current != NULL)
            {
                if (value.first > current->_value->first)
                    current = current->_rightChild;
                else if (value.first < current->_value->first)
                    current = current->_leftChild;
                else
                    return true;
            }
            return false;
        }

        Node *find(const value_type &value) const
        {
            Node *current = _root;
            while (current != NULL)
            {
                if (!_comp(value.first, current->_value->first) && !_comp(current->_value->first, value.first))
                    return current;
                if (!_comp(value.first, current->_value->first))
                    current = current->_rightChild;
                else
                    current = current->_leftChild;
            }
            return NULL;
        }

        /*
         * returns true if found otherwise false
         */

        bool contains(const value_type &x) const _NOEXCEPT
        {
        }

        std::size_t size() const _NOEXCEPT
        {
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

        void remove(value_type const &x)
        {
            bool isRemoved(false);
            _root = _remove(_root, x, isRemoved);
            // if (isRemoved)
            //     std::cout << "removed" << std::endl;
            // else
            //     std::cout << "not in the tree (not removed)" << std::endl;
        }

        Node* _remove(Node *currNode, const value_type &x, bool &isDeleted)
        {
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

            /*
            *
                base condition. 
            *
            */

            if (!currNode)
                return currNode;



            if (!_comp(x.first, currNode->_value->first) && !_comp(currNode->_value->first, x.first))
                {
                    --_size;
                    isDeleted = true;
                    Node *successorRef;

                    // Case 1
                    if (_isLeaf(currNode))
                    {

                        /* has no left or right subtree.

                        **
                     //    \\
                     
                        */
                        if (currNode->_parent)
                        {
                            if (currNode->_parent->_leftChild && *currNode->_parent->_leftChild->_value == x)
                                currNode->_parent->_leftChild = NULL;
                            else if (currNode->_parent->_rightChild && *currNode->_parent->_rightChild->_value == x)
                                currNode->_parent->_rightChild = NULL;
                        }
                        currNode->_parent = NULL;
                        _deleteNode(currNode);
                        return NULL;
                    }
                    // Case 2
                    else if (_hasLeftOnly(currNode))
                    {

                        /* has only a left subtree.

                     **
                   //   \\
                  **     
                  
                    */

                        successorRef = currNode->_leftChild;
                        Node *currNodeParent = currNode->_parent;
                        _deleteNode(currNode);
                        currNodeParent->_leftChild = successorRef;
                        successorRef->_parent = currNodeParent;
                        return successorRef;
                    }

                    // Case 3
                    else if (_hasRightOnly(currNode))
                    {
                        /* has only a right subtree.
                     **
                   //   \\
                         **
                  
                    */

                        successorRef = currNode->_rightChild;
                        Node *currNodeParent = currNode->_parent;
                        _deleteNode(currNode);
                        currNodeParent->_rightChild = successorRef;
                        successorRef->_parent = currNodeParent;
                        return successorRef;    
                    }
                    
                    // Case 4
                    else {
                        
                        // -> Algorithm: 
                        // the successor can either be the largest value
                        // in the left subtree OR the smallest value
                        // in the right subtree.

                        // Once the successor  node has been found,
                        // replace the value of the node to remove with
                        // the value in the successor node.

                        // and remove the duplicate value of the successor node
                        // that still exists in the tree.

                        successorRef = _max(currNode->_rightChild);
                        std::swap(successorRef->_value->first, currNode->_value->first);
                        std::swap(successorRef->_value->second, currNode->_value->second);

                        currNode->_rightChild = _remove(currNode->_rightChild, *successorRef->_value, isDeleted);
                        return successorRef;

                    }

                    // RETTTT
                }

            // Finding the __x__ node which we want to remove;
            if (!_comp(x.first, currNode->_value->first))
                currNode->_rightChild = _remove(currNode->_rightChild, x, isDeleted);
            else
                currNode->_leftChild = _remove(currNode->_leftChild, x, isDeleted);

            /*
                * Update Balance Factor.
                */

            currNode->_height = 1 + std::max(_getHeight(currNode->_leftChild), _getHeight(currNode->_rightChild));

            /*
            * Rebalance tree.
            */
            return _balanceTree(currNode);
        }

        /**
         * 
         * return an iterator pointing to the first item (in-order-traversal).
         * 
         */

        iterator begin()
        {
            return iterator(min(), this);
        }

        const_iterator begin() const
        {
            return const_iterator(min(), this);
        }

        /**
         * 
         * return an iterator pointing to the last item (in-order-traversal)
         * 
         */

        reverse_iterator rbegin()
        {
            return reverse_iterator(iterator(max(), this));
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(const_iterator(max(), this));
        }

        /**
         * 
         * return an iterator pointing just past the end of the tree data
         * 
         */

        iterator end()
        {
            return iterator(NULL, this);
        }

        const_iterator end() const
        {
            return const_iterator(NULL, this);
        }

        reverse_iterator rend()
        {
            return reverse_iterator(iterator(NULL, this));
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(const_iterator(NULL, this));
        }

        /**
         * Relational Operators
         *
         */

        friend bool operator==(const avltree &lhs, const avltree &rhs)
        {
            return lhs.equals(rhs);
        }

        void preOrderTraversal() const _NOEXCEPT
        {
            _preOrderTraversal(_root);
            std::cout << std::endl;
        }

        void inOrderTraversal() const _NOEXCEPT
        {
            _inOrderTraversal(_root);
            std::cout << std::endl;
        }

        void postOrderTraversal() const _NOEXCEPT
        {
            _postOrderTraversal(_root);
            std::cout << std::endl;
        }

        Node *_root;

    private:
        bool _hasLeftOnly(Node *node)
        {
            return node->_rightChild == NULL;
        }

        bool _hasRightOnly(Node *node)
        {
            return node->_leftChild == NULL;
        }
        Node *_insert(Node *cur_node, Node *newNode, const T &value, bool &isInserted, Node *parent = NULL)
        {
            if (!cur_node)
            {
                newNode->_parent = parent;
                isInserted = true;
                return newNode;
            }

            //
            if (!_comp(value.first, cur_node->_value->first) && !_comp(cur_node->_value->first, value.first))
                return cur_node;
            if (!_comp(value.first, cur_node->_value->first))
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

        int height() const _NOEXCEPT
        {
            if (_root == NULL)
                return -1;
            return _height(_root);
        }

        Node *min()
        {
            return _min(_root);
        }

        Node *max()
        {
            return _max(_root);
        }

        bool equals(const avltree &other) const
        {
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
        std::size_t _size;
        Compare _comp;
        std::allocator<Node> _node_alloc;
        Alloc _alloc;

        /*
         * Private Member Functions
         */

    private:
        Node *_balanceTree(Node *root)
        {
            int balanceFactor = _getBalanceFactor(root);

            if (_isLeftHeavy(balanceFactor))
            {
                if (_getBalanceFactor(root->_leftChild) < 0)
                    root->_leftChild = _leftRotate(root->_leftChild);
                return _rightRotate(root);
            }
            else if (_isRightHeavy(balanceFactor))
            {
                if (_getBalanceFactor(root->_rightChild) > 0)
                    root->_rightChild = _rightRotate(root->_rightChild);
                return _leftRotate(root);
            }
            return root;
        }

        Node *_leftRotate(Node *root)
        {
            Node *newRoot = root->_rightChild;
            root->_rightChild = newRoot->_leftChild;
            newRoot->_leftChild = root;
            _resetHeight(root, newRoot);
            _resetParent(root, newRoot);
            return newRoot;
        }

        Node *_rightRotate(Node *root)
        {
            Node *newRoot = root->_leftChild;
            root->_leftChild = newRoot->_rightChild;
            newRoot->_rightChild = root;
            _resetHeight(root, newRoot);
            _resetParent(root, newRoot);
            return newRoot;
        }

        void _resetParent(Node *oldRoot, Node *newRoot) const
        {
            if (!oldRoot->_parent)
            {
                newRoot->_parent = NULL;
                if (oldRoot->_leftChild)
                    oldRoot->_leftChild->_parent = oldRoot;
                if (oldRoot->_rightChild)
                    oldRoot->_rightChild->_parent = oldRoot;
                oldRoot->_parent = newRoot;
                return;
            }
            newRoot->_parent = oldRoot->_parent;
            oldRoot->_parent = newRoot;
            if (oldRoot->_leftChild)
                oldRoot->_leftChild->_parent = oldRoot;
            if (oldRoot->_rightChild)
                oldRoot->_rightChild->_parent = oldRoot;
        }

        void _resetHeight(Node *root, Node *newRoot)
        {
            root->_height = 1 + std::max(_getHeight(root->_leftChild), _getHeight(root->_rightChild));
            newRoot->_height = 1 + std::max(_getHeight(newRoot->_leftChild), _getHeight(newRoot->_rightChild));
        }

        bool _isRightHeavy(int balanceFactor) const { return balanceFactor < -1; }

        bool _isLeftHeavy(int balanceFactor) const { return balanceFactor > 1; }

        int _getBalanceFactor(Node *root) { return _getHeight(root->_leftChild) - _getHeight(root->_rightChild); }

        int _getHeight(Node *node)
        {
            if (!node)
                return -1;
            return node->_height;
        }

        void _preOrderTraversal(Node *root) const _NOEXCEPT
        {
            if (root == NULL)
                return;

            std::cout << root->_value << ' ';
            _preOrderTraversal(root->_leftChild);
            _preOrderTraversal(root->_rightChild);
        }

        void _inOrderTraversal(Node *root) const _NOEXCEPT
        {
            if (root == NULL)
                return;

            _inOrderTraversal(root->_leftChild);
            std::cout << *root->_value;
            if (root->_parent)
                std::cout << " Parent"
                          << "[" << *root->_parent->_value << "]" << std::endl;
            else
                std::cout << " Parent"
                          << "[(null)]" << std::endl;
            _inOrderTraversal(root->_rightChild);
        }

        void _postOrderTraversal(Node *root) const _NOEXCEPT
        {
            if (root == NULL)
                return;

            _postOrderTraversal(root->_leftChild);
            _postOrderTraversal(root->_rightChild);
            std::cout << root->_value << ' ';
        }

        std::size_t _height(Node *root) const _NOEXCEPT
        {
            if (_isLeaf(root))
                return 0;

            return 1 + std::max(_height(root->_leftChild), _height(root->_rightChild));
        }

        bool _isLeaf(const Node *root) const { return root->_leftChild == NULL && root->_rightChild == NULL; }

        Node *_min(Node *root)
        { // O(Log(n)) time complexity.
            if (!_root)
                throw std::logic_error("root node is null");
            Node *current = _root;
            Node *minNode = _root;
            while (current != NULL)
            {
                minNode = current;
                current = current->_leftChild;
            }
            return minNode;
        }

        Node *_max(Node *root)
        { // O(Log(n)) time complexity.
            if (!_root)
                throw std::logic_error("root node is null");
            Node *current = _root;
            Node *maxNode = _root;
            while (current != NULL)
            {
                maxNode = current;
                current = current->_rightChild;
            }
            return maxNode;
        }

        bool _equals(Node *root, Node *other) const
        {
            if (root == NULL && other == NULL)
                return true;

            if (root != NULL && other != NULL)
                return (root->_value == other->_value && _equals(root->_leftChild, other->_leftChild) && _equals(root->_rightChild, other->_rightChild));
            return false;
        }
    };

}

#endif // __AVL_HPP__


/*

    MAP <k,v> -> 
*/