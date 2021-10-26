//
// Created by moboustt on 9/8/2021.
//

#ifndef __ENABLE_IF_HPP__
#define __ENABLE_IF_HPP__

namespace ft {
	template<bool Cond, typename T = void>
	struct enable_if {
	};

	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

}

#endif // __ENABLE_IF_HPP__
