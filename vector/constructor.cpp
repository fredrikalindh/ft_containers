#include <iostream>
#include <vector>

int main(){
	std::vector<int> test(1);

	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.resize(100, 3);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.capacity() << '\n';
	test.insert( test.end(), 100000000, 0);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
	test.push_back(2);
	std::cout << test.size() << '\n';
	std::cout << test.capacity() << '\n';
}
