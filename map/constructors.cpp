#include "ft.h"
#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  std::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  std::map<char,int> second (first.begin(),first.end());

  std::map<char,int> third (second);

  std::map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

 first.clear();
 second.clear();

 first['x']=8;
 first['y']=16;
 first['z']=32;

 second=first;                // second now contains 3 ints
 first=std::map<char,int>();  // and first is now empty

 std::cout << "Size of first: " << first.size() << '\n';
 std::cout << "Size of second: " << second.size() << '\n';
 return 0;
}