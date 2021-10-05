//
// Created by moboustt on 19/8/2021.
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <functional>
#include "../Utility/avltree.hpp"
#include "../Utility/reverse_iterator.hpp"
#include "../Utility/enable_if.hpp"
#include "../Utility/iterator_traits.hpp"
#include "../Utility/pair.hpp"

namespace ft
{

    template <class, class, class>
    class Node;

    template <
        typename Key,
        typename T,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;
        typedef typename avltree<value_type, Compare, Alloc>::Node Node;
        typedef avltree<value_type, Compare, Alloc> avltree;
        typedef Iterator<Node, value_type, Compare, Alloc, avltree> iterator;
        typedef Iterator<Node, const value_type, Compare, Alloc, avltree> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        class value_compare
        {

            friend class map;
        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        // Member functions ************************************************************************** //

        // Constructor, Destructor , copy assignment operator.
        map() : _tree(), _size(), _compare()
        {
            _tree.init(_compare, _alloc);
        }

        explicit map(const Compare &comp, const Alloc &alloc = Alloc())
            : _tree(), _alloc(alloc), _size(), _compare(comp)
        {
            _tree.init(_compare, _alloc);
        }

        template <typename InputIt>
        map(InputIt first, InputIt last, const Compare &comp = Compare(),
            const Alloc &alloc = Alloc()) : _alloc(alloc), _compare(comp)
        {
            _tree.init(_compare, _alloc);
            for (; first != last; ++first)
                _tree.insert(*first);
            _size = _tree.size();
        }

        map(const map &other)
        {
            *this = other;
        }

        map &operator=(const map &other)
        {
            if (this != &other)
            {
                _tree = other._tree;
                _size = other._size;
            }
            return *this;
        }

        allocator_type get_allocator() const { return _alloc; }

        //  Iterators: ************************************************************************** //

        iterator begin() { return _tree.begin(); }

        iterator end() { return _tree.end(); }

        reverse_iterator rbegin() { return _tree.rbegin(); }

        reverse_iterator rend() { return _tree.rend(); }

        const_iterator begin() const { return _tree.begin(); }

        const_iterator end() const { return _tree.end(); }

        const_reverse_iterator rbegin() const { return _tree.rbegin(); }

        const_reverse_iterator rend() const { return _tree.rend(); }

        // Capacity: ************************************************************************** //

        size_type size() const _NOEXCEPT { return _size; }

        bool empty() const _NOEXCEPT { return !_size; }

        size_type max_size() const _NOEXCEPT { return _alloc.max_size(); }

        // Element access: ************************************************************************** //

        mapped_type &operator[](const Key &key)
        {
            return insert(ft::make_pair(key, mapped_type())).first->second;
        }

        // Modifiers: ************************************************************************** //

        /**
         * clears the contents  
         */
        void clear() { _tree.makeEmpty(); }

        /**
         * inserts elements
         */
        ft::pair<iterator, bool> insert(const value_type &value) { return _tree.insert(value); }

        iterator insert(iterator hint, const value_type &value) { (void) hint; return _tree.insert(value).first; }

        template <class InputIt>
        void insert(InputIt first, InputIt last)
        {
            for (; first != last; ++first)
            {
                // std::cout << *first << " is inserted!" << std::endl;
                insert(*first);
            }
            _size += std::distance(first, last);
        }

        /**
         * erases elements 
         */
        void erase(iterator pos)
        {
            _tree.remove(*pos);
        }

        void erase(iterator first, iterator last)
        {
            _tree.remove(first, last);
        }

        size_type erase(const key_type &key)
        {
            return _tree.remove(ft::make_pair(key, mapped_type())) ? 1 : 0;
        }

        /**
         * swaps the contents 
         */
        void swap(map &other)
        {
            std::swap(_alloc, other._alloc);
            std::swap(_size, other._size);
            avltree tmp = other._tree;
            other._tree = _tree;
            _tree = tmp;

            std::swap(_compare, other._compare);
        }

        // Lookup: ************************************************************************** //

        /**
         * Count elements with a specific key.
         */

        size_type count(const Key &key) const { return _tree.findByKey(key); }

        /**
         *  Get an iterator to element with key.
         */
        iterator find(const Key &key)
        {
            return _tree.find(key);
        }

        /**
         * Get a const_iterator to element with key
         */
        const_iterator find(const Key &key) const
        {
            return _tree.find(key);
        }

        /**
         * Returns an iterator pointing to the first element that is not less than
         * (i.e. greater or equal to) key.
         */
        iterator lower_bound(const key_type &k)
        {
            iterator it = _tree.find(k);
            if (it->first == k)
                return it;
            else
                return ++it;
        }

        /**
         *  Returns a const_iterator pointing to the first element that is greater than key
         */
        const_iterator lower_bound(const key_type &k) const
        {
            const_iterator c_it = _tree.find(k);
            if (c_it->first == k)
                return c_it;
            else
                return ++c_it;
        }

        /**
         *  Returns an iterator pointing to the first element that is greater than key
         */

        iterator upper_bound(const Key &key)
        {
            return ++(_tree.find(key));
        }

        /**
         *  Returns a const_iterator pointing to the first element that is greater than key
         */
        const_iterator upper_bound(const Key &key) const
        {
            return ++(_tree.find(key));
        }

        // Observers: ************************************************************************** //

        /**
         *  returns the function that compares keys 
         */

        key_compare key_comp() const
        {
            return _compare;
        }

        /**
         * 
         */

        value_compare value_comp() const
        {
            return value_compare(_compare);
        }

        const avltree &getTree() const { return _tree; }

        /*
         * Rational Operators (==,!=,<,<=,>,>=,<=>)
         */

        friend bool operator==(const map &lhs, const map &rhs) { return (lhs.size() == rhs.size() && lhs._tree == rhs._tree); }

    private:
        avltree _tree;
        allocator_type _alloc;
        std::size_t _size;
        key_compare _compare;
    };

    //    template<class Key, class T, class Compare, class Alloc>
    //    bool operator==(const map<Key, T, Compare, Alloc> &lhs,
    //                    const map<Key, T, Compare, Alloc> &rhs) {
    //        return (lhs.size() == rhs.size() && lhs._tree == rhs._tree);
    //    }
}

#endif // __MAP_HPP__
