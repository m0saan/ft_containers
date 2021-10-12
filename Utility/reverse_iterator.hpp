//
// Created by moboustt on 8/8/2021.
//

#ifndef __REVERSE_ITERATOR_HPP__
#define __REVERSE_ITERATOR_HPP__

#include <ostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "../utility/choose.hpp"

namespace ft {


    template<typename Iterator>
    class reverse_iterator {

    public:

        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;

        // Constructors.
        reverse_iterator() : _baseIter() {}

        explicit reverse_iterator(const iterator_type &it) {
            // if (it.getNodePtr() == NULL && std::is_same<iterator_category, std::bidirectional_iterator_tag>::value)
                // _baseIter = it;
            // else {
            Iterator cIt = it;
            --cIt;
            _baseIter = cIt;
            // }
        }

        reverse_iterator(const reverse_iterator &revIt) { *this = revIt; }

        template<typename U>
        reverse_iterator(const reverse_iterator<U>& x) : _baseIter(--x.base()) {  }

        // Member functions.
        iterator_type base() const;

        // Overloaded operators.
        reverse_iterator &operator=(const reverse_iterator &revIter) {
            if (this != &revIter)
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

        // friend std::ostream &operator<<(std::ostream &os, const reverse_iterator &iterator);

        template<typename Iter1, typename Iter2>
        friend typename reverse_iterator<Iter1>::difference_type
        operator-(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs);

        template<typename Iter>
        friend reverse_iterator<Iter>
        operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &rhs);
        // template<typename Iter> friend reverse_iterator operator-(difference_type n, reverse_iterator<Iter>  const& rhs);

    private:

        Iterator _baseIter;
    };

    // template<typename Iterator>
    // reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iterator> &revIt)
    // 		: _baseIter(revIt._baseIter) {}

    template<typename Iterator>
    typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const {
        Iterator tmp(this->_baseIter);
        return ++tmp;
    }

    template<typename Iterator>
    typename reverse_iterator<Iterator>::reference reverse_iterator<Iterator>::operator*() {
        Iterator tmp(_baseIter);
        return *tmp;
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
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator++() {
        --_baseIter;
        return *this;
    }

    // --operator;
    template<typename Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator--() {
        ++_baseIter;
        return *this;
    }

    // template<typename Iterator>
    // std::ostream &operator<<(std::ostream &os, const reverse_iterator<Iterator> &iterator) {
    //     os << iterator._baseIter;
    //     return os;
    // }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+(difference_type n) const {
        return reverse_iterator(_baseIter - n + 1);
    }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(difference_type n) const {
        return reverse_iterator(_baseIter + n + 1);
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
    reverse_iterator<Iter>
    operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &rhs) {
        return rhs + n;
    }

    template<typename Iter1, typename Iter2>
    typename reverse_iterator<Iter1>::difference_type
    operator-(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
        return (rhs.base() - lhs.base());
    }



    /*
        Retional Operators.
    */

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
                 {
                     return lhs.base() == rhs.base();
                 }
	
template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs)
                 {
                     return !(lhs == rhs);
                 }
	
template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
                {
                    return (lhs.base() >= rhs.base());
                }
	
template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
                 {
                    return (lhs.base() >= rhs.base()); 
                 }
	
template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
                {
                            return (lhs.base() < rhs.base());
                }
	
template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
                 {
                      return (lhs.base() <= rhs.base());
                 }

}

#endif // __REVERSE_ITERATOR_HPP__
