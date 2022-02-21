#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "include/utils.hpp"

/*		
 *		[ VECTOR ]
 *
 *			Container SEQUENCIAL que representa ponteiros que são dinamicamente alocados.
 *		Consomem mais memoria devido ao fato de gerenciar o armazenamento e crescer dinamicamente.
 *
 *		Member types
 *			value_type, allocator_type, reference, const_reference, pointer, const_pointer, iterator,
 *			const_iterator, reverse_iterator, const_reverse_iterator, difference_type, size_type.
 *		Member functions
 *			Constructors, destructor, operator=
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
		typedef ft::random_access_iterator<pointer>							iterator;
		typedef ft::random_access_iterator<const_pointer>					const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type; 
		typedef typename allocator_type::size_type							size_type;

		/*
		 *		CONSTRUCTORS (default, fill, range, copy)
		 *		DESTRUCTOR
		 *		OPERATOR=
		 */

		// Default: Constroi um container vazio com o allocator padrao.
		explicit vector(const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0), _vec(NULL){clear();};

		// Fill: Constroi um container com n elementos, cada elemento eh uma copia de val.
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n), _vec(_alloc.allocate(_capacity))
		{
			iterator it;

			it = begin();
			while (it != end())
			{
				_alloc.construct(&(*it), val);
				it++;
			}
		};

		// Range: Constroi um container com a quantidade de elementos do range (primeiro - ultimo),
		//		  cada elemento construido corresponde a ordem do range. Tem que checar se recebe
		//		  iterador ou size_t para nao confundir com o Fill.
		template <class InputIterator>
		vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(static_cast<size_type>(ft::distance(first, last))), _capacity(_size), _vec(_alloc.allocate(_capacity)) 
		{
			iterator it;

			it = begin();
			while (first != last)
			{
				_alloc.construct(&(*it), *first);
				first++;
				it++;
			}
		};

		// Copy: Faz a copia de cada elemento em x na mesma ordem.
		vector (const vector& x)
			: _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _vec(_alloc.allocate(_capacity))
		{
			iterator it = begin();
			const_iterator x2 = x.begin();
			
			while (x2 != x.end())
			{
				_alloc.construct(&(*it), *x2);
				it++;
				x2++;
			}
		};

		// Destructor: destroi todos elementos do container e desaloca toda o armazenamento alocado.
		~vector() 
		{
			clear();
			_alloc.deallocate(_vec, _capacity);
		};

		// operator=: substitui o conteudo do container pelo conteudo de x.
		vector& operator= (const vector& x)
		{
			if (this == &x)
				return (*this);
			if (x.size() >= _capacity)
			{
				clear();
				_alloc.deallocate(_vec, _capacity);
				_vec = _alloc.allocate(x._capacity);
			}
			while (_size > x._size)
				pop_back();
			_size = x._size;
			_capacity = x._capacity;
			iterator it = begin();
			const_iterator xit = x.begin();
			while (xit != x.end())
			{
				_alloc.construct(&(*it), *xit);
				it++;
				xit++;
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

		reverse_iterator rbegin()
		{ return (reverse_iterator(end())); };
		
		const_reverse_iterator rbegin() const
		{ return (const_reverse_iterator(end())); };

		reverse_iterator rend()
		{ return (reverse_iterator(begin())); };

		const_reverse_iterator rend() const
		{ return (const_reverse_iterator(begin())); };

		/*
		 *		CAPACITY (size, max_size, resize, capacity, empty, reserve)
		 */
		size_type size() const
		{ return (_size); };

		// Deve ser menor do que a quantidade de RAM disponivel.
		size_type max_size() const
		{ return (_alloc.max_size());};

		// muda o tamanho do vector
		// se n > size: realoca com size n, preenchendo com 0 ou val se especificado
		// se n < size: destroi tudo a partir de n
		void resize (size_type n, value_type val = value_type())
		{
			if (n > size())
				insert(end(), n - size(), val);
			else if (n < size())
				erase(begin() + n,end());
		};
		
		size_type capacity() const
		{ return (_capacity); };

		// true se vazio, senao false
		bool empty() const
		{ 
			if (_size != 0)
				return (false);
			return (true);
		};

		// Realoca o vector para o indicado de memoria requerida (n) mas mantem intacto seus elementos e tamanho.
		void reserve (size_type n)
		{
			if (n > _capacity)
			{
				size_type x = -1;
				pointer aux = _alloc.allocate(n);
				_capacity = n;
				while (++x < _size)
					aux[x] = _vec[x];
				_alloc.deallocate(_vec, _capacity);
				_vec = aux;
			}
		};
		
		/*
		 *		ELEMENT ACCESS (operator[], at, front, back)
		 */
		
		// operator[] Nao checa se esta fora do range
		reference operator[] (size_type n)
		{ return (*(_vec + n)); };

		const_reference operator[] (size_type n) const
		{ return (const_reference(*(_vec + n))); };
		
		// at checa se esta fora do range
		reference at (size_type n)
		{ 
			if (n >= _size)
				throw out_of_range();
			return (*(_vec + n));
		};

		const_reference at (size_type n) const
		{ 
			if (n >= _size)
				throw out_of_range();
			return (*(_vec + n));
		};


		reference front()
		{
			reference ref(*(_vec));
			return (ref);
		};

		const_reference front() const
		{
			const_reference ref(*(_vec));
			return (ref);
		};

		reference back()
		{
			reference ref(*(end() - 1));
			return (ref);
		};

		const_reference back() const
		{
			const_reference ref(*(end() - 1));
			return (ref);
		};

		/*
		 *		MODIFIERS (assign, push_back, pop_back, insert, erase, swap, clear)
		 */

		// assign: atribui novos conteudos ao vetor (substitui se necessario) e modifica o seu size de acordo.
		// assign range: troca os valores pelo range(first - last)
		template <class InputIterator>
		void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
		{
			iterator it;
			clear();
			_alloc.deallocate(_vec, _capacity);
			_size = ft::distance(first, last);
			if (_capacity < _size)
				_capacity = _size;
			_vec = _alloc.allocate(_capacity);
			it = begin();
			while (first != last)
			{
				_alloc.construct(&(*it), *first);
				it++;
				first++;
			}
		};

		// assign fill: troca os valores por val
		void assign (size_type n, const value_type& val)
		{
			iterator it;
			size_type x = -1;
			clear();
			_alloc.deallocate(_vec, _capacity);
			_size = n;
			if (_capacity < _size)
				_capacity = _size;
			_vec = _alloc.allocate(_capacity);
			it = begin();
			while (++x < n)
			{
				_alloc.construct(&(*it), val);
				it++;
			}
		};
		
		// adiciona val no fim do vector
		void push_back (const value_type& val)
		{
			//while (_capacity <= _size)
			if (_capacity < _size + 1)
				reserve(_size + 1);
			_alloc.construct(&(*end()), val);
			_size++;
		};

		// remove o ultimo elemento
		void pop_back()
		{
			_alloc.destroy(&(*end()));
			_size--;
		};

		// insere novos elementos (val) antes do elemento especificado por position e aumenta o size, retorna iterator do primeiro elemento adicionado
		// single element: apenas um elemento
		iterator insert (iterator position, const value_type& val)
		{
			difference_type	diff = begin() - position;

			while (_capacity <= _size)
				reserve(_capacity + 1);
			iterator	iter = end();
			for (; iter != begin() + diff; iter--)
			{
				_alloc.construct(&(*iter), *(iter - 1));
				_alloc.destroy(&(*(iter - 1)));
			}
			_alloc.construct(&(*iter), val);
			_size++;
			return (iter);
		};

		// fill: n elementos val
		void insert (iterator position, size_type n, const value_type& val)
		{
			if (n)
			{
				difference_type diff = begin() - position;
				if (_capacity <= _size + n)
					reserve(_size + n + 1);
				while (n--)
					insert(begin() + diff, val);
			}
		};

		// range: do first ao last
		template <class InputIterator>
		void insert(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
		{
			iterator it = end();
			size_type dist = ft::distance(first, last);
			difference_type diff = begin() - position;

			if (_capacity <= _size + dist)
				reserve(_size + dist + 1);
			dist = 0;
			while (first != last)
			{
				insert(begin() + diff + dist, *first);
				first++;
				it++;
				dist++;
			}
		};

		// Erase: remove posicao ou range do vector. Retorna o elemento que viria seguinte ao que foi apagado.
		iterator erase (iterator position)
		{
			_alloc.destroy(&(*(position)));
			iterator it = position;
			while (it != end())
			{
				_alloc.construct(&(*it), *(it + 1));
				_alloc.destroy(&(*(it + 1)));
				it++;
			}
			_size--;
			return (position);
		};

		// erase range
		iterator erase (iterator first, iterator last)
		{
			iterator it = first;
			while (it != last)
			{
				erase(it);
				last--;
			}
			return (first);
		};

		// swap: troca o vector por x e vice-versa. ambos devem ser do mesmo tipo (n precisa do alloc).
		void swap (vector& x)
		{
		size_type		aux_size = _size;
		size_type		aux_capacity = _capacity;
		pointer			aux_vec = _vec;
			_vec = x._vec;
			_capacity = x._capacity;
			_size = x._size;
			x._vec = aux_vec;
			x._capacity = aux_capacity;
			x._size = aux_size;
		};

		// clear: limpa todo vector
		void clear()
		{
			iterator it = begin();

			while (it != end())
			{
				_alloc.destroy(&(*it));
				it++;
			}
			_size = 0;
		};

		/*
		 *		ALLOCATOR
		 */
		allocator_type get_allocator() const
		{
			return (_alloc);
		};
		
	private:
		allocator_type  _alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_vec;
	};

	/*
	 *		RELATIONAL OPERATORS	
	 *		SWAP
	 */

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size()); };
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (!(lhs == rhs)); };
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (lhs < rhs || lhs == rhs); };
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); };
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (rhs < lhs || lhs == rhs); };

	// swap x por y
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{ x.swap(y); };
};

#endif
