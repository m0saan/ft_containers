//
// Created by moboustt on 12/8/2021.
//

#ifndef __CHOOSE_HPP__
#define __CHOOSE_HPP__

namespace ft {

	template<bool flag, class IsTrue, class IsFalse>
	struct choose;

	template<class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse> {
		typedef IsTrue type;
	};

	template<class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse> {
		typedef IsFalse type;
	};

	template<class T>
	struct is_const : std::false_type {
	};
	template<class T>
	struct is_const<const T> : std::true_type {
	};
}

#endif // __CHOOSE_HPP__
