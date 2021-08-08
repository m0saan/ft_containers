//
// Created by moboustt on 8/8/2021.
//


#include <typeinfo>
#include "../Utility/iterator.hpp"
#include "../Utility/iterator_traits.hpp"



int main() {
	typedef ft::iterator_traits<ft::iterator< std::random_access_iterator_tag, int*> > traits;
	std::cout << typeid(traits::iterator_category).name() << std::endl;
	std::cout << typeid(std::random_access_iterator_tag).name() << std::endl;
		// std::cout << "int* is a random-access iterator" << std::endl;
}