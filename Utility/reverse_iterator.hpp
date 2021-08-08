//
// Created by moboustt on 8/8/2021.
//

#ifndef __REVERSE_ITERATOR_HPP__
#define __REVERSE_ITERATOR_HPP__

#include <ostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"

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

		// Constructors.
		reverse_iterator();

		explicit reverse_iterator(iterator_type it);

		reverse_iterator(const reverse_iterator<Iterator> &revIt);

		// Member functions.
		iterator_type base() const;

		// Overloaded operators.
		reference operator*();
		reference operator++();
		reference operator--();
		reverse_iterator operator++(int);
		reverse_iterator operator--(int);

		friend std::ostream &operator<<(std::ostream &os, const reverse_iterator &iterator);

	private:

		Iterator _baseIter;
		Iterator _revIter;
	};

	template<typename Iterator>
	reverse_iterator<Iterator>::reverse_iterator(): _baseIter() {}

	template<typename Iterator>
	reverse_iterator<Iterator>::reverse_iterator(iterator_type it) {
		_baseIter = it;
	}

	template<typename Iterator>
	reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iterator> &revIt)
			:
			_baseIter(revIt._baseIter),
			_revIter(revIt._revIter) {}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const {
		return _baseIter;
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator*() {
		Iterator tmp = _baseIter;
		return *(--tmp);
	}

	// int parameter means this is postfix operator++;
	template<typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int) {
		reverse_iterator tmp (*this);
		--_baseIter;
		return tmp;
	}


	// int parameter means this is postfix operator--;
	template<typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int) {
		reverse_iterator tmp (*this);
		++_baseIter;
		return tmp;
	}

	// ++operator;
	template<typename Iterator>
	typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator++() {
		++_baseIter;
		return this;
	}

	// --operator;
	template<typename Iterator>
	typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator--() {
		--_baseIter;
		return this;
	}

	template<typename Iterator>
	std::ostream &operator<<(std::ostream &os, const reverse_iterator<Iterator> &iterator) {
		os << iterator._baseIter;
		return os;
	}

	template<typename Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs) {
		return lhs.base() == rhs.base();
	}

	template<typename Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs){
		return !(lhs == rhs);
	}

	template<typename Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs){
		return (lhs.base() > rhs.base());
	}

	template<typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs){
		return (lhs.base() >= rhs.base());
	}

	template<typename Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs){
		return (lhs.base() < rhs.base());
	}

	template<typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs){
		return (lhs.base() <= rhs.base());
	}

}

#endif // __REVERSE_ITERATOR_HPP__
