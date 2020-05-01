#include "../ft.hpp"
#include <iostream>
#include <list>
#ifndef LIBRARY
# define LIBRARY ft
#endif
int main ()
{
  LIBRARY::list<int> mylist1, mylist2;
  LIBRARY::list<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=4; ++i)
     mylist1.push_back(i);      // mylist1: 1 2 3 4

  for (int i=1; i<=3; ++i)
     mylist2.push_back(i*10);   // mylist2: 10 20 30

  it = mylist1.begin();
  ++it;                         // points to 2

  mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                // mylist2 (empty)
                                // "it" still points to 2 (the 5th element)
	std::cout << "MYLIST1 SIZE: " << mylist1.size() << '\n'
				<< "MYLIST2 empty: " << mylist2.empty() << '\n'
				<< "MYLIST2 SIZE: " << mylist2.size() << '\n'
				<< "IT POINTING AT: " << *it << '\n';
	// for (it = mylist1.begin(); it != mylist1.end(); it++)
	// 	std::cout << *it << ' ';
	// 	std::cout << '\n';
  mylist2.splice (mylist2.begin(), mylist1, it);
                                // mylist1: 1 10 20 30 3 4
                                // mylist2: 2
                                // "it" is now invalid.
	std::cout << "MYLIST1 SIZE: " << mylist1.size() << '\n'
				<< "MYLIST2 SIZE: " << mylist2.size() << '\n';
	// for (it = mylist1.begin(); it != mylist1.end(); it++)
	// 	std::cout << *it << ' ';
	// std::cout << '\n';
	// for (it = mylist2.begin(); it != mylist2.end(); it++)
	// 	std::cout << *it << ' ';
	// std::cout << '\n';
  it = mylist1.begin();
  advance(it,3);           // "it" points now to 30

  mylist1.splice (mylist1.begin(), mylist1, it, mylist1.end());
                                // mylist1: 30 3 4 1 10 20

  std::cout << "mylist1 contains:";
  for (it=mylist1.begin(); it!=mylist1.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "mylist2 contains:";
  for (it=mylist2.begin(); it!=mylist2.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
