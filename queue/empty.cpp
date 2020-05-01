#include <iostream>       // std::cout
#include <queue>          // LIBRARY::queue
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif


int main ()
{
  std::queue<int> myqueue;
  int sum (0);

  for (int i=1;i<=10;i++) myqueue.push(i);

  while (!myqueue.empty())
  {
     sum += myqueue.front();
     myqueue.pop();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}
