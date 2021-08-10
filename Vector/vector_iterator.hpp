//
// Created by moboustt on 10/8/2021.
//

#ifndef __VECTOR_ITERATOR_HPP__
#define __VECTOR_ITERATOR_HPP__

#include "../Utility/iterator.hpp"
#include "../Utility/iterator_traits.hpp"

namespace ft {

	template<typename T>
	class VectorIterator : iterator<std::random_access_iterator_tag, T> {

	public:

		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		/*
		 * Constructor & Copy assignment operator.
		 */

		VectorIterator() : _p() {}; // NOLINT(modernize-use-equals-default)
		explicit VectorIterator(T *p) : _p(p) {}

		VectorIterator(const VectorIterator &other) { *this = other; }

		VectorIterator &operator=(const VectorIterator &other) {
			if(this != &other)
				_p = other._p;
			return *this;
		}

		/*
		 * Overloaded operators
		 */

		T &operator*() { return *_p; }

		T *operator->() { return operator*(_p); }

		VectorIterator& operator++() { ++_p; return *this; }

		VectorIterator& operator--() { --_p; return *this; }

		// int parameter means this is postfix operator++;
		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			operator++();
			return tmp;
		}

		VectorIterator operator--(int) {
			VectorIterator tmp = (*this);
			operator--();
			return tmp;
		}

		VectorIterator operator+(difference_type n) { return VectorIterator(_p + n); }

		VectorIterator operator-(difference_type n) { return VectorIterator(_p - n); }

		VectorIterator &operator+=(difference_type n) {
			_p += n;
			return VectorIterator(_p);
		}

		VectorIterator &operator-=(difference_type n) {
			_p -= n;
			return VectorIterator(_p);
		}

		T &operator[](difference_type n) {
			assert(n > 0);
			return *(_p + n);
		}


		friend bool operator==(const VectorIterator &lhs, const VectorIterator &rhs);

		friend bool operator!=(const VectorIterator &lhs, const VectorIterator &rhs);

		friend bool operator<(const VectorIterator &lhs, const VectorIterator &rhs);

		friend bool operator<=(const VectorIterator &lhs, const VectorIterator &rhs);

		friend bool operator>(const VectorIterator &lhs, const VectorIterator &rhs);

		friend bool operator>=(const VectorIterator &lhs, const VectorIterator &rhs);


	protected:

		T *_p;
	};

	template<typename T>
	bool operator==(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs) {
		return (lhs._p == rhs._p);
	}

	template<typename T>
	bool operator!=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs) {
		return !(lhs == rhs);
	}

	template<typename T>
	bool operator<(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs) {
		return (lhs._p < rhs._p);
	}

	template<typename T>
	bool operator<=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs) {
		return (lhs._p <= rhs._p);
	}

	template<typename T>
	bool operator>(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs) {
		return !(lhs < rhs);
	}

	template<typename T>
	bool operator>=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs) {
		return !(lhs <= rhs);
	}

}


#endif // __VECTOR_ITERATOR_HPP__
