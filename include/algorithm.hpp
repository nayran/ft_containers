#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

/*
 *		ALGORITHM
 *			Funcoes obrigatorias: equal, lexicographical_compare
 *
 *		https://www.cplusplus.com/reference/algorithm/equal/
 *		https://en.cppreference.com/w/cpp/algorithm/equal
 *
 *		https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
 */

#include <iostream>

namespace ft
{
	/*
	 *			EQUAL
	 *				equality, predicate
	 *			Compara se os elementos no range first1 ate last1 sao iguais a first2++
	 *
	 *			Predicate recebe binary predicate retorna true se os elementos sao iguais.
	 *			Prototipo da funcao pred deve ser o seguinte:
	 *				bool pred(const Type1 &a, const Type2 &b);
	 */
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	/*
	 *			LEXICOGRAPHICAL_COMPARE
	 *				default, custom
	 *			Faz comparacao em ordem alfabetica, se o primeiro iterador for menor que o segundo
	 *			eh verdadeiro. Se o segundo iterador chegar ao final antes que o primeiro, falso.
	 *
	 *			Custom recebe funcao cmp que retorna true se o primeiro argumento for menor que o segundo.
	 *			Prototipo da fucao cmp deve ser o seguinte:
	 *				bool cmp(const Type1 &a, const Type2 &b);
	 */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (*first1 < *first2)
				return (true);
			else if(*first1 > *first2 || first2 == last2)
				return (false);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (comp(*first1, *first2))
				return (true);
			if(comp(*first2, *first1))
				return (false);
			first1++;
			first2++;
		}
		return ((first1 == last1) && (first2 != last2));
	}
}
#endif
