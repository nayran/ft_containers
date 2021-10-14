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
  
	return (0);
}
