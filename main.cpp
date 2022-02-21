#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

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
	std::cout << ", distance until end: " << ft::distance(it_int,last) << std::endl;
	ft::advance (it_int,5);
	std::cout << "\tSixth element in mylist is: " << *it_int;
	std::cout << ", distance until end: " << ft::distance(it_int,last) << std::endl;
	ft::advance (it_int,4);
	std::cout << "\tLast element in mylist is: " << *it_int;
	std::cout << ", distance until end: " << ft::distance(it_int,last) << std::endl;
	
	std::cout << "\n\nALGORITHM";
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
	std::cout << "\n\nTYPE_TRAITS";
	std::cout << "\nEnable_if and is_integral\n";
	std::cout << "\tenable_if::is_odd(1): " << is_odd(1) << std::endl;
	std::cout << "\tenable_if::is_even(1): " << is_even(1) << std::endl;
	std::cout << "\tis_integral<char>::value: " << ft::is_integral<char>::value << std::endl;
	std::cout << "\tis_integral<float>::value: " << ft::is_integral<float>::value << std::endl;


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
	ft::vector<int> vec2(vec);
	std::cout << "VEC: ";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nSecond: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";

	std::cout << "\n\tVector operator = \n";
	std::cout << "aux: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	second = vec;
	std::cout << "\naux = vec: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	second = third;
	std::cout << "\naux = aux2: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	


	/*
	 *		Para fins de comparacao, o valor retornado pode variar entao eh
	 *		impossivel comparar com outra saida
	 *
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
	*/

	//	CAPACITY
	std::cout << "\n\tVector capacity\n";
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Max_size: " << vec.max_size() << std::endl;
	vec.resize(5);
	std::cout << "Resize(5): " << vec.size() << std::endl;
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	

	vec.resize(7, 5);
	std::cout << "\nResize(7, 5): " << vec.size() << std::endl;
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "Capacity: " << vec.capacity() << std::endl;

		
	vec.resize(4);
	std::cout << "\nResize(4): " << vec.size() << std::endl;
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nEmpty:" << fourth.empty();
	fourth.clear();
	std::cout << "\tEmpty:" << fourth.empty() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	vec.reserve(10);
	std::cout << "Reserve new capacity (10): " << vec.capacity() << std::endl;
	
	//	ELEMENT ACCESS
	std::cout << "\n\tElement access\n";
	
	//vec = vec2;
	std::cout << "vec[2]: " << vec[2] << std::endl;
	try {
		std::cout << "vec.at(2): " << vec.at(2) << std::endl;
		//std::cout << "vec.at(4): " << vec.at(4) << std::endl;
	}
	catch (std::exception& out) {
		std::cout << out.what() << std::endl;
	}
	std::cout << "vec.front(): " << vec.front() << std::endl;
	std::cout << "vec.back(): " << vec.back() << std::endl;
	

	//	MODIFIERS
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
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	second.pop_back();
	std::cout << "\npop_back():\t\t";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";

	ft::vector<int>a;
	a.push_back(1);
	std::cout << "\npush_back(1) empty vector: ";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "Capacity: " << a.capacity() << std::endl;
	a.pop_back();
	std::cout << "\npop_back() empty vector: ";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	a.clear();
	std::cout << "\ninsert single: insert(a.begin(), 300), insert(a.begin(), 100, insert(a.begin() + 1, 200))\n";
	a.insert(a.begin(), 300);
	a.insert(a.begin(), 100);
	a.insert(a.begin() + 1, 200);
	a.insert(a.end() - 1, 250);
	std::cout << "Capacity: " << a.capacity() << std::endl;
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//ft::vector<int>::iterator it = vec.begin();
	it = a.insert(a.begin() + 1, 110);
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
	std::cout << "Capacity: " << a.capacity() << std::endl;

	
	int i[] = {105, 106, 107};
	a.insert(a.begin() + 3, i, i+3);
	std::cout << "\ninsert range: a.insert(a.begin() + 3, i, i + 3)\t i = {105, 106, 107}\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "\nerase single element: a.erase(a.begin() + 3) -- inicio do iterador retornado\n";
	it = a.erase(a.begin() + 3);
	for (; it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nerase single element: a.erase(a.begin() + 3) -- mostra todo o vector\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	it = a.erase(a.begin() + 1, a.begin() + 4);
	std::cout << "\nerase range: a.erase(a.begin() + 1, a.begin() + 4) -- inicio do iterador retornado\n";
	for (; it != a.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nerase range: a.erase(a.begin() + 1, a.begin() + 4) -- mostra todo o vector\n";
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
		std::cout << *it << " ";


	std::cout << "\nSwap\nbefore VEC: ";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nbefore Second: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	vec.swap(second);
	std::cout << "\n\nVEC: ";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nSecond: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";

	//RELATIONAL OPERATORS
	
	
	ft::vector<int> aux(vec);
	std::cout << "\nAUX: ";
	for (ft::vector<int>::iterator it = aux.begin(); it != aux.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nvec == aux: " << (vec == aux) << std::endl;
	std::cout << "vec == second: " << (vec == second) << std::endl;
	std::cout << "vec != second: " << (vec != second) << std::endl;
	std::cout << "vec != aux: " << (vec != aux) << std::endl;
	std::cout << "vec < second: " << (vec < second) << std::endl;
	std::cout << "vec <= second: " << (vec <= second) << std::endl;
	std::cout << "vec <= aux: " << (vec <= aux) << std::endl;
	std::cout << "vec > aux: " << (vec > second) << std::endl;
	std::cout << "vec <= second: " << (vec >= second) << std::endl;
	std::cout << "vec <= aux: " << (vec >= aux) << std::endl;

	// Swap public;
	std::cout << "\nPublic swap\nbefore VEC: ";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nbefore Second: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";
	swap(vec, second);
	std::cout << "\nVEC: ";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nSecond: ";
	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << " ";



	// STACK
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
	stack.push(99);
	std::cout << "\nstack.push(99); stack.top(): " << stack.top() << " stack.size(): " << stack.size() << std::endl;
	stack.pop();
	std::cout << "stack.pop(); stack.top(): " << stack.top() << " stack.size(): " << stack.size() << std::endl;

	//RELATIONAL OPERATORS
	std::cout << "\nRelational operators\n";
	std::cout << "stack == stack2: " << (stack == stack2) << std::endl;
	std::cout << "stack == auxstack: " << (stack == auxstack) << std::endl;
	std::cout << "stack != auxstack: " << (stack != auxstack) << std::endl;
	std::cout << "stack < auxstack: " << (stack < auxstack) << std::endl;
	std::cout << "stack <= auxstack: " << (stack <= auxstack) << std::endl;
	std::cout << "stack <= stack2: " << (stack <= stack2) << std::endl;
	std::cout << "stack > stack2: " << (stack > auxstack) << std::endl;
	std::cout << "stack <= auxstack: " << (stack >= auxstack) << std::endl;
	std::cout << "stack <= stack2: " << (stack >= stack2) << std::endl;



	// UTILITY
	std::cout << "\n\nUTILITY" << std::endl;
	
	// PAIR
	std::cout << "\nPair" << std::endl;
	ft::pair<int, double> p(42, 3.1415);
	ft::pair<int, double> p2(42, 3.1415);
	ft::pair<int, double> p3(42, 13);
	std::cout << "pair.first: " << p.first << "\tpair.second: " << p.second << std::endl;
	std::cout << "pair2.first: " << p2.first << "\tpair2.second: " << p2.second << std::endl;
	std::cout << "pair3.first: " << p3.first << "\tpair3.second: " << p3.second << std::endl;
	std::cout << "pair == pair2: " << (p == p2) << std::endl;
	std::cout << "pair == pair3: " << (p == p3) << std::endl;
	std::cout << "pair != pair2: " << (p != p2) << std::endl;
	std::cout << "pair != pair3: " << (p != p3) << std::endl;
	std::cout << "pair < pair2: " << (p < p2) << std::endl;
	std::cout << "pair < pair3: " << (p < p3) << std::endl;
	std::cout << "pair <= pair2: " << (p <= p2) << std::endl;
	std::cout << "pair <= pair2: " << (p <= p2) << std::endl;
	std::cout << "pair > pair2: " << (p > p2) << std::endl;
	std::cout << "pair > pair3: " << (p > p3) << std::endl;
	std::cout << "pair >= pair2: " << (p >= p2) << std::endl;
	std::cout << "pair >= pair3: " << (p >= p3) << std::endl;
	ft::pair<int, int> pair;
	pair = p;
	std::cout << "p = pair: " << pair.first << " " << pair.second << std::endl;

	// Make_pair
	std::cout << "\nMake pair" << std::endl;
	int n = 1;
    int n2[5] = {1, 2, 3, 4, 5};
    pair = ft::make_pair(n, n2[1]);
	std::cout << "mkpair.first: " << pair.first << "\tmkpair.second: " << pair.second << std::endl;




	/*
	 *		MAP
	 */
	{
		std::cout << "\n\nMAP:\n";
		// constructors
		ft::map<char,int> m;
		std::cout << "size: " << m.size() << " empty: " << m.empty();
		ft::pair<char,int> p = ft::make_pair('a', 10);
		m['b']=30;
		m['c']=50;
		m['d']=70;
		m.insert(p);
		ft::map<char,int> m2(m.begin(),m.end());
		ft::map<char,int> m3(m2);
		

		// constructors e operator[]
		std::cout << "\nm['a':10, 'b':30, 'c':50, 'd':70]: " << m['a'] << " " << m['b'] << " " << m['c'] << " " << m['d'];
		std::cout << "\nm2(m.begin(), m.end()): " << m2['a'] << " " << m2['b']<< " " << m2['c'] << " " << m2['d'];
		std::cout << "\nm3(m2): " << m3['a'] << " " << m3['b'] << " " << m3['c'] << " " << m3['d'];

		//operator=
		ft::map<char,int> aux;
		aux = m;
		std::cout << "\naux = m: " << aux['a'] << " " << aux['b'] << " " << aux['c'] << " " << aux['d'];

		// capacity (empty, size, max_size)
		std::cout << "\nsize: " << m.size() << " empty: " << m.empty() << " max_size: " << m.max_size() << std::endl;

		// modifiers
		p = ft::make_pair ('e', 100);
		m.insert(p);
		std::cout << "m.insert('e', 100): " << m['a'] << " " << m['b'] << " " << m['c'] << " " << m['d'] << " " << m['e'];
		ft::map<char,int>::iterator it = m.begin();
		m.insert(it, ft::pair<char,int>('f', 120));
		std::cout << "\nm.insert(it, pair('f', 120)): " << m['a'] << " " << m['b'] << " " << m['c'] << " " << m['d'] << " " << m['e'] << " " << m['f'];
	}
	return (0);
}
