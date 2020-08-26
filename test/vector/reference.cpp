#include <iostream>
#include <vector>
#include "../vector.hpp"

int main(){
	ft::vector<int> test;
	ft::vector<int> test2(size_t(10),10);

	for (int i = 0; i < 102; i++)
		test.push_back(i);
	test.pop_back();
	std::cout << test.front() << '\n';
	std::cout << test.back() << '\n';
	std::cout << test.at(50) << '\n';
	test.at(50) = 500;
	std::cout << test[50] << '\n';
	test2.assign(&test[40], &test[50]);
	for (ft::vector<int>::reverse_iterator it = test2.rbegin(); it != test2.rend(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
	test2.assign(size_t(30), 0);
	for (ft::vector<int>::reverse_iterator it = test2.rbegin(); it != test2.rend(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
	for (ft::vector<int>::iterator it = test2.begin(); it != test2.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}
