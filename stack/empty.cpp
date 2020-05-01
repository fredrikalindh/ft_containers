#include <iostream>       // std::cout
#include <stack>          // std::stack
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
  LIBRARY::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}
