//
// Created by moboustt on 9/8/2021.
//

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

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

		template<class InputIterator>
		vector(InputIterator first, InputIterator last,        // Range
			   const allocator_type &alloc = allocator_type());

	private:
		int _size;
		int _capacity;
		T *_arr;
	};

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const allocator_type &alloc) : _size(0), _capacity(0), _arr(NULL) {
		std::cout << "default" << std::endl;
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(vector::size_type n, const value_type &val, const allocator_type &alloc)
			: _size(n), _capacity(n) {
		std::cout << "fill" << std::endl;
	}

	template<typename T, typename Alloc>
	template<typename InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc) {
		std::cout << "range" << std::endl;
	}
}

#endif // __VECTOR_HPP__
