#include "vector2.hpp"
#include "include/utils.hpp"
//#include "map.hpp"
//#include "stack.hpp"
#include <iterator>

int main()
{
	ft::vector<std::string> vector_str;
	ft::vector<char> vector_char;
	ft::vector<int> vector_int;
	
	// Iterator traits
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator";
	ft::random_access_iterator<int*> it;
	ft::random_access_iterator<int*> it2;
	if (it == it)
		std::cout << "equal";
	
	ft::vector<int> mylist;
	for (int i=0; i<10; i++)
		mylist.push_back (i*10);
	// Advance
	ft::vector<int>::iterator it_int = mylist.begin();
	ft::advance (it_int,5);
	std::cout << "The sixth element in mylist is: " << *it_int << '\n';
  
	// Distance
	ft::vector<int>::iterator first = mylist.begin();
	ft::vector<int>::iterator last = mylist.end();
	std::cout << "The distance is: " << ft::distance(first,last) << '\n';

	return (0);
}
