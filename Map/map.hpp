//
// Created by moboustt on 19/8/2021.
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <functional>
#include "../Utility/AVLTree.hpp"
#include "../Utility/reverse_iterator.hpp"
#include "../Utility/enable_if.hpp"
#include "../Utility/iterator_traits.hpp"
#include <map>

namespace ft {

    template<
            typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Allocator = std::allocator<std::pair<const Key, T> >
    >
    class map {

    public:

        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<Key, T> value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename AVLTree<value_type, Compare>::AVLTreeIterator iterator;
        typedef const iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


        class value_compare {

        protected:

            explicit value_compare(Compare c) : comp(c) {}

            bool operator()(const value_type &lhs, const value_type &rhs) const {
                return comp(lhs.first, rhs.first);
            }

            Compare comp;
        };


        map() : _tree(), _size(), _compare() {}

        explicit map(const Compare &comp, const Allocator &alloc = Allocator())
                : _tree(), _alloc(alloc), _size(), _compare(comp) {}

        template<typename InputIt>
        map(InputIt first, InputIt last, const Compare &comp = Compare(),
            const Allocator &alloc = Allocator()) : _alloc(alloc), _compare(comp) {
            assert(value_type == ft::iterator_traits<InputIt>::value_type);
            for (; first != last; ++first) {
                _tree.insert(*first);
            }
        }

        map(const map &other) {
            *this = other;
        }

        map &operator=(const map &other) {
            if (this != &other) {
                _tree = other._tree;
                _size = other._size;
                _compare = other._compare;
            }
            return *this;
        }

        mapped_type &operator[](const Key &key) {
            return insert(std::make_pair(key, T())).first->second;
        }

        std::pair<iterator, bool> insert(const value_type &value) {
            //std::pair<iterator, bool> res = _tree.find(value);
            //if (res.second)
            //	return res;
            return _tree.insert(value);
        }

        /*
         * -> Capacity
         */

        size_type size() const _NOEXCEPT {
            return _tree.size();
        }

        bool empty() const _NOEXCEPT {
            return _tree.isEmpty();
        }

        size_type max_size() const _NOEXCEPT {
            return _alloc.max_size();
        }

        iterator begin() const _NOEXCEPT {
            return iterator(_tree.begin());
        }

        iterator end() const _NOEXCEPT {
            return iterator(_tree.end());
        }

        const AVLTree<value_type, Compare> &getTree() const {
            return _tree;
        }


        /*
         * Rational Operators (==,!=,<,<=,>,>=,<=>)
         */

        friend bool operator==(const map &lhs, const map &rhs) {
            return (lhs.size() == rhs.size() && lhs._tree == rhs._tree);
        }

    private:

        AVLTree<value_type, Compare> _tree;
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
