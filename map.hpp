#ifndef MAP_HPP
# define MAP_HPP

#include "include/utils.hpp"
#include "include/utility.hpp"
#include "include/rb_tree.hpp"
#include <functional>

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
	template < class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
	public:
		/*
		 *		MEMBER TYPES
		 */
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef std::pair<const Key, T>							value_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		class value_compare
		: public std::binary_function<value_type, value_type, bool>
		{
			public:
				key_compare	comp;
				value_compare(key_compare c = key_compare()) : comp(c) {}
				bool operator()(const value_type& x, const value_type& y) const
				{ return (comp(x.first, y.first)); }
		};

		rb_tree<int> rbt;
		/*
		 *		Constructors (empty, range, copy)
		 *		Destructor
		 *		Operator=
		// Empty: container vazio
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		{};

		// Range: constroi um container igual ao range (inicio - final)
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
		{};

		// Copy: faz a copia de x
		map (const map& x);

		~map();
		map& operator= (const map& x);

		 */
	};
};

#endif
