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
	/*
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

std::cout << "\n\tModifiers\n";

	second.assign(vec.begin(), vec.end());
	std::cout << "assign range(vec.begin(), vec.end()): ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	second.assign(5, 1);
	std::cout << "\nassign fill(5, 1):\t";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	second.push_back(2);
	std::cout << "\npush_back(2):\t\t";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	second.pop_back();
	std::cout << "\npop_back():\t\t";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";

	ft::vector<int>a;
	a.push_back(1);
	std::cout << "\npush_back(1) empty vector: ";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	a.pop_back();
	std::cout << "\npop_back() empty vector: ";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	a.clear();

	std::cout << "\ninsert single: insert(a.begin(), 300), insert(a.begin(), 100, insert(a.begin() + 1, 200))\n";
	a.clear();
	a.insert(a.begin(), 300);
	a.insert(a.begin(), 100);
	a.insert(a.begin() + 1, 200);
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	ft::vector<int>::iterator it = a.begin();
	it = a.insert(it + 1, 110);
	std::cout << "insert single: a.insert(it[1], 110) -- inicio no iterador retornado\n";
	for (; it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "\ninsert single: a.insert(it[1], 110) -- mostra todo o vector\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	a.insert(a.begin() + 1, 2, 101);
	std::cout << "\ninsert fill: a.insert(it[1], 2, 101)\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";

	int i[] = {105, 106, 107};
	a.insert(a.begin() + 3, i, i+3);
	std::cout << "\ninsert range: a.insert(a.begin() + 3, i, i + 3)\t i = {105, 106, 107}\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nerase single element: a.erase(a.begin() + 3) -- inicio do iterador retornado\n";
	it = a.erase(a.begin() + 3);
	for (; it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nerase single element: a.erase(a.begin() + 3) -- mostra todo o vector\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	it = a.erase(a.begin() + 1, a.begin() + 4);
	std::cout << "\nerase range: a.erase(a.begin() + 1, a.begin() + 4) -- inicio do iterador retornado\n";
	for (; it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nerase range: a.erase(a.begin() + 1, a.begin() + 4) -- mostra todo o vector\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";

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
	std::cout << "\nSecond: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";

	ft::stack<int> s; 
	ft::stack<int, ft::vector<int> > stack(vec); 
	ft::stack<int, ft::vector<int> > stack2(vec); 
	ft::stack<int, ft::vector<int> > auxstack(second); 

	std::cout << "\n\nSTACK:\n";
	
	// ELEMENT ACCESS
	std::cout << "\ntop\nstack.top(): " << stack.top() << std::endl;

	// CAPACITY
	ft::stack<int> teste;
	std::cout << "\nempty and size\nteste.empty(): " << teste.empty() << std::endl;
	std::cout << "teste.size(): " << teste.size() << std::endl;
	std::cout << "stack.empty(): " << stack.empty() << std::endl;
	std::cout << "stack.size(): " << stack.size() << std::endl;

	// MODIFIERS
	stack.push(5);
	std::cout << "\nstack.push(5); stack.top(): " << stack.top() << " stack.size(): " << stack.size() << std::endl;
	stack.pop();
	std::cout << "stack.pop(); stack.top(): " << stack.top() << " stack.size(): " << stack.size() << std::endl;

	return (0);
}
