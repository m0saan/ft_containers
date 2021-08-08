#include <iostream>
#include "Utility/iterator.hpp"

#include <vector>

class MyIterator
{
	int* p;
public:
	MyIterator(int* x) : p(x) {}
	MyIterator(const MyIterator& mit) : p(mit.p) {}
	MyIterator& operator++() {++p; return *this;}
	MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
	bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
	bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
	int& operator*() {return *p;}
};


int main () {
	int numbers[]={10,20,30,40,50};
	MyIterator from(numbers);
	MyIterator until(numbers+5);
	for (MyIterator it=from; it!=until; it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	std::vector<int> v;

	v.rbegin();

	return 0;
}

