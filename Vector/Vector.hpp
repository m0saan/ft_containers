//
// Created by moboustt on 9/8/2021.
//

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>

#include "../Utility/iterator.hpp"
#include "../Utility/reverse_iterator.hpp"
#include "../Utility/enable_if.hpp"
#include "../Utility/is_integral.hpp"
#include "../Utility/iterator_traits.hpp"
#include "../Utility/choose.hpp"

#include <algorithm>

namespace ft {

    typedef ptrdiff_t difference_type;

    // Vector<T>::
    template<typename T>
    class VectorIterator : public ft::iterator<std::random_access_iterator_tag, T> {

    public:

        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;

        typedef typename ft::choose<is_const<value_type>::value, const value_type &, value_type &>::type reference;
        typedef typename ft::choose<is_const<value_type>::value, const value_type *, value_type *>::type pointer;

        /*
         * Constructor & Copy assignment operator.
         */

        explicit VectorIterator(pointer p = NULL) : _ptr(p) {}

        VectorIterator(const VectorIterator &other) { *this = other; }

        VectorIterator &operator=(const VectorIterator &other) {
            if (this != &other)
                _ptr = other._ptr;
            return *this;
        }

        operator VectorIterator<const T>() { return (VectorIterator<const T>(_ptr)); }

        /*
         * Overloaded operators
         */

        reference operator*() { return *_ptr; }

        pointer operator->() { return &(*_ptr); }

        VectorIterator &operator++() {
            _ptr++;
            return *this;
        }

        VectorIterator &operator--() {
            _ptr--;
            return *this;
        }

        // int parameter means this is postfix operator++;
        VectorIterator operator++(int) {
            VectorIterator tmp = *this;
            _ptr++;
            return tmp;
        }

        VectorIterator operator--(int) {
            VectorIterator tmp = (*this);
            operator--();
            return tmp;
        }

        VectorIterator operator+(difference_type n) const { return VectorIterator(_ptr + n); }

        VectorIterator operator-(difference_type n) const { return VectorIterator(_ptr - n); }

        VectorIterator operator+=(difference_type n) {
            _ptr += n;
            return VectorIterator(_ptr);
        }

        VectorIterator operator-=(difference_type n) {
            _ptr -= n;
            return VectorIterator(_ptr);
        }

        reference operator[](difference_type n) {
            assert(n >= 0);
            return *(_ptr + n);
        }

        template<class Iter>
        friend bool operator==(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs);

        template<class Iter>
        friend bool operator!=(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs);

        template<class Iter>

        friend bool operator<(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs);

        template<class Iter>
        friend bool operator<=(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs);

        template<class Iter>
        friend bool operator>(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs);

        template<class Iter>
        friend bool operator>=(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs);

        template<class Iter>
        friend VectorIterator operator-(difference_type n, const VectorIterator<Iter> &rhs);

        template<class Iter>
        friend VectorIterator<Iter> operator+(typename VectorIterator<Iter>::difference_type, VectorIterator<Iter>);

        template<class Iter1, class Iter2>
        friend typename VectorIterator<Iter1>::difference_type operator-(const VectorIterator<Iter1> &lhs,
                                                                         const VectorIterator<Iter2> &rhs);

        template<class Iter1, class Iter2>
        friend typename VectorIterator<Iter1>::difference_type operator+(const VectorIterator<Iter1> &lhs,
                                                                         const VectorIterator<Iter2> &rhs);

    private:
        pointer _ptr;
    };

    template<typename Iter>

    bool operator==(const VectorIterator<Iter> &lhs, const VectorIterator<Iter> &rhs) {
        return (lhs._ptr == rhs._ptr);
    }

    template<typename Iter>

    bool operator!=(const VectorIterator<Iter>
                    &lhs, const VectorIterator<Iter>
                    &rhs) {
        return !(lhs == rhs);
    }

    template<typename Iter>

    bool operator<(const VectorIterator<Iter>
                   &lhs, const VectorIterator<Iter>
                   &rhs) {
        return (lhs._ptr < rhs._ptr);
    }

