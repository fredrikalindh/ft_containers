#include <iostream>
#include <map>
#include "../ft.hpp"

#ifndef LIBRARY
# define LIBRARY ft
#endif

int main()
{
	LIBRARY::pair<string, int> pa[] =
	{
		LIBRARY::pair<string,int>("alpha", 1),
		LIBRARY::pair<string,int>("bravo", 2),
		LIBRARY::pair<string,int>("charlie", 3),
		LIBRARY::pair<string,int>("bravo", 6),   // unordered `bravo' values
		LIBRARY::pair<string,int>("delta", 5),
		LIBRARY::pair<string,int>("bravo", 4),
	};
	LIBRARY::multimap<string, int> object(&pa[0], &pa[6]);

	typedef LIBRARY::multimap<string, int>::iterator msiIterator;

	msiIterator it = object.lower_bound("brava");

	std::cout << "Lower bound for `brava': " <<
			it->first << ", " << it->second << '\n';

	it = object.upper_bound("bravu");

	std::cout << "Upper bound for `bravu': " <<
			it->first << ", " << it->second << '\n';

	LIBRARY::pair<msiIterator, msiIterator>
		itPair = object.equal_range("bravo");

	std::cout << "Equal range for `bravo':\n";
	for (it = itPair.first; it != itPair.second; ++it)
		std::cout << it->first << ", " << it->second << '\n';
	std::cout << "Upper bound: " << it->first << ", " << it->second << '\n';

	std::cout << "Equal range for `brav':\n";
	itPair = object.equal_range("brav");
	for (it = itPair.first; it != itPair.second; ++it)
		std::cout << it->first << ", " << it->second << '\n';
	std::cout << "Upper bound: " << it->first << ", " << it->second << '\n';
}
/*
	Generated output:

	Lower bound for `brava': bravo, 2
	Upper bound for `bravu': charlie, 3
	Equal range for `bravo':
	bravo, 2
	bravo, 6
	bravo, 4
	Upper bound: charlie, 3
	Equal range for `brav':
	Upper bound: bravo, 2
*/
