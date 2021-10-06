#pragma once

namespace ft
{
    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        {
            if (comp(*first1 , *first2))
                return true;
            if (!comp(*first1 , *first2))
                return false;
        }

        return (!comp(*first1, *last1) && !comp(*last1, *first1)) && !(!comp(*first2, *last2) && !comp(*last2, *first2));
 
    }

}