    template<typename Iter>

    bool operator<=(const VectorIterator<Iter>
                    &lhs, const VectorIterator<Iter>
                    &rhs) {
        return (lhs._ptr <= rhs._ptr);
    }

    template<typename Iter>

    bool operator>(const VectorIterator<Iter>
                   &lhs, const VectorIterator<Iter>
                   &rhs) {
        return !(lhs < rhs);
    }

    template<typename Iter>

    bool operator>=(const VectorIterator<Iter>
                    &lhs, const VectorIterator<Iter>
                    &rhs) {
        return !(lhs <= rhs);
    }

    template<class Iter>
    VectorIterator<Iter> operator+(typename VectorIterator<Iter>::difference_type n, VectorIterator<Iter> rhs) {
        rhs += n;
        return rhs;
    }

    template<class Iter>
    VectorIterator<Iter> operator-(difference_type n, const VectorIterator<Iter> &rhs) {
        rhs -= n;
        return rhs;
    }

    template<class Iter1, class Iter2>
    typename VectorIterator<Iter1>::difference_type
    operator-(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return (lhs._ptr - rhs._ptr);
    }

    template<class Iter1, class Iter2>
    typename VectorIterator<Iter1>::difference_type
    operator+(const VectorIterator<Iter1> &lhs, const VectorIterator<Iter2> &rhs) {
        return (lhs._ptr + rhs._ptr);
    }


    template<typename T, typename Alloc = std::allocator<T> >
    class Vector {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef const reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef VectorIterator<T> iterator;
        typedef VectorIterator<const T> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;


        /*
         * Constructor & Destructor.
         */

        explicit Vector(const allocator_type &alloc = allocator_type()); // Default.
        explicit Vector(size_type n, const value_type &val = value_type(), // Fill
                        const allocator_type &alloc = allocator_type());

        /*
         * typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()
         */
        template<class InputIterator>
        Vector(InputIterator first, InputIterator last,        // Range
               const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                       InputIterator>::type = InputIterator());

        Vector(const Vector &x);

        ~Vector();

        size_type size() const;

        Vector &operator=(const Vector &x);

        reference operator[](difference_type n) { return *(_arr + n); }

        const reference operator[](difference_type n) const { return *(_arr + n); }
        // reference operator->() { return _arr; }

        void print();

        allocator_type get_allocator() const;

        void push_back(const T &value);

        void pop_back();

        size_type max_size() const;

        size_type capacity() const;

        bool empty() const;

        void resize(size_type n, value_type val = value_type());

        void reserve(size_type n);

        reference at(size_type pos);

        const_reference at(size_type pos) const;

        reference front();

        const_reference front() const;

        reference back();

        const_reference back() const;

        pointer data();

        void clear();

        iterator insert(iterator pos, const T &value);
        // void insert( iterator pos, size_type count, const T& value );
        // template< typename InputIt >
        //     void insert( iterator pos, InputIt first, InputIt last);

        iterator erase(iterator pos);

        iterator erase(iterator first, iterator last);

        void assign(size_type count, const T &value);

        template<typename InputIt>
        void assign(InputIt first, InputIt last);

        // void swap(Vector &other);

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        reverse_iterator rbegin();

        reverse_iterator rend();

        const_reverse_iterator rbegin() const;

        const_reverse_iterator rend() const;


    private:
        std::size_t _size;
        std::size_t _capacity;
        allocator_type _alloc;
        T *_arr;

    private:


        T *_allocate(std::allocator<T> &alloc, std::size_t n);

        void _reallocate(std::allocator<T> &alloc, std::size_t newSize);

        void _fill(std::size_t start, std::size_t end, const value_type &val);

        template<typename InputIterator>
        void _fill(InputIterator first, InputIterator last);

        void _deallocate(std::size_t start, std::size_t end, bool reset);
    };

