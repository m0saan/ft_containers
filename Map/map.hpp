//
// Created by moboustt on 19/8/2021.
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <functional>
#include "../Utility/AVL.hpp"
#include "../Utility/reverse_iterator.hpp"
#include "../Utility/enable_if.hpp"
#include <map>

namespace ft {


	template<class Map>
	class MapIterator {
	public:
		typedef typename Map::value_type value_type;
		typedef typename Map::pointer pointer;
		typedef typename Map::reference reference;

		explicit MapIterator(pointer p = NULL) : _ptr(p) {}

	private:
		pointer _ptr;
	};

	template <
			typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Allocator = std::allocator<std::pair<const Key, T>>
	>
	class map {

	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const Key, T> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef MapIterator<value_type> iterator;
		typedef MapIterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


		map() {}

		explicit map(const Compare &comp, const Allocator &alloc = Allocator())
				: _compare(comp), _alloc(alloc) {}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare &comp = Compare(),
			const Allocator &alloc = Allocator()) : _compare(comp), _alloc(alloc) {
			for(; first != last; ++first) {
				_tree.insert(_alloc.allocate(*first));
			}
		}

		map(const map &other) {
			*this = other;
		}

		map &operator=(const map &other) {
			if(this != &other) {
				_tree = other._tree;
				_size = other._size;
				_compare = other._compare;
			}
			return *this;
		}

		reference operator[](const Key &key) {
			return insert(std::make_pair(key, T())).first->second;
		}

		std::pair<iterator, bool> insert(const value_type &value) {
			bool isFound = _tree.find(value);
			if (isFound)
				return std::make_pair(iterator(), false);
			_tree.insert(value);
			return std::make_pair(iterator(), true);
		}

		iterator insert(iterator hint, const value_type &value) {

		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {

		}

		/*
		 * -> Capacity
		 */

		size_type size() const _NOEXCEPT {
			return _size;
		}

		bool empty() const _NOEXCEPT {
			return _size == 0;
		}

		size_type max_size() const _NOEXCEPT {
			return _alloc.max_size();
		}

	private:

		AVL<value_type> _tree;
		allocator_type _alloc;
		std::size_t _size;
		key_compare _compare;
	};
}


#endif // __MAP_HPP__
