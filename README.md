# ft_containers

In this project, I am implementing the various container types of the C++ standard template library.  
The namespace will always be ft.  
As a reminder, all of the containers are coded in C++98, so any new feature of the containers ARE NOT
implemented, but every old feature (even deprecated) is present.


#### Vector:  
(constructor) 
    Construct vector (public member function )  

(destructor)  
    Vector destructor (public member function ) 

operator= 
    Assign content (public member function )  


Iterators:  

begin 
    Return iterator to beginning (public member function )

end
    Return iterator to end (public member function )

rbegin
    Return reverse iterator to reverse beginning (public member function )

rend
    Return reverse iterator to reverse end (public member function )

cbegin
    Return const_iterator to beginning (public member function )

cend
    Return const_iterator to end (public member function )

crbegin
    Return const_reverse_iterator to reverse beginning (public member function )

crend
    Return const_reverse_iterator to reverse end (public member function )


Capacity:

size
    Return size (public member function )

max_size
    Return maximum size (public member function )

resize
    Change size (public member function )

capacity
    Return size of allocated storage capacity (public member function )

empty
    Test whether vector is empty (public member function )

reserve
    Request a change in capacity (public member function )

shrink_to_fit
    Shrink to fit (public member function )


Element access:

operator[]
    Access element (public member function )

at
    Access element (public member function )

front
    Access first element (public member function )

back
    Access last element (public member function )

data
    Access data (public member function )


Modifiers:

assign
    Assign vector content (public member function )

push_back
    Add element at the end (public member function )

pop_back
    Delete last element (public member function )

insert
    Insert elements (public member function )

erase
    Erase elements (public member function )

swap
    Swap content (public member function )

clear
    Clear content (public member function )

emplace
    Construct and insert element (public member function )

emplace_back
    Construct and insert element at the end (public member function )


Allocator:

get_allocator
    Get allocator (public member function )


### NOTES:
  - implemented containers: vector, stack, map.
  - iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical com-
pare, std::pair, std::make_pair, are reimplemented.


### - Observations : 

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

This is my implementation for the c++ containers [vector, stack, map] of the 42 cursus,  
need help:  
moboustt@student.1337.ma
