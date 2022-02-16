#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "utils.hpp"
#include "../vector.hpp"

/*
 *		[ RED BLACK TREE ]
 *		
 *			Arvore de busca binaria autobalanceavel. Cada no da arvore tem um no pai,
 *		dois nos filhos (direita e esquerda), uma key e uma cor (vermelho ou preto).
 *		A cor do no serve apenas para balanceamento da arvore durante inserts e
 *		deletes. Sempre insere os maiores a esquerda e os menores a direita.
 *
 *		A RBT tem cinco propriedades invariaveis:
 *			1. Todo no eh vermelho ou preto.
 *			2. O no raiz eh preto.
 *			3. Todo no NULL eh preto.*
 *			4. Se um no eh vermelho, ambos filhos sao pretos.
 *			5. Todo caminho da raiz ate um NULL tem o mesmo numero de nos pretos.
 *				* No NULL eh no folha, nao contem nenhuma key. Quando procuramos por
 *				uma key que nao existe na arvore, chegamos no no NULL).
 *
 *		https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
 *		https://algorithmtutor.com/Data-Structures/Tree/Binary-Search-Trees/
 */

#define RED 1
#define BLACK 0

namespace ft
{
	template <typename T>
	struct node {
		T		key;
		bool	color;
		node	*parent;
		node	*right;
		node	*left;

		node(const T & k)
				: key(k), color(1), parent(nullptr), right(nullptr), left(nullptr) {};
	};

	template <typename T>
	class rb_tree
	{

	public:
		// Member types
		typedef node<T>				node;



		// constructors (normal, copy)
		// operator=
		// destructor
		rb_tree();
		rb_tree(const rb_tree<T>& rbt);
		rb_tree<T>& operator= (const rb_tree<T>& rbt);
		~rb_tree();

		/*
		 *		Operacoes: search, minimum, maximum, predecessor, successor, insert, delete
		 */

		// SEARCH: procura uma key na arvore e retorna o no correspondente
		node search(T k);

		// MINIMUM: retorna o no com o menor valor
		node minimum(node n);

		// MAXIMUM: retorna o no com o maior valor
		node maximum(node n);

		// PREDECESSOR/SUCCESSOR: como se todas as keys estivessem em ordem crescente, o predecessor
		//						  equivale ao valor anterior e o successor ao proximo da key do no
		//						  passador por parametro.
		// predecessor
		node predecessor(node n);

		// successor 
		node successor(node n);

		// INSERT: insere a key na arvore em sua devida posicao, depois checa se violou propriedades
		bool insert(T k);

		// DELETE: remove a key da arvore, depois checa se violou propriedades
		bool delet(T k);

	private:
		node	*root;
		size_t	size;

		// limpa arvore
		void clear(node *n) const;

		/*
		 *		Manuseio da arvore: rotacao direita, rotacao esquerda e recolor.
		 */

		// Rotacao direita: faz x subir a direita e seu parent vira seu filho direito.
		//		antes		depois
		//	      y			  x
		//		 /|			 /|
		//		x			  y
		void right_rotation(node *x);

		// Rotacao esquerda: faz x ir para baixo e seu filho da direita pra cima.
		//		antes		depois
		//	      x			  y
		//		 /|			 /|
		//		  y			x
		void left_rotation(node *x);

		// Recolor: muda a cor de um no
		void recolor (node *n)
		{
			if (n->color == 0)
				n->color = 1;
			else
				n->color = 0;
		}
	};
}

#endif
