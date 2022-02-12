#ifndef UTILITY_HPP
# define UTILITY_HPP

/*
 *		UTILITY
 *			Funcoes obrigatorias: pair, make_pair
 *
 *		https://www.cplusplus.com/reference/utility/pair/
 *		https://en.cppreference.com/w/cpp/utility/pair/
 *		https://www.cplusplus.com/reference/utility/make_pair/
 *
 *		ADICIONAR MAKEPAIR
 */

namespace ft
{
	/*
	 *		PAIR
	 *			Junta dois valores, que podem ser de tipos diferentes.
	 */

	template <class T1, class T2>
	struct pair
	{
		pair();
		
		template<class U, class V>
		pair (const pair<U,V>& pr);

		pair (const T1& a, const T2& b);

		pair& operator= (const pair& pr);

		template <class Type1, class Type2>
		friend bool operator== (const pair<Type1,Type2>& lhs, const pair<Type1,Type2>& rhs);
		template <class Type1, class Type2>
		friend bool operator!= (const pair<Type1,Type2>& lhs, const pair<Type1,Type2>& rhs);
		template <class Type1, class Type2>
		friend bool operator<  (const pair<Type1,Type2>& lhs, const pair<Type1,Type2>& rhs);
		template <class Type1, class Type2>
		friend bool operator<= (const pair<Type1,Type2>& lhs, const pair<Type1,Type2>& rhs);
		template <class Type1, class Type2>
		friend bool operator>  (const pair<Type1,Type2>& lhs, const pair<Type1,Type2>& rhs);
		template <class Type1, class Type2>
		friend bool operator>= (const pair<Type1,Type2>& lhs, const pair<Type1,Type2>& rhs);

		// Member types
		typedef T1	first_type;
		typedef	T2	second_type;

		// Member objects
		T1	first;
		T2	second;

	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	
	/*
	 *		MAKE_PAIR
	 *			Constroi um objeto pair
	 */
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	};

}
#endif
