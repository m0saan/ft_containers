//
// Created by Mohammad  Boustta on 9/25/21.
//

#ifndef __PAIR_HPP__
#define __PAIR_HPP__

/**
 * std::pair is a class template that provides
 * a way to store two heterogeneous objects as a single unit.
 * @tparam T1
 * @tparam T2
 */

namespace ft {
    template<typename T1, typename T2>
    struct pair {
        pair() : first(), second() {};

        pair(const T1 &x, const T2 &y) : first(x), second(y) {}

        template<typename U, typename V>
        pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

        pair &operator=(const pair &pr) {
            if (this != &pr) {
                this->first = pr.first;
                this->second = pr.second;
            }
            return *this;
        }

        /**
         * Rational Operators
         */


        friend bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }

        friend bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
            return (lhs.first < rhs.first && lhs.second < rhs.second);
        }

        friend bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
            return (lhs.first <= rhs.first && lhs.second <= rhs.second);
        }

        friend bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
            return !(lhs < rhs);
        }

        friend bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
            return !(lhs <= rhs);
        }

        T1 first;
        T2 second;

        typedef T1 first_type;
        typedef T2 second_type;
    };

    template<typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return pair<T1, T2>(x, y);
    }

    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, pair<T1, T2> const & p) {
        os << '(' << p.first << ", " << p.second << ")";
        return os;
    }
}
#endif // __PAIR_HPP__
