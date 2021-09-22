/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   Vector_test.cpp                                   :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: mamoussa <mamoussa@student.1337.ma>           +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2021/07/10 19:43:45 by mamoussa        #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2021/07/10 19:43:45 by mamoussa     ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include <vector>
#include <iostream>
#include <iterator>
#include "vector.hpp"


# define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

void    iterator_tests()
{
	std::cout << "\033[1;37m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
	/*------------ std::vector ---------*/
	std::vector<int> v(3,4);
	std::vector<int>::iterator it,it1;
	it = v.begin();
	it1 = v.begin() + 1;
	/*----------------------------------*/
	/*------------ ft::Vector ---------*/
	ft::vector<int>    my_v(3,4);
	ft::vector<int>::iterator my_it, my_it1, tmp;
	my_it = my_v.begin();
	my_it1 = my_v.begin() + 1;
	/*----------------------------------*/
	std::cout << "\033[1;37m[------------------ [ copy constructor  ] ----------------]\t\t\t\t\033[0m";
	{
		ft::vector<int>::iterator ob(my_it);
		EQUAL(&(*my_it) == &(*ob));
	}
	std::cout << "\033[1;37m[---------- [ iterator to const_iterator  ] --------------]\t\t\t\t\033[0m";
	{
		ft::vector<int>::const_iterator c_it, c_ob(my_it);
		c_it = my_it;
		EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
	}
	std::cout << "\033[1;37m[--------------------- [ == operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it == it1) == (my_it == my_it1));
	std::cout << "\033[1;37m[--------------------- [ != operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it != it1) == (my_it != my_it1));
	std::cout << "\033[1;37m[---------------------- [ > operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it > it1) == (my_it > my_it1));
	std::cout << "\033[1;37m[--------------------- [ >= operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it >= it1) == (my_it >= my_it1));
	std::cout << "\033[1;37m[---------------------- [ < operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it < it1) == (my_it < my_it1));
	std::cout << "\033[1;37m[--------------------- [ <= operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it <= it1) == (my_it <= my_it1));
	std::cout << "\033[1;37m[---------------------- [ * operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(((*my_it = 6) == 6) && (*my_it == *(my_v.begin())));
	std::cout << "\033[1;37m[--------------------- [ -> operator ] -------------------]\t\t\t\t\033[0m";
	{
		/*--------------- std::vector-------------------- */
		std::vector<std::string>    v(3, "hello");
		std::vector<std::string>::iterator it = v.begin();
		/*---------------------------------------------- */
		// std::cout << it->length() << std::endl;
		// exit(0);
		/*--------------- ft::vector-------------------- */
		ft::vector<std::string>    my_v(3, "hello");
		ft::vector<std::string>::iterator my_it = my_v.begin();
		/*---------------------------------------------- */
		EQUAL(it->length() == my_it->length());
	}
	std::cout << "\033[1;37m[---------------------- [ - operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(&(*my_it) == &(*(my_it1 - 1)));
	std::cout << "\033[1;37m[--------------------- [ += operator ] -------------------]\t\t\t\t\033[0m";
	my_it += 1;
	EQUAL(&(*my_it) == &(*my_it1));
	std::cout << "\033[1;37m[--------------------- [ -= operator ] -------------------]\t\t\t\t\033[0m";
	my_it -= 1;
	EQUAL(&(*my_it) == &(*(my_it1 - 1)));
	std::cout << "\033[1;37m[--------------------- [ [] operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(((my_it[0] = 5) == 5) && (*my_it == 5));
	std::cout << "\033[1;37m[------------------- [ ++it operator ] -------------------]\t\t\t\t\033[0m";
	++my_it; // I incremented here to make sure that the object changes
	EQUAL(&(*my_it) == &(*my_it1));
	std::cout << "\033[1;37m[------------------- [ --it operator ] -------------------]\t\t\t\t\033[0m";
	--my_it; // I decremented here to make sure that the object changes
	EQUAL(&(*my_it) == &(*(my_it1 - 1)));
	std::cout << "\033[1;37m[---------------- [ + operator (n + it) ] ----------------]\t\t\t\t\033[0m";
	EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
	std::cout << "\033[1;37m[--------------- [ - operator (it1 - it) ] ---------------]\t\t\t\t\033[0m";
	EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
	std::cout << "\033[1;37m[------------------- [ it++ operator ] -------------------]\t\t\t\t\033[0m";
	tmp = my_it++;
	EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
	std::cout << "\033[1;37m[------------------- [ it-- operator ] -------------------]\t\t\t\t\033[0m";
	tmp = my_it--;
	EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
	std::cout << "\033[1;37m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void    const_iterator_tests(void)
{
	std::cout << "\033[1;37m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Vector const_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
	/*------------ std::vector ---------*/
	std::vector<int> v(3,4);
	std::vector<int>::const_iterator it,it1;
	it = v.begin();
	it1 = v.begin() + 1;
	/*----------------------------------*/
	/*------------ ft::Vector ---------*/
	ft::vector<int>    my_v(3,4);
	ft::vector<int>::const_iterator my_it,my_it1, tmp;
	my_it = my_v.begin();
	my_it1 = my_v.begin() + 1;
	/*----------------------------------*/
	std::cout << "\033[1;37m[------------------ [ copy constructor  ] ----------------]\t\t\t\t\033[0m";
	{
		ft::vector<int>::const_iterator ob(my_it);
		EQUAL(&(*my_it) == &(*ob));
	}
	std::cout << "\033[1;37m[--------------------- [ == operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it == it1) == (my_it == my_it1));
	std::cout << "\033[1;37m[--------------------- [ != operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it != it1) == (my_it != my_it1));
	std::cout << "\033[1;37m[---------------------- [ > operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it > it1) == (my_it > my_it1));
	std::cout << "\033[1;37m[--------------------- [ >= operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it >= it1) == (my_it >= my_it1));
	std::cout << "\033[1;37m[---------------------- [ < operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it < it1) == (my_it < my_it1));
	std::cout << "\033[1;37m[--------------------- [ <= operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((it <= it1) == (my_it <= my_it1));
	std::cout << "\033[1;37m[---------------------- [ * operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(*my_it == *(my_v.begin()) && (&(*my_it) == &(*(my_v.begin()))));
	std::cout << "\033[1;37m[--------------------- [ -> operator ] -------------------]\t\t\t\t\033[0m";
	{
		/*--------------- std::vector-------------------- */
		std::vector<std::string>    v(3, "hello");
		std::vector<std::string>::const_iterator it = v.begin();
		/*---------------------------------------------- */
		/*--------------- ft::vector-------------------- */
		ft::vector<std::string>    my_v(3, "hello");
		ft::vector<std::string>::const_iterator my_it = my_v.begin();
		/*---------------------------------------------- */
		EQUAL(it->length() == my_it->length());
	}
	std::cout << "\033[1;37m[---------------------- [ - operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(&(*my_it) == &(*(my_it1 - 1)));
	std::cout << "\033[1;37m[--------------------- [ += operator ] -------------------]\t\t\t\t\033[0m";
	my_it += 1;
	EQUAL(&(*my_it) == &(*my_it1));
	std::cout << "\033[1;37m[--------------------- [ -= operator ] -------------------]\t\t\t\t\033[0m";
	my_it -= 1;
	EQUAL(&(*my_it) == &(*(my_it1 - 1)));
	std::cout << "\033[1;37m[--------------------- [ [] operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((my_it[0] == *(my_v.begin())) && (&(my_it[0]) == &(*(my_v.begin()))));
	std::cout << "\033[1;37m[------------------- [ ++it operator ] -------------------]\t\t\t\t\033[0m";
	++my_it; // I incremented here to make sure that the object changes
	EQUAL(&(*my_it) == &(*my_it1));
	std::cout << "\033[1;37m[------------------- [ --it operator ] -------------------]\t\t\t\t\033[0m";
	--my_it; // I decremented here to make sure that the object changes
	EQUAL(&(*my_it) == &(*(my_it1 - 1)));
	std::cout << "\033[1;37m[---------------- [ + operator (n + it) ] ----------------]\t\t\t\t\033[0m";
	EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
	std::cout << "\033[1;37m[--------------- [ - operator (it1 - it) ] ---------------]\t\t\t\t\033[0m";
	EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
	std::cout << "\033[1;37m[------------------- [ it++ operator ] -------------------]\t\t\t\t\033[0m";
	tmp = my_it++;
	EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
	std::cout << "\033[1;37m[------------------- [ it-- operator ] -------------------]\t\t\t\t\033[0m";
	tmp = my_it--;
	EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
	std::cout << "\033[1;37m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

#if 1
void    reverse_iterator_tests(void)
{
	std::cout << "\033[1;37m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
	/*------------ std::reverse_iterator ---------*/
	std::vector<int> v(3,4);
	std::reverse_iterator<std::vector<int>::iterator> rit(v.end()), rit_1(v.end() - 1);
	/*----------------------------------*/
	/*------------ ft::reverse_iterator ---------*/
	ft::reverse_iterator<std::vector<int>::iterator> my_rit(v.end()), my_rit1(v.end() - 1);
	/*----------------------------------*/
	std::cout << "\033[1;37m[------------------ [ copy constructor  ] ----------------]\t\t\t\t\033[0m";
	{
		ft::reverse_iterator<std::vector<int>::iterator> ob(my_rit);
		EQUAL(&(*my_rit) == &(*ob));
	}
	std::cout << "\033[1;37m[------------------ [  base function  ] ----------------]\t\t\t\t\033[0m";
	EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
	std::cout << "\033[1;37m[--------------------- [ == operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((rit == rit_1) == (my_rit == my_rit1));
	std::cout << "\033[1;37m[--------------------- [ != operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((rit != rit_1) == (my_rit != my_rit1));
	std::cout << "\033[1;37m[---------------------- [ > operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((rit > rit_1) == (my_rit > my_rit1));
	std::cout << "\033[1;37m[--------------------- [ >= operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
	std::cout << "\033[1;37m[---------------------- [ < operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((rit < rit_1) == (my_rit < my_rit1));
	std::cout << "\033[1;37m[--------------------- [ <= operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
	std::cout << "\033[1;37m[---------------------- [ * operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(((*my_rit == *(v.end() - 1)) && (&(*my_rit) == &(*(v.end() - 1))))
		  && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
	std::cout << "\033[1;37m[--------------------- [ -> operator ] -------------------]\t\t\t\t\033[0m";
	{
		std::vector<std::string> v(3, "hello");
		std::reverse_iterator<std::vector<std::string>::iterator> rit(v.end());
		ft::reverse_iterator<std::vector<std::string>::iterator> my_rit(v.end());
		EQUAL(rit->length() == my_rit->length());
	}
	std::cout << "\033[1;37m[---------------------- [ - operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
	std::cout << "\033[1;37m[---------------------- [ + operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
	std::cout << "\033[1;37m[--------------------- [ += operator ] -------------------]\t\t\t\t\033[0m";
	my_rit += 1;
	rit += 1;
	EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
	std::cout << "\033[1;37m[--------------------- [ -= operator ] -------------------]\t\t\t\t\033[0m";
	my_rit -= 1;
	rit -= 1;
	EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
	std::cout << "\033[1;37m[--------------------- [ [] operator ] -------------------]\t\t\t\t\033[0m";
	EQUAL(((my_rit[0] = 5) == 5) && (rit[0] == 5));
	std::cout << "\033[1;37m[------------------- [ ++rit operator ] -------------------]\t\t\t\t\033[0m";
	++my_rit; // I incremented here to make sure that the object changes
	++rit;
	EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
	std::cout << "\033[1;37m[------------------- [ --rit operator ] -------------------]\t\t\t\t\033[0m";
	--my_rit; // I incremented here to make sure that the object changes
	--rit;
	EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
	std::cout << "\033[1;37m[---------------- [ + operator (n + rit) ] ----------------]\t\t\t\t\033[0m";
	EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
	std::cout << "\033[1;37m[--------------- [ - operator (rit1 - rit) ] ---------------]\t\t\t\t\033[0m";
	EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
	std::cout << "\033[1;37m[------------------- [ it++ operator ] -------------------]\t\t\t\t\033[0m";
	{
		std::reverse_iterator<std::vector<int>::iterator>   tmp(rit++);
		ft::reverse_iterator<std::vector<int>::iterator>    my_tmp(my_rit++);
		EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
	}
	std::cout << "\033[1;37m[------------------- [ it-- operator ] -------------------]\t\t\t\t\033[0m";
	{
		std::reverse_iterator<std::vector<int>::iterator>   tmp(rit--);
		ft::reverse_iterator<std::vector<int>::iterator>    my_tmp(my_rit--);
		EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
	}
	std::cout << "\033[1;37m[------------------- [ *it++ test ] -------------------]\t\t\t\t\033[0m";
	{
		std::vector<char> v(10);
		std::string res, my_res;
		std::reverse_iterator<std::vector<char>::iterator> start(v.end()), end(v.begin());
		ft::reverse_iterator<std::vector<char>::iterator> my_start(v.end()), my_end(v.begin());

		for(size_t i = 0; i < 10; ++i)
			v[i] = '0' + i;
		while (start != end)
			res.push_back(*start++);
		while (my_start != my_end)
			my_res.push_back(*my_start++);
		EQUAL(res == my_res);
	}
	std::cout << "\033[1;37m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}
#endif

void vector_tests(void)
{
	std::cout << "\033[1;37m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
	std::cout << "\033[1;37m[------------------- [ fill and range constructor ] -------------------]\t\t\t\t\033[0m";
	// code
	std::cout << "\033[1;37m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

int main(void)
{
	iterator_tests();
	const_iterator_tests();
	reverse_iterator_tests();
	vector_tests();
	return 0;
}