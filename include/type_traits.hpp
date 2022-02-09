#ifndef TYPE_TRAITS_HPP 
# define TYPE_TRAITS_HPP

/*
 *		TYPE_TRAITS
 *			Funcoes obrigatorias: enable_if, is_integral
 *
 *		https://en.cppreference.com/w/cpp/types/enable_if
 *		https://www.cplusplus.com/reference/type_traits/enable_if/
 *		https://www.cplusplus.com/reference/type_traits/is_integral/
 *		https://www.cplusplus.com/reference/type_traits/integral_constant/
 */

#include <iostream>

namespace ft
{
	/*
	 *		ENABLE_IF
	 *			Tipo T eh liberado como membro se Cond == true
	 */

	template<bool Cond, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	/*
	 *		IS_INTEGRAL
	 *			Identifica se tipo T eh um integral type
	 *
	 *		Integral constant <- is_integral
	 *		Tipos fundamentais: bool, char, char16_t, char32_t, wchar_t, signed char, short int,
	 *							int, long int, long long int, unsigned char, unsigned short int,
	 *							unsigned int, unsigned long int, unsigned long long int
	 */
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator const T(){
			return v;
		}
	};
	template<typename T>
	struct is_integral : public integral_constant<bool, false> {} ;

	template<>
	struct is_integral<bool> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<char> : public integral_constant<bool, true> {} ;

	/*
	template<>
	struct is_integral<char16_t> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<char32_t> : public integral_constant<bool, true> {} ;
*/
	template<>
	struct is_integral<wchar_t> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<signed char> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<short int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<long int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<long long int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned char> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned short int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned long int> : public integral_constant<bool, true> {} ;

	template<>
	struct is_integral<unsigned long long int> : public integral_constant<bool, true> {} ;
}
#endif
