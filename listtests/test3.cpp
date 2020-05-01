#include "../ft.hpp"
#include <iostream>
#include <list>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main ()
{
	LIBRARY::list<int> mylist (size_t(2),100);         // two ints with a value of 100
	mylist.push_front (200);
	mylist.push_front (300);
	mylist.push_back (100);
	mylist.push_back (200);
	mylist.push_back (300);


	std::cout << "mylist contains:";
	for (LIBRARY::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << "\nPopping out the elements in mylist of size " << mylist.size() << ": ";
	while (!mylist.empty())
	{
		if (mylist.size() % 2)
	  	{
			std::cout << "\nfrom front: " << mylist.front();
	  		mylist.pop_front();
		}else {
	  		std::cout << "\nfrom back:  " << mylist.back();
	  		mylist.pop_back();
		}
	}
  	std::cout << '\n';
  return 0;
}
