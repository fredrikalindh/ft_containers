#include "../ft.hpp"
#include <iostream>
#include <vector>

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
  LIBRARY::vector<int>::size_type sz;

  LIBRARY::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
	foo.push_back(i);
	if (sz!=foo.capacity()) {
	  sz = foo.capacity();
	  std::cout << "capacity changed: " << sz << '\n';
	}
  }

  LIBRARY::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "sz == " << sz << " bar.capacity == " << bar.capacity() << '\n';
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
	bar.push_back(i);
	if (sz!=bar.capacity()) {
	  sz = bar.capacity();
	  std::cout << "capacity changed: " << sz << '\n';
	}
  }
  return 0;
}
