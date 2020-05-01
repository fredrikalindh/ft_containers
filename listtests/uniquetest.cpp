#include "../ft.hpp"
#include <iostream>
#include <cmath>
#include <list>
#ifndef LIBRARY
# define LIBRARY ft
#endif
// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

int main ()
{
  double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                       12.77, 73.35, 72.25, 15.3,  72.25 };
  LIBRARY::list<double> mylist (mydoubles,mydoubles+10);

  std::cout << "mylist contains:";
  for (LIBRARY::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
  mylist.reverse();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                             // 15.3,  72.25, 72.25, 73.0,  73.35
 std::cout << "mylist contains:" ;
 for (LIBRARY::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
   std::cout << ' ' << *it;
 std::cout << '\n';
  mylist.unique();           //  2.72,  3.14, 12.15, 12.77
                             // 15.3,  72.25, 73.0,  73.35

  mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                       // 15.3,  72.25, 73.0

  mylist.unique (is_near());           //  2.72, 12.15, 72.25

  std::cout << "mylist contains:";
  for (LIBRARY::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
