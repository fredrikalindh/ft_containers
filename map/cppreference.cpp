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
  LIBRARY::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  LIBRARY::map<char,int> second (first.begin(),first.end());

  LIBRARY::map<char,int> third (second);

  LIBRARY::map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  LIBRARY::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

  return 0;
}

int Assignment ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> first;
  LIBRARY::map<char,int> second;

  first['x']=8;
  first['y']=16;
  first['z']=32;

  second=first;                // second now contains 3 ints
  first=LIBRARY::map<char,int>();  // and first is now empty

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
  return 0;
}

int Begin ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (LIBRARY::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int RBegin ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  LIBRARY::map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

  return 0;
}

int Empty ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }
	std::cout << "SIZE: " << mymap.size() << '\n';
  return 0;
}
int Size ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;
  mymap['a']=101;
  mymap['b']=202;
  mymap['c']=302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';

  return 0;
}

int MaxSize ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  int i;
  LIBRARY::map<int,int> mymap;

	std::cout << "max: " << mymap.max_size() << '\n';
  if (mymap.max_size()>1000)
  {
    for (i=0; i<1000; i++) mymap[i]=0;
    std::cout << "The map contains 1000 elements.\n";
  }
  else std::cout << "The map could not hold 1000 elements.\n";

  return 0;
}

int Brackets ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,std::string> mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

	// for (ft::map<char, std::string>::iterator it = mymap.begin(); it != mymap.end(); it++)
	// 	std::cout << it->first << " => " << it->second << '\n';

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";

  return 0;
}
int Insert ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( LIBRARY::pair<char,int>('a',100) );
  mymap.insert ( LIBRARY::pair<char,int>('z',200) );

  LIBRARY::pair<LIBRARY::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( LIBRARY::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  LIBRARY::map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, LIBRARY::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, LIBRARY::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  LIBRARY::map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
int Erase ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;
  LIBRARY::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  mymap.erase (it);                   // erasing by iterator

  mymap.erase ('c');                  // erasing by key

  it=mymap.find ('e');
  mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}
int Swap ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (LIBRARY::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (LIBRARY::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  swap(bar, foo);

  std::cout << "foo contains:\n";
  for (LIBRARY::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (LIBRARY::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int Clear ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['x']=100;
  mymap['y']=200;
  mymap['z']=300;

  std::cout << "mymap contains:\n";
  for (LIBRARY::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a']=1101;
  mymap['b']=2202;

  std::cout << "mymap contains:\n";
  for (LIBRARY::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int KeyComp ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  LIBRARY::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap.rbegin()->first;     // key value of last element

  LIBRARY::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';

  return 0;
}

int ValComp ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  LIBRARY::pair<char,int> highest = *mymap.rbegin();          // last element

  LIBRARY::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  return 0;
}
int Find ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;
  LIBRARY::map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  return 0;
}
int Count ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;
  char c;

  mymap ['a']=101;
  mymap ['c']=202;
  mymap ['f']=303;

  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else
      std::cout << " is not an element of mymap.\n";
  }

  return 0;
}

int Bound ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;
  LIBRARY::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	std::cout << "lower = " << itlow->first << '\n';
	std::cout << "upper = " << itup->first << '\n';

  // mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (LIBRARY::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int EqualRange ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  LIBRARY::pair<LIBRARY::map<char,int>::iterator,LIBRARY::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

  return 0;
}

// int RelOps ()
// {
// 	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
//   LIBRARY::map<char,int> foo,bar;
//   foo['a']=100;
//   foo['b']=200;
//   bar['a']=10;
//   bar['z']=1000;
//
//   // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
//   if (foo==bar) std::cout << "foo and bar are equal\n";
//   if (foo!=bar) std::cout << "foo and bar are not equal\n";
//   if (foo< bar) std::cout << "foo is less than bar\n";
//   if (foo> bar) std::cout << "foo is greater than bar\n";
//   if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
//   if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
//
//   return 0;
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
	Brackets ();
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
