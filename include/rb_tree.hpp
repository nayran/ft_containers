#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include "utils.hpp"
#include "functional.hpp"
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
	/*
	 *		NODE STRUCT
	 */
	template <typename T>
	struct s_node {
		T		key;
		bool	color;
		s_node	*parent;
		s_node	*right;
		s_node	*left;

		s_node(const T & k)
		: key(k), color(1), parent(nullptr), right(nullptr), left(nullptr){};
	};

	template <class T, class Compare, class Alloc = std::allocator<s_node<T> > >
	class rb_tree
	{

	public:
		// Member types
		typedef T				value_type;
		typedef Alloc			allocator_type;
		typedef Compare			compare;
		typedef s_node<T>		node;
		typedef size_t			size_type;
		typedef node			*node_pointer;
		

		// constructors (normal, copy)
		
		rb_tree(const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, value_type());
			_nil->parent = _nil;
			_nil->right = _nil;
			_nil->left = _nil;
			_nil->color = BLACK;
			_size = 0;
			_root = _nil;
		};

		rb_tree(rb_tree const &rbt)
		{
			_alloc = rbt._alloc;
			_nil = rbt._nil;
			_size = rbt._size;
			copy(*this, rbt._root, rbt._nil);
		}

		// destructor
		~rb_tree()
		{
			clear(_root);
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		};

		// operator=
		rb_tree &operator=(rb_tree const &rbt)
		{
			clear();
			copy(*this, rbt._root, rbt._nil);
			return (*this);
		};

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
		node_pointer predecessor(node_pointer n);

		// successor 
		node_pointer successor(node_pointer n);


		// fix_insert: arruma as cores da arvore
		// MELHORAR CODIGO
		// MELHORAR CODIGO
		// MELHORAR CODIGO
		// MELHORAR CODIGO
		// MELHORAR CODIGO
		void fix_insert(node_pointer n)
		{
			node_pointer uncle;
			while (n->parent->color == RED)
			{
				// checa se esta do lado direito do no vo 
				if (n->parent == n->parent->parent->right)
				{
					uncle = n->parent->parent->left;
					// se a cor do pai e do tio forem vermelhas, viram pretos e o vo vira vermelho
					// se o no vo for root nao pode virar vermelho
					if (uncle->color == RED)
					{
						uncle->color = BLACK;
						n->parent->color = BLACK;
						if (n->parent->parent != _root)
							n->parent->parent->color = RED;
						n = n->parent->parent;
					}
					else
					{
						// se esta do lado esquerdo do pai, gira para a direita convertendo no caso
						// acima, bastando aplicar os mesmos principios
						if (n == n->parent->left)
						{
							n = n->parent;
							right_rotation(n);
						}
						n->parent->color = BLACK;
						if (n->parent->parent != _root)
							n->parent->parent->color = RED;
						left_rotation(n->parent->parent);
					}
				}
				else
				{
					uncle = n->parent->parent->right;
					// mesmo caso que para a esquerda
					if (uncle->color == RED)
					{
						uncle->color = BLACK;
						n->parent->color = BLACK;
						if (n->parent->parent != _root)
							n->parent->parent->color = RED;
						n = n->parent->parent;
					}
					else
					{
						// mesmo caso da esquerda mas muda as rotacoes
						if (n == n->parent->right)
						{
							n = n->parent;
							left_rotation(n);
						}
						n->parent->color = BLACK;
						if (n->parent->parent != _root)
							n->parent->parent->color = RED;
						right_rotation(n->parent->parent);
					}
				}
				if (n == _root)
					break;
			}
			_root->color = BLACK;
		}

		// INSERT: insere a key na arvore em sua devida posicao, depois checa se violou propriedades
		//		   novo no deve ser vermelho
		void insert(T k)
		{
			node_pointer aux = _alloc.allocate(1);
			aux->parent = nullptr;
			aux->key = k;
			aux->left = _nil;
			aux->right = _nil;
			aux->color = RED;

			node_pointer y = nullptr;
			node_pointer x = _root;
			// navega x ate uma folha e deixa y como pai de x
			while (x != _nil)
			{
				y = x;
				if (aux->key < x->key)
					x = x->left;
				else
					x = x->right;
			}
			// adiciona o no criado na posicao correta
			aux->parent = y;
			if (y == nullptr)
				_root = aux;
			else if (aux->key < y->key)
				y->left = aux;
			else
				y->right = aux;
			// se o no criado for root (nao tiver pai), ele esta na posicao certa mas o root
			// sempre eh preto se o avo for o root, ele esta correto. Para outras excecoes
			// a arvore deve ser consertada.
			if (aux->parent == nullptr)
				aux->color = BLACK;
			else if (!(aux->parent->parent == nullptr))
				fix_insert(aux);
		};

		// DELETE: remove a key da arvore, depois checa se violou propriedades
		bool delet(T k);

		size_t get_size()
		{ return (_size); };



		void printHelper(node_pointer root, std::string indent, bool last)
		{
		// print the tree structure on the screen
			if (root != _nil)
			{
				std::cout<<indent;
				if (last)
				{
					std::cout<<"R----";
					indent += "     ";
				}
				else
				{
					std::cout<<"L----";
					indent += "|    ";
				}
				std::string sColor = root->color?"RED":"BLACK";
				std::cout<<root->key<<"("<<sColor<<")"<<std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		// cout<<root->left->data<<endl;
		}
		void print()
		{
			if (_root)
				printHelper(this->_root, "", true);
		}


	private:
		allocator_type	_alloc;
		node_pointer	_root;
		node_pointer	_nil;
		size_type		_size;
		compare			_compare;

		// copia recursiva
		void copy(rb_tree &rbt, node_pointer n, node_pointer nil)
		{
			if (n != nil)
			{
				copy(rbt, n->left, nil);
				rbt.insert(n->key);
				copy(rbt, n->right, nil);
			}
		};
		// limpa arvore
		void clear(node_pointer n)
		{
			if (n != _nil)
			{
				//_size--;
				clear(n->left);
				clear(n->right);
				if (n)
				{
					_alloc.destroy(n);
					_alloc.deallocate(n, 1);
				}
			}
		};

		/*
		 *		Manuseio da arvore: rotacao direita, rotacao esquerda e recolor.
		 */

		// Rotacao direita: faz x descer a direita e seu filho esquerdo vira seu pai.
		//		antes		depois
		//	      y			  x
		//		 /|			 /|
		//		x			  y
		void right_rotation(node_pointer x)
		{
			node_pointer y = x->left;
			// puxa a direita do y para a esquerda do x
			x->left = y->right;
			if (y->right != _nil)
				y->right->parent = x;
			// iguala os pais
			y->parent = x->parent;
			// verifica se eh root, caso nao seja, y sera adicionado ao lado certo do seu novo pai
			if (x->parent == nullptr) 
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			// faz o ultimo giro colocando os nos aos lugares certos
			y->right = x;
			x->parent = y;
		};

		// Rotacao esquerda: faz x ir para baixo e seu filho da direita pra cima.
		//		antes		depois
		//	      x			  y
		//		 /|			 /|
		//		  y			x
		void left_rotation(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		};
	};
}

