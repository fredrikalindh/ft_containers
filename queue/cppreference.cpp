#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <queue>         // std::vector
#include <list>         // std::vector
#include <deque>          // std::deque
#include "../ft.hpp"          // std::deque

#ifndef LIBRARY
# define LIBRARY ft
#endif

int Constructor()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
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


int Empty()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::queue<int> myqueue;
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

int Push()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::queue<int> myqueue;
    int myint;

    std::cout << "Please enter some integers (enter 0 to end):\n";

    do {
      std::cin >> myint;
      myqueue.push (myint);
    } while (myint);

    std::cout << "myqueue contains: ";
    while (!myqueue.empty())
    {
      std::cout << ' ' << myqueue.front();
      myqueue.pop();
    }
    std::cout << '\n';

    return 0;
}

int Pop()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::queue<int> myqueue;
	int myint;

	std::cout << "Please enter some integers (enter 0 to end):\n";

	do {
	  std::cin >> myint;
	  myqueue.push (myint);
	} while (myint);

	std::cout << "myqueue contains: ";
	while (!myqueue.empty())
	{
	  std::cout << ' ' << myqueue.front();
	  myqueue.pop();
	}
	std::cout << '\n';

	return 0;
}

int Size()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::queue<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';

    return 0;
}

int Front()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	std::queue<int> myqueue;

    myqueue.push(77);
    myqueue.push(16);

    myqueue.front() -= myqueue.back();    // 77-16=61

    std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

    return 0;
}

int Back()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	std::queue<int> myqueue;

    myqueue.push(12);
    myqueue.push(75);   // this is now the back

    myqueue.back() -= myqueue.front();

    std::cout << "myqueue.back() is now " << myqueue.back() << '\n';

    return 0;
}

void RelOp()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	  LIBRARY::list<int> a;
	  a.push_back(10);
	  a.push_back(20);
	  a.push_back(30);
	  LIBRARY::list<int> b;
	  b.push_back(10);
	  b.push_back(20);
	  b.push_back(30);
	  LIBRARY::list<int> c;
	  c.push_back(30);
	  c.push_back(20);
	  c.push_back(10);

	  // std::deque<int> mydeck (3,100);        // deque with 3 elements
  	LIBRARY::list<int> mylist (size_t(2),200);         // list with 2 elements

  	LIBRARY::queue<int> first;                 // empty queue
  	// LIBRARY::queue<int, std::deque<int> > second (mydeck);
  	LIBRARY::queue<int, LIBRARY::list<int> > third (a);
  	LIBRARY::queue<int, LIBRARY::list<int> > fourth (b);
  	LIBRARY::queue<int, LIBRARY::list<int> > fifth (b);

  // if (first==second) std::cout << "first and fourth are equal\n";
  // if (first!=second) std::cout << "fourth and fifth are not equal\n";
  if (third==fourth) std::cout << "third and fourth are equal\n";
  if (fourth!=fifth) std::cout << "fourth and fifth are not equal\n";
  if (fourth<fifth) std::cout << "fourth is less than fifth\n";
  if (fifth>fourth) std::cout << "fifth is greater than fourth\n";
  if (third<=fourth) std::cout << "third is less than or equal to fourth\n";
  if (third>=fourth) std::cout << "third is greater than or equal to fourth\n";
}

int main()
{
	Constructor();
	Empty();
	Push();
	Pop();
	Size();
	Front();
	Back();
	RelOp();
}
