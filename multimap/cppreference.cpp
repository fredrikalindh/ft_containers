#include <map>
#include <iostream>
#include "../ft.hpp"

#ifndef LIBRARY
# define LIBRARY ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int Constructors ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> first;

   first.insert(LIBRARY::pair<char,int>('a',10));
   first.insert(LIBRARY::pair<char,int>('b',15));
   first.insert(LIBRARY::pair<char,int>('b',35));
   first.insert(LIBRARY::pair<char,int>('b',20));
   first.insert(LIBRARY::pair<char,int>('c',25));
   for (LIBRARY::multimap<char,int>::iterator it=first.begin(); it!=first.end(); ++it)
	 std::cout << (*it).first << " => " << (*it).second << '\n';

   LIBRARY::multimap<char,int> second (first.begin(),first.end());
   for (LIBRARY::multimap<char,int>::iterator it=first.begin(); it!=first.end(); ++it)
	 std::cout << (*it).first << " => " << (*it).second << '\n';

   LIBRARY::multimap<char,int> third (second);

   LIBRARY::multimap<char,int,classcomp> fourth;                 // class as Compare

   bool(*fn_pt)(char,char) = fncomp;
   LIBRARY::multimap<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as comp

   return 0;
}

int Assignment ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> foo,bar;

	  foo.insert(LIBRARY::make_pair('x',32));
	  foo.insert(LIBRARY::make_pair('y',64));
	  foo.insert(LIBRARY::make_pair('y',96));
	  foo.insert(LIBRARY::make_pair('z',128));

	  bar = foo;                  // bar now contains 4 ints
	  foo.clear();                // and first is now empty

	  for (LIBRARY::multimap<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
	  std::cout << (*it).first << " => " << (*it).second << '\n';

	  std::cout << "Size of foo: " << foo.size() << '\n';
	  std::cout << "Size of bar: " << bar.size() << '\n';
	  return 0;
}

int Begin ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

   mymultimap.insert (LIBRARY::pair<char,int>('a',10));
   mymultimap.insert (LIBRARY::pair<char,int>('b',20));
   mymultimap.insert (LIBRARY::pair<char,int>('b',150));

   // show content:
   for (LIBRARY::multimap<char,int>::iterator it=mymultimap.begin(); it!=mymultimap.end(); ++it)
     std::cout << (*it).first << " => " << (*it).second << '\n';

   return 0;
}

int RBegin ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

  mymultimap.insert (LIBRARY::make_pair('x',10));
  mymultimap.insert (LIBRARY::make_pair('y',20));
  mymultimap.insert (LIBRARY::make_pair('y',150));
  mymultimap.insert (LIBRARY::make_pair('z',9));

  // show content:
  LIBRARY::multimap<char,int>::reverse_iterator rit;
  for (rit=mymultimap.rbegin(); rit!=mymultimap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

  return 0;
}

int Empty ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

  mymultimap.insert (LIBRARY::pair<char,int>('b',101));
  mymultimap.insert (LIBRARY::pair<char,int>('b',202));
  // mymultimap.insert (LIBRARY::pair<char,int>('q',505));
  // mymultimap.insert (LIBRARY::pair<char,int>('q',405));

  while (!mymultimap.empty())
  {
     std::cout << mymultimap.begin()->first << " => ";
     std::cout << mymultimap.begin()->second << '\n';
     mymultimap.erase(mymultimap.begin());
  }

  return 0;
}
int Size ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

     mymultimap.insert(LIBRARY::make_pair('x',100));
     mymultimap.insert(LIBRARY::make_pair('y',200));
     mymultimap.insert(LIBRARY::make_pair('y',350));
     mymultimap.insert(LIBRARY::make_pair('z',500));

     std::cout << "mymultimap.size() is " << mymultimap.size() << '\n';

     return 0;
}

int MaxSize ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<int,int> mymultimap;

    if (mymultimap.max_size() >= 1000u)
    {
      for (int i=0; i<1000; i++)
        mymultimap.insert(LIBRARY::make_pair(i,0));
      std::cout << "The multimap contains 1000 elements.\n";
    }
    else std::cout << "The multimap could not hold 1000 elements.\n";

    return 0;
}

