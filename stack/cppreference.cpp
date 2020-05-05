#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <list>         // std::vector
#include <deque>          // std::deque
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif

int Constructor()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::list<int> mylist (3,100);          // deque with 3 elements
  LIBRARY::vector<int> myvector (2,200);        // vector with 2 elements

  LIBRARY::stack<int, LIBRARY::list<int> > first;                    // empty stack
  LIBRARY::stack<int, LIBRARY::list<int> > second (mylist);         // stack initialized to copy of deque

  LIBRARY::stack<int,LIBRARY::vector<int> > third;  // empty stack using vector
  LIBRARY::stack<int,LIBRARY::vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}


int Empty()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
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

int Push()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';

  return 0;
}

int Size()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';

  return 0;
}

int Top()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';

  return 0;
}

int main()
{
	Constructor();
	Empty();
	Push();
	Size();
	Top();
}
