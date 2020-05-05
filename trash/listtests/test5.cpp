#include "../ft.hpp"
#include <iostream>
#include <list>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
  LIBRARY::list<int> mylist;
  LIBRARY::list<int>::iterator it1,it2;

  // set some values:
  for (int i=1; i<10; ++i)
  	mylist.push_back(i*10);


                              // 10 20 30 40 50 60 70 80 90
  it1 = it2 = mylist.begin(); // ^^
  std::cout << " IT1: " << *it1   << " IT2: " << *it2  << '\n';

  std::advance (it2,6);            // ^                 ^
  std::cout << " IT1: " << *it1   << " IT2: " << *it2  << '\n';

  ++it1;                      //    ^              ^
  it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
                              //    ^           ^
// std::cout << "IT1: " << *it1 << '\n';

  it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
                              //    ^           ^
std::cout << " IT1: " << *it1   << " IT2: " << *it2  << '\n';

  ++it1;                      //       ^        ^
  --it2;                      //       ^     ^
  std::cout << " IT1: " << *it1   << " IT2: " << *it2  << '\n';

  mylist.erase (it1,it2);     // 10 30 60 80 90
                              //        ^

  std::cout << "mylist contains:";
  for (it1=mylist.begin(); it1!=mylist.end(); ++it1)
    std::cout << ' ' << *it1;
  std::cout << '\n';

  return 0;
}
