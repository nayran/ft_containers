#ifndef ITERATOR_HPP
# define ITERATOR_HPP

/*
 *		Iterator Classes
 *			Iterator
 *				Categoriy tags
 *				Random access iterator
 *				Reverse iterator
 *			Iterator traits
 *		Functions
 *			advance, distance
 *
 *		https://en.cppreference.com/w/c/types/ptrdiff_t
 *		https://www.cplusplus.com/reference/iterator/
 *		https://en.cppreference.com/w/cpp/header/iterator
 *
 */

#include <stddef.h>

namespace ft
{

	/*
	 *		ITERATOR
	 *		Fornece o template dos iteradores e faz a tag (para reconhecimento de tipo e propriedades)
	 *
	 *		Input <- Forward <- Bidirecional <- Random Access
	 *		Output
	 */
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator{
		typedef T         value_type;
		typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;
	};

	/*
	 *		Iterator categories
	 */
	struct input_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};
	struct output_iterator_tag {};
	
	/*
	 *		ITERATOR TRAITS
	 */
	template <class Iterator>
	class iterator_traits
	{
		typedef	typename Iterator::difference_type		difference_type;
		typedef	typename Iterator::value_type			value_type;
		typedef	typename Iterator::pointer				pointer;
		typedef	typename Iterator::reference			reference;
		typedef	typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		typedef	ptrdiff_t								difference_type;
		typedef	T										value_type;
		typedef	T										*pointer;
		typedef	T										&reference;
		typedef	random_access_iterator_tag				iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		typedef	ptrdiff_t								difference_type;
		typedef	T										value_type;
		typedef	const T									*pointer;
		typedef	const T									&reference;
		typedef	random_access_iterator_tag				iterator_category;
	};
	
	/*
	 *		Random access iterator
	 */
	template <class Iterator>
	class random_access_iterator{
		typedef Iterator												iterator_type;
		typename iterator_traits<Iterator>::iterator_category			iterator_category;
		typename iterator_traits<Iterator>::value_type					value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		
		/*
		 *		Member functions overload
		 *		Constructors, base, operators(*, +, ++, +=, -, --, -=, ->, [])
		 */
		random_access_iterator();
		explicit random_access_iterator (Iterator it);
		template <class Iter>
		random_access_iterator (const random_access_iterator<Iter>& rev_it);
		
		iterator_type base() const;

		reference				operator*() const;
		random_access_iterator		operator+ (difference_type n) const;
		random_access_iterator&		operator++();
		random_access_iterator		operator++(int);
		random_access_iterator&		operator+= (difference_type n);
		random_access_iterator		operator- (difference_type n) const;
		random_access_iterator&		operator--();
		random_access_iterator		operator--(int);
		random_access_iterator&		operator-= (difference_type n);
		pointer					operator->() const;
		reference				operator[] (difference_type n) const;
		
	};
	

	/*
	 *		[random access iterator] Non-member functions overload
	 *		+, -, relational operators (== != < <= > >=)
	 */
	template< class Iter > 
	random_access_iterator<Iter> operator+( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it )
	{
		return (random_access_iterator<Iter>(it.base() - n));
	}
	template< class Iterator >
	typename random_access_iterator<Iterator>::difference_type operator-( const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs )
	{
		return (rhs.base() - lhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator==( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	/*
	 *		Reverse iterator
	 *		https://www.cplusplus.com/reference/iterator/reverse_iterator/
	 *		https://en.cppreference.com/w/cpp/iterator/reverse_iterator
	 */
	template <class Iterator>
	class reverse_iterator{
		typedef Iterator												iterator_type;
		typename iterator_traits<Iterator>::iterator_category			iterator_category;
		typename iterator_traits<Iterator>::value_type					value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		
		/*
		 *		Member functions overload
		 *		Constructors, base, operators(*, +, ++, +=, -, --, -=, ->, [])
		 */
		reverse_iterator();
		explicit reverse_iterator (Iterator it);
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it);
		// destructor??
		
		iterator_type base() const;

		reference				operator*() const;
		reverse_iterator		operator+ (difference_type n) const;
		reverse_iterator&		operator++();
		reverse_iterator		operator++(int);
		reverse_iterator&		operator+= (difference_type n);
		reverse_iterator		operator- (difference_type n) const;
		reverse_iterator&		operator--();
		reverse_iterator		operator--(int);
		reverse_iterator&		operator-= (difference_type n);
		pointer					operator->() const;
		reference				operator[] (difference_type n) const;
		
	};
	

	/*
	 *		[Reverse iterator] Non-member functions overload
	 *		+, -, relational operators (== != < <= > >=)
	 */
	template< class Iter > 
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
	{
		return (reverse_iterator<Iter>(it.base() - n));
	}
	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
	{
		return (rhs.base() - lhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	/*
	 *		FUNCTIONS 
	 *		Iterator operations: advance, distance
	 */
	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n);

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last);

}

#endif
