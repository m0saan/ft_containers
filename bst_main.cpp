//
// Created by Mohammad  Boustta on 9/25/21.
//

#include "Utility/AVLTree.hpp"
#include "Utility/pair.hpp"
#include <string>
#include <map>

#define TestPair 0

int main() {


#if TestPair
    std::cout << "*------------------- Testing pair -------------------*" << std::endl;
    ft::pair <std::string,double> product1;                     // default constructor
    ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
    ft::pair <std::string,double> product3 (product2);          // copy constructor

    product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

    product2.first = "shoes";                  // the type of first is string
    product2.second = 39.90;                   // the type of second is double

    std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
    std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
    std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    ft::pair <std::string,int> planet, homeplanet;

    planet = ft::make_pair("Earth",6371);

    homeplanet = planet;

    std::cout << "Home planet: " << homeplanet.first << '\n';
    std::cout << "Planet size: " << homeplanet.second << '\n';

    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    ft::pair<int,char> foo (10,'z');
    ft::pair<int,char> bar (90,'a');

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";


    ft::pair <int,int> fooo;
    ft::pair <int,int> barr;

    fooo = ft::make_pair (10,20);
    barr = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

    std::cout << "fooo: " << fooo.first << ", " << fooo.second << '\n';
    std::cout << "barr: " << barr.first << ", " << barr.second << '\n';

#endif


    ft::AVLTree<ft::pair<int, int>, std::greater<int> > avlTree;

    for (int i = 1; i < 4; ++i)
        avlTree.insert(ft::make_pair(i, i * 2));

    avlTree.remove(ft::make_pair(3, 6));

    avlTree.inOrderTraversal();

    return 0;
}