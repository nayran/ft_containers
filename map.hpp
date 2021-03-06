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
 *		Non-member functions
 *			Relational operators
 *			Swap
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
		typedef ft::pair<key_type, mapped_type>					value_type;
		typedef value_type										&reference;
		typedef value_type										&const_reference;
		typedef value_type										*pointer;
		typedef value_type										*const_pointer;
		typedef size_t											size_type;
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
		map (const map& x) {
			_rbt = x._rbt;
			_alloc = x._alloc;
			_comp = x._comp;};

		map& operator= (const map& x)
		{
			if (&x == this)
				return (*this);
			_alloc = x._alloc;
			_comp = x._comp;
			_rbt = x._rbt;
			return (*this);
		};

		~map() {};

		//		Iterators
		//			begin, end, rbegin, rend
		
		iterator begin()
		{ return (_rbt.begin()); };

		const_iterator begin() const
		{ return (_rbt.begin()); };

		iterator end()
		{ return (_rbt.end()); };

		const_iterator end() const
		{ return (_rbt.end()); };

		reverse_iterator rbegin()
		{ return (_rbt.rbegin()); };

		const_reverse_iterator rbegin() const
		{ return (_rbt.rbegin()); };

		reverse_iterator rend()
		{ return (_rbt.rend()); };

		const_reverse_iterator rend() const
		{ return (_rbt.rend()); };

		//		Capacity
		//			empty, size, max_size
		bool empty() const
		{
			if (_rbt.get_size() == 0)
				return (true);
			return (false);
		};

		size_type size() const
		{ return (_rbt.get_size()); };

		size_type max_size() const
		{ return (_rbt.max_size()); };
		
		//		Element Access
		//			operator[]
		mapped_type& operator[] (const key_type& k)
		{
			iterator i = find(k);
			if (i == end())
			{
				_rbt.insert(ft::make_pair(k, mapped_type()));
				i = find(k);
			}
			return (i._node->key.second);
		};
		
		//		Modifiers
		//			Insert, erase, swap, clear
		
		// Insert single
		pair<iterator,bool> insert (const value_type& val)
		{
			iterator x(_rbt.search(_rbt.get_root(), val), _rbt.get_root(), _rbt.get_nil());
			if (x != end())
				return (ft::make_pair(x, false));
			else
			{
				_rbt.insert(val);
				iterator y(_rbt.search(_rbt.get_root(), val), _rbt.get_root(), _rbt.get_nil());
				return (ft::make_pair(y, true));
			}
		};

		// Insert hint: otimiza a insercao se position aponta para o elemento que
		//				vai preceder o elemento inserido. 
		//				Position eh so uma dica(hint), nao forca a arvore a colocar
		//				nessa posicao.
		iterator insert (iterator position, const value_type& val)
		{
			_rbt.position_insert(position._node, val);
			return(iterator(_rbt.search(_rbt.get_root(), make_pair(val.first, val.second)), _rbt.get_root(), _rbt.get_nil()));
		};

		// Insert range 
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_rbt.insert(*first);
				first++;
			}
		};

		// Erase: apaga o no
		void erase (iterator position)
		{ 
			if (position._node != _rbt.get_nil())
				_rbt.del(position._node->key);
		};

		size_type erase (const key_type& k)
		{
			size_type d = 0;
			if (_rbt.search(_rbt.get_root(), ft::make_pair(k, mapped_type())) != _rbt.get_nil())
			{
				_rbt.del(ft::make_pair(k, mapped_type()));
				d = 1;
			}
			return (d);
		};

		// apaga todos menos o ultimo
		void erase (iterator first, iterator last)
		{ 
			iterator next = first; 
			while (first != last)
			{
				next++;
				_rbt.del(first._node->key);
				first = next;
			}
		};

		// Swap
		void swap (map& x)
		{
			_rbt.swap(x._rbt);
			allocator_type auxa = x._alloc;
			key_compare auxc = x._comp;
			x._alloc = _alloc;
			x._comp = _comp;
			_alloc = auxa;
			_comp = auxc;
		};
		
		// Clear
		void clear()
		{ _rbt.clear(); };

		//		Observers
		//			key_comp, value_comp
		
		// Key_comp
		key_compare key_comp() const
		{ return (_comp); };
		// Value_comp
		value_compare value_comp() const
		{ return (value_compare()); };

		//		Operations
		//			find, count, lower_bound, upper_bound, equal_range
		
		// Find
		iterator find (const key_type& k)
		{
			return (iterator(_rbt.search(_rbt.get_root(), make_pair(k, mapped_type())), _rbt.get_root(), _rbt.get_nil()));
		};

		const_iterator find (const key_type& k) const
		{
			return (const_iterator(_rbt.search(_rbt.get_root(), ft::make_pair(k, mapped_type())), _rbt.get_root(), _rbt.get_nil()));
		};

		// Count: procura por elementos equivalente a k e retorna o numero de equivalentes
		size_type count (const key_type& k) const
		{ return (_rbt.count(ft::make_pair(k, mapped_type()))); };

		// Lower_bound: retorna um iterador para o primeiro elemento que a key 
		// nao eh considerada ir antes de k (pode ser igual ou maior).
		// Usa key_comp para determinar isso.
		iterator lower_bound (const key_type& k)
		{ return (_rbt.lower_bound(ft::make_pair(k, mapped_type()))); };
		
		const_iterator lower_bound (const key_type& k) const
		{ return (_rbt.lower_bound(ft::make_pair(k, mapped_type()))); };

		// Upper_bound: elemento depois de k. sempre que key_comp voltar true
		iterator upper_bound (const key_type& k)
		{ return (_rbt.upper_bound(ft::make_pair(k, mapped_type()))); };

		const_iterator upper_bound (const key_type& k) const
		{ return (_rbt.upper_bound(ft::make_pair(k, mapped_type()))); };

		// Equal_range: retorna os limites (bounds) que tenham um equivalente de k
		//				primeiro elemento eh lower_bound, segundo eh upper_bound.
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			const_iterator lower = lower_bound(k);
			const_iterator upper = upper_bound(k);
			return (ft::make_pair(lower, upper));
		};

		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			iterator lower = lower_bound(k);
			iterator upper = upper_bound(k);
			return (ft::make_pair(lower, upper));
		};

		//		Allocator
		//			get_allocator
		allocator_type get_allocator() const
		{ return (_alloc); };

	private:
		rb_tree<value_type, value_compare>			_rbt;
		allocator_type								_alloc;
		key_compare									_comp;

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{ return (!(lhs == rhs)); };

	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{ return (!(lhs > rhs)); };

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{ return (lhs > rhs); };

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{ return (!(lhs < rhs)); };

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{ x.swap(y); };
};

#endif
