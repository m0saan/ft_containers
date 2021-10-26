//
// Created by moboustt on 8/8/2021.
//

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <cstddef>

namespace ft {                                    // Defining the namespace ft.

	template<typename Category,
			typename T,
			typename Distance = ptrdiff_t,
			typename Pointer = T *,
			typename Reference= T &>

	class iterator {

	public:

		typedef T 			value_type; 		// Type of elements pointed by the iterator.
		typedef Distance 	difference_type;	// Type to represent the difference between two iterators.
		typedef Pointer 	pointer;			//
		typedef Reference 	reference;
		typedef Category 	iterator_category;	// Category to which the iterator belongs to.
	};
}

#endif // __ITERATOR_HPP__
