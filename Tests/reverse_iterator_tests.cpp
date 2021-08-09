//
// Created by moboustt on 8/8/2021.
//

#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <iterator>
#include "../Utility/reverse_iterator.hpp"

/*
int main () {
	std::vector<int> myvector;
	for (int i=0; i<10; i++)
		myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;
	// ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from (myvector.begin());                     //   ^
	//         ------>
	iter_type until (myvector.end());                      //                       ^
	//
	ft::reverse_iterator<iter_type> rev_until (from);     // ^
	//         <------
	ft::reverse_iterator<iter_type> rev_from (until);     //

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';

	return 0;
}

*/

/*
int main () {
	std::vector<int> myvector;
	myvector.reserve(10);
for (int i=0; i<10; i++)
		myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	rev_iterator += 2;

	std::cout << "The third element from the end is: " << *rev_iterator << '\n';

	return 0;
}
 */


#include <iostream>
#include <type_traits>
#include "../Utility/is_integral.hpp"

int main() {
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	return 0;
}