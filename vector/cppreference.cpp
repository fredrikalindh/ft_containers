#include "../ft.hpp"
#include <iostream>
#include <vector>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int NonMemberSwap()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  // unsigned int i;
  LIBRARY::vector<int> foo (3,100);   // three ints with a value of 100
  LIBRARY::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (LIBRARY::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (LIBRARY::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int RelationalOperators()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> foo (3,100);   // three ints with a value of 100
  LIBRARY::vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

  return 0;
}

int Clear()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

int Swap()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> foo (3,100);   // three ints with a value of 100
  LIBRARY::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo.size(); i++)
    std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar.size(); i++)
    std::cout << ' ' << bar[i];
  std::cout << '\n';

  return 0;
}

int Erase()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase (myvector.begin()+5);
  // erase the first 3 elements:
  myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

int Insert()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector (3,100);
  LIBRARY::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  LIBRARY::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int PopBack()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  return 0;
}

int PushBack()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    myvector.push_back (myint);
  } while (myint);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  return 0;
}

int Assign()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> first;
  LIBRARY::vector<int> second;
  LIBRARY::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  LIBRARY::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
  return 0;
}

int Back()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

int Front()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';

  return 0;
}

int At()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  return 0;
}

int BracketOperator()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector (10);   // 10 zero-initialized elements

  LIBRARY::vector<int>::size_type sz = myvector.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) myvector[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = myvector[sz-1-i];
    myvector[sz-1-i]=myvector[i];
    myvector[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

int Reserve()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int>::size_type sz;

  LIBRARY::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  LIBRARY::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  return 0;
}

int Empty()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}

int Capacity()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << (int) myvector.size() << '\n';
  std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  std::cout << "max_size: " << (int) myvector.max_size() << '\n';
  return 0;
}

int Resize()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (LIBRARY::vector<int>::size_type i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

int MaxSize()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";
  return 0;
}

int Size()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.end(),10,100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';

  return 0;
}

int ReverseEnd()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector (5);  // 5 default-constructed ints

  LIBRARY::vector<int>::reverse_iterator rit = myvector.rbegin();

  int i=0;
  for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (LIBRARY::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int ReverseBegin()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  LIBRARY::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (LIBRARY::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int End()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (LIBRARY::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int Begin()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (LIBRARY::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int AssignOperator()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> foo (3,0);
  LIBRARY::vector<int> bar (5,0);

  bar = foo;
  foo = LIBRARY::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}

int Constructor()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	// constructors used in the same order as described above:
	LIBRARY::vector<int> first;                                // empty vector of ints
	LIBRARY::vector<int> second (4,100);                       // four ints with value 100
	LIBRARY::vector<int> third (second.begin(),second.end());  // iterating through second
	LIBRARY::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	LIBRARY::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (LIBRARY::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}

int main ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	Constructor();
	AssignOperator();
	Begin();
	End();
	ReverseBegin();
	ReverseEnd();
	Size();
	MaxSize();
	Resize();
	Capacity();
	Empty();
	Reserve();
	BracketOperator();
	At();
	Front();
	Back();
	Assign();
	PushBack();
	PopBack();
	Insert();
	Erase();
	Swap();
	Clear();
	RelationalOperators();
	NonMemberSwap();
}
