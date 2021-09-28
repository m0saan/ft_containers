#include <iostream>
#include "Vector/Vector.hpp"
#include "Map/map.hpp"
#include "Utility/AVLTree.hpp"
#include "Utility/bst.hpp"
#include <iterator>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <map>


void equalMaps(std::map<std::string, int> &orig_map, const ft::map<std::string, int> &my_map);

void test_map_constructors() {
    std::map<std::string, int> orig_map;
    ft::map<std::string, int> my_map;

    orig_map["something"] = 69;
    orig_map["anything"] = 199;
    orig_map["that thing"] = 50;

    my_map["something"] = 69;
    my_map["anything"] = 199;
    my_map["that thing"] = 50;


    std::cout << std::boolalpha;
    std::cout << "are maps sizes equal: " << (my_map.size() == orig_map.size()) << std::endl;
    std::cout << orig_map.size() << std::endl << my_map.size() << std::endl;
    equalMaps(orig_map, my_map);
    std::cout << "maps are equal" << std::endl;

    // (2) Range constructor
    std::map<std::string, int> iter(orig_map.find("anything"), orig_map.end());
    ft::map<std::string, int> my_iter(orig_map.find("anything"), orig_map.end());


    std::cout << (orig_map == iter) << std::endl;
    std::cout << (my_map == my_iter) << std::endl;


    // (3) Copy constructor
    std::map<std::string, int> copied(orig_map);
    ft::map<std::string, int> my_copied(my_map);

    std::cout << (my_map == my_copied) << std::endl;
    std::cout << (orig_map == copied) << std::endl;

}

void equalMaps(std::map<std::string, int> &orig_map, const ft::map<std::string, int> &my_map) {
    std::__1::map<std::string, int>::iterator it = orig_map.begin();
    ft::map<std::string, int>::iterator my_it = my_map.begin();
    for (; it != orig_map.end() && my_it != my_map.end(); ++it, ++my_it) {
        if (it->first != my_it->first && it->second != my_it->second) {
            std::cout << "maps are not equal" << std::endl;
            break;
        }
    }
}

