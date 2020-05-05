#include "../ft.hpp"
#include <iostream>
#include <cmath>
#include <list>
#ifndef LIBRARY
# define LIBRARY ft
#endif
// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

// int main ()
// {
//   LIBRARY::list<double> first, second;
//
//   first.push_back (3.1);
//   first.push_back (3.1);
//   first.push_back (2.2);
//   first.push_back (2.9);
//
//   second.push_back (3.7);
//   second.push_back (15.1);
//   second.push_back (1.4);
//   second.push_back (3.8);
//   second.push_back (7.8);
//   second.push_back (1.8);
//   second.push_back (3.2);
//   second.push_back (7.2);
//   second.push_back (1.3);
//   second.push_back (1.3);
//   second.push_back (23.0);
//   second.push_back (7.8);
//   second.push_back (1.8);
//   second.push_back (3.2);
//   second.push_back (7.2);
//   second.push_back (1.3);
//   second.push_back (1.3);
//   second.push_back (23.0);
//
//   first.sort();
//   second.sort();
//   std::cout << "first contains:";
//   for (LIBRARY::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
//   std::cout << "second contains:";
//   for (LIBRARY::list<double>::iterator it=second.begin(); it!=second.end(); ++it)
// 	std::cout << ' ' << *it;
//   std::cout << '\n';
//   std::cout << "first last " << first.back() << " second last " << second.back() << '\n';
//   first.merge(second);
//
// 	// std::cout << second.empty() << '\n';
//   // (second is now empty)
//
//   second.push_back (2.1);
//
//   first.merge(second);
//   first.merge(second,mycomparison);
//
//   std::cout << "first contains:";
//   for (LIBRARY::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
//
//   return 0;
// }

int main() {
	LIBRARY::list<int> first, second;

	first.push_back (4);
     first.push_back (5);
     first.push_back (6);
	first.push_back (8);
     first.push_back (12);
     first.push_back (0);
     first.push_back (2);
     first.push_back (2);
     first.push_back (4);
	 std::cout << "first contains:";
	 for (LIBRARY::list<int>::iterator it=first.begin(); it!=first.end(); ++it)
	     std::cout << ' ' << *it;
	   std::cout << '\n';
     // second.push_back (0);
     // second.push_back (2);
     // second.push_back (6);
	 first.sort();
	 std::cout << "first contains:";
	 for (LIBRARY::list<int>::iterator it=first.begin(); it!=first.end(); ++it)
		 std::cout << ' ' << *it;
	   std::cout << '\n';
	   std::cout << "last: " << first.back() << '\n';
	 //   std::cout << "second contains:";
	 //   for (LIBRARY::list<int>::iterator it=second.begin(); it!=second.end(); ++it)
		//    std::cout << ' ' << *it;
		//  std::cout << '\n';
	 //   second.sort();
	 // first.merge(second);
	 // std::cout << "first contains:";
	 // for (LIBRARY::list<int>::iterator it=first.begin(); it!=first.end(); ++it)
	 //     std::cout << ' ' << *it;
	 //   std::cout << '\n';
	return 0;
}
