//
// Created by moboustt on 19/8/2021.
//

#include "map.hpp"
#include <vector>
#include <map>

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

class Foo
{
public:
    Foo() { std::cout << "Foo is born!" << std::endl; }
    ~Foo() { std::cout << "Foo is gone!" << std::endl; }

    int i;
};

#if 0



int main(int argc, const char **argv)
{

    // std::vector<ft::pair<char, int> > v;
    // v.push_back(ft::make_pair('a', 10));
    // v.push_back(ft::make_pair('a', 10));
    // v.push_back(ft::make_pair('a', 10));
    // v.push_back(ft::make_pair('b', 20));
    // v.push_back(ft::make_pair('b', 20));
    // v.push_back(ft::make_pair('b', 20));
    // v.push_back(ft::make_pair('c', 30));
    // v.push_back(ft::make_pair('d', 40));


    std::chrono::steady_clock::time_point _start = std::chrono::steady_clock::now();
    
    ft::map<char, int> first;
    for (int i = 0; i < 1e7; i++)
        first.insert(ft::make_pair(i, i));

    // std::cout << "first size == " << first.size() << std::endl;
    // std::cout << "first: -------------------------------------------" << std::endl;
    // for (ft::map<char, int>::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
    //     std::cout << *it << std::endl;

    std::chrono::steady_clock::time_point _end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count()
              << "[ms]" << std::endl;



    _start = std::chrono::steady_clock::now();
    
    std::map<char, int> _first;
    for (int i = 0; i < 1e7; i++)
        _first.insert(std::make_pair(i, i));

    // std::cout << "first size == " << first.size() << std::endl;
    // std::cout << "first: -------------------------------------------" << std::endl;
    // for (ft::map<char, int>::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
    //     std::cout << *it << std::endl;

    _end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count()
              << "[ms]" << std::endl;


    // std::cout << "second: -------------------------------------------" << std::endl;
    // ft::map<char, int> second(first.begin(), first.end());

    // for (ft::map<char, int>::reverse_iterator it = second.begin(); it != second.end(); ++it)
    //     std::cout << *it << std::endl;

    // std::cout << "third: -------------------------------------------" << std::endl;
    // ft::map<char, int> third(second);
    // for (ft::map<char, int>::reverse_iterator it = third.begin(); it != third.end(); ++it)
    //     std::cout << *it << std::endl;

    // ft::map<char, int, classcomp> fourth; // class as Compare
    // std::cout << "fourth: -------------------------------------------" << std::endl;
    // for (ft::map<char, int, classcomp>::reverse_iterator it = fourth.begin(); it != fourth.end(); ++it)
    //     std::cout << *it << std::endl;

    // bool (*fn_pt)(char, char) = fncomp;
    // ft::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare

    // std::cout << "fifth: -------------------------------------------" << std::endl;
    // for (ft::map<char, int, bool (*)(char, char)>::reverse_iterator it = fifth.begin(); it != fifth.end(); ++it)
    //     std::cout << *it << std::endl;

    // return 0;
}

#endif

int main()
{

    //     ft::map<char,std::string> mymap;

    //     mymap['a']="an element";
    //     mymap['b']="another element";
    //     mymap['c']=mymap['b'];

    //     std::cout << "mymap['a'] is " << mymap['a'] << '\n';
    //     std::cout << "mymap['b'] is " << mymap['b'] << '\n';
    //     std::cout << "mymap['c'] is " << mymap['c'] << '\n';
    //     std::cout << "mymap['d'] is " << mymap['d'] << '\n';

    //   std::cout << "mymap now contains " << mymap.size() << " elements.\n";
    // std::chrono::steady_clock::time_point _start = std::chrono::steady_clock::now();
    // ft::map<int, int> m;

    // for (size_t i = 0; i < 1e6; i++)
    //     m.insert(ft::make_pair(i, -1));

    // std::chrono::steady_clock::time_point _end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count()
    //           << "[ms]" << std::endl;

    // std::map<int, int> m1;

    // std::chrono::steady_clock::time_point _start = std::chrono::steady_clock::now();
    // for (size_t i = 0; i < 1e6; i++)
    //     m1.insert(std::make_pair(i, -1));
    // std::chrono::steady_clock::time_point _end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count()
    //           << "[ms]" << std::endl;

#if 0

    ft::avltree<ft::pair<int, int> > avl1;
    ft::avltree<ft::pair<int, int> > avl2;
    for (size_t i = 0; i < 10; i++)
        avl1.insert(ft::make_pair(i, -1));

    avl2 = avl1;


    std::cout << (avl1.size() == avl2.size()) << std::endl;
    std::cout << (avl1 == avl2) << std::endl;

    for ( ft::avltree<ft::pair<int, int> >::iterator it = avl1.begin(); it != avl1.end(); it++)
        std::cout << *it << std::endl;
    
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for ( ft::avltree<ft::pair<int, int> >::iterator it = avl2.begin(); it != avl1.end(); it++)
        std::cout << *it << std::endl;

#endif

    // ft::map<char, int> foo, bar;

    // foo['x'] = 100;
    // foo['y'] = 200;

    // bar['a'] = 11;
    // bar['b'] = 22;
    // bar['c'] = 33;

    // // bar = foo;
    // // foo = bar;

    // foo.swap(bar);

    // std::cout << "foo contains:\n";
    // for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';

    // std::cout << "bar contains:\n";
    // for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';
    // ft::map<char, int> mymap;
    // ft::map<char, int>::iterator it;

    // mymap['a'] = 50;
    // mymap['b'] = 100;
    // mymap['c'] = 150;
    // mymap['d'] = 200;

    // it = mymap.find('b');
    // if (it != mymap.end())
    //     mymap.erase(it);

    // // print content:
    // std::cout << "elements in mymap:" << '\n';
    // std::cout << "a => " << mymap.find('a')->second << '\n';
    // std::cout << "c => " << mymap.find('c')->second << '\n';
    // std::cout << "d => " << mymap.find('d')->second << '\n';
    // return 0;

    ft::map<char, int> mymap;
    ft::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound('b'); // itlow points to b
    itup = mymap.upper_bound('d');  // itup points to e (not d!)

    // mymap.erase(itlow, itup); // erases [itlow,itup)

      ft::map<char, int>::iterator it_low_copy, it_up_copy;

      it_low_copy = itlow;
      it_up_copy = itup;

      it_low_copy->second = -1;
      it_up_copy->second = -2;

      std::cout << * it_low_copy << std::endl;
      std::cout << * it_up_copy << std::endl;

      std::cout << * itlow << std::endl;
      std::cout << * itup << std::endl;

    // print content:
    // for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';
}