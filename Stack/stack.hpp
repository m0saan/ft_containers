//
// Created by moboustt on 19/8/2021.
//

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "../Vector/Vector.hpp"

namespace ft {

	template<typename T, class Container = ft::vector<T> >
	class stack {

	public:

		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	public:

		explicit stack(const Container &cont = Container()) : _c(cont) {}

		stack(const stack &other) { *this = other; }

		template<class InputIt>
		stack(InputIt first, InputIt last): _c(first, last) {}

		template<class InputIt, class Alloc>
		stack(InputIt first, InputIt last, const Alloc &alloc) : _c(first, last, alloc) {}

		~stack() {}

		stack &operator=(const stack &other) {
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
		friend bool operator==(const stack &lhs, const stack &rhs);

		friend bool operator!=(const stack &lhs, const stack &rhs);

		friend bool operator<(const stack &lhs, const stack &rhs);

		friend bool operator<=(const stack &lhs, const stack &rhs);

		friend bool operator>(const stack &lhs, const stack &rhs);

		friend bool operator>=(const stack &lhs, const stack &rhs);

	protected:

		container_type _c;
	};

	template<class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._c == rhs._c;
	}

	template<class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._c < rhs._c;
	}

	template<class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return lhs._c <= rhs._c;
	}

	template<class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs < rhs);
	}

	template<class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return !(lhs <= rhs);
	}

}


#endif // __STACK_HPP__
