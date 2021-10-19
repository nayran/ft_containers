#include <iostream>
#include <string>
#include <stdlib.h>
#include <deque>
#include <map>
#include <stack>
#include <vector>
#include <iterator>
#include <exception>
namespace ft = std;

int main()
{
	ft::vector<int> mylist;
	for (int i=0; i<10; i++)
		mylist.push_back (i*10);

	// Iterator
	std::cout << "Iterator" << std::endl;
	std::cout << "\tIterator++: ";
	ft::vector<int>::iterator it = mylist.begin();
	for (int i=0; i<10; i++)
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;

	// Reverse iterator
	ft::vector<int>::reverse_iterator rit = mylist.rbegin();
	std::cout << "\tReverse iterator++: ";
	for (int i=0; i<10; i++)
	{
		std::cout << *rit << " ";
		rit++;
	}
	std::cout << std::endl;

	// Iterator traits
	std::cout << std::endl << "Iterator traits" << std::endl;
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
	std::cout << std::endl << "Iterator functions" << std::endl;
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
	
	ft::vector<std::string> vector_str;
	ft::vector<char> vector_char;
	ft::vector<int> vector_int;
  

	return (0);
}
