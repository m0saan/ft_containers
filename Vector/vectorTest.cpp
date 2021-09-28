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
# include <iostream>
# include <iterator>
# include <ctime>
# include <iomanip>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include "Vector.hpp"


# define BLUE "\e[0;34m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[1;33m"
# define RESET "\e[0m"

# define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
# define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void) {
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

void equalOperatorTests() {
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(fill) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            std::vector<std::string> v1(1e6, "string2");
            start = get_time();
            v1.assign(1e6 + 1, "assign");
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            ualarm(diff * 1e3, 0);
            ft_v1.assign(1e6 + 1, "assign");
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<char> ft_v2;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v1.assign(20, "assign");
        ft_v1.assign(20, "assign");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s1 += ft_v1.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(10, "less");
        ft_v1.assign(10, "less");

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(20, 'h');
        ft_v2.assign(20, 'h');

        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2)
              && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
#if 0
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(range) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*-------------------------------------- time limit test -----------------------------------*/
        {
            time_t start, end, diff;
            /*------------------ std::vectors ---------------------*/
            ft::Vector<std::string> ft_v1(1e6, "string2");
            // std::vector<std::string>    v1(1e6, "string2");
            std::vector<std::string> v2(1e4, "string2");
            start = get_time();
            v2.assign(ft_v1.begin(), ft_v1.end());
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*------------------ ft::vectors ---------------------*/
            // ft::Vector<std::string>    ft_v1(1e6, "string2");
            ft::Vector<std::string> ft_v2(1e4, "string2");
            ualarm(diff * 1e3, 0);
            ft_v2.assign(ft_v1.begin(), ft_v1.end());
            ualarm(0, 0);
        }
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "less");
        std::vector<std::string> v2;
        std::vector<std::string> v3(10, "string2");
        /*------------------ std::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(20, "less");
        ft::Vector<std::string> ft_v2;
        ft::Vector<std::string> ft_v3(10, "string2");
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v3.assign(v1.begin(), v1.end());
        ft_v3.assign(v1.begin(), v1.end());

        z1 = v3.size();
        c1 = v3.capacity();
        ft_z1 = ft_v3.size();
        ft_c1 = ft_v3.capacity();
        for (size_t i = 0; i < v3.size(); ++i)
            s1 += v3.at(i);

        for (size_t i = 0; i < ft_v3.size(); ++i)
            ft_s1 += ft_v3.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(v3.begin(), v3.end());
        ft_v1.assign(ft_v3.begin(), ft_v3.end());

        z2 = v1.size();
        c2 = v1.capacity();
        ft_z2 = ft_v1.size();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(v1.begin(), v1.end());
        ft_v2.assign(ft_v1.begin(), ft_v1.end());

        z3 = v2.size();
        c3 = v2.capacity();
        ft_z3 = ft_v2.size();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2)
              && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
#endif
}

int main(void) {
     equalOperatorTests();

//    std::vector<std::string> v1(10, "string2");
//    std::vector<char> v2;
//    /*------------------ std::vectors ---------------------*/
//    ft::Vector<std::string> ft_v1(10, "string2");
//    ft::Vector<char> ft_v2;
//
//    // test for n greater than the vector capactiy
//    v1.assign(20, "assign");
//    ft_v1.assign(20, "assign");
//
//    std::cout << v1.size() << std::endl;
//    std::cout << ft_v1.size() << std::endl;
//    std::cout << v1.capacity() << std::endl;
//    std::cout << ft_v1.capacity() << std::endl;
//
//    std::cout << "v = { ";
//    for (std::string n: v1) {
//        std::cout << n << ", ";
//    }
//    std::cout << "}; \n";
//
//    std::cout << "v = { ";
//    for (std::string n: ft_v1) {
//        std::cout << n << ", ";
//    }
//    std::cout << "}; \n";
//    std::cout << v1.size() << std::endl;
//    std::cout << ft_v1.size() << std::endl;
//    std::cout << v1.capacity() << std::endl;
//    std::cout << ft_v1.capacity() << std::endl;
//
//    std::cout << "---------------------- testing reducing the vector----------------------" << std::endl;
//
//    std::cout << v1.size() << std::endl;
//    std::cout << ft_v1.size() << std::endl;
//    std::cout << v1.capacity() << std::endl;
//    std::cout << ft_v1.capacity() << std::endl;
//    v1.assign(15, "mam");
//    ft_v1.assign(15, "mam");
//
//    std::cout << "v = { ";
//    for (std::string n: v1) {
//        std::cout << n << ", ";
//    }
//    std::cout << "}; \n";
//
//    std::cout << "v = { ";
//    for (std::string n: ft_v1) {
//        std::cout << n << ", ";
//    }
//    std::cout << "}; \n";
//    std::cout << v1.size() << std::endl;
//    std::cout << ft_v1.size() << std::endl;
//    std::cout << v1.capacity() << std::endl;
//    std::cout << ft_v1.capacity() << std::endl;
    return 0;
}
