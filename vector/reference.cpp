#include <iostream>
#include <vector>
#include "../vector.hpp"

int main(){
	ft::vector<int> test;

	for (int i = 0; i < 102; i++)
		test.push_back(i);
	test.pop_back();
	std::cout << test.front() << '\n';
	std::cout << test.back() << '\n';
	std::cout << test.at(50) << '\n';
	test.at(50) = 500;
	std::cout << test[50] << '\n';
}
