#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "utils.hpp"

/*
 *		[ RED BLACK TREE ]
 *		
 *			Arvore de busca binaria autobalanceavel. Cada no da arvore tem um no pai,
 *		dois nos filhos (direita e esquerda), uma key e uma cor (vermelho ou preto).
 *		A cor do no serve apenas para balanceamento da arvore durante inserts e
 *		deletes.
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
	};

	template <typename T>
	class rb_tree
	{
	private:
		node<T>	root;
		node<T>	nn;		// Null node

	public:
		typedef node<T>			node;


		rb_tree()
		{
			nn = new node<T>;
			nn->color = BLACK;
			nn->right = nullptr;
			nn->left = nullptr;
			nn->key = 0;
			root = nn;
		};
		// Rotacao esquerda: faz x ir para baixo e seu filho da direita pra cima.
		//		antes		depois
		//	      x			  y
		//		 /|			 /|
		//		  y			x
		void left_rotation(node *x)
		{

		}


	};
}

#endif
