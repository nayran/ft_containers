# ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP 

namespace ft
{

	// Binary_function: classe base para funcoes de objetos binarios padroes.
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	// Less: Funcao binaria que retorna um bool comparando se o primeiro argumento
	//		 eh menor que o segundo.
	template <class T> struct less : binary_function <T,T,bool>
	{ 
		bool operator() (const T& x, const T& y) const 
		{ return (x<y); }
	};
}

# endif
