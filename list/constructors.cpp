#include "../list.hpp"
#include <iostream>

// void

int main()
{
	ft::list<int> clean;
	ft::list<int> withn(10);
	ft::list<int> withnnum(10, 5);
	ft::list<int>::iterator first = withnnum.begin();
	ft::list<int>::iterator last = withnnum.end();
	last--;
	last--;
	ft::list<int> cpynum(first, last);
	ft::list<int> cpycpy(cpynum);
	ft::list<int> eq = withn;
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
