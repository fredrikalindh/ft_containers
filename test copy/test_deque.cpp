#include <deque>
#include <vector>
#include <iostream>
#include "../ft.hpp"

#ifndef LIBRARY
#define LIBRARY ft
#endif

int Constructors()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  // unsigned int i;

  // constructors used in the same order as described above:
  LIBRARY::deque<int> first;                               // empty deque of ints
  LIBRARY::deque<int> second(4, 100);                      // four ints with value 100
  LIBRARY::deque<int> third(second.begin(), second.end()); // iterating through second
  LIBRARY::deque<int> fourth(second);                       // a copy of third

  // the iterator constructor can be used to copy arrays:
  int myints[] = {16, 2, 77, 29};
  LIBRARY::deque<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  std::cout << "The " << second.size() << " contents of second are:";
  for (LIBRARY::deque<int>::iterator it = second.begin(); it != second.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  std::cout << "The " << third.size() << " contents of third are:";
  for (LIBRARY::deque<int>::iterator it = third.begin(); it != third.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  std::cout << "The " << fourth.size() << " contents of fourth are:";
  for (LIBRARY::deque<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  std::cout << "The contents of fifth are:";
  for (LIBRARY::deque<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int Assignment()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> first(3);  // deque with 3 zero-initialized ints
  LIBRARY::deque<int> second(5); // deque with 5 zero-initialized ints
  LIBRARY::deque<int> third;

  second = first;
  first = third;
  first = LIBRARY::deque<int>();

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
  return 0;
}

int Begin()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;

  for (int i = 1; i <= 5; i++)
    mydeque.push_back(i);

  std::cout << "mydeque contains:";

  LIBRARY::deque<int>::iterator it = mydeque.begin();

  while (it != mydeque.end())
    std::cout << ' ' << *it++;

  std::cout << '\n';
  return 0;
}

int RBegin()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque(5); // 5 default-constructed ints

  LIBRARY::deque<int>::reverse_iterator rit = mydeque.rbegin();

  int i = 0;
  for (rit = mydeque.rbegin(); rit != mydeque.rend(); ++rit)
  {
    *rit = ++i;
  }

  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int Empty()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;
  int sum(0);

  for (int i = 1; i <= 10; i++)
    mydeque.push_back(i);

  while (!mydeque.empty())
  {
    sum += mydeque.front();
    mydeque.pop_front();
  }

  std::cout << "total: " << sum << '\n';
  return 0;
}
int Size()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i = 0; i < 5; i++)
    myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert(myints.begin(), 5, 100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';

  return 0;
}

int MaxSize()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  // unsigned int i;
  LIBRARY::deque<int> mydeque;

  // std::cout << "Enter number of elements: ";
  // std::cin >> i;

  // if (i < mydeque.max_size())
  //   mydeque.resize(i);
  // else
  //   std::cout << "That size exceeds the limit.\n";

  return 0;
}

int Resize()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;
  // LIBRARY::deque<int>::iterator it;

  // set some initial content:
  for (int i = 1; i < 10; ++i)
    mydeque.push_back(i);

  mydeque.resize(5);
   std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  mydeque.resize(8, 100);
  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  mydeque.resize(12);

  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  return 0;
}

int Bracket()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque(10); // 10 zero-initialized elements
  LIBRARY::deque<int>::size_type sz = mydeque.size();

  // assign some values:
  for (unsigned i = 0; i < sz; i++)
    mydeque[i] = i;

  // reverse order of elements using operator[]:
  for (unsigned i = 0; i < sz / 2; i++)
  {
    int temp;
    temp = mydeque[sz - 1 - i];
    mydeque[sz - 1 - i] = mydeque[i];
    mydeque[i] = temp;
  }

  // print content:
  std::cout << "mydeque contains:";
  for (unsigned i = 0; i < sz; i++)
    std::cout << ' ' << mydeque[i];
  std::cout << '\n';

  return 0;
}

int At()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<unsigned> mydeque(10); // 10 zero-initialized unsigneds

  // assign some values:
  for (unsigned i = 0; i < mydeque.size(); i++)
    mydeque.at(i) = i;

  std::cout << "mydeque contains:";
  for (unsigned i = 0; i < mydeque.size(); i++)
    std::cout << ' ' << mydeque.at(i);

  std::cout << '\n';

  return 0;
}

