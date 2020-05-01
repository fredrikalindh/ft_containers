#include "../ft.hpp"
#include <iostream>
#include <list>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
  LIBRARY::list<int> first;
  LIBRARY::list<int> second;

  first.assign (size_t(7),100);                      // 7 ints with value 100

  second.assign (first.begin(),first.end()); // a copy of first

  int myints[]={1776,7,4};
  first.assign (myints,myints+3);            // assigning from array

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  return 0;
}
