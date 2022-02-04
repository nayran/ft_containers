#ifndef UTILS_HPP
# define UTILS_HPP

#include <deque>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <memory>
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
 *				value_type, allocator_type, reference, const_reference, pointer,
 *				const_pointer, iterator, const_iterator, reverse_iterator,
 *				const_reverse_iterator, difference_type, size_type.
 *			Member functions
 *				Constructors, destructor, operator=
 *				Iterators
 *					Begin, end, rbegin, rend
 *				Capacity
 *					Size, max_size, resize, capacity, empty, reserve
 *				Element Access
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
 *				Element Access
 *					top
 *				Capacity
 *					empty, size
 *				Modifiers
 *					push, pop
 *			Member objects
 *				Container C
 *			Non-member functions
 *				Relational Operators (==, !=, <, <=, >, >=)
 *
 *		<map>
 *
 *		<utility>
 *			ft::pair, ft::make_pair
 *
 */

class out_of_range : public std::exception {
	public:
		virtual const char* what() const throw(){
			return ("Out of range");
		}
};

#endif
