#include "vector.hpp"
//#include "map.hpp"
//#include "stack.hpp"
#include <exception>

bool mycomp (char c1, char c2)
{ return c1 < c2; }

bool mypredicate (int i, int j)
{ return (i==j); }

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i)
{ return bool(i%2); }

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_even (T i)
{ return bool(!(i%2)); }


int main()
{
	/*
	ft::vector<int> mylist;
	for (int i=0; i<10; i++)
		mylist.push_back (i*10);

	// Iterator
	std::cout << "Iterator\n";
	std::cout << "\tIterator++: ";
	ft::vector<int>::iterator it = mylist.begin();
	for (int i=0; i<10; i++)
	{
		std::cout << *it << " ";
		it++;
	}

	// Reverse iterator
	ft::vector<int>::reverse_iterator rit = mylist.rbegin();
	std::cout << "\n\tReverse iterator++: ";
	for (int i=0; i<10; i++)
	{
		std::cout << *rit << " ";
		rit++;
	}
	std::cout << std::endl;

	// Iterator traits
	std::cout << "\nIterator traits\n";
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
		std::cout << "\tTag test: random-access iterator" << std::endl;
	ft::vector<int>::iterator it2= it;
	if (it == it2)
		std::cout << "\tit == it2" << std::endl;
	it2++;
	if (it != it2)
		std::cout << "\tit != it2" << std::endl;

	// Advance and Distance
	std::cout << "\nIterator functions\n";
	ft::vector<int>::iterator last = mylist.end();
	ft::vector<int>::iterator it_int = mylist.begin();
	ft::advance (it_int,0);
	std::cout << "\tFirst element in mylist is: " << *it_int;
	std::cout << ", distance until last element is: " << ft::distance(it_int,last) << std::endl;
	ft::advance (it_int,5);
	std::cout << "\tSixth element in mylist is: " << *it_int;
	std::cout << ", distance until last element is: " << ft::distance(it_int,last) << std::endl;
	ft::advance (it_int,5);
	std::cout << "\tLast element in mylist is: " << *it_int;
	std::cout << ", distance until last element is: " << ft::distance(it_int,last) << std::endl;
	
	//  Equal and Lexicographical_compare
	std::cout << "\nEqual and Lexicographical_compare\n";
	char foo[]="apple";
	char bar[]="apartment";
	char bar2[]="apple";
	std::cout << "\tEqual: apple x apple\n";
	std::cout << "\t\tDefault comparison: ";
	std::cout << ft::equal(foo, foo+5, bar2) << std::endl;
	std::cout << "\t\tCustom comparison: ";
	std::cout << ft::equal(foo, foo+5, bar2, mypredicate) << std::endl;
	std::cout << "\tEqual: apple x apartment\n";
	std::cout << "\t\tDefault comparison: ";
	std::cout << ft::equal(foo, foo+5, bar) << std::endl;
	std::cout << "\t\tCustom comparison: ";
	std::cout << ft::equal(foo, foo+5, bar, mypredicate) << std::endl;
	std::cout << "\tLexico: apple x apartment" << std::endl;
	std::cout << "\t\tDefault comparison: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9) << std::endl;
	std::cout << "\t\tCustom comparison: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp) << std::endl;
	std::cout << "\tLexico: apartment x apple" << std::endl;
	std::cout << "\t\tDefault comparison: ";
	std::cout << ft::lexicographical_compare(bar,bar+9,foo,foo+5) << std::endl;
	std::cout << "\t\tCustom comparison: ";
	std::cout << ft::lexicographical_compare(bar, bar+9, foo,foo+5,mycomp) << std::endl;

	// Enable_if and is_integral
	std::cout << "\nEnable_if and is_integral\n";
	std::cout << "\tenable_if::is_odd(1): " << is_odd(1) << std::endl;
	std::cout << "\tenable_if::is_even(1): " << is_even(1) << std::endl;
	std::cout << "\tis_integral<char>::value: " << ft::is_integral<char>::value << std::endl;
	std::cout << "\tis_integral<float>::value: " << ft::is_integral<float>::value << std::endl;
*/


	/*
	 *		VECTOR
	 */

	/*
	// Vector constructors
	ft::vector<int>	first;
	ft::vector<int> second (4,100);
	ft::vector<int> third (second.begin(),second.end());
	ft::vector<int> fourth (third);
	// Vector operator =
	ft::vector<int> aux(6,0);
	for (ft::vector<int>::iterator it = aux.begin(); it != aux.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	aux = second;
	for (ft::vector<int>::iterator it = aux.begin(); it != aux.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	*/
	// Begin
	int myints[] = {16,2,77,29};
	ft::vector<int> aux (myints, myints + sizeof(myints) / sizeof(int) );
	for (ft::vector<int>::iterator it = aux.begin(); it != aux.end(); it++)
		std::cout << *it << " ";
	ft::vector<int>::iterator it = aux.begin();
	ft::vector<int>::const_iterator it2 = aux.begin();
	std::cout << "\nBegin: " << *it << "\tConst begin: " << *it2 << std::endl;
	// End  -- um elemento apos o fim da sequencia (quase sempre nulo)
	it = aux.end();
	it2 = aux.end();
	std::cout << "End: " << *it << "\t\tConst end: " << *it2 << std::endl;

	return (0);
}
