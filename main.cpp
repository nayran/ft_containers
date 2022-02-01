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

	std::cout << "VECTOR\n";
	// Vector constructors
	ft::vector<int>	first;
	ft::vector<int> second (7,100);
	ft::vector<int> third (second.begin(),second.end());
	ft::vector<int> fourth (third);
	// Vector operator =
	int myints[] = {16,2,77,29};
	ft::vector<int> vec(myints, myints + sizeof(myints) / sizeof(int) );
	std::cout << "VEC: ";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	/*
	std::cout << "\n\tVector operator = \n";
	std::cout << "aux: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	second = vec;
	std::cout << "\naux = vec: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	//	Vector iterators 
	std::cout << "\n\tVector iterators\n";
	// Begin
	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::const_iterator it2 = vec.begin();
	std::cout << "Begin: " << *it << "\tConst begin: " << *it2 << std::endl;
	// End  -- um elemento apos o fim da sequencia (quase sempre nulo)
	it = vec.end();
	it2 = vec.end();
	std::cout << "End: " << *it << "\t\tConst end: " << *it2 << std::endl;
	//Rbegin
	ft::vector<int>::reverse_iterator it3;
	it3 = vec.rbegin();
	ft::vector<int>::const_reverse_iterator it4;
	it4 = vec.rbegin();
	std::cout << "Rbegin: " << *it3 << "\tConst rbegin: " << *it4 << std::endl;
	//Rend
	it3 = vec.rend();
	it4 = vec.rend();
	std::cout << "Rend: " << *it3 << "\tConst rend: " << *it4 << std::endl;
	//	CAPACITY
	std::cout << "\n\tVector capacity\n";
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Max_size: " << vec.max_size() << std::endl;
	//vec.resize(5);
	//for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	//	std::cout << *it << " ";
	//std::cout << "Resize(5): " << vec.size() << std::endl;
	//vec.resize(4);
	std::cout << "Empty:" << fourth.empty();
	fourth.clear();
	std::cout << "\tEmpty:" << fourth.empty() << std::endl;


	std::cout << "\nCapacity: " << vec.capacity() << std::endl;
	vec.reserve(8);
	std::cout << "Reserve new capacity (8): " << vec.capacity() << std::endl;
	
*/

	//	ELEMENT ACCESS
	std::cout << "\n\tElement access\n";
	
	std::cout << "vec[2]: " << vec[2] << std::endl;
	try {
		std::cout << "vec.at(2): " << vec.at(2) << std::endl;
		std::cout << "vec.at(4): " << vec.at(4) << std::endl;
	}
	catch (std::exception& out) {
		std::cout << out.what() << std::endl;
	}

	return (0);
}
