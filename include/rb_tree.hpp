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
	template <class Node>
	class rbt_iterator;

	/*
	 *		NODE STRUCT
	 */
	template <typename T>
	struct s_node {
		typedef T	value_type;
		T			key;
		bool		color;
		s_node		*parent;
		s_node		*right;
		s_node		*left;

		s_node(const T & k)
		: key(k), color(BLACK), parent(nullptr), right(nullptr), left(nullptr){};
	};

	template <class T, class Compare, class Alloc = std::allocator<s_node<T> > >
	class rb_tree
	{
	public:
		// Member types
		typedef T										value_type;
		typedef Alloc									allocator_type;
		typedef Compare									compare;
		typedef s_node<value_type>						node;
		typedef size_t									size_type;
		typedef node									*node_pointer;
		typedef ft::rbt_iterator<node>					iterator;
		typedef ft::rbt_iterator<node>					const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		

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

		// ITERATORS
		iterator begin()
		{ return (iterator(minimum(_root), _root, _nil)); };

		const_iterator begin() const
		{ return (const_iterator(minimum(_root), _root, _nil)); };

		iterator end()
		{ return (iterator(_nil, _root, _nil)); };

		const_iterator end() const
		{ return (const_iterator(_nil, _root, _nil)); };

		reverse_iterator rbegin()
		{ return (reverse_iterator(end())); };

		const_reverse_iterator rbegin() const
		{ return (const_reverse_iterator(end())); };

		reverse_iterator rend()
		{ return (reverse_iterator(begin())); };

		const_reverse_iterator rend() const
		{ return (const_reverse_iterator(begin())); };

		/*
		 *		Operacoes: search, minimum, maximum, predecessor, successor, insert, delete
		 */

		// SEARCH: procura uma key na arvore e retorna o no correspondente
		node_pointer search(node_pointer n, T k)
		{
			
			if (n == _nil || n->key.first == k.first)
				return (n);
			if (n->key > k)
				return search(n->left, k);
			return search(n->right, k);
		};

		// MINIMUM: retorna o no com o menor valor
		node_pointer minimum(node_pointer n)
		{
			while (n->left != _nil)
				n = n->left;
			return (n);
		};

		// MAXIMUM: retorna o no com o maior valor
		node_pointer maximum(node_pointer n)
		{
			while (n->right != _nil)
				n = n->right;
			return (n);
		};

		// PREDECESSOR/SUCCESSOR: como se todas as keys estivessem em ordem crescente, o predecessor
		//						  equivale ao valor anterior e o successor ao proximo da key do no
		//						  passador por parametro.
		// predecessor
		node_pointer predecessor(node_pointer n)
		{
			// se n->left nao for nulo, o valor anterior eh o mais a direita
			// dentre o n->left;
			if (n->left != _nil)
				return (maximum(n->left));
			// caso n->left for nulo e n tiver um sucessor(aux), entao aux eh o menor
			// ancestral de n 
			node_pointer aux = n->parent;
			while (aux != _nil && n == aux->left)
			{
				n = aux;
				aux = aux->parent;
			}
			return (aux);
		};

		// successor 
		node_pointer successor(node_pointer n)
		{
			// inverso do predecessor
			if (n->right != _nil)
				return (minimum(n->right));
			node_pointer aux = n->parent;
			while (aux != _nil && n == aux->right)
			{
				n = aux;
				aux = aux->parent;
			}
			return (aux);
		};

		// recolor_uncle_parent: refaz codigo repetitivo
		node_pointer recolor_uncle_parent(node_pointer n, node_pointer uncle)
		{
			uncle->color = BLACK;
			n->parent->color = BLACK;
			if (n->parent->parent != _root)
				n->parent->parent->color = RED;
			return (n->parent->parent);

		};
		// recolor_insert: arruma as cores da arvore
		void recolor_insert(node_pointer n)
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
						n = recolor_uncle_parent(n, uncle);
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
						n = recolor_uncle_parent(n, uncle);
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
			aux->key = k;
			aux->parent = _nil;
			aux->left = _nil;
			aux->right = _nil;
			aux->color = RED;

			node_pointer y = _nil;
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
			if (y == _nil)
				_root = aux;
			else if (aux->key < y->key)
				y->left = aux;
			else
				y->right = aux;
			// se o no criado for root (nao tiver pai), ele esta na posicao certa mas o root
			// sempre eh preto se o avo for o root, ele esta correto. Para outras excecoes
			// a arvore deve ser consertada.
			if (aux->parent == _nil)
				aux->color = BLACK;
			else if (!(aux->parent->parent == _nil))
				recolor_insert(aux);
			_size++;
		};


		// coloca o y no lugar do x
		void occupy(node_pointer x, node_pointer y)
		{
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right= y;
			y->parent = x->parent;
		};

		// DELETE: remonta a arvore deixando os nos linkados adequadamente para
		//		   remover o no especificado.
		void del(T k)
		{
			node_pointer r = _root;
			node_pointer n = search(r, k);
			node_pointer x, y;
			// caso nao ache a key
			if (n == _nil)
				return ;
			bool n_color = n->color;
			if (n->left == _nil)
			{
				// se esquerda do no for nulo, faz copia do filho da direita
				// o no vira o filho da direita. Isola o no da direita para excluir.
				x = n->right;
				occupy(n, n->right);
			}
			else if (n->right == _nil)
			{
				// se direita do no for nulo, faz copia do filho da esquerda 
				// o no vira o filho da esquerda
				x = n->left;
				occupy(n, n->left);
			}
			else
			{
				// se nenhum filho for nulo. 
				// isola o no para o maximo a esquerda da subarvore direita
				// e substitui
				y = minimum(n->right);
				n_color = y->color;
				x = y->right;
				if (y->parent == n)
					x->parent = y;
				else
				{
					occupy(y, y->right);
					y->right = n->right;
					y->right->parent = y;
				}
				occupy(n, y);
				y->left = n->left;
				y->left->parent = y;
				y->color = n->color;
			}
			_alloc.destroy(n);
			_alloc.deallocate(n, 1);
			// se a cor do no que foi excluido for preta, precisa consertar a arvore.
			// excluir ultimo no vermelho nao infringe regras.
			if (n_color == BLACK)
				recolor_delete(x);
		};



		// Recolor delete: arruma as cores da arvore apos a remocao do no comparando com irmao(s)
		void recolor_delete(node_pointer n)
		{
			node_pointer s;

			while (n != _root && n->color == BLACK)
			{
				// caso esteja a esquerda (menor que s)
				if (n == n->parent->left)
				{
					s = n->parent->right;
					// caso o irmao seja vermelho, irmao vira preto e pai vira vermelho
					if (s->color == RED)
					{
						s->color = BLACK;
						n->parent->color = RED;
						left_rotation(n->parent);
						s = n->parent->right;
					}
					// com certeza aqui o irmao(s) sera preto. Se os filhos do irmao forem pretos
					// o irmao vira vermelho. Se o pai for vermelho, vira preto. A posicao do
					// ponteiro vai para o pai.
					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						n = n->parent;
					}
					else
					{
						// Se o filho direito do irmao for preto, o filho esquerdo do irmao tb
						// sera. Assim, irmao vira vermelho. Fazendo com que o irmao fique do lado
						// direito.
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							right_rotation(s);
							s = n->parent->right;
						} 
						// Se o irmao for preto, mas o filho direito do irmao eh vermelho.
						// Irmao vai ter a mesma cor do pai, pai e filho direito do irmao viram
						// pretos.
						s->color = n->parent->color;
						n->parent->color = BLACK;
						s->right->color = BLACK;
						left_rotation(n->parent);
					}
				}
				else 
				{
					// exatamente a mesma coisa do acima, mas muda a direita pela esquerda.
					s = n->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						n->parent->color = RED;
						right_rotation(n->parent);
						s = n->parent->left;
					}
					if (s->right->color == BLACK && s->left->color == BLACK)
					{
						s->color = RED;
						n = n->parent;
					}
					else 
					{
						if (s->left->color == BLACK) 
						{
							s->right->color = BLACK;
							s->color = RED;
							left_rotation(s);
							s = n->parent->left;
						} 
						s->color = n->parent->color;
						n->parent->color = BLACK;
						s->left->color = BLACK;
						right_rotation(n->parent);
					}
				}
				// aponta o ponteiro para root
				n = _root;
			}
			// o root sempre eh preto.
			n->color = BLACK;
		};

		size_t get_size()
		{ return (_size); };

		node_pointer get_root()
		{ return (_root); };

		node_pointer get_nil()
		{ return (_nil); };


		void print2(node_pointer root, std::string indent, bool last)
		{
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
		print2(root->left, indent, false);
		print2(root->right, indent, true);
	}
}

	void print() {
    	print2(this->_root, "", true);
	}


	private:
		allocator_type	_alloc;
		node_pointer	_root;
		node_pointer	_nil;
		size_type		_size;
		//compare			_compare;

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
			if (x->parent == _nil) 
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
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		};
	};

	/*
	 *			TREE ITERATOR
	 */
	template <class Node>
	class rbt_iterator
	{
	public:
		typedef Node									value_type;
		typedef value_type								*node_pointer;
		typedef typename Node::value_type const			data_type;
		typedef data_type								&reference;
		typedef data_type const							&const_reference;
		typedef data_type								*pointer;
		typedef data_type const							*const_pointer;
		typedef typename std::ptrdiff_t					difference_type;
		typedef ft::bidirectional_iterator_tag			iterator_category;
		node_pointer									_node;

		// constructors
		rbt_iterator() : _node(NULL), _root(NULL), _nil(NULL) {};
		
		rbt_iterator(node_pointer node, node_pointer root, node_pointer nil)
		: _node(node), _root(root), _nil(nil) {};

		rbt_iterator(const rbt_iterator &rbit)
		: _node(rbit._node), _root(rbit._root), _nil(rbit._nil) {};

		// operator=
		rbt_iterator& operator=(const rbt_iterator& rbit)
		{
			if (&rbit == this)
 				return (*this);
			_node = rbit._node;
			_root = rbit._root;
			_nil = rbit._nil;
			return (*this);
		};

		// destructor
		~rbt_iterator() {};

		//overload for const iterator
		//operator rbt_iterator<value_type const>(void) const
		//{ return rbt_iterator<value_type const>(_node, _root, _nil); };

		bool operator==(const rbt_iterator &rbit) const
		{ return (_node == rbit._node); };
		
		bool operator!=(const rbt_iterator &rbit) const
		{ return (_node != rbit._node); };
		
		reference operator*()
		{ return (_node->key); };

		const_reference operator*() const
		{ return (*(_node->key)); };

		pointer operator->()
		{ return (&(operator*())); };

		const_pointer operator->() const
		{ return (&(operator*())); };

		rbt_iterator &operator++()
		{
			if (_node != _nil)
				_node = successor();
			else
				_node = minimum(_root);
			return (*this);
		};
		
		rbt_iterator operator++(int)
		{
			rbt_iterator aux(*this);
			++(*this);
			return (aux);
		}

		rbt_iterator &operator--()
		{
			if (_node != _nil)
				_node = predecessor();
			else
				_node = maximum(_root);
			return (*this);
		}
		
		rbt_iterator operator--(int)
		{
			rbt_iterator aux(*this);
			--(*this);
			return (aux);
		}

	private:
		node_pointer	_root;
		node_pointer	_nil;
		
		node_pointer predecessor()
		{
			node_pointer n = _node;
			if (n->left != _nil)
				return (maximum(n->left));
			node_pointer aux = n->parent;
			while (aux != _nil && n == aux->left)
			{
				n = aux;
				aux = aux->parent;
			}
			return (aux);
		};

		node_pointer successor()
		{
			node_pointer n = _node;
			if (n->right != _nil)
				return (minimum(n->right));
			node_pointer aux = n->parent;
			while (aux != _nil && aux->right == n)
			{
				n = aux;
				aux = aux->parent;
			}
			return (aux);
		};
		
		node_pointer minimum(node_pointer n)
		{
			while (n->left != _nil)
				n = n->left;
			return (n);
		};

		node_pointer maximum(node_pointer n)
		{
			while (n->right != _nil)
				n = n->right;
			return (n);
		};


	};
};

