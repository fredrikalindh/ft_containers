#include <iostream>
#include "../vector.hpp"
#include <vector>

int main(){
	ft::vector<int> test1;
	ft::vector<int> test2(size_t(100), 3);
	ft::vector<int> test3(test2.begin(), test2.end());
	ft::vector<int> test4(test3);
	test3.push_back(5);
	ft::vector<int> test5 = test3;
	std::cout << "TEST 1:\n" << test1.size() << '\n';
	std::cout << test1.capacity() << '\n';
	std::cout << "TEST 2:\n" << test2.size() << '\n';
	std::cout << test2.capacity() << '\n';
	std::cout << test2.front() << '\n';
	std::cout << test2.back() << '\n';
	std::cout << "TEST 3:\n" << test3.size() << '\n';
	std::cout << test3.capacity() << '\n';
	std::cout << test3.front() << '\n';
	std::cout << test3.back() << '\n';
	std::cout << "TEST 4:\n"<< test4.size() << '\n';
	std::cout << test4.capacity() << '\n';
	std::cout << test4.front() << '\n';
	std::cout << test4.back() << '\n';
	std::cout << "TEST 5:\n"<< test5.size() << '\n';
	std::cout << test5.capacity() << '\n';
	std::cout << test5.front() << '\n';
	std::cout << test5.back() << '\n';
	try {
		test5.reserve(4611686018427387904);
	}catch(std::exception &e){
		std::cout << e.what() << '\n'; // allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size
	}
	try {
		std::cout << test1.at(500) << '\n'; // terminating with uncaught exception of type std::out_of_range: vector
	}catch(std::exception &e){
		std::cout << e.what() << '\n'; //vector
	}
}
