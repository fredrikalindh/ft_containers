#include <iostream>       // std::cout
#include <queue>          // LIBRARY::queue
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif


int main ()
{
  std::queue<int> myqueue;

  myqueue.push(12);
  myqueue.push(75);   // this is now the back

  myqueue.back() -= myqueue.front();

  std::cout << "myqueue.back() is now " << myqueue.back() << '\n';

  return 0;
}
