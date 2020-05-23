#include <iostream>
#include <map>
#include <iomanip>
#include "../ft.hpp"

#ifndef LIBRARY
# define LIBRARY ft
#endif
 int main()
 {
	 LIBRARY::pair<string, int>
		 pa[] =
		 {
			 LIBRARY::pair<string,int>("one", 10),
			 LIBRARY::pair<string,int>("two", 20),
			 LIBRARY::pair<string,int>("three", 30),
		 };
	LIBRARY::map<string, int>
		 object(&pa[0], &pa[3]);

	 for
	 (
		 map<string, int>::iterator it = object.begin();
			 it != object.end();
				 ++it
	 )
		 std::cout << setw(5) << it->first.c_str() <<
				 setw(5) << it->second << '\n';
 }
 /*
	 Generated output:
   one   10
 three   30
   two   20
 */
