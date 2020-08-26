#include <iostream>
#include <vector>
#include "../vector.hpp"

int main(){
	ft::vector<int> test;

	for (int i = 100; i < 203; i++)
		test.push_back(i);
	test.pop_back();
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	std::cout << test.front() << '\n';
	std::cout << test.back() << '\n';
	test.pop_back();
	for (ft::vector<int>::iterator it = test.begin(); it != test.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
	for (ft::vector<int>::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}
