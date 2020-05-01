#include "../ft.hpp"
#include <iostream>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
	LIBRARY::list<int> clean;
	LIBRARY::list<int> withn(10);
	LIBRARY::list<int> withnnum(10, 5);
	LIBRARY::list<int>::iterator first = withnnum.begin();
	LIBRARY::list<int>::iterator last = withnnum.end();
	last--;
	last--;
	LIBRARY::list<int> cpynum(first, last);
	LIBRARY::list<int> cpycpy(cpynum);
	LIBRARY::list<int> eq = withn;
	std::cout << "SIZE = " << clean.size() << " IS EMPTY ? " << (clean.empty()) << " LIST: " ;
	clean.print();
	std::cout << "SIZE = " << withn.size() << " IS EMPTY ? " << (withn.empty()) << " LIST: " ;
	withn.print();
std::cout << "SIZE = " << withnnum.size() << " IS EMPTY ? " << (withnnum.empty()) << " LIST: " ;
	withnnum.print();
	std::cout << "SIZE = " << cpynum.size() << " IS EMPTY ? " << (cpynum.empty()) << " LIST: " ;
	cpynum.print();
	std::cout << "SIZE = " << cpycpy.size() << " IS EMPTY ? " << (cpycpy.empty()) << " LIST: " ;
	cpycpy.print();
	std::cout << "SIZE = " << eq.size() << " IS EMPTY ? " << (eq.empty()) << " LIST: " ;
	eq.print();
	std::cout << "################### RESIZE ##################" << '\n';
	withn.clear();
	std::cout << "SIZE = " << withn.size() << " IS EMPTY ? " << (withn.empty()) << '\n' ;
	withn.resize(11, 2);
	std::cout << "SIZE = " << withn.size() << " IS EMPTY ? " << (withn.empty()) << '\n' ;
	withn.print();
	withn.resize(3, 2);
	std::cout << "SIZE = " << withn.size() << " IS EMPTY ? " << (withn.empty()) << '\n' ;
	withn.print();
	return 0;
}
