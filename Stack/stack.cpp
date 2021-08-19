//
// Created by moboustt on 19/8/2021.
//

#include "stack.hpp"
#include <stack>

int main() {

	std::cout << "********************* <Testing Stack Constructors *********************" << std::endl;
	{
		ft::stack<int> c1;
		c1.push(5);
		std::cout << c1.size() << '\n';

		ft::stack<int> c2(c1);
		std::cout << c2.size() << '\n';

		ft::vector<int> vec(2, 10);
		ft::stack<int> c3(vec);
		std::cout << c3.size() << '\n';
	}

	std::cout << "********************* <Testing Top() method. *********************" << std::endl;
	{
		ft::stack<int>   s;

		s.push( 2 );
		s.push( 6 );
		s.push( 51 );

		std::cout << s.size() << " elements on stack\n";
		std::cout << "Top element: "
		<< s.top()         // Leaves element on stack
		<< "\n";
		std::cout << s.size() << " elements on stack\n";
		s.pop();
		std::cout << s.size() << " elements on stack\n";
		std::cout << "Top element: " << s.top() << "\n";
	}

	std::cout << "********************* <Testing empty() method.> *********************" << std::endl;
	{
		std::cout << std::boolalpha;

		ft::stack<int> container;

		std::cout << "Initially, container.empty(): " << container.empty() << '\n';

		container.push(42);
		std::cout << "After adding elements, container.empty(): " << container.empty() << '\n';
	}

	std::cout << "********************* <Testing size() method.> *********************" << std::endl;
	{
		std::cout << std::boolalpha;

		ft::stack<int> container;

		std::cout << "Initially, container.size(): " << container.size() << '\n';

		for (int i = 0; i < 7; ++i)
			container.push(i);
		std::cout << "After adding elements, container.size(): " << container.size() << '\n';
	}
	return 0;
}