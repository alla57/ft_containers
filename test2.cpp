#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>
// #include <type_traits>

#include "type_traits.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "vector.hpp"

int main()
{
	ft::vector<int> v(3, 24);
	ft::vector<int> v2(v);
	// std::cout << *v.begin() << std::endl;
	// std::cout << *(v.begin() + 1) << std::endl;
	// std::cout << *(v.begin() + 2) << std::endl;
	std::cout << "size = " << v2.size() << std::endl;
	// std::vector<int> v;
	// v.push_back(22);
	// bool b = v.begin() == v.end();
	// std::cout << b << std::endl;
	return (0);
}