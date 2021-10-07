//
// Created by moboustt on 19/8/2021.
//

#include "map.hpp"
#include "map.hpp"
#include "../Utility/Algorithms.hpp"
#include "map-test-helper.hpp"
#include <vector>
#include <map>

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

using namespace std;

void showResult(bool cond)
{
    if (cond)
        std::cout << GREEN << "ok" << RESET << std::endl;
    else
        std::cout << RED << "ko" << RESET << std::endl;
}

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

bool testOperatorEqual()
{
    bool cond;
    ft::map<char, int> m_first;
    ft::map<char, int> m_second;

    std::map<char, int> first;
    std::map<char, int> second;

    m_first['x'] = 8;
    m_first['y'] = 16;
    m_first['z'] = 32;

    first['x'] = 8;
    first['y'] = 16;
    first['z'] = 32;

    second = first;                 // second now contains 3 ints
    m_second = m_first;             // second now contains 3 ints
    first = std::map<char, int>();  // and first is now empty
    m_first = ft::map<char, int>(); // and first is now empty

    cond = first.size() == m_first.size() && m_second.size() == second.size();
    return cond;
}

bool testMapConstructors()
{
    bool cond;
    std::map<char, int> first;
    ft::map<char, int> m_first;

    for (size_t i = 97; i < 110; i++)
    {
        first[i - 97] = i;
        m_first[i - 97] = i;
    }

    std::map<char, int> copy(first);
    ft::map<char, int> m_copy(m_first);

    cond = first.size() == m_first.size() && compareMaps(first.begin(), first.end(), m_first.begin(), m_first.end());

    std::map<char, int> second(first.begin(), first.end());
    ft::map<char, int> m_second(m_first.begin(), m_first.end());

    cond = cond && second.size() == m_second.size() && compareMaps(second.begin(), second.end(), m_second.begin(), m_second.end());

    std::map<char, int> third(second);
    ft::map<char, int> m_third(m_second);

    cond = cond && third.size() == m_third.size() && compareMaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    std::map<char, int, classcomp> fourth;  // class as Compare
    ft::map<char, int, classcomp> m_fourth; // class as Compare

    cond = fourth.size() == m_fourth.size() && cond && compareMaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    bool (*fn_pt)(char, char) = fncomp;
    std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    ft::map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    cond = fifth.size() == m_fifth.size() && cond && compareMaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    first = std::map<char, int>();
    m_first = ft::map<char, int>();

    cond = copy.size() == m_copy.size() && cond && compareMaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

    return cond;
}

bool testMapIterators()
{
    bool cond;

    std::map<char, int> map;
    ft::map<char, int> mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    map['b'] = 100;
    map['a'] = 200;
    map['c'] = 300;

    std::map<char, int>::iterator it = map.begin();
    std::map<char, int>::const_iterator cIt = map.begin();
    std::map<char, int>::reverse_iterator rIt = map.rbegin();
    std::map<char, int>::const_reverse_iterator cRIt = map.rbegin();
    
    ft::map<char, int>::iterator myit = mymap.begin();
    ft::map<char, int>::const_iterator mycIt = mymap.begin();
    ft::map<char, int>::reverse_iterator myrIt = mymap.rbegin();
    ft::map<char, int>::const_reverse_iterator mycRIt = mymap.rbegin();

    // test iterators contents:

    cond = (it->first == mycIt->first) && (cIt->first == mycIt->first);
    cond = cond && (rIt->first == myrIt->first) && (cRIt->first == mycRIt->first);

    it++; myit++; mycIt++; cIt++; myrIt++; rIt++; mycRIt++; cRIt++;

    cond = (it->first == mycIt->first) && (cIt->first == mycIt->first);
    cond = cond && (rIt->first == myrIt->first) && (cRIt->first == mycRIt->first);

    it--; myit--; mycIt--; cIt--; myrIt--; rIt--; mycRIt--; cRIt--;

    for (; myit != mymap.end() && it != map.end(); it++, myit++)
        if (it->first != myit->first && it->second != myit->second) cond = false;

    for (; mycIt != mymap.end() && cIt != map.end(); cIt++, mycIt++)
        if (cIt->first != mycIt->first && cIt->second != mycIt->second) cond = false;

    for (; myrIt != mymap.rend() && rIt != map.rend(); myrIt++, rIt++)
        if (rIt->first != myrIt->first && rIt->second != myrIt->second) cond = false;

    for (; mycRIt != mymap.rend() && cRIt != map.rend(); cRIt++, mycRIt++)
        if (cRIt->first != mycRIt->first && cRIt->second != mycRIt->second) cond = false;
    return cond;
}

#define TEST_CASE(fn)                                                                                                       \
    cout << GREEN << "==================================================================================" << RESET << endl; \
    cout << "   Running " << #fn << "... \t\t\t\t\t\t";                                                                     \
    showResult(fn());                                                                                                       \
    cout << GREEN << "==================================================================================" << RESET << endl

int main()
{
    TEST_CASE(testOperatorEqual);
    TEST_CASE(testMapConstructors);
    TEST_CASE(testMapIterators);
    return 0;
}
