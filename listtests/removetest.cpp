#include "../ft.hpp"
#include <iostream>
#include <list>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
  int myints[]= {17,89,7,14};
  LIBRARY::list<int> mylist (myints,myints+4);

  mylist.remove(89);

  std::cout << "mylist contains:";
  for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
