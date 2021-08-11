//
// Created by moboustt on 9/8/2021.
//

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>
#include <vector>

#include "../Utility/iterator.hpp"
#include "../Utility/reverse_iterator.hpp"
#include "../Utility/enable_if.hpp"
#include "../Utility/is_integral.hpp"
#include "../Utility/iterator_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

	template<typename T, typename Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef VectorIterator<value_type> iterator;
		typedef VectorIterator<const value_type> const_iterator;
		// typedef reverse_iterator<iterator> reverse_iterator;
		// typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;


		/*
		 * Constructor & Destructor.
		 */

		explicit vector(const allocator_type &alloc = allocator_type()); // Default.
		explicit vector(size_type n, const value_type &val = value_type(), // Fill
						const allocator_type &alloc = allocator_type());

		/*
		 * typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()
		 */
		template<class InputIterator>
		vector(InputIterator first, InputIterator last,        // Range
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					   InputIterator>::type = InputIterator());

		vector(const vector &x);

		~vector();

		size_type size() const;

		vector &operator=(const vector &x);

		reference operator[](difference_type n) { return *(_arr + n); }
		// reference operator->() { return _arr; }

		void print();

		iterator begin();

		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

	private:
		std::size_t _size;
		std::size_t _capacity;
		allocator_type _alloc;
		T *_arr;

	private:


		T *_allocate(std::allocator<T> &alloc, std::size_t n);

		void _fill(const value_type &val);

		template<typename InputIterator>
		void _fill(InputIterator first, InputIterator last);

		void _deallocate();
	};

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const allocator_type &alloc) : _size(0), _capacity(0), _alloc(alloc), _arr(NULL) {
		std::cout << "default" << std::endl;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(vector::size_type n, const value_type &val, const allocator_type &alloc)
			: _size(n), _capacity(n), _alloc(alloc) {
		_arr = _allocate(_alloc, n);
		_fill(val);
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc,
							 typename ft::enable_if<!ft::is_integral<InputIterator>::value,
									 InputIterator>::type)
			: _size(last - first), _capacity(last - first), _alloc(alloc) {
		_arr = _allocate(_alloc, last - first);
		_fill(first, last);
	}

	template<typename T, typename Alloc>
	T *vector<T, Alloc>::_allocate(std::allocator<T> &alloc, std::size_t n) {
		T *arr;
		try {
			arr = alloc.allocate(n);
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		return arr;
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::_fill(const value_type &val) {
		for(std::size_t i = 0; i < _size; ++i)
			_arr[i] = val;
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	void vector<T, Alloc>::_fill(InputIterator first, InputIterator last) {
		int i = 0;
		while(first != last)
			_arr[i++] = *(first++);
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::~vector() {
		_deallocate();
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::print() {
		std::cout << "[ ";
		for(std::size_t i = 0; i < _size; ++i)
			std::cout << _arr[i] << ' ';
		std::cout << ']' << std::endl;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const vector &x) : _size(0), _capacity(0) {
		*this = x;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &x) {
		if(this != &x) {
			_deallocate();
			_size = x._size;
			_capacity = x._capacity;
			_arr = _allocate(_alloc, _size);
			_fill(x._arr, x._arr + _size);
		}
		return *this;
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::_deallocate() {
		if(!_size) return;
		for(std::size_t i = 0; i < _size; ++i)
			_alloc.destroy(&_arr[i]);
		_alloc.deallocate(_arr, _size);
		_arr = NULL;
		_size = 0;
		_capacity = 0;
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
		return _size;
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
		return VectorIterator<T>(_arr);
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
		return iterator(_arr + _size);
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
		return const_iterator(_arr);
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
		return const_iterator (_arr + _size);
	}

}

#endif // __VECTOR_HPP__