#endif
	


/*
void print(ft::rb_tree<int, int>::node_pointer root, std::string indent, bool last, ft::rb_tree<int,int>::node_pointer nil)
{
	if (root != nil)
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
		print(root->left, indent, false, nil);
		print(root->right, indent, true, nil);
	}
}

	*
	 *		RED BLACK TREE
	 *
	 *			 61b
	 *			/  \
	 *		   /    \
	 *		  52b	85b
	 *				/ \
	 *		       76r 93r
	 *
	std::cout << "\nRED BLACK TREE:\n";
	ft::rb_tree<int,int> rbt;
	rbt.insert(61);
	rbt.insert(52);
	rbt.insert(85);
	rbt.insert(76);
	rbt.insert(93);
	print(rbt.get_root(), "", true, rbt.get_nil());
	rbt.insert(100);
	print(rbt.get_root(), "", true, rbt.get_nil());
	rbt.del(85);
	print(rbt.get_root(), "", true, rbt.get_nil());
	std::cout << "minimum: " << rbt.minimum(rbt.get_root())->key << std::endl;
	std::cout << "maximum: " << rbt.maximum(rbt.get_root())->key << std::endl;
	ft::rb_tree<int,int>::node_pointer rbtp = rbt.search(rbt.get_root(), 76);
	std::cout << "search(76): " << rbtp->key << std::endl;
	std::cout << "inexistent search(64): " << rbt.search(rbt.get_root(), 64)->key << std::endl;
	std::cout << "predecessor(76): " << rbt.predecessor(rbt.get_root())->key << std::endl;
	std::cout << "successor(76): " << rbt.successor(rbtp)->key << std::endl;
	
	*/