#endif
	

	/*
	 *		TREE_ITERATOR
	 *
	template <typename Node>
	class tree_iterator
	{
	public:
		typedef Node								value_type;
		typedef value_type							*node_pointer;
		typedef typename Node::value_type const		data_type;
		typedef data_type							&reference;
		typedef data_type const						&const_reference;
		typedef data_type							*pointer;
		typedef data_type const						*const_pointer;
		

		node_pointer		node;

		// constructor
		// operator=
		tree_iterator()
		: node(nullptr), _root(nullptr), _nil(nullptr) {};

		tree_iterator(node_pointer n, node_pointer root, node_pointer nil)
		: node(n), _root(root), _nil(nil) {};

		tree_iterator(const tree_iterator &rbt)
		: node(rbt.node), _root(rbt._root), _nil(rbt._nil) {};

		// destructor
		//~tree_iterator() {};

		tree_iterator& operator= (const tree_iterator& ti)
		{
			if (ti == this)
				return (*this);
			this->node = ti.node;
			this->_root = ti._root;
			this->_nil = ti._nil;
			return (*this);
		};

		// overloads
		bool operator==(const tree_iterator &ti)
		{ return (node == ti.node); };
		
		bool operator!=(const tree_iterator &ti)
		{ return (node != ti.node); };

		reference operator*()
		{ return (node->key); }
		
		const_reference operator*() const
		{ return (*(node->key)); }

		
		pointer operator->()
		{ return (&(operator*())); }

		const_pointer operator->(void) const
		{ return (&(operator*())); }

		tree_iterator &operator++()
		{
			if (node != _nil)
				node = successor(node);
			return (*this);
		}

		// PREDECESSOR/SUCCESSOR: como se todas as keys estivessem em ordem crescente, o predecessor
		//						  equivale ao valor anterior e o successor ao proximo da key do no
		//						  passador por parametro.
		// successor 
		node_pointer successor(node_pointer n)
		{};
		// predecessor
		node_pointer predecessor(node_pointer n)
		{};

	private:
		node_pointer _root;
		node_pointer _nil;

	};

*/

