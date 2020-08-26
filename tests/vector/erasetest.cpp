#include "../ft.hpp"
#include <iostream>
#include <vector>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
	std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
  LIBRARY::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
 std::cout << "after: " << *(myvector.erase (myvector.begin()+5)) << '\n';

  // erase the first 3 elements:
  std::cout << "after: " << *(myvector.erase (myvector.begin(),myvector.begin()+3)) << '\n';

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}
