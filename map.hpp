#ifndef MAP_HPP
# define MAP_HPP

#include "include/utils.hpp"
#include "include/utility.hpp"
#include "include/rb_tree.hpp"

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
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
	public:
		/*
		 *		MEMBER TYPES
		 */
		typedef T												mapped_type;
		typedef Key												key_type;
		typedef Alloc											allocator_type;
		typedef Compare											key_compare;
		typedef ft::pair<Key, T>								value_type;
		typedef value_type										&reference;
		typedef value_type										&const_reference;
		typedef value_type										*pointer;
		typedef value_type										*const_pointer;
		typedef size_t											size_type;
		typedef s_node<value_type>								node;
		typedef node											*node_pointer;
		class value_compare
		: public std::binary_function<value_type, value_type, bool>
		{
			public:
				key_compare	comp;
				value_compare(key_compare c = key_compare()) : comp(c) {}
				bool operator()(const value_type& x, const value_type& y) const
				{ return (comp(x.first, y.first)); }
		};
		typedef typename rb_tree<value_type, value_compare>::iterator					iterator;
		typedef typename rb_tree<value_type, value_compare>::const_iterator				const_iterator;
		typedef typename rb_tree<value_type, value_compare>::reverse_iterator			reverse_iterator;
		typedef typename rb_tree<value_type, value_compare>::const_reverse_iterator		const_reverse_iterator;

		/*
		 *		Constructors (empty, range, copy)
		 *		Destructor
		 *		Operator=
		 */
		// Empty: container vazio
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _rbt(), _alloc(alloc), _comp(comp) {};

		// Range: constroi um container igual ao range (inicio - final)
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _rbt(), _alloc(alloc), _comp(comp)
		{ insert(first, last); };

		// Copy: faz a copia de x
		map (const map& x)
		: _rbt(rb_tree<value_type, value_compare>(x._rbt)) {};

		/*
		map& operator= (const map& x);
		*/

		~map() {};

		//		Iterators
		//			begin, end, rbegin, rend
		
		iterator begin()
		{ return (_rbt.get_root()); };

		const_iterator begin() const
		{ return (_rbt.get_root()); };

		iterator end()
		{ return (_rbt.get_nil()); };

		const_iterator end() const
		{ return (_rbt.get_nil()); };

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//		Capacity
		//			empty, size, max_size
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		
		//		Element Access
		//			operator[]
		mapped_type& operator[] (const key_type& k)
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(k, mapped_type());
			node_pointer n = _rbt.search(_rbt.get_root(), p);
			if (n != _rbt.get_nil())
				return (n->key.second);
			else
				return (insert(p).first._node->key.second);
		};
		
		//		Modifiers
		//			Insert, erase, swap, clear
		
		// Insert single
		pair<iterator,bool> insert (const value_type& val)
		{
			node_pointer i = _rbt.s_node(val);
			_rbt.insert(_rbt.get_root(), val);
			ft::pair<iterator, bool> x = _rbt.search(_rbt.get_root(), val);
			if (!x.second)
				return(ft::make_pair(iterator(x.first, _rbt.get_root(), _rbt.get_nil()), true));
			else
			{
				_rbt._size++;
				if (i->parent == _rbt._nil)
					i->color = BLACK;
				else
					_rbt.recolor_insert(i);
				_rbt._root = i;
				while (i->parent != _rbt.get_nil())
					i = i->parent;
				return (ft::make_pair(iterator(i, _rbt.get_root(), _rbt.get_nil()), true));
			}

		};
		// Insert hint
		iterator insert (iterator position, const value_type& val);
		// Insert range 
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_rbt.insert(first);
				first++;
			}
		};
		// Erase
		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		// Swap
		void swap (map& x);
		// Clear
		void clear();

		//		Observers
		//			key_comp, value_comp
		
		// Key_comp
		key_compare key_comp() const;
		// Value_comp
		value_compare value_comp() const;

		//		Operations
		//			find, count, lower_bound, upper_bound, equal_range
		
		// Find
		iterator find (const key_type& k);
			//return (_rbt.search(_rbt._root, k));
		const_iterator find (const key_type& k) const;
		//	return (_rbt.search(_rbt._root, k));
		
		// Count
		size_type count (const key_type& k) const;
		// Lower_bound
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		// Upper_bound
		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;
		// Equal_range
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);
		
		//		Allocator
		//			get_allocator
		allocator_type get_allocator() const
		{ return (_alloc); };

	private:
		rb_tree<value_type, value_compare>			_rbt;
		allocator_type								_alloc;
		key_compare									_comp;

	};
};

#endif
