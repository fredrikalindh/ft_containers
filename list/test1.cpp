#include "../ft.hpp"
#include <iostream>
#include <list>

int main ()
{
	  // constructors used in the same order as described above:
	  ft::list<int> first;                                // empty list of ints
	  ft::list<int> second (size_t(4),100);
	// the iterator constructor can be used to construct from arrays:
	  int myints[] = {16,2,77,29,141,-24};
	  ft::list<int> third (myints, myints + sizeof(myints) / sizeof(int) );
	  ft::list<int> fourth (second);                       // a copy of second
	  ft::list<int> fifth (++third.begin(),third.end());  // iterating through third

	std::cout << "The contents of 1st are: (empty)";
  	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++)
    std::cout << *it << ' ';
	std::cout << "\nThe contents of 2nd are: (4 elem of 100) = ";
  	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++)
    std::cout << *it << ' ';
	std::cout << "\nThe contents of 3rd are: (from array) = ";
  	for (ft::list<int>::iterator it = third.begin(); it != third.end(); it++)
    std::cout << *it << ' ';
	std::cout << "\nThe contents of 4th are: (a copy of second) = ";
  	for (ft::list<int>::iterator it = fourth.begin(); it != fourth.end(); it++)
    std::cout << *it << ' ';
	std::cout << "\nThe contents of fifth are: (from thirds 2nd element) = ";
	for (ft::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
	  std::cout << *it << ' ';

  std::cout << '\n';

  return 0;
}
