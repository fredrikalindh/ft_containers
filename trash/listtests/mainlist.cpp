#include "../ft.hpp"
#include <iostream>
#ifndef LIBRARY
# define LIBRARY ft
#endif
int main()
{
	LIBRARY::list<int> my;

	for (int i = 0; i < 3; i++)
	 my.push_back(i);
	for (int i = 30; i > 27; i--)
	 my.push_front(i);

	std::cout << "SIZE = " << my.size() << std::endl;

	LIBRARY::list<int>::iterator start = my.begin();
	LIBRARY::list<int>::iterator end = my.end();
	while (start != end)
		std::cout << *start++ << ' ';
	my.reverse();
	std::cout << "\nAFTER REVERSE:" << '\n';
	start = my.begin();
	while (start != end)
		std::cout << *start++ << ' ';
	my.sort();
	std::cout << "\nAFTER SORT:" << '\n';
	start = my.begin();
	while (start != end)
		std::cout << *start++ << ' ';
	my.clear();
	std::cout << "\nIs empty = " << my.empty() << " SIZE = "<< my.size() << std::endl;
	my.push_back(2);
	std::cout << "back = " << my.back() << " front = " << my.front() << " size = " << my.size() << "\n\n";

	LIBRARY::list<std::string> strmy;
	strmy.push_front("hej ");
	strmy.push_back("jag ");
	strmy.push_back("heter ");
	strmy.push_back("fredrika ");
	LIBRARY::list<std::string>::iterator b = strmy.begin();
	LIBRARY::list<std::string>::iterator e = strmy.end();
	while (b != e)
		std::cout << *b++;
	strmy.sort();
	std::cout << "\nAFTER SORT:" << '\n';
	b = strmy.begin();
	while (b != e)
		std::cout << *b++ << ' ';
	strmy.reverse();
	std::cout << "\nAFTER REVERSE:" << '\n';
	b = strmy.begin();
	while (b != e)
		std::cout << *b++;
	return 0;
}
