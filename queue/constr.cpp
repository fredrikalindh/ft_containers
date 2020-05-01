#include <iostream>       // std::cout
#include <deque>          // std::deque
#include <list>           // std::list
#include <queue>          // LIBRARY::queue
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
  std::deque<int> mydeck (3,100);        // deque with 3 elements
  LIBRARY::list<int> mylist (size_t(2),200);         // list with 2 elements

  LIBRARY::queue<int> first;                 // empty queue
  LIBRARY::queue<int, std::deque<int> > second (mydeck);       // queue initialized to copy of deque

  LIBRARY::queue<int,LIBRARY::list<int> > third; // empty queue with list as underlying container
  LIBRARY::queue<int,LIBRARY::list<int> > fourth (mylist);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}
