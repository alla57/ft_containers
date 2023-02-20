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
	ft::vector<int> v;
	v.assign(0, 3);
	// std::cout << *v.begin() << std::endl;
	std::cout << v.capacity() << std::endl;
	std::cout << v.size() << std::endl;
	return (0);
}