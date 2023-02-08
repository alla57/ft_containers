#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

#include "Vector.hpp"

int main()
{
	std::vector<int> v(10, 8);
	ft::vector<int> u(10, 8);
	if (*v.begin() == *u.begin())
		std::cout << "hello" << std::endl;
	return (0);
}