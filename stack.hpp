#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

/*		
 *		[ STACK ]
 *			
 *			ADAPTADOR de container que operam em pilha (stack), mais especificamente LIFO
 *		(Last In First Out). Stacks sao implementadas como adaptadores de container, são classes
 *		que usam um objeto encapsulado de um container especifico tornando-os um container 
 *		implicito. O container implicito pode ser qualquer um dos stds, desde que suporte as
 *		operacoes: empty, size, back, push_back e pop_back.
 *
 *		Member types
 *			value_type, container_type, size_type
 *		Member functions
 *			Constructor, destructor
 *			Element Access
 *				top
 *			Capacity
 *				empty, size
 *			Modifiers
 *				push, pop
 *		Member objects
 *			Container C
 *		Non-member functions
 *			Relational Operators (==, !=, <, <=, >, >=)
 *
 *		https://www.cplusplus.com/reference/stack/stack/
 *		https://en.cppreference.com/w/cpp/container/stack
 */

namespace ft
{
	template< class T, class Container = vector<T> >
	class stack
	{
		public:
			/*
			 *		MEMBER TYPES
			 */
			typedef T									value_type;
			typedef Container							container_type;
			typedef typename container_type::size_type	size_type;

			/*
			 *		CONSTRUCTOR, DESTRUCTOR
			 */
			explicit stack (const container_type& ctnr = container_type())
				: _ctnr(ctnr){};

			~stack(){};

			/*
			 *		ELEMENT ACCESS
			 *			top: elemento de cima da pilha (ultimo);
			 */
			value_type& top()
			{ return (_ctnr.back()); };

			const value_type& top() const
			{ return (_ctnr.back()); };

			/*
			 *		CAPACITY
			 *			empty, size	
			 */
			bool empty() const
			{ return (_ctnr.empty()); };

			size_type size() const
			{ return (_ctnr.size()); };
			
			/*
			 *		MODIFIERS
			 *			push: adiciona elemento no topo da pilha
			 *			pop: remove elemento no topo da pilha
			 */
			void push (const value_type& val)
			{ _ctnr.push_back(val); };

			void pop()
			{ _ctnr.pop_back(); };
			

		protected:
			Container _ctnr;


		// Friend function: para funcoes friend declaradas fora do escopo da classe poderem
		//					acessar conteudos privados ou protegidos. 
		// 
		// https://stackoverflow.com/questions/1787143/template-friend-function-of-a-template-class
		template <typename Type, typename Ctnr>
		friend bool operator== (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);
		template <typename Type, typename Ctnr>
		friend bool operator!= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);
		template <typename Type, typename Ctnr>
		friend bool operator<  (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);
		template <typename Type, typename Ctnr>
		friend bool operator<= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);
		template <typename Type, typename Ctnr>
		friend bool operator>  (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);
		template <typename Type, typename Ctnr>
		friend bool operator>= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

	};
	/*
	 *		RELATIONAL OPERATORS
	 *		==, !=, <, <=, >, >=
	 */
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs._ctnr == rhs._ctnr); };

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs._ctnr != rhs._ctnr); };

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs._ctnr < rhs._ctnr); };

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs._ctnr <= rhs._ctnr); };

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs._ctnr > rhs._ctnr); };

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs._ctnr >= rhs._ctnr); };
}

#endif