    template<typename T, typename Alloc>
    Vector<T, Alloc>::Vector(const allocator_type &alloc) : _size(0), _capacity(0), _alloc(alloc), _arr(NULL) {}

    template<typename T, typename Alloc>
    Vector<T, Alloc>::Vector(Vector::size_type n, const value_type &val, const allocator_type &alloc)
            : _size(n), _capacity(n), _alloc(alloc) {
        _arr = _allocate(_alloc, n);
        _fill(0, _size, val);
    }

    template<typename T, typename Alloc>
    template<typename InputIterator>
    Vector<T, Alloc>::Vector(InputIterator first, InputIterator last, const allocator_type &alloc,
                             typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type)
            : _size(last - first), _capacity(last - first), _alloc(alloc) {
        _arr = _allocate(_alloc, last - first);
        _fill(first, last);
    }

    template<typename T, typename Alloc>
    T *Vector<T, Alloc>::_allocate(std::allocator<T> &alloc, std::size_t n) {
        T *arr;
        try {
            arr = alloc.allocate(n);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        return arr;
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::_fill(std::size_t start, std::size_t end, const value_type &val) {
        for (std::size_t i = start; i < end; ++i) {
            _arr[i] = val;
        }

    }

    template<typename T, typename Alloc>
    template<typename InputIterator>
    void Vector<T, Alloc>::_fill(InputIterator first, InputIterator last) {
        int i = 0;
        while (first != last)
            _arr[i++] = *(first++);
    }

    template<typename T, typename Alloc>
    Vector<T, Alloc>::~Vector() {
        _deallocate(0, _size, true);
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::print() {
        std::cout << "[ ";
        for (std::size_t i = 0; i < _size; ++i)
            std::cout << _arr[i] << ' ';
        std::cout << ']' << std::endl;
    }

    template<typename T, typename Alloc>
    Vector<T, Alloc>::Vector(const Vector &x) : _size(0), _capacity(0) {
        *this = x;
    }

    template<typename T, typename Alloc>
    Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector &x) {
        if (this != &x) {
            _deallocate(0, _size, true);
            _size = x._size;
            _capacity = x._capacity;
            _arr = _allocate(_alloc, _size);
            _fill(x._arr, x._arr + _size);
        }
        return *this;
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::allocator_type Vector<T, Alloc>::get_allocator() const {
        return _alloc;
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::_deallocate(std::size_t start, std::size_t end, bool reset) {
        if (!_size) return;
        for (std::size_t i = start; i < end; ++i)
            _alloc.destroy(&_arr[i]);
        _alloc.deallocate(_arr, _size);
        if (reset) {
            _arr = NULL;
            _size = 0;
            _capacity = 0;
        }
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::size_type Vector<T, Alloc>::size() const {
        return _size;
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::reference Vector<T, Alloc>::at(typename Vector<T, Alloc>::size_type pos) {
        if (!(pos < size()))
            throw std::out_of_range("Vector::_M_range_check: __n (which is "
                                    + std::to_string(pos)
                                    + ") >= this->size() (which is "
                                    + std::to_string(_size) + ")");
        return _arr[pos];
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::at(typename Vector<T, Alloc>::size_type pos) const {
        if (!(pos < size()))
            throw std::out_of_range("Vector::_M_range_check: __n (which is "
                                    + std::to_string(pos)
                                    + " >= this->size() (which is "
                                    + std::to_string(_size) + ")");
        return _arr[pos];
    }


    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::front() const {
        return *begin();
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::reference Vector<T, Alloc>::front() {
        return *begin();
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::reference Vector<T, Alloc>::back() {
        return *(end() - 1);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::back() const {
        return *(end() - 1);
    }


    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::pointer Vector<T, Alloc>::data() {
        return _arr;
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::clear() {
        _alloc.deallocate(_arr, _size);
        _size = 0;
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::begin() {
        return iterator(_arr);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::end() {
        return iterator(_arr + _size);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::begin() const {
        return const_iterator(_arr);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::end() const {
        return const_iterator(_arr + _size);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin() {

        return reverse_iterator(iterator(end()));
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend() {
        return reverse_iterator(iterator(begin() - 1));
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reverse_iterator Vector<T, Alloc>::rbegin() const {
        return const_reverse_iterator(const_iterator(end() - 1));;
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::const_reverse_iterator Vector<T, Alloc>::rend() const {
        return const_reverse_iterator(const_iterator(begin() - 1));
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::push_back(const value_type &value) {
        std::size_t newSize = 0;
        if (_size + 1 > _capacity) {
            newSize = std::max((std::size_t) 1, (std::size_t) 2 * _size);
            _reallocate(_alloc, newSize);
        }
        _arr[_size++] = value;
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::pop_back() {
        _alloc.destroy(&back());
        --_size;
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::size_type Vector<T, Alloc>::max_size() const {
        return _alloc.max_size();
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::size_type Vector<T, Alloc>::capacity() const {
        return _capacity;
    }

    template<typename T, typename Alloc>
    bool Vector<T, Alloc>::empty() const {
        return !_size;
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::resize(size_type n, value_type val) {
        if (n < _size) {
            _deallocate(n, _size, false);
            _size = n;
        }

        if (n > _size) {
            if (n > _capacity)
                _reallocate(_alloc, n);
            _fill(_size, n, val);
            _size = n;
        }
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::_reallocate(std::allocator<T> &alloc, std::size_t newSize) {
        value_type *other = alloc.allocate(newSize);
        for (std::size_t i = 0; i < _size; ++i)
            other[i] = _arr[i];
        _deallocate(0, size(), false);
        _arr = other;
        _capacity = newSize;
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::reserve(Vector::size_type n) { if (n > _capacity) _reallocate(_alloc, n); }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(Vector<T, Alloc>::iterator pos, const T &value) {
        std::size_t dst = pos - begin();
        if (_size + 1 >= _capacity)
            _reallocate(_alloc, std::max((std::size_t) 1, _size * 2));
        std::size_t last = _size - 1;
        for (; last > dst; --last)
            _arr[last + 1] = _arr[last];
        ++_size;
        _arr[dst] = value;
        return iterator(_arr + dst);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(Vector<T, Alloc>::iterator pos) {
        int dst = pos - begin();
        int otherDst = pos - begin();
        _alloc.destroy(&(*pos));
        int last = _size - 1;
        for (; dst < last; ++dst)
            _arr[dst] = _arr[dst + 1];
        --_size;
        return iterator(_arr + otherDst);
    }

    template<typename T, typename Alloc>
    typename Vector<T, Alloc>::iterator
    Vector<T, Alloc>::erase(typename Vector<T, Alloc>::iterator first, typename Vector<T, Alloc>::iterator last) {
        int dst = last - first;
        int from = first - begin();
        int to = last - begin();
        for (; first != last; ++first) {
            // std::cout << "deleting: " << *first << std::endl;
            _alloc.destroy(&(*first));
        }
        _size -= dst;
        dst += 1;
        while (dst-- > 0)
            _arr[from++] = _arr[to++];
        return iterator(_arr + (last - first) + 1);
    }

    template<typename T, typename Alloc>
    void Vector<T, Alloc>::assign(typename Vector<T, Alloc>::size_type count, const T &value) {
        if (count > _capacity)
            _reallocate(_alloc, count);
        _size = _capacity = count;
        _fill(0, _size, value);

    }

    template<typename T, typename Alloc>
    template<typename InputIt>
    void Vector<T, Alloc>::assign(InputIt first, InputIt last) {
        int dst = last - first;
        if (dst > _capacity) {
            _capacity = std::max((std::size_t) 1, _size * 2);
            _reallocate(_alloc, _capacity);
        }
        _fill(first, last);
        _size = dst;
    }

    // template<typename T, typename Alloc>
    // void Vector<T, Alloc>::swap(Vector &other) {
    // 	pointer beginTmp = begin();
    // 	pointer endTmp = end();}
}

#endif // __VECTOR_HPP__