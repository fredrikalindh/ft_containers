#include "../ft.hpp"
#include <iostream>
#include <list>
#include <vector>
#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::list<int> mylist;
  LIBRARY::list<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

  it = mylist.begin();
  ++it;       // it points now to number 2           ^

  mylist.insert (it,10);                        // 1 10 2 3 4 5


  std::cout << "mylist contains:";
  for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

	std::cout << "it points at 2 ? " << *it << '\n';

  // "it" still points to number 2                      ^
  mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5

  std::cout << "mylist contains:";
  for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';


  --it;       // it points now to the second 20            ^

  std::cout << "it points at 20 ? " << *it << '\n';

  LIBRARY::vector<int> myvector (2,30);
  mylist.insert (it,myvector.begin(),myvector.end());
                                                // 1 10 20 30 30 20 2 3 4 5
                                                //               ^
	std::cout << "it points at 20 ? " << *it << '\n';


  std::cout << "mylist contains:";
  for (it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}
