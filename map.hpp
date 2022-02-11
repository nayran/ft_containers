#ifndef MAP_HPP
# define MAP_HPP

#include "include/utils.hpp"

/*		
 *		[ MAP ]
 *
 *			Container ASSOCIATIVO que armazena elementos formados por uma combinacao de um key value
 *		e um mapped value, seguindo uma ordem especifica. Key values sao usados para sortear e
 *		unicamente identificar os elementos, enquanto mapped values guardam o conteudo associado
 *		a essa key. Key e mapped sao agrupadas em value_type por um pair. Map sao implementadas
 *		como binary search trees.
 *
 *		Member types
 *			key_type, mapped_type, value_type, key_compare, value_compare, allocator_type,
 *			reference, const_reference, pointer, const_pointer, iterator, const_iterator,
 *			reverse_iterator, const_reverse_iterator, difference_type, size_type
 *		Member functions
 *			Constructors, destructor, operator=
 *			Iterators
 *				Begin, end, rbegin, rend
 *			Capacity
 *				Empty, size, max_size
 *			Element access
 *				Operator[]
 *			Modifiers
 *				Insert, erase, swap, clear
 *			Observers
 *				Key_comp, value_comp
 *			Operations
 *				Find, count, lower_bound, upper_bound, equal_range
 *			Allocator
 *				Get_allocator
 *
 *		https://www.cplusplus.com/reference/map/map/
 *		https://en.cppreference.com/w/cpp/container/vector
 */

namespace ft
{
	/*
	template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> > >
	class map
	{

	};
	*/
};

#endif