int Front()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;

  mydeque.push_front(77);
  std::cout << "pushed f" << std::endl;
  mydeque.push_back(20);
 std::cout << "pushed b" << std::endl;
  mydeque.front() -= mydeque.back();

  std::cout << "mydeque.front() is now " << mydeque.front() << '\n';

  return 0;
}
int Back()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;

  mydeque.push_back(10);

  while (mydeque.back() != 0)
    mydeque.push_back(mydeque.back() - 1);

  std::cout << "mydeque contains:";

  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
}
int Assign()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> first;
  LIBRARY::deque<int> second;
  LIBRARY::deque<int> third;

  first.assign(7, 100); // 7 ints with a value of 100

  LIBRARY::deque<int>::iterator it = first.begin() + 1;

  second.assign(it, first.end() - 1); // the 5 central values of first

  int myints[] = {1776, 7, 4};
  third.assign(myints, myints + 3); // assigning from array.

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
  std::cout << "Size of third: " << int(third.size()) << '\n';
  return 0;
}
int PushBack()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do
  {
    std::cin >> myint;
    mydeque.push_back(myint);
  } while (myint);

  std::cout << "mydeque stores " << (int)mydeque.size() << " numbers.\n";

  return 0;
}
int PushFront()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque(2, 100); // two ints with a value of 100
  mydeque.push_front(200);
  mydeque.push_front(300);

  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
int PopBack()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;
  int sum(0);
  mydeque.push_back(10);
  mydeque.push_back(20);
  mydeque.push_back(30);

  while (!mydeque.empty())
  {
    sum += mydeque.back();
    mydeque.pop_back();
  }

  std::cout << "The elements of mydeque add up to " << sum << '\n';

  return 0;
}
int PopFront()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;

  mydeque.push_back(100);
  mydeque.push_back(200);
  mydeque.push_back(300);

  std::cout << "Popping out the elements in mydeque:";
  while (!mydeque.empty())
  {
    std::cout << ' ' << mydeque.front();
    mydeque.pop_front();
  }

  std::cout << "\nThe final size of mydeque is " << int(mydeque.size()) << '\n';

  return 0;
}
int Insert()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;

  // set some initial values:
  for (int i = 1; i < 6; i++)
    mydeque.push_back(i); // 1 2 3 4 5

  LIBRARY::deque<int>::iterator it;
  it = mydeque.begin();
  ++it;

  it = mydeque.insert(it, 10); // 1 10 2 3 4 5
  // "it" now points to the newly inserted 10

  mydeque.insert(it, 2, 20); // 1 20 20 10 2 3 4 5
  // "it" no longer valid!

  it = mydeque.begin() + 2;

  std::vector<int> myvector(2, 30);
  mydeque.insert(it, myvector.begin(), myvector.end());
  // 1 20 30 30 20 10 2 3 4 5

  std::cout << "mydeque contains:";
  for (it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
int Erase()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;

  // set some values (from 1 to 10)
  for (int i = 1; i <= 10; i++)
    mydeque.push_back(i);

  // erase the 6th element
  mydeque.erase(mydeque.begin() + 5);

  // erase the first 3 elements:
  mydeque.erase(mydeque.begin(), mydeque.begin() + 3);

  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
int Swap()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> foo(3, 100); // three ints with a value of 100
  LIBRARY::deque<int> bar(5, 200); // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (LIBRARY::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (LIBRARY::deque<int>::iterator it = bar.begin(); it != bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int Clear()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> mydeque;
  mydeque.push_back(100);
  mydeque.push_back(200);
  mydeque.push_back(300);

  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  mydeque.clear();
  mydeque.push_back(1101);
  mydeque.push_back(2202);

  std::cout << "mydeque contains:";
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int RelOps()
{
  std::cout << '\n'
            << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::deque<int> foo(3, 100); // three ints with a value of 100
  LIBRARY::deque<int> bar(2, 200); // two ints with a value of 200

  if (foo == bar)
    std::cout << "foo and bar are equal\n";
  if (foo != bar)
    std::cout << "foo and bar are not equal\n";
  if (foo < bar)
    std::cout << "foo is less than bar\n";
  if (foo > bar)
    std::cout << "foo is greater than bar\n";
  if (foo <= bar)
    std::cout << "foo is less than or equal to bar\n";
  if (foo >= bar)
    std::cout << "foo is greater than or equal to bar\n";

  return 0;
}

int main()
{
  Constructors();
  Assignment();
  Begin();
  RBegin();
  Empty();
  Size();
  MaxSize();
  Resize();
  Bracket();
  At();
  Front();
  Back();
  Assign();
  PushBack();
  PushFront();
  PopBack();
  PopFront();
  Insert();
  Erase();
  Swap();
  Clear();
  RelOps ();
}
