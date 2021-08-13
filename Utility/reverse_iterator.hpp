//
// Created by moboustt on 8/8/2021.
//

#ifndef __REVERSE_ITERATOR_HPP__
#define __REVERSE_ITERATOR_HPP__

#include <ostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "../Utility/choose.hpp"

namespace ft {

	template<typename Iterator>
	class reverse_iterator {

	public:

		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		// typedef typename Iterator::value_type value_type;
		// typedef typename std::ptrdiff_t difference_type;

		// typedef typename choose<is_const<value_type>::value, const value_type &, value_type &>::type reference;
		// typedef typename choose<is_const<value_type>::value, const value_type *, value_type *>::type pointer;

		// Constructors.
		reverse_iterator() : _baseIter() {}

		explicit reverse_iterator(const iterator_type &it) : _baseIter(it) {}

		reverse_iterator(const reverse_iterator &revIt) { *this = revIt; }

		// Member functions.
		iterator_type base() const;

		// Overloaded operators.
		reverse_iterator &operator=(const reverse_iterator &revIter) {
			if(this != &revIter)
				_baseIter = revIter._baseIter;
			return *this;
		}

		reference operator*();

		reverse_iterator &operator++();

		reverse_iterator &operator--();

		reverse_iterator operator++(int);

		reverse_iterator operator--(int);

		reverse_iterator operator+(difference_type n) const;

		reverse_iterator operator-(difference_type n) const;

		reverse_iterator &operator+=(difference_type n);

		reverse_iterator &operator-=(difference_type n);

		pointer operator->();

		reference operator[](difference_type n);

		friend std::ostream &operator<<(std::ostream &os, const reverse_iterator &iterator);

		template<typename Iter1, typename Iter2>
		friend typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs);

		template<typename Iter>
		friend reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs);
		// template<typename Iter> friend reverse_iterator operator-(difference_type n, reverse_iterator<Iter>  const& rhs);

	private:

		Iterator _baseIter;
	};

	// template<typename Iterator>
	// reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iterator> &revIt)
	// 		: _baseIter(revIt._baseIter) {}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const {
		return _baseIter;
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator*() {
		Iterator tmp = _baseIter;
		return *--tmp;
	}

	// int parameter means this is postfix operator++;
	template<typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int) {
		reverse_iterator tmp(*this);
		--_baseIter;
		return tmp;
	}


	// int parameter means this is postfix operator--;
	template<typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int) {
		reverse_iterator tmp(*this);
		++_baseIter;
		return tmp;
	}

	// ++operator;
	template<typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator++() {
		--_baseIter;
		return *this;
	}

	// --operator;
	template<typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator--() {
		++_baseIter;
		return *this;
	}

	template<typename Iterator>
	std::ostream &operator<<(std::ostream &os, const reverse_iterator<Iterator> &iterator) {
		os << iterator._baseIter;
		return os;
	}

	template<typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+(difference_type n) const {
		return reverse_iterator(_baseIter - n);
	}

	template<typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(difference_type n) const {
		return reverse_iterator(_baseIter + n);
	}

	template<typename Iterator>
	reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator+=(difference_type n) {
		_baseIter -= n;
		return *this;
	}

	template<typename Iterator>
	reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator-=(difference_type n) {
		_baseIter += n;
		return *this;
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::pointer reverse_iterator<Iterator>::operator->() {
		return &(operator*());
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator[](difference_type n) {
		assert(n >= 0);
		return *(*this + n);
	}

	template<typename Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs) {
		return rhs + n;
	}

	template<typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return (rhs.base() - lhs.base());
	}

	template<typename Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs) {
		return lhs.base() == rhs.base();
	}

	template<typename Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs) {
		return !(lhs == rhs);
	}

	template<typename Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template<typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template<typename Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template<typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() <= rhs.base());
	}

}

#endif // __REVERSE_ITERATOR_HPP__
