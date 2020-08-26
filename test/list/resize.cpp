#include "../ft.hpp"
#include <iostream>
#include <list>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::list<int> mylist;

  // set some initial content:
  for (int i=1; i<10; ++i) mylist.push_back(i);

  mylist.resize(5);
  std::cout << "mylist contains:";
  for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
	std::cout << ' ' << *it;
  std::cout << '\n';
  mylist.resize(8,100);
  std::cout << "mylist contains:";
  for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
	std::cout << ' ' << *it;
  std::cout << '\n';
  mylist.resize(12);

  std::cout << "mylist contains:";
  for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}
