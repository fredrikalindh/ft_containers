#include <iostream>       // std::cout
#include <stack>          // std::stack
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
  LIBRARY::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';

  return 0;
}
