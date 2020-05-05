#include "../ft.hpp"
#include <iostream>
#include <list>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	  LIBRARY::list<int> a;
	  a.push_back(10);
	  a.push_back(20);
	  a.push_back(30);
	  LIBRARY::list<int> b;
	  b.push_back(10);
	  b.push_back(20);
	  b.push_back(30);
	  LIBRARY::list<int> c;
	  c.push_back(30);
	  c.push_back(20);
	  c.push_back(10);
  if (a==b) std::cout << "a and b are equal\n";
  if (b!=c) std::cout << "b and c are not equal\n";
  if (b<c) std::cout << "b is less than c\n";
  if (c>b) std::cout << "c is greater than b\n";
  if (a<=b) std::cout << "a is less than or equal to b\n";
  if (a>=b) std::cout << "a is greater than or equal to b\n";
}
