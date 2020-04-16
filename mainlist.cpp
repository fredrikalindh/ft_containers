#include "ft.hpp"
#include <iostream>

int main()
{
	ft::list<int> my;

	for (int i = 0; i < 10; i++)
	 my.push_back(i);
	for (int i = 30; i > 20; i--)
	 my.push_front(i);

	std::cout << "SIZE = " << my.size() << std::endl;

	ft::list<int>::iterator start = my.begin();
	ft::list<int>::iterator end = my.end();
	while (start != end)
		std::cout << *start++ << ' ';
	my.clear();
	std::cout << "\nIs empty = " << my.empty() << " SIZE = "<< my.size() << std::endl;
	my.push_back(2);
	std::cout << "back = " << my.back() << " front = " << my.front() << " size = " << my.size() << "\n\n";

	ft::list<std::string> strmy;
	strmy.push_front("hej ");
	strmy.push_back("jag ");
	strmy.push_back("heter ");
	strmy.push_back("fredrika\n");
	ft::list<std::string>::iterator b = strmy.begin();
	ft::list<std::string>::iterator e = strmy.end();
	while (b != e)
		std::cout << *b++;
	return 0;
}
