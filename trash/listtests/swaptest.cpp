#include "../ft.hpp"
#include <iostream>
#include <list>
#ifndef LIBRARY
# define LIBRARY ft
#endif
int main ()
{
  LIBRARY::list<int> first (size_t(3),100);   // three ints with a value of 100
  LIBRARY::list<int> second (size_t(5),200);  // five ints with a value of 200

  first.swap(second);

  std::cout << "first contains:";
  for (LIBRARY::list<int>::iterator it=first.begin(); it!=first.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "second contains:";
  for (LIBRARY::list<int>::iterator it=second.begin(); it!=second.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
