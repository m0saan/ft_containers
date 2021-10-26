//
// Created by moboustt on 19/8/2021.
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <functional>

#include "../utility/avltree.hpp"
#include "../utility/reverse_iterator.hpp"
#include "../utility/enable_if.hpp"
#include "../utility/iterator_traits.hpp"
#include "../utility/pair.hpp"
#include "../vector/Vector.hpp"

namespace ft
{

    template <class, class, class>
    class Node;

    template <
        typename Key,
        typename T,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<ft::pair<const Key, T> > >
    class Map
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

            friend class Map;
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
        Map() : _tree(), _size(), _compare()
        {
            _tree.init(_compare, _alloc);
        }

        explicit Map(const Compare &comp, const Alloc &alloc = Alloc())
            : _tree(), _alloc(alloc), _size(), _compare(comp)
        {
            _tree.init(_compare, _alloc);
        }

        template <typename InputIt>
        Map(InputIt first, InputIt last, const Compare &comp = Compare(),
            const Alloc &alloc = Alloc()) : _alloc(alloc), _compare(comp)
        {
            _tree.init(_compare, _alloc);
            for (; first != last; first++){
                // std::cout << *first << " is inserted!" << std::endl;
                _tree.insert(*first);
            }
        }

        Map(const Map &other)
        {
            *this = other;
        }

        Map &operator=(const Map &other)
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

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }

        const_iterator begin() const { return _tree.begin(); }

        const_iterator end() const { return _tree.end(); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        // Capacity: ************************************************************************** //

        size_type size() const _NOEXCEPT { return _tree.size(); }

        bool empty() const _NOEXCEPT { return _tree.isEmpty(); }

        size_type max_size() const _NOEXCEPT { return _tree.max_size(); }

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
            int size = 0;
            for (; first != last; ++first)
            {
                // std::cout << *first << " is inserted!" << std::endl;
                insert(*first);
                ++size;
            }
            _size = size;
        }

        /**
         * erases elements 
         */
        void erase(iterator pos)
        {
            _tree.remove((*pos).first);
        }

        void erase(iterator first, iterator last)
        {
            ft::Vector<Key> keys;
            if (first == begin() && last == end())
                keys.reserve(size());
            else
                keys.reserve(size() / 2);
            for (; last != first; first++)   keys.push_back((*first).first);
            // std::cout << "done getting keys." << std::endl; 

            for (size_t i = 0; i < keys.size(); ++i){
                // std::cout << keys[i] << " is deleted!" << std::endl;
                erase(keys[i]);
            }
            
        }

        size_type erase(const key_type &key)
        {
            return _tree.remove(key) ? 1 : 0;
        }

        /**
         * swaps the contents 
         */
        void swap(Map &other)
        {
            std::swap(_alloc, other._alloc);
            std::swap(_size, other._size);
            _tree.swap(other._tree);

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
            return _tree.lower_bound(k);
        }

        /**
         *  Returns a const_iterator pointing to the first element that is greater than key
         */
        const_iterator lower_bound(const key_type &k) const
        {
          return _tree.lower_bound(k);
        }

        /**
         *  Returns an iterator pointing to the first element that is greater than key
         */

        iterator upper_bound(const Key &key)
        {
            return _tree.upper_bound(key);
        }

        /**
         *  Returns a const_iterator pointing to the first element that is greater than key
         */
        const_iterator upper_bound(const Key &key) const
        {
            return _tree.upper_bound(key);
        }


        /**
         * Returns a range containing all elements with the given key in the container.
         */

        ft::pair<iterator,iterator> equal_range( const Key& key ) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }


        ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
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
         * Rational Operators (==,!=,<,<=,>,>=)
         */

        friend bool operator==(const Map &lhs, const Map &rhs)      {  return   (lhs.size() == rhs.size() && lhs._tree == rhs._tree);  }
        friend bool operator!=( const Map& lhs, const Map& rhs)     {  return   !(lhs == rhs);                                         }
        friend bool operator<(const Map& lhs,const Map& rhs)        {   return    ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
        friend bool operator<=(const Map& lhs,const Map& rhs)        { return   !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()); }
        friend bool operator>( const Map& lhs, const Map& rhs )     {  return   ft::lexicographical_compare( rhs.begin(), rhs.end(), lhs.begin(), lhs.end() );}
        friend bool operator>=( const Map& lhs,const Map& rhs )     {  return   !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end() ); }


    private:
        avltree _tree;
        allocator_type _alloc;
        std::size_t _size;
        key_compare _compare;
    };
}

#endif // __Map_HPP__