int Insert ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;
  LIBRARY::multimap<char,int>::iterator it;

  // first insert function version (single parameter):
  mymultimap.insert ( LIBRARY::pair<char,int>('a',100) );
  mymultimap.insert ( LIBRARY::pair<char,int>('z',150) );
  it=mymultimap.insert ( LIBRARY::pair<char,int>('b',75) );

  // second insert function version (with hint position):
  mymultimap.insert (it, LIBRARY::pair<char,int>('c',300));  // max efficiency inserting
  mymultimap.insert (it, LIBRARY::pair<char,int>('z',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  LIBRARY::multimap<char,int> anothermultimap;
  anothermultimap.insert(mymultimap.begin(),mymultimap.find('c'));

  // showing contents:
  std::cout << "mymultimap contains:\n";
  for (it=mymultimap.begin(); it!=mymultimap.end(); ++it)
    std::cout << (*it).first << " => " << (*it).second << '\n';

  std::cout << "anothermultimap contains:\n";
  for (it=anothermultimap.begin(); it!=anothermultimap.end(); ++it)
    std::cout << (*it).first << " => " << (*it).second << '\n';

  return 0;
}
int Erase ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

    // insert some values:
    mymultimap.insert(LIBRARY::pair<char,int>('a',10));
    mymultimap.insert(LIBRARY::pair<char,int>('b',20));
    mymultimap.insert(LIBRARY::pair<char,int>('b',30));
    mymultimap.insert(LIBRARY::pair<char,int>('c',40));
    mymultimap.insert(LIBRARY::pair<char,int>('d',50));
    mymultimap.insert(LIBRARY::pair<char,int>('d',60));
    mymultimap.insert(LIBRARY::pair<char,int>('e',70));
    mymultimap.insert(LIBRARY::pair<char,int>('f',80));

    LIBRARY::multimap<char,int>::iterator it = mymultimap.find('b');

    mymultimap.erase (it);                     // erasing by iterator (1 element)

    mymultimap.erase ('d');                    // erasing by key (2 elements)

    it=mymultimap.find ('e');
    mymultimap.erase ( it, mymultimap.end() ); // erasing by range

    // show content:
    for (it=mymultimap.begin(); it!=mymultimap.end(); ++it)
      std::cout << (*it).first << " => " << (*it).second << '\n';

    return 0;
}
int Swap ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> foo,bar;

    foo.insert(LIBRARY::make_pair('x',100));
    foo.insert(LIBRARY::make_pair('y',200));

    bar.insert(LIBRARY::make_pair('a',11));
    bar.insert(LIBRARY::make_pair('b',22));
    bar.insert(LIBRARY::make_pair('a',55));

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (LIBRARY::multimap<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (LIBRARY::multimap<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  swap(bar, foo);

  std::cout << "foo contains:\n";
  for (LIBRARY::multimap<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (LIBRARY::multimap<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int Clear ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;
    LIBRARY::multimap<char,int>::iterator it;

    mymultimap.insert(LIBRARY::pair<char,int>('b',80));
    mymultimap.insert(LIBRARY::pair<char,int>('b',120));
    mymultimap.insert(LIBRARY::pair<char,int>('q',360));

    std::cout << "mymultimap contains:\n";
    for (it=mymultimap.begin(); it!=mymultimap.end(); ++it)
      std::cout << (*it).first << " => " << (*it).second << '\n';

    mymultimap.clear();

    mymultimap.insert(LIBRARY::pair<char,int>('a',11));
    mymultimap.insert(LIBRARY::pair<char,int>('x',22));

    std::cout << "mymultimap contains:\n";
    for (it=mymultimap.begin(); it != mymultimap.end(); ++it)
      std::cout << (*it).first << " => " << (*it).second << '\n';

    return 0;
}

int KeyComp ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

    LIBRARY::multimap<char,int>::key_compare mycomp = mymultimap.key_comp();

    mymultimap.insert (LIBRARY::make_pair('a',100));
    mymultimap.insert (LIBRARY::make_pair('b',200));
    mymultimap.insert (LIBRARY::make_pair('b',211));
    mymultimap.insert (LIBRARY::make_pair('c',300));
    // mymultimap.insert (LIBRARY::make_pair('a',100));
    // mymultimap.insert (LIBRARY::make_pair('b',200));
    // mymultimap.insert (LIBRARY::make_pair('b',211));
    // mymultimap.insert (LIBRARY::make_pair('c',300));

    std::cout << "mymultimap contains:\n";

    char highest = mymultimap.rbegin()->first;     // key value of last element

    LIBRARY::multimap<char,int>::iterator it = mymultimap.begin();
    do {
      std::cout << (*it).first << " => " << (*it).second << '\n';
    } while ( mycomp((*it++).first, highest) );

    std::cout << '\n';

    return 0;
}

int ValComp ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;

    mymultimap.insert(LIBRARY::make_pair('x',101));
    mymultimap.insert(LIBRARY::make_pair('y',202));
    mymultimap.insert(LIBRARY::make_pair('y',252));
    mymultimap.insert(LIBRARY::make_pair('z',303));

    std::cout << "mymultimap contains:\n";

    LIBRARY::pair<char,int> highest = *mymultimap.rbegin();          // last element

    LIBRARY::multimap<char,int>::iterator it = mymultimap.begin();
    do {
      std::cout << (*it).first << " => " << (*it).second << '\n';
    } while ( mymultimap.value_comp()(*it++, highest) );

    return 0;
}
int Find ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymm;

     mymm.insert (LIBRARY::make_pair('x',10));
     mymm.insert (LIBRARY::make_pair('y',20));
     mymm.insert (LIBRARY::make_pair('z',30));
     mymm.insert (LIBRARY::make_pair('z',40));

     LIBRARY::multimap<char,int>::iterator it = mymm.find('x');
     mymm.erase (it);
     mymm.erase (mymm.find('z'));

     // print content:
     std::cout << "elements in mymm:" << '\n';
     std::cout << "y => " << mymm.find('y')->second << '\n';
     std::cout << "z => " << mymm.find('z')->second << '\n';

     return 0;

  return 0;
}
int Count ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymm;

    mymm.insert(LIBRARY::make_pair('x',50));
    mymm.insert(LIBRARY::make_pair('y',100));
    mymm.insert(LIBRARY::make_pair('y',150));
    mymm.insert(LIBRARY::make_pair('y',200));
    mymm.insert(LIBRARY::make_pair('z',250));
    mymm.insert(LIBRARY::make_pair('z',300));

    for (char c='x'; c<='z'; c++)
    {
      std::cout << "There are " << mymm.count(c) << " elements with key " << c << ":";
      LIBRARY::multimap<char,int>::iterator it;
      for (it=mymm.equal_range(c).first; it!=mymm.equal_range(c).second; ++it)
        std::cout << ' ' << (*it).second;
      std::cout << '\n';
    }

    return 0;
}

