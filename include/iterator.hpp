#ifndef ITERATOR_HPP
# define ITERATOR_HPP

/*
 *		[ ITERATOR ]
 *
 *		Iterator Classes
 *			Iterator
 *				Categoriy tags
 *				Random access iterator
 *				Reverse iterator
 *			Iterator traits
 *		Functions
 *			Advance, distance
 *
 *		https://en.cppreference.com/w/c/types/ptrdiff_t
 *		https://www.cplusplus.com/reference/iterator/
 *		https://en.cppreference.com/w/cpp/header/iterator
 *
 */

#include <stddef.h>
#include <typeinfo>
#include <iostream>

namespace ft
{

	/*
	 *		ITERATOR
	 *		Fornece o template dos iteradores e faz a tag (para reconhecimento de tipo e propriedades)
	 *
	 *		Input <- Forward <- Bidirecional <- Random Access
	 *		Output
	 */
	template <typename Category, typename T, typename Distance, typename Pointer, typename Reference>
	struct iterator{
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
	template <typename Iterator>
	struct iterator_traits
	{
		typedef	typename Iterator::difference_type		difference_type;
		typedef	typename Iterator::value_type			value_type;
		typedef	typename Iterator::pointer				pointer;
		typedef	typename Iterator::reference			reference;
		typedef	typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef	ptrdiff_t								difference_type;
		typedef	T										value_type;
		typedef	T										*pointer;
		typedef	T										&reference;
		typedef	random_access_iterator_tag				iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
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
	template <typename Iterator>
	class random_access_iterator :
		public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator	current;

	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		
		/*
		 *		Member functions overload
		 *		Constructors, base, operators(*, +, ++, +=, -, --, -=, ->, [])
		 *		https://gcc.gnu.org/onlinedocs/gcc-6.3.0/libstdc++/api/a01623_source.html#l00173
		 */
		random_access_iterator() {};
		explicit random_access_iterator (Iterator it) : current(it) {};
		template <typename Iter>
		random_access_iterator (const random_access_iterator<Iter>& rai) : current(rai.base()) {};
		
		iterator_type base() const
		{ return (current); }

		reference					operator*() const
		{
			return (*current);
		}
		random_access_iterator		operator+ (difference_type n) const
		{
			return (current + n);
		}
		random_access_iterator&		operator++()
		{
			current++;
			return (*this);
		}
		random_access_iterator		operator++(int)
		{
			current++;
			return (*this);
		}
		random_access_iterator&		operator+= (difference_type n)
		{
			current += n;
			return (*this);
		}
		random_access_iterator		operator- (difference_type n) const
		{
			std::cout << "entra";
			return (current - n);
		}
		random_access_iterator&		operator--()
		{
			current--;
			return (*this);
		}
		random_access_iterator		operator--(int)
		{
			current--;
			return (*this);
		}
		random_access_iterator&		operator-= (difference_type n)
		{
			current -= n;
			return (*this);
		}
		pointer						operator->() const
		{
			return (&(operator*()));
		}
		reference					operator[] (difference_type n) const
		{
			return (current[n]);
		}
		
	};
	

	/*
	 *		[random access iterator] Non-member functions overload
	 *		+, -, relational operators (== != < <= > >=)
	 */
	template< typename Iter > 
	random_access_iterator<Iter> operator+( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it )
	{
		return (random_access_iterator<Iter>(it.base() - n));
	}
	template< typename Iterator >
	typename random_access_iterator<Iterator>::difference_type operator-( const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs )
	{
		return (rhs.base() - lhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator==( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator!=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator<( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator<=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator>( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator>=( const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	/*
	 *		Reverse iterator
	 *		https://www.cplusplus.com/reference/iterator/reverse_iterator/
	 *		https://en.cppreference.com/w/cpp/iterator/reverse_iterator
	 */
	template <typename Iterator>
	class reverse_iterator : 
		public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator	current;

	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		
		/*
		 *		Member functions overload
		 *		Constructors, base, operators(*, +, ++, +=, -, --, -=, ->, [])
		 */
		reverse_iterator() {};
		explicit reverse_iterator (Iterator it) : current(it) {};
		template <typename Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {};
		// destructor??
		
		iterator_type base() const
		{ return (current); }

		reference				operator*() const
		{
			Iterator tmp = current;
			return (*--tmp);
		}
		reverse_iterator		operator+ (difference_type n) const
		{
			return (current - n);
		}
		reverse_iterator&		operator++()
		{
			current--;
			return (*this);
		}
		reverse_iterator		operator++(int)
		{
			current--;
			return (*this);
		}
		reverse_iterator&		operator+= (difference_type n)
		{
			current -= n;
			return (*this);
		}
		reverse_iterator		operator- (difference_type n) const
		{
			return (current + n);
		}
		reverse_iterator&		operator--()
		{
			current++;
			return (*this);
		}
		reverse_iterator		operator--(int)
		{
			current++;
			return (*this);
		}
		reverse_iterator&		operator-= (difference_type n)
		{
			current += n;
			return (*this);
		}
		pointer					operator->() const
		{
			return (&(operator*()));
		}
		reference				operator[] (difference_type n) const
		{
			return (*(*this + n));
		}
	};
	

	/*
	 *		[Reverse iterator] Non-member functions overload
	 *		+, -, relational operators (== != < <= > >=)
	 */
	template< typename Iter > 
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
	{
		return (reverse_iterator<Iter>(it.base() - n));
	}
	template< typename Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs )
	{
		return (rhs.base() - lhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< typename Iterator1, typename Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	/*
	 *		FUNCTIONS 
	 *		Iterator operations: advance, distance
	 */
	template <typename InputIterator, typename Distance>
	void advance (InputIterator& it, Distance n)
	{
		if (typeid(typename iterator_traits<InputIterator>::iterator_category) == typeid(random_access_iterator_tag))
		{
			it += n;
		}
		else
		{
			while (n-- > 0)
				it++;
			while (n++ > 0)
				it--;
		}
	}

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type result = 0;
		while (first != last)
		{
			++result;
			++first;
		}
		return (result);
	}

}

#endif
