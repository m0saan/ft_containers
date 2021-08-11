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

		typedef ptrdiff_t difference_type;

		/*
		 * Constructor & Copy assignment operator.
		 */

		VectorIterator() : _p() {}; // NOLINT(modernize-use-equals-default)
		explicit VectorIterator(T *p) : _p(p) {}

		VectorIterator(const VectorIterator &other) { *this = other; }

		VectorIterator& operator=(const VectorIterator &other) {
			if(this != &other)
				_p = other._p;
			return *this;
		}

		/*
		 * Overloaded operators
		 */

		T &operator*() { return *_p; }

		T *operator->() { return operator*(_p); }

		VectorIterator &operator++() {
			_p++;
			return *this;
		}

		VectorIterator &operator--() {
			_p++;
			return *this;
		}

		// int parameter means this is postfix operator++;
		VectorIterator operator++(int) {
			VectorIterator tmp = *this;
			_p++;
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


	protected:

		T *_p;
	};

	template<typename U>
	bool operator==(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return (lhs._p == rhs._p);
	}

	template<typename U>
	bool operator!=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return !(lhs == rhs);
	}

	template<typename U>
	bool operator<(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return (lhs._p < rhs._p);
	}

	template<typename U>
	bool operator<=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return (lhs._p <= rhs._p);
	}

	template<typename U>
	bool operator>(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return !(lhs < rhs);
	}

	template<typename U>
	bool operator>=(const VectorIterator<U> &lhs, const VectorIterator<U> &rhs) {
		return !(lhs <= rhs);
	}

}


#endif // __VECTOR_ITERATOR_HPP__
