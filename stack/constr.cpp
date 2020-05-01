#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <list>         // std::vector
#include <deque>          // std::deque
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif

// int main ()
// {
//   ft::stack<int> mystack;          // deque with 3 elements
//
// 	mystack.push(1);
// 	mystack.push(2);
// 	mystack.push(3);
//
// 	while (!mystack.empty()){
// 		std::cout << "popping : " << mystack.top() << '\n';
// 		mystack.pop();
// 	}
//
//   return 0;
// }
int main ()
{
  std::list<int> mylist (size_t(3),100);          // deque with 3 elements
  std::vector<int> myvector (size_t(2),200);        // vector with 2 elements

  LIBRARY::stack<int, std::list<int> > first;                    // empty stack
  LIBRARY::stack<int, std::list<int> > second (mylist);         // stack initialized to copy of deque

  LIBRARY::stack<int,std::vector<int> > third;  // empty stack using vector
  LIBRARY::stack<int,std::vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}
