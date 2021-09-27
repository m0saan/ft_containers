#include <iostream>
#include "Vector/vector.hpp"
#include <iterator>
#include <vector>

template<typename T>
void print(T const &xs) {
	std::cout << "[ ";
	for(auto const &x : xs) {
		std::cout << x << ' ';
	}
	std::cout << "]\n";
}
template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
	os << "{";
	for (auto const& i : co) { os << ' ' << i; }
	return os << " } ";
}

int main() {
	# if(0)
	// constructors used in the same order as described above:
	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second(4, 100);                       // four ints with value 100
	second.print();
	std::vector<int> _second(4, 100);                       // four ints with value 100
	ft::vector<int> third(_second.begin(), _second.end());  // iterating through second
	third.print();
	ft::vector<int> fourth(third);                       // a copy of third
	fourth.print();

	std::vector<int> foo(3, 0);
	std::vector<int> bar(5, 0);

	ft::vector<int> my_foo(3, 0);
	ft::vector<int> my_bar(5, 0);

	bar = foo;
	my_bar = my_foo;
	foo = std::vector<int>();
	my_foo = ft::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

	std::cout << "Size of my_foo: " << int(my_foo.size()) << '\n';
	std::cout << "Size of my_bar: " << int(my_bar.size()) << '\n';

	std::cout << "********************* Testing Iterators *********************" << std::endl;
	{
		ft::vector<int> testIter(5);

		for(int i = 0; i < 5; ++i)
			testIter[i] = i * 2;

		ft::vector<int>::iterator itFirst = testIter.begin();
		ft::vector<int>::iterator itEnd = testIter.end();
		testIter.print();
		for(; itFirst != itEnd; ++itFirst) {
			std::cout << *itFirst << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "********************* Testing size(), capacity() and max_size() *********************" << std::endl;
	{
		std::vector<int> vector;
		ft::vector<int> my_vector;

		std::cout << my_vector.size() << std::endl << my_vector.capacity() << std::endl;

		// set some content in the vector:
		for(int i = 0; i < 4; i++) {
			vector.push_back(i);
			my_vector.push_back(i);
		}

		my_vector.print();

		std::cout << "size: " << (vector.size() == my_vector.size()) << "\n"; // 100
		std::cout << "capacity: " << (vector.capacity() == my_vector.capacity()) << "\n"; // 128
		std::cout << "max_size: " << (vector.max_size() == my_vector.max_size()) << "\n"; // 1073741823
	}


	std::cout << "********************* Testing push_back() and pop_back() *********************" << std::endl;
	{
		ft::vector<int> v;
		std::vector<int> v2;
		for (int i = 0; i < 10; ++i) {
			v.push_back(10 + i);
			v2.push_back(10 + i);
		}

		std::cout << "my vector data: " << std::endl;
		print_collection(v);

		std::cout << "vector data: " << std::endl;
		print_collection(v2);

		std::cout << std::boolalpha;
		std::cout << "size: " << (v.size() == v2.size()) << "\n"; // 100
		std::cout << "capacity: " << (v.capacity() == v2.capacity()) << "\n"; // 128
		std::cout << "max_size: " << (v.max_size() == v2.max_size()) << "\n"; // 1073741823
		std::cout << '\n';
	}

	std::cout << "********************* Testing begin *********************" << std::endl;
	{
		ft::vector<int> c1;
		ft::vector<int>::iterator c1_Iter;
		ft::vector<int>::const_iterator c1_cIter;

		c1.push_back(1);
		c1.push_back(2);

		std::cout << "The vector c1 contains elements:";
		c1_Iter = c1.begin();
		for(; c1_Iter != c1.end(); c1_Iter++) {
			std::cout << " " << *c1_Iter;
		}
		std::cout << std::endl;

		std::cout << "The vector c1 now contains elements:";
		c1_Iter = c1.begin();
		*c1_Iter = 20;
		for(; c1_Iter != c1.end(); c1_Iter++) {
			std::cout << " " << *c1_Iter;
		}
		std::cout << std::endl;

		// The following line would be an error because iterator is const
		// *c1_cIter = 200;
	}
	std::cout << "********************* Testing reserve() *********************" << std::endl;
	{
		ft::vector<int>::size_type sz;

		ft::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for(int i = 0; i < 100; ++i) {
			foo.push_back(i);
			if(sz != foo.capacity()) {
				sz = foo.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}

		ft::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for(int i = 0; i < 100; ++i) {
			bar.push_back(i);
			if(sz != bar.capacity()) {
				sz = bar.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
	}

	std::vector<int> v(5);
	for(int i = 0; i < 5; ++i)
		v[i] = i + 1;

	std::vector<int>::reverse_iterator rv = (v.rbegin());
	std::cout << *(++rv) << ' '; // 3
	std::cout << *(--rv) << ' '; // 4
	std::cout << *(rv + 3) << ' '; // 1
	rv += 3;
	std::cout << rv[0] << ' '; // 1
	rv -= 3;
	std::cout << rv[0] << '\n'; // 4
	std::cout << "myvector contains:";
	for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	std::cout << "********************* Testing at() **********************"<< std::endl;
	{
		int arr[] = {1,2,4,5,5,6};
		ft::vector<int> data(arr, arr+6);

		// Set element 1
		data.at(1) = 88;

		// Read element 2
		std::cout << "Element at index 2 has value " << data.at(2) << '\n';

		std::cout << "data size = " << data.size() << '\n';

		try {
			// Set element 6
			data.at(6) = 666;
		} catch (std::out_of_range const& exc) {
			std::cout << exc.what() << '\n';
		}

		// Print final values
		std::cout << "data:";
		for (int elem : data)
			std::cout << " " << elem;
		std::cout << '\n';
	}

	std::cout << "******************** Testting operator[] **********************" << std::endl;
	{
		std::vector<int> numbers {2, 4, 6, 8};
		ft::vector<int> my_numbers (numbers.begin(), numbers.end());

		std::cout << std::boolalpha;
		std::cout << "Second element: " << (numbers[1] == my_numbers[1]) << '\n';

		numbers[0] = 5;
		my_numbers[0] = 5;

		std::cout << "All numbers:";
		int j = 0;
		std::cout << std::boolalpha;
		for (auto i : numbers) {
			std::cout << ' ' << (i == my_numbers[j++]);
		}
		std::cout << '\n';
	}

	std::cout << "****************** Testing front() and back() ************************" << std::endl;
	{
		std::vector<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
		ft::vector<char> my_letters(letters.begin(), letters.end());

		if (!letters.empty()) {
			std::cout << "The first character is '" << letters.front() << "'.\n";
			std::cout << "The last character is '" << letters.back() << "'.\n";
		}

		if (!my_letters.empty())
			std::cout << "The first character is '" << my_letters.front() << "'.\n";
		std::cout << "The last character is '" << my_letters.back() << "'.\n";
	}

	std::cout << "******************* Testing clear() *****************************" << std::endl;
	{
		std::vector<int> container{1, 2, 3};
		ft::vector<int> my_container(container.begin(), container.end());

		auto print = [](const int& n) { std::cout << " " << n; };

		std::cout << "Before clear:";
		std::for_each(container.begin(), container.end(), print);
		std::cout << "\nSize=" << container.size() << ", Capacity=" << container.capacity() << '\n';

		std::for_each(my_container.begin(), my_container.end(), print);
		std::cout << "\nSize=" << my_container.size() << ", Capacity=" << my_container.capacity() << '\n';


		std::cout << "Clear\n";
		container.clear();
		my_container.clear();

		std::cout << "After clear:";
		std::for_each(container.begin(), container.end(), print);
		std::cout << "\nSize=" << container.size() << ", Capacity=" << container.capacity() << '\n';

		std::for_each(my_container.begin(), my_container.end(), print);
		std::cout << "\nSize=" << my_container.size() << ", Capacity=" << my_container.capacity() << '\n';


	}

	std::cout << "******************* Testing pop_back() ************************* "<< std::endl;
	{
		ft::vector<Foo> numbers;

		//print(numbers);

		numbers.push_back(Foo());
		numbers.push_back(Foo());
		numbers.push_back(Foo());

		// print(numbers);
		cout << "+++++++++++++++ poping ++++++++++++++++" << endl;

		numbers.pop_back();

		cout << "size: " << numbers.size() << endl;

		// print(numbers);
	}

	{

		ft::vector<int> my_vec(10);
		std::vector<int> vec(10);

		for(int i = 0; i < 10; i++) {
			my_vec[i] = i;
			vec[i] = i;
		}
		vec.erase(vec.begin());
		my_vec.erase(my_vec.begin());
		std::cout << "vec: ";
		print(vec);
		std::cout << std::endl << "my_vec: ";
		print(my_vec);
		vec.erase(vec.begin() + 2, vec.begin() + 5);
		my_vec.erase(my_vec.begin() + 2, my_vec.begin() + 5);
		std::cout << std::endl << "vec: ";
		print(vec);
		std::cout << std::endl << "my_vec: ";
		print(my_vec);

		for (auto it = my_vec.begin(); it != my_vec.end(); ) {
			// my_vec.print();
			if (*it % 2 == 0) {
				it = my_vec.erase(it);
			} else {
				++it;
			}
		}
		print(my_vec);
	}
		#endif

	{
		ft::vector<char> characters;

		characters.assign(5, 'a');
		print(characters);

		const std::string extra(6, 'b');
		characters.assign(extra.begin(), extra.end());
		print(characters);

	}

	{
		std::vector<int> a1(3), a2(2);
		for(int i = 0; i < 3; ++i)
			a1[i] = i+1;
		for(int i = 0; i < 2; ++i)
			a2[i] = i+1;

		auto it1 = std::next(a1.begin());
		auto it2 = std::next(a2.begin());

		int& ref1 = a1.front();
		int& ref2 = a2.front();

		std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
		a1.swap(a2);
		std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

	}
}

