#include "ft.hpp"
#include <map>

int main ()
{
  std::map<char,int> mymap;

  std::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap.rbegin()->first;     // key value of last element

  std::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';

	std::cout << "mymap contains:\n";

	std::pair<char,int> high = *mymap.rbegin();          // last element

	std::map<char,int>::iterator it2 = mymap.begin();
	do {
	  std::cout << it2->first << " => " << it2->second << '\n';
  	} while ( mymap.value_comp()(*it2++, high) );

  return 0;
}
