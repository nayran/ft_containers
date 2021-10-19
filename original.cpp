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

class Except: public std::exception{
	public:
		virtual const char* what() const throw(){
			return ("Error!");
		}
};

int main()
{
	// Iterator traits
	try {
		typedef ft::iterator_traits<int*> traits;
		if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
			std::cout << "Tag test: random-access iterator" << std::endl;
		ft::vector<int>::iterator it;
		ft::vector<int>::iterator it2= it;
		if (it == it2)
			std::cout << "it == it2" << std::endl;
		else
			throw Except();
		it2++;
		if (it != it2)
			std::cout << "it != it2" << std::endl;
		else
			throw Except();
	}
	catch (std::exception &e){
		std::cout << "ERROR: Iterator Traits!" << std::endl;
		return (0);
	}

	// Advance and Distance
	try {
		ft::vector<int> mylist;
		std::cout << "mylist: ";
		for (int i=0; i<10; i++)
		{
			mylist.push_back (i*10);
			std::cout << mylist[i] << " ";
		}
		std::cout << std::endl;
		ft::vector<int>::iterator last = mylist.end();
		ft::vector<int>::iterator it_int = mylist.begin();
		ft::advance (it_int,0);
		std::cout << "First element in mylist is: " << *it_int;
		std::cout << ", distance until last element is: " << ft::distance(it_int,last) << std::endl;
		ft::advance (it_int,5);
		std::cout << "Sixth element in mylist is: " << *it_int;
		std::cout << ", distance until last element is: " << ft::distance(it_int,last) << std::endl;
		ft::advance (it_int,5);
		std::cout << "Last element in mylist is: " << *it_int;
		std::cout << ", distance until last element is: " << ft::distance(it_int,last) << std::endl;
	}
	catch (std::exception &e){
		std::cout << "ERROR: Iterator functions!" << std::endl;
		return (0);
	}
	
	ft::vector<std::string> vector_str;
	ft::vector<char> vector_char;
	ft::vector<int> vector_int;
  

	return (0);
}
