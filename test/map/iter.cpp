#include <map>
#include <iostream>
#include "../ft.hpp"

#ifndef LIBRARY
# define LIBRARY ft
#endif
// int main ()
// {
//   std::map<char,int> mymap;
//
//   mymap['b'] = 100;
//   mymap['a'] = 200;
//   mymap['c'] = 300;
//
//   // show content:
//   for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';
//
// 	std::map<char,int>::reverse_iterator rit;
//     for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
//        std::cout << rit->first << " => " << rit->second << '\n';
//
//   return 0;
// }

int main ()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::map<char,int> mymap;

  mymap['c'] = 30;
  mymap['b'] = 40;
  mymap['a'] = 50;
  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;
  mymap['f'] = 300;
  mymap['e'] = 300;
  mymap['r'] = 300;
  mymap['k'] = 300;

  // show content:
  for (LIBRARY::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  // LIBRARY::map<char,int>::reverse_iterator rit;
  std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';

	 LIBRARY::map<char,int>::reverse_iterator it = mymap.rbegin();
	 LIBRARY::map<char,int>::reverse_iterator it2 = mymap.rend();

	 // if (it2.base() == mymap.begin())
	 	std::cout << "rend : " << it2.base()->first << '\n';
	 // it2--;
	 for ( ; it != it2; it++)
	 	std::cout << it->first << " => " << it->second << '\n';
	//  it++;
  // std::cout << it->first << " => " << it->second << '\n';
	//  it++;
  // std::cout << it->first << " => " << it->second << '\n';
	//  LIBRARY::map<char,int>::iterator it = mymap.end();
	//  it--;
  // std::cout << it->first << " => " << it->second << '\n';
	//  it--;
  // std::cout << it->first << " => " << it->second << '\n';
	//  it--;
  // std::cout << it->first << " => " << it->second << '\n';


  // for (rit=mymap.rbegin(); rit!=mymap.rend(); rit++)
  //   std::cout << rit->first << " => " << rit->second << '\n';

	// std::cout << rit->first << " => " << rit->second << '\n';

  return 0;
}
