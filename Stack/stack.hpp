//
// Created by moboustt on 19/8/2021.
//

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "../vector/Vector.hpp"

namespace ft {

	template<typename T, class Container = ft::Vector<T> >
	class Stack {

	public:

		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	public:

		explicit Stack(const Container &cont = Container()) : _c(cont) {}

		Stack(const Stack &other) { *this = other; }

		template<class InputIt>
		Stack(InputIt first, InputIt last): _c(first, last) {}

		template<class InputIt, class Alloc>
		Stack(InputIt first, InputIt last, const Alloc &alloc) : _c(first, last, alloc) {}

		~Stack() {}

		Stack &operator=(const Stack &other) {
			if(this != &other)
				_c = other._c;
			return *this;
		}

		// -*-  Element access  -*-

		reference top() {
			return _c.back();
		}

		const_reference top() const {
			return _c.back();
		}

		// -*-  Capacity  -*-

		bool empty() const {
			return _c.empty();
		}

		size_type size() const {
			return _c.size();
		}


		// -*-  Modifiers  -*-

		void push(const value_type &value) {
			_c.push_back(value);
		}

		void pop() {
			_c.pop_back();
		}

		// -*-  Non-member functions  -*-


		

	friend bool operator==(const Stack &lhs, const Stack &rhs) {
		return lhs._c == rhs._c;
	}

	friend bool operator!=(const Stack &lhs, const Stack &rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const Stack &lhs, const Stack &rhs) {
		return lhs._c < rhs._c;
	}

	friend bool operator<=(const Stack &lhs, const Stack &rhs) {
		return lhs._c <= rhs._c;
	}

	friend bool operator>(const Stack &lhs, const Stack &rhs) {
		return lhs._c > rhs._c;
	}

	friend bool operator>=(const Stack &lhs, const Stack &rhs) {
		return lhs._c >= rhs._c;
	}


	protected:

		container_type _c;
	};

	
}


#endif // __Stack_HPP__
