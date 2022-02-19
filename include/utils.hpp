#ifndef UTILS_HPP
# define UTILS_HPP

#include <stdlib.h>
#include <string>
#include <iostream>
#include <memory>
#include <exception>
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

/*
 *		https://en.cppreference.com/w/cpp/container
 *		https://www.cplusplus.com/reference/stl/
 */


/*		
 *		<iterator>
 *			Iterator Classes
 *				Iterator
 *					Categoriy tags
 *					Random access iterator
 *					Reverse iterator
 *				Iterator traits
 *			Functions
 *				Advance, distance
 *			Tree Iterator*
 *
 *
 *		<algorithm>
 *			ft::equal
 *			ft::lexicographical_compare
 *
 *		<type_traits>
 *			ft::enable_if
 *			ft::is_integral
 *
 *		<vector>
 *			Member types
 *				value_type, allocator_type, reference, const_reference, pointer, const_pointer,
 *				iterator, const_iterator, reverse_iterator, const_reverse_iterator,
 *				difference_type, size_type
 *			Member functions
 *				Constructors, destructor, operator=
 *				Iterators
 *					Begin, end, rbegin, rend
 *				Capacity
 *					Size, max_size, resize, capacity, empty, reserve
 *				Element access
 *					Operator[], at, front, back
 *				Modifiers
 *					Assign, push_back, pop_back, insert, erase, swap, clear
 *				Allocator
 *					Get_allocator
 *			Non-member functions
 *				Relational Operators (==, !=, <, <=, >, >=)
 *				Swap
 *			
 *		<stack>
 *			Member types
 *				value_type, container_type, size_type
 *			Member functions
 *				Constructor, destructor
 *				Element access
 *					Top
 *				Capacity
 *					Empty, size
 *				Modifiers
 *					Push, pop
 *			Member objects
 *				Container C
 *			Non-member functions
 *				Relational Operators (==, !=, <, <=, >, >=)
 *
 *		<map>
 *			Member types
 *				key_type, mapped_type, value_type, key_compare, value_compare, allocator_type,
 *				reference, const_reference, pointer, const_pointer, iterator, const_iterator,
 *				reverse_iterator, const_reverse_iterator, difference_type, size_type
 *			Member functions
 *				Constructors, destructor, operator=
 *				Iterators
 *					Begin, end, rbegin, rend
 *				Capacity
 *					Empty, size, max_size
 *				Element access
 *					Operator[]
 *				Modifiers
 *					Insert, erase, swap, clear
 *				Observers
 *					Key_comp, value_comp
 *				Operations
 *					Find, count, lower_bound, upper_bound, equal_range
 *				Allocator
 *					Get_allocator
 *
 *		<utility>
 *			ft::pair, ft::make_pair
 *
 *		<functional>
 *			ft::binary_function, ft::less
 *
 */


class out_of_range : public std::exception {
	public:
		virtual const char* what() const throw(){
			return ("vector");
		}
};

#endif