int main() {
#if 0
    // constructors used in the same order as described above:
    ft::Vector<int> first;                                // empty Vector of ints
    ft::Vector<int> second(4, 100);                       // four ints with value 100
    second.print();
    std::Vector<int> _second(4, 100);                       // four ints with value 100
    ft::Vector<int> third(_second.begin(), _second.end());  // iterating through second
    third.print();
    ft::Vector<int> fourth(third);                       // a copy of third
    fourth.print();

    std::Vector<int> foo(3, 0);
    std::Vector<int> bar(5, 0);

    ft::Vector<int> my_foo(3, 0);
    ft::Vector<int> my_bar(5, 0);

    bar = foo;
    my_bar = my_foo;
    foo = std::Vector<int>();
    my_foo = ft::Vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';

    std::cout << "Size of my_foo: " << int(my_foo.size()) << '\n';
    std::cout << "Size of my_bar: " << int(my_bar.size()) << '\n';

    std::cout << "********************* Testing Iterators *********************" << std::endl;
    {
        ft::Vector<int> testIter(5);

        for(int i = 0; i < 5; ++i)
            testIter[i] = i * 2;

        ft::Vector<int>::iterator itFirst = testIter.begin();
        ft::Vector<int>::iterator itEnd = testIter.end();
        testIter.print();
        for(; itFirst != itEnd; ++itFirst) {
            std::cout << *itFirst << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "********************* Testing size(), capacity() and max_size() *********************" << std::endl;
    {
        std::Vector<int> Vector;
        ft::Vector<int> my_vector;

        std::cout << my_vector.size() << std::endl << my_vector.capacity() << std::endl;

        // set some content in the Vector:
        for(int i = 0; i < 4; i++) {
            Vector.push_back(i);
            my_vector.push_back(i);
        }

        my_vector.print();

        std::cout << "size: " << (Vector.size() == my_vector.size()) << "\n"; // 100
        std::cout << "capacity: " << (Vector.capacity() == my_vector.capacity()) << "\n"; // 128
        std::cout << "max_size: " << (Vector.max_size() == my_vector.max_size()) << "\n"; // 1073741823
    }


    std::cout << "********************* Testing push_back() and pop_back() *********************" << std::endl;
    {
        ft::Vector<int> v;
        std::Vector<int> v2;
        for (int i = 0; i < 10; ++i) {
            v.push_back(10 + i);
            v2.push_back(10 + i);
        }

        std::cout << "my Vector data: " << std::endl;
        print_collection(v);

        std::cout << "Vector data: " << std::endl;
        print_collection(v2);

        std::cout << std::boolalpha;
        std::cout << "size: " << (v.size() == v2.size()) << "\n"; // 100
        std::cout << "capacity: " << (v.capacity() == v2.capacity()) << "\n"; // 128
        std::cout << "max_size: " << (v.max_size() == v2.max_size()) << "\n"; // 1073741823
        std::cout << '\n';
    }

    std::cout << "********************* Testing begin *********************" << std::endl;
    {
        ft::Vector<int> c1;
        ft::Vector<int>::iterator c1_Iter;
        ft::Vector<int>::const_iterator c1_cIter;

        c1.push_back(1);
        c1.push_back(2);

        std::cout << "The Vector c1 contains elements:";
        c1_Iter = c1.begin();
        for(; c1_Iter != c1.end(); c1_Iter++) {
            std::cout << " " << *c1_Iter;
        }
        std::cout << std::endl;

        std::cout << "The Vector c1 now contains elements:";
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
        ft::Vector<int>::size_type sz;

        ft::Vector<int> foo;
        sz = foo.capacity();
        std::cout << "making foo grow:\n";
        for(int i = 0; i < 100; ++i) {
            foo.push_back(i);
            if(sz != foo.capacity()) {
                sz = foo.capacity();
                std::cout << "capacity changed: " << sz << '\n';
            }
        }

        ft::Vector<int> bar;
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

    std::Vector<int> v(5);
    for(int i = 0; i < 5; ++i)
        v[i] = i + 1;

    std::Vector<int>::reverse_iterator rv = (v.rbegin());
    std::cout << *(++rv) << ' '; // 3
    std::cout << *(--rv) << ' '; // 4
    std::cout << *(rv + 3) << ' '; // 1
    rv += 3;
    std::cout << rv[0] << ' '; // 1
    rv -= 3;
    std::cout << rv[0] << '\n'; // 4
    std::cout << "myvector contains:";
    for(std::Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';


    std::cout << "********************* Testing at() **********************"<< std::endl;
    {
        int arr[] = {1,2,4,5,5,6};
        ft::Vector<int> data(arr, arr+6);

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
        std::Vector<int> numbers {2, 4, 6, 8};
        ft::Vector<int> my_numbers (numbers.begin(), numbers.end());

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
        std::Vector<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
        ft::Vector<char> my_letters(letters.begin(), letters.end());

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
        std::Vector<int> container{1, 2, 3};
        ft::Vector<int> my_container(container.begin(), container.end());

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
        ft::Vector<Foo> numbers;

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

#endif


#if 0

    std::chrono::steady_clock::time_point _start = std::chrono::steady_clock::now();
    ft::map<int, std::string> map;
    for (int i = 0; i < 10; ++i) {
        map.insert(std::make_pair(i, "hei"));
    }
    std::chrono::steady_clock::time_point _end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count()
              << "[ms]" << std::endl;
    sleep(3);
    // map.getTree().inOrderTraversal();

#endif

#if 0
    ft::map<int, std::string> map;
    map.insert(std::make_pair(10, "A"));
    map.insert(std::make_pair(20, "B"));
    map.insert(std::make_pair(10, "C"));
    map.insert(std::make_pair(14, "CD"));
    map.insert(std::make_pair(1, "DE"));
    map.insert(std::make_pair(98, "EFF"));

    ft::map<int, std::string>::iterator it = map.begin();
    for (; it != map.end(); it++) {
        std::cout << '(' << it->first << " " << it->second << ')' << std::endl;
    }

#endif

    test_map_constructors();
    return 0;
}