int Bound ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymultimap;
    LIBRARY::multimap<char,int>::iterator it,itlow,itup;

    mymultimap.insert(LIBRARY::make_pair('a',10));
    mymultimap.insert(LIBRARY::make_pair('b',121));
    mymultimap.insert(LIBRARY::make_pair('c',1001));
    mymultimap.insert(LIBRARY::make_pair('c',2002));
    mymultimap.insert(LIBRARY::make_pair('d',11011));
    mymultimap.insert(LIBRARY::make_pair('e',44));

    itlow = mymultimap.lower_bound ('b');  // itlow points to b
    itup = mymultimap.upper_bound ('d');   // itup points to e (not d)

    // print range [itlow,itup):
    for (it=itlow; it!=itup; ++it)
      std::cout << (*it).first << " => " << (*it).second << '\n';

    return 0;
}

int EqualRange ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
	LIBRARY::multimap<char,int> mymm;

    mymm.insert(LIBRARY::pair<char,int>('a',10));
    mymm.insert(LIBRARY::pair<char,int>('b',20));
    mymm.insert(LIBRARY::pair<char,int>('b',30));
    mymm.insert(LIBRARY::pair<char,int>('b',40));
    mymm.insert(LIBRARY::pair<char,int>('c',50));
    mymm.insert(LIBRARY::pair<char,int>('c',60));
    mymm.insert(LIBRARY::pair<char,int>('d',60));

    std::cout << "mymm contains:\n";
    for (char ch='a'; ch<='d'; ch++)
    {
      LIBRARY::pair <LIBRARY::multimap<char,int>::iterator, LIBRARY::multimap<char,int>::iterator> ret;
      ret = mymm.equal_range(ch);
      std::cout << ch << " =>";
      for (LIBRARY::multimap<char,int>::iterator it=ret.first; it!=ret.second; ++it)
        std::cout << ' ' << it->second;
      std::cout << '\n';
    }

    return 0;
}

// int RelOps ()
// {
// 	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
// 	LIBRARY::multimap<char,int> foo,bar;
//
//     foo.insert (LIBRARY::make_pair('a',100));
//     foo.insert (LIBRARY::make_pair('z',900));
//     bar.insert (LIBRARY::make_pair('b',250));
//     bar.insert (LIBRARY::make_pair('b',350));
//
//     // foo ({{a,100},{z,900}}) vs bar ({b,250},{b,350}}):
//     if (foo==bar) std::cout << "foo and bar are equal\n";
//     if (foo!=bar) std::cout << "foo and bar are not equal\n";
//     if (foo< bar) std::cout << "foo is less than bar\n";
//     if (foo> bar) std::cout << "foo is greater than bar\n";
//     if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
//     if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
//
//     return 0;
// }

int main()
{
	Constructors();
	Assignment ();
	Begin ();
	RBegin ();
	Empty ();
	Size ();
	MaxSize ();
	Insert ();
	Erase ();
	Swap();
	Clear();
	KeyComp ();
	ValComp ();
	Find ();
	Count ();
	Bound ();
	EqualRange ();
	// RelOps ();
}
