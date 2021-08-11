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

	template<typename Vector>
	class VectorIterator {

	public:

		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename Vector::value_type value_type;
		typedef value_type &reference;
		typedef value_type *pointer;

		/*
		 * Constructor & Copy assignment operator.
		 */

		explicit VectorIterator(pointer p = NULL) : _ptr(p) {}

		VectorIterator(const VectorIterator &other) { *this = other; }

		VectorIterator &operator=(const VectorIterator &other) {
			if(this != &other)
				_ptr = other._ptr;
			return *this;
		}

		/*
		 * Overloaded operators
		 */

		reference &operator*() { return *_ptr; }

		pointer *operator->() { return operator*(); }

		VectorIterator &operator++() {
			_ptr++;
			return *this;
		}

		VectorIterator &operator--() {
			_ptr++;
			return *this;
		}

		// int parameter means this is postfix operator++;
		VectorIterator operator++(int) {
			VectorIterator tmp = *this;
			_ptr++;
			return tmp;
		}

		VectorIterator operator--(int) {
			VectorIterator tmp = (*this);
			operator--();
			return tmp;
		}

		VectorIterator operator+(difference_type n) { return VectorIterator(_ptr + n); }

		VectorIterator operator-(difference_type n) { return VectorIterator(_ptr - n); }

		VectorIterator &operator+=(difference_type n) {
			_ptr += n;
			return VectorIterator(_ptr);
		}

		VectorIterator &operator-=(difference_type n) {
			_ptr -= n;
			return VectorIterator(_ptr);
		}

		reference &operator[](difference_type n) {
			assert(n > 0);
			return *(_ptr + n);
		}

		template<class U>
		friend bool operator==(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs);

		template<class U>
		friend bool operator!=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs);

		template<class U>
		friend bool operator<(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs);

		template<class U>
		friend bool operator<=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs);

		template<class U>
		friend bool operator>(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs);

		template<class U>
		friend bool operator>=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs);


	private:
		pointer _ptr;
	};

	template<typename U>
	bool operator==(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return (lhs._ptr == rhs._ptr);
	}

	template<typename U>
	bool operator!=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return !(lhs == rhs);
	}

	template<typename U>
	bool operator<(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return (lhs._ptr < rhs._ptr);
	}

	template<typename U>
	bool operator<=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return (lhs._ptr <= rhs._ptr);
	}

	template<typename U>
	bool operator>(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return !(lhs < rhs);
	}

	template<typename U>
	bool operator>=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return !(lhs <= rhs);
	}


	template<typename T, typename Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef VectorIterator<vector<T> > iterator;
		typedef VectorIterator<const vector<T> > const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
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

		void push_back(const T &value);

		size_type max_size() const;

		size_type capacity() const;

		bool empty() const;

		void resize(size_type n, value_type val = value_type());

		void reserve(size_type n);

		iterator begin();

		iterator end();

		const_iterator begin() const;

		const_iterator end() const;

		reverse_iterator rbegin();

		reverse_iterator rend();

		const_reverse_iterator rbegin() const;

		const_reverse_iterator rend() const;


	private:
		std::size_t _size;
		std::size_t _capacity;
		allocator_type _alloc;
		T *_arr;

	private:


		T *_allocate(std::allocator<T> &alloc, std::size_t n);

		void _reallocate(std::allocator<T> &alloc, std::size_t newSize);

		void _fill(std::size_t start, std::size_t end, const value_type &val);

		template<typename InputIterator>
		void _fill(InputIterator first, InputIterator last);

		void _deallocate(std::size_t start, std::size_t end, bool reset);
	};

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const allocator_type &alloc) : _size(0), _capacity(0), _alloc(alloc), _arr(NULL) {}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(vector::size_type n, const value_type &val, const allocator_type &alloc)
			: _size(n), _capacity(n), _alloc(alloc) {
		_arr = _allocate(_alloc, n);
		_fill(0, _size, val);
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
	void vector<T, Alloc>::_fill(std::size_t start, std::size_t end, const value_type &val) {
		for(std::size_t i = start; i < end; ++i) {
			_arr[i] = val;
		}

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
		_deallocate(0, _size, true);
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
			_deallocate(0, _size, true);
			_size = x._size;
			_capacity = x._capacity;
			_arr = _allocate(_alloc, _size);
			_fill(x._arr, x._arr + _size);
		}
		return *this;
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::_deallocate(std::size_t start, std::size_t end, bool reset) {
		if(!_size) return;
		for(std::size_t i = start; i < end; ++i)
			_alloc.destroy(&_arr[i]);
		_alloc.deallocate(_arr, _size);
		if(reset) {
			_arr = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
		return _size;
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
		return iterator(_arr);
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
		return const_iterator(_arr + _size);
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {
		return reverse_iterator(end());
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
		return reverse_iterator(begin());
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const {
		return reverse_iterator(end());;
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const {
		return reverse_iterator(begin());
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::push_back(const value_type &value) {
		if(empty() && !_capacity)
			_arr = _allocate(_alloc, 1);
		else if(_size >= _capacity)
			_reallocate(_alloc, _size * 2);
		_arr[_size++] = value;

		if(empty() || _capacity == 1)
			_capacity = 1;
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
		return _alloc.max_size();
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const {
		return _capacity;
	}

	template<typename T, typename Alloc>
	bool vector<T, Alloc>::empty() const {
		return !_size;
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val) {
		if(n < _size) {
			_deallocate(n, _size, false);
			_size = n;
		}

		if(n > _size) {
			if(n > _capacity)
				_reallocate(_alloc, n);
			else
				_fill(_size, n, val);
		}
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::_reallocate(std::allocator<T> &alloc, std::size_t newSize) {
		value_type *other = alloc.allocate(newSize);
		for(std::size_t i = 0; i < _size; ++i)
			other[i] = _arr[i];
		_deallocate(0, size(), false);
		_arr = other;
		_capacity = newSize;
	}

	template<typename T, typename Alloc>
	void vector<T, Alloc>::reserve(vector::size_type n) { if(n > _capacity) _reallocate(_alloc, n); }
	
}

#endif // __VECTOR_HPP__
