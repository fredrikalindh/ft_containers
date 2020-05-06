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


int main ()
{
  LIBRARY::map<char,int> first;

  first['i']=10;
  first['h']=30;
  first['g']=50;
  first['a']=70;
  // first.printTree();
  first['b']=100;
  first['c']=20;
  first['d']=120;
  first['e']=160;
  first['f']=160;
// std::cout << "\n/* ----------------------------- */" << '\n';
	// first.printTree();

	for (LIBRARY::map<char,int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << it->key << ' ' << it->value << '\n';
  LIBRARY::map<char,int> second (first.begin(),first.end());
  std::cout << "second:" << '\n';
  for (LIBRARY::map<char,int>::iterator it = second.begin(); it != second.end(); it++)
	  std::cout << it->key << ' ' << it->value << '\n';
 //
  LIBRARY::map<char,int> third (second);
  std::cout << "third:" << '\n';
  for (LIBRARY::map<char,int>::iterator it = third.begin(); it != third.end(); it++)
	 std::cout << it->key << ' ' << it->value << '\n';

  LIBRARY::map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  LIBRARY::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

 first.clear();
 second.clear();

 first['x']=8;
 first['y']=16;
 first['z']=32;
 //
 second=first;                // second now contains 3 ints
	std::cout << "----------------------------------------------------" << '\n';
 for (LIBRARY::map<char,int>::iterator it = first.begin(); it != first.end(); it++)
	 std::cout << it->key << ' ' << it->value << '\n';
 first=LIBRARY::map<char,int>();  // and first is now empty

 std::cout << "Size of first: " << first.size() << '\n';
 std::cout << "Size of second: " << second.size() << '\n';
 return 0;
}
