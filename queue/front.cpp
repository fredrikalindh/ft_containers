#include <iostream>       // std::cout
#include <queue>          // LIBRARY::queue
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif


int main ()
{
  std::queue<int> myqueue;

  myqueue.push(77);
  myqueue.push(16);

  myqueue.front() -= myqueue.back();    // 77-16=61

  std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

  return 0;
}
