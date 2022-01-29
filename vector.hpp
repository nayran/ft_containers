#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "include/utils.hpp"

/*		
 *		[ VECTOR ]
 *
 *			Container sequencial que representa ponteiros que são dinamicamente alocados.
 *		Consomem mais memoria devido ao fato de gerenciar o armazenamento e crescer dinamicamente.
 *
 *		Member types
 *		Member functions
 *			Constructors, destructor, operator
 *			Iterators
 *				Begin, end, rbegin, rend
 *			Capacity
 *				Size, max_size, resize, capacity, empty, reserve
 *			Element Access
 *				Operator[], at, front, back
 *			Modifiers
 *				Assign, push_back, pop_back, insert, erase, swap, clear
 *			Allocator
 *				Get_allocator
 *		Non-member functions
 *			Relational Operators (==, !=, <, <=, >, >=)
 *
 *		https://www.cplusplus.com/reference/vector/vector/
 *		https://en.cppreference.com/w/cpp/container/vector
 */

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		/*
		 *		MEMBER TYPES
		 */
		typedef T															value_type;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef ft::random_access_iterator<pointer>						iterator;
		typedef ft::random_access_iterator<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type; 
		typedef typename allocator_type::size_type							size_type;

		/*
		 *		CONSTRUCTORS (default, fill, range, copy)
		 *		DESTRUCTOR
		 *		OPERATOR
		 */

		// Default: Constroi um container vazio com o allocator padrao.
		explicit vector(const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _size(0), _vec(NULL){}
		// Fill: Constroi um container com n elementos, cada elemento eh uma copia de val.
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n)
		{
			iterator it;

			_vec = _alloc.allocate(n);
			it = begin();
			while (it != end())
			{
				_alloc.construct(&(*it), val);
				it++;
			}
		}

		// Range: Constroi um container com a quantidade de elementos do range (primeiro - ultimo),
		//		  cada elemento construido corresponde a ordem do range. Tem que checar se recebe
		//		  iterador ou size_t para nao confundir com o Fill.
		template <class InputIterator>
		vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(static_cast<size_type>(ft::distance(first, last))), _vec(_alloc.allocate(_size)) 
		{
			iterator it;

			it = begin();
			while (first != last)
			{
				_alloc.construct(&(*it), *first);
				first++;
				it++;
			}
		}

		// Copy: Faz a copia de cada elemento em x na mesma ordem.
		vector (const vector& x)
			: _alloc(x._alloc), _size(x._size), _vec(_alloc.allocate(_size))
		{
			iterator it = begin();
			const_iterator x2 = x.begin();
			
			while (x2 != x.end())
			{
				_alloc.construct(&(*it), *x2);
				it++;
				x2++;
			}
		}

		// Destructor: destroi todos elementos do container e desaloca toda o armazenamento alocado.
		~vector() 
		{
			iterator it = begin();

			while (it != end())
			{
				_alloc.destroy(&(*it));
				it++;
			}
			_alloc.deallocate(_vec, _size);
		};

		// operator=: substitui o conteudo do container pelo conteudo de x.
		vector& operator= (const vector& x)
		{
			if (this != &x)
			{
				iterator it = begin();
				const_iterator x2 = x.begin();
				while (it != end())
				{
					_alloc.destroy(&(*it));
					it++;
				}
				_alloc.deallocate(_vec, _size);
				_alloc = x._alloc;
				_size = x._size;
				_vec = _alloc.allocate(_size);
				it = begin();
				while (x2 != x.end())
				{
					_alloc.construct(&(*it), *x2);
					it++;
					x2++;
				}
			}
			return (*this);
		};


		/*
		 *		ITERATORS (begin, end, rbegin, rend)
		 */
		iterator begin()
		{ return (iterator(_vec)); };

		const_iterator begin() const
		{ return (const_iterator(_vec)); };
		
		iterator end()
		{ return (iterator(_vec + _size)); };

		const_iterator end() const
		{ return (const_iterator(_vec + _size)); };

		/*
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;
		*/

		/*
		 *		CAPACITY (size, max_size, resize, capacity, empty, reserve)
		 *
		size_type size() const;

		size_type max_size() const;

		void resize (size_type n, value_type val = value_type());

		size_type capacity() const;

		bool empty() const;

		void reserve (size_type n);
		
		*
		 *		ELEMENT ACCESS (operator[], at, front, back)
		 *
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
		
		reference at (size_type n);
		const_reference at (size_type n) const;

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		*
		 *		MODIFIERS (assign, push_back, pop_back, insert, erase, swap, clear)
		 *
		template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);
		
		void push_back (const value_type& val);

		void pop_back();

		iterator insert (iterator position, const value_type& val);
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);

		void swap (vector& x);

		void clear();
		*/

		/*
		 *		ALLOCATOR
		 */
		allocator_type get_allocator() const
		{
			return (_alloc);
		}
		

	private:
		allocator_type  _alloc;
		size_type		_size;
		pointer			_vec;
	};

	/*
	 *		RELATIONAL OPERATORS	
	 *		SWAP
	 */
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